
#include <Eigen/Geometry>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <imgui.h>
#include <implot.h>
#include <implot3d.h>
#include <vector>
#include <algorithm>

#include "math/CoordinateConversion.h"
#include "simulator/Dynamics.h"

#if defined(__APPLE__)
#include <OpenGL/gl3.h>
#else
#include <GL/gl.h>
#endif


int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if defined(__APPLE__)
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(1280, 800, "Icarus", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImPlot3D::CreateContext();
    ImGui::StyleColorsDark();

    if (!ImGui_ImplGlfw_InitForOpenGL(window, true)) {
        std::cerr << "Failed to initialize ImGui GLFW backend\n";
        ImPlot::DestroyContext();
        ImGui::DestroyContext();
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }

#if defined(__APPLE__)
    constexpr const char* glslVersion = "#version 150";
#else
    constexpr const char* glslVersion = "#version 130";
#endif
    if (!ImGui_ImplOpenGL3_Init(glslVersion)) {
        std::cerr << "Failed to initialize ImGui OpenGL backend\n";
        ImGui_ImplGlfw_Shutdown();
        ImPlot::DestroyContext();
        ImGui::DestroyContext();
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }

    double engineThrust = 845.0;
    int numEngines = 9;
    double dryMass = 26200.0;
    double fuelMass = 362600.0;
    double oxidizerMass = 155800.0;
    double fuelRate = 194.0;
    double oxidizerRate = 79.0;
    double launchLongitude = -80.5772;
    double launchLatitude = 28.5619;
    double launchAltitude = 3.0;
    std::vector<double> timeIncrements;
    std::vector<double> calculatedHeights;
    std::vector<double> xPositions3D;
    std::vector<double> yPositions3D;
    std::vector<double> zPositions3D;
    double seaLevelIntersectionX = 0.0;
    double seaLevelIntersectionY = 0.0;
    bool hasSeaLevelIntersection = false;
    bool fit2DAxes = false;
    bool fit3DAxes = false;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        const ImVec2 displaySize = ImGui::GetIO().DisplaySize;
        ImGui::GetBackgroundDrawList()->AddRectFilled(
            ImVec2(0.0f, 0.0f),
            displaySize,
            IM_COL32(26, 26, 26, 255));

        // ROCKET CONFIG WINDOW BEGIN ---------------------------------
        ImGui::Begin("Rocket Data", nullptr, ImGuiWindowFlags_MenuBar);
        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Exit")) {
                    glfwSetWindowShouldClose(window, GLFW_TRUE);
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        ImGui::Text("Rocket Configuration");
        ImGui::InputDouble("Engine Thrust (kN)", &engineThrust);
        ImGui::InputInt("Number of Engines", &numEngines);

        ImGui::Text("Rocket Data");
        ImGui::InputDouble("Dry Mass (kg)", &dryMass);
        ImGui::InputDouble("Fuel Mass (kg)", &fuelMass);
        ImGui::InputDouble("Oxidizer Mass (kg)", &oxidizerMass);
        ImGui::InputDouble("Fuel Drain Rate (kg/s)", &fuelRate);
        ImGui::InputDouble("Oxidizer Drain Rate (kg/s)", &oxidizerRate);

        ImGui::Text("Launch Data");
        ImGui::InputDouble("Launchpad Longitude", &launchLongitude);
        ImGui::InputDouble("Launchpad Latitude", &launchLatitude);
        ImGui::InputDouble("Launchpad Altitude", &launchAltitude);

        const double altitude = 1000.0;
        const double longitude = launchLongitude + 300.0;
        const double latitude = launchLatitude + 300.0;
        const Eigen::Vector3d rocketPosition =
            CoordinateConversion::gpsToECEF(longitude, latitude, altitude);
        const Eigen::Vector3d launchPosition =
            CoordinateConversion::gpsToECEF(launchLongitude, launchLatitude, launchAltitude);
        const Eigen::Vector3d enu = CoordinateConversion::ECEFtoENU(
            rocketPosition,
            launchPosition,
            Eigen::Vector3d(launchLongitude, launchLatitude, launchAltitude));
        ImGui::Text("Rocket Position in ENU: %.2f, %.2f, %.2f", enu.x(), enu.y(), enu.z());
        ImGui::End();
        // ROCKET CONFIG WINDOW END ---------------------------------


        // PROJECTILE TEST WINDOW BEGIN -----------------------------
        ImGui::Begin("Projectile Configuration", nullptr, ImGuiWindowFlags_MenuBar);
        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Exit")) {
                    glfwSetWindowShouldClose(window, GLFW_TRUE);
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        static double initialVelocity = 20.0;
        static double launchAngle = 45;
        static double startTime = 0;
        static double endTime = 6;
        static int numSamples = 100;

        ImGui::Text("Configure Projectile");
        ImGui::InputDouble("Launch Velocity", &initialVelocity);
        ImGui::InputDouble("Launch Angle", &launchAngle);

        ImGui::Text("Configure Simulator");
        ImGui::InputDouble("Start Time", &startTime);
        ImGui::InputDouble("End Time", &endTime);
        ImGui::InputInt("Simulation Steps", &numSamples);
        numSamples = std::clamp(numSamples, 2, 10000);
        if (endTime <= startTime) {
            endTime = startTime + 0.1;
        }

        if (ImGui::Button("Simulate!")) {
            fit2DAxes = true;
            timeIncrements.clear();
            calculatedHeights.clear();

            timeIncrements.resize(numSamples);
            calculatedHeights.resize(numSamples);
            const double verticalVelocity =
                initialVelocity * std::sin(launchAngle * 3.14159265358979323846 / 180.0);
            for (int i = 0; i < numSamples; ++i) {
                const double fraction = static_cast<double>(i) / (numSamples - 1);
                timeIncrements[i] = startTime + fraction * (endTime - startTime);
                calculatedHeights[i] =
                    std::max(Dynamics::projectileDisplacement(verticalVelocity, timeIncrements[i]), 0.0);
            }
        }

        ImGui::End();
        // PROJECTILE TEST WINDOW END -----------------------------

        //PROJECTILE GRAPH BEGIN 
        ImGui::Begin("Projectile Simulation", nullptr, ImGuiWindowFlags_MenuBar);
        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Exit")) {
                    glfwSetWindowShouldClose(window, GLFW_TRUE);
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
        
        if (fit2DAxes) {
            ImPlot::SetNextAxesToFit();
        }
        if (ImPlot::BeginPlot("Projectile Simulation")) {
            if (!timeIncrements.empty()) {
                ImPlot::SetupAxes("Time (s)", "Height (m)");
                ImPlot::PlotLine(
                    "Height over Time",
                    timeIncrements.data(),
                    calculatedHeights.data(),
                    static_cast<int>(timeIncrements.size()));
            } else {
                ImPlot::SetupAxes("Time (s)", "Height (m)");
            }
            ImPlot::EndPlot();
            fit2DAxes = false;
        }

        ImGui::End();
        //PROJECTILE GRAPH END 

        //3D PLOTTER BEGIN
        ImGui::Begin("Path Plotter", nullptr, ImGuiWindowFlags_MenuBar);
        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Exit")) {
                    glfwSetWindowShouldClose(window, GLFW_TRUE);
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        static double initialVelocity_3D = 20.0;
        static Vector3d launchAngle_3D = {0,0,0};
        static double startTime_3D = 0;
        static double endTime_3D = 6;
        static int numSamples3D = 100;

        ImGui::Text("Configure Projectile");
        ImGui::InputDouble("Launch Velocity", &initialVelocity_3D);
        ImGui::InputDouble("Launch Angle X", &launchAngle_3D.x());
        ImGui::InputDouble("Launch Angle Y", &launchAngle_3D.y());
        ImGui::InputDouble("Launch Angle Z", &launchAngle_3D.z());

        ImGui::Text("Configure Simulator");
        ImGui::InputDouble("Start Time", &startTime_3D);
        ImGui::InputDouble("End Time", &endTime_3D);
        ImGui::InputInt("Simulation Steps", &numSamples3D);
        numSamples3D = std::clamp(numSamples3D, 2, 10000);
        if (endTime_3D <= startTime_3D) {
            endTime_3D = startTime_3D + 0.1;
        }
        
        if (ImGui::Button("Simulate!##3D")) {
            fit3DAxes = true;
            hasSeaLevelIntersection = false;
            xPositions3D.resize(numSamples3D);
            yPositions3D.resize(numSamples3D);
            zPositions3D.resize(numSamples3D);

            for (int i = 0; i < numSamples3D; ++i) {
                const double fraction = static_cast<double>(i) / (numSamples3D - 1);
                const double time = startTime_3D + fraction * (endTime_3D - startTime_3D);
                const Vector3d position = Dynamics::parabolicMotion3D(
                    Vector3d::Zero(), initialVelocity_3D, launchAngle_3D, time);

                xPositions3D[i] = position.x();
                yPositions3D[i] = position.y();
                zPositions3D[i] = position.z();
            }

            for (std::size_t i = 1; i < zPositions3D.size(); ++i) {
                const double previousZ = zPositions3D[i - 1];
                const double currentZ = zPositions3D[i];
                if (previousZ >= 0.0 && currentZ <= 0.0 && (previousZ > 0.0 || currentZ < 0.0)) {
                    const double fraction = previousZ / (previousZ - currentZ);
                    seaLevelIntersectionX =
                        xPositions3D[i - 1] + fraction * (xPositions3D[i] - xPositions3D[i - 1]);
                    seaLevelIntersectionY =
                        yPositions3D[i - 1] + fraction * (yPositions3D[i] - yPositions3D[i - 1]);
                    hasSeaLevelIntersection = true;
                    break;
                }
            }

            if (!hasSeaLevelIntersection) {
                const auto zeroPosition = std::find(zPositions3D.begin(), zPositions3D.end(), 0.0);
                if (zeroPosition != zPositions3D.end()) {
                    const std::size_t index = static_cast<std::size_t>(
                        zeroPosition - zPositions3D.begin());
                    seaLevelIntersectionX = xPositions3D[index];
                    seaLevelIntersectionY = yPositions3D[index];
                    hasSeaLevelIntersection = true;
                }
            }
        }

        if (xPositions3D.empty()) {
            ImGui::TextUnformatted("Click Simulate! to display the projectile trajectory.");
        }

        if (ImPlot3D::BeginPlot("Path Visualization", ImVec2(-1, 0), ImPlot3DFlags_Equal)) {
            ImPlot3D::SetupAxes("East(m)", "North(m)", "Altitude(m)");

            double planeMinX = -10.0;
            double planeMaxX = 10.0;
            double planeMinY = -10.0;
            double planeMaxY = 10.0;
            double dataMin = -10.0;
            double dataMax = 10.0;
            if (!xPositions3D.empty()) {
                const auto xBounds = std::minmax_element(xPositions3D.begin(), xPositions3D.end());
                const auto yBounds = std::minmax_element(yPositions3D.begin(), yPositions3D.end());
                const auto zBounds = std::minmax_element(zPositions3D.begin(), zPositions3D.end());
                const double xPadding = std::max((*xBounds.second - *xBounds.first) * 0.1, 1.0);
                const double yPadding = std::max((*yBounds.second - *yBounds.first) * 0.1, 1.0);
                planeMinX = *xBounds.first - xPadding;
                planeMaxX = *xBounds.second + xPadding;
                planeMinY = *yBounds.first - yPadding;
                planeMaxY = *yBounds.second + yPadding;
                dataMin = std::min({
                    *xBounds.first, *yBounds.first, *zBounds.first, planeMinX, planeMinY, 0.0});
                dataMax = std::max({
                    *xBounds.second, *yBounds.second, *zBounds.second, planeMaxX, planeMaxY, 0.0});
            }

            if (fit3DAxes) {
                const double padding = std::max((dataMax - dataMin) * 0.1, 1.0);
                const double axisMin = dataMin - padding;
                const double axisMax = dataMax + padding;
                ImPlot3D::SetupAxesLimits(
                    axisMin,
                    axisMax,
                    axisMin,
                    axisMax,
                    axisMin,
                    axisMax,
                    ImPlot3DCond_Always);
            }

            const double seaLevelX[] = {planeMinX, planeMaxX, planeMaxX, planeMinX};
            const double seaLevelY[] = {planeMinY, planeMinY, planeMaxY, planeMaxY};
            const double seaLevelZ[] = {0.0, 0.0, 0.0, 0.0};
            ImPlot3DSpec seaLevelStyle;
            seaLevelStyle.FillColor = ImVec4(0.20f, 0.55f, 0.85f, 0.25f);
            seaLevelStyle.LineColor = ImVec4(0.20f, 0.55f, 0.85f, 0.35f);
            seaLevelStyle.Flags = ImPlot3DQuadFlags_NoLines;
            ImPlot3D::PlotQuad("Sea Level", seaLevelX, seaLevelY, seaLevelZ, 4, seaLevelStyle);

            if (!xPositions3D.empty()) {
                ImPlot3D::PlotLine(
                    "Projectile Trajectory",
                    xPositions3D.data(),
                    yPositions3D.data(),
                    zPositions3D.data(),
                    static_cast<int>(xPositions3D.size()));
            }

            if (hasSeaLevelIntersection) {
                ImPlot3DSpec intersectionStyle;
                intersectionStyle.Marker = ImPlot3DMarker_Circle;
                intersectionStyle.MarkerSize = 8.0f;
                intersectionStyle.MarkerFillColor = ImVec4(1.0f, 0.25f, 0.05f, 1.0f);
                intersectionStyle.MarkerLineColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
                const double intersectionZ = 0.0;
                ImPlot3D::PlotScatter(
                    "Sea-Level Intersection",
                    &seaLevelIntersectionX,
                    &seaLevelIntersectionY,
                    &intersectionZ,
                    1,
                    intersectionStyle);
            }

            ImPlot3D::EndPlot();
            fit3DAxes = false;
        }
        ImGui::End();
        //3D PLOTTER END

        ImGui::Render();
        int framebufferWidth = 0;
        int framebufferHeight = 0;
        glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
        glViewport(0, 0, framebufferWidth, framebufferHeight);
        glDisable(GL_SCISSOR_TEST);
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        glDrawBuffer(GL_BACK);
        glClearColor(0.10f, 0.10f, 0.10f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImPlot::DestroyContext();
    ImPlot3D::DestroyContext();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
