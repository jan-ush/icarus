>NOTE: This project is **very** early in its programming stages

### About Icarus
This program is designed to be a simple implementation of atmospheric dynamics for rockets, with the core goal of guiding self-propelled vertical rocket landings (a-la SpaceX).  To achieve this, Icarus is built on a foundation of various modules, which all work together to calculate and identify the best possible time and angle for the rocket to fire its boosters so that it completes a smooth and safe landing:

<img width="1028" height="4666" alt="output-onlinepngtools" src="https://github.com/user-attachments/assets/bc8ba705-9334-4778-80d8-c9960b46b536" />

## TODO

### Initialization & Input
- [x] Get and store rocket configuration data (dry mass, fuel mass, engine specifications, geometry, etc.)
- [x] Define launch and landing coordinates
- [x] Acquire and process initial flight telemetry
- [x] Convert latitude, longitude, and altitude (LLA) coordinates into Earth-Centered, Earth-Fixed (ECEF) coordinates
- [x] Convert ECEF coordinates into a local East-North-Up (ENU) coordinate system relative to the launch site

### Models & Environment
- [x] Define rocket configuration and physical properties
- [x] Establish the initial rocket flight state (position, velocity, acceleration, orientation, and mass)
- [ ] Implement environmental models (gravity, atmospheric density, and wind)
- [ ] Define engine and aerodynamic properties

### Physics & Dynamics
- [ ] Calculate gravitational forces acting on the rocket
- [x] Calculate engine thrust and fuel consumption
- [ ] Implement aerodynamic drag calculations
- [ ] Calculate resultant forces and acceleration
- [ ] Propagate rocket velocity and position over time
- [ ] Update rocket mass and fuel state throughout the simulation
- [ ] Implement rotational dynamics and orientation updates

### Guidance
- [x] Evaluate the current rocket flight state
- [ ] Predict the rocket's future trajectory
- [ ] Compare predicted trajectory against desired landing conditions
- [ ] Determine the control inputs required to reach the target
- [ ] Update guidance decisions throughout the flight

### Simulator
- [ ] Initialize the simulation using rocket, environment, and flight data
- [ ] Implement the timestep-based simulation loop
- [ ] Integrate Guidance, Physics, and Dynamics into each simulation iteration
- [ ] Update and store the rocket state at each timestep
- [ ] Implement flight termination conditions (target reached, ground contact, fuel depletion, etc.)
- [ ] Record simulation telemetry and results

### Testing & Validation
- [ ] Validate coordinate transformations against known reference points
- [ ] Test physics calculations against analytical solutions
- [ ] Verify simulation behaviour under simplified conditions
- [ ] Compare simulated trajectories against expected results





