>NOTE: This project is **very** early in its programming stages 

### About Icarus
This program is designed to be a simple implementation of atmospheric dynamics for rockets, with the core goal of guiding self-propelled vertical rocket landings (a-la SpaceX).  To achieve this, Icarus is built on a foundation of various different individually configurable "modules", allowing parameters to be set for the exact type of rocket, fuel, takeoff, and target landing positions.  These parameters are then passed into a single Dynamics function, which will calculate the state of the system after a specific amount of time, iterating until a target time is found for *when* and *how long* to fire the boosters for landing.

```mermaid
flowchart TD

X[**SIMULATION START**]-->A

A[**INPUT**

Sensor Telemetry

...

*What is physically happening around the rocket?*]

--> B[**PREPROCESSING**

Coordinate Conversion

Unit Conversion

...

*Converting sensor data into better formats*]

  

-->C[**MODELS**

Current Rocket State

Current Flight State

...

*What is the current state of the flight system?*]

  
  

-->D[**GUIDANCE**

Evaluate Flight State

Predict Current Trajectory

Determine Best Control Inputs

...

*Based on the current state of the flight, determine the inputs required to make the rocket reach its target*]

  

-->E[**PHYSICS**

Calculate Forces & Dynamics of the System

Calculate Resultant State of the Rocket

...

*If the inputs calculated by the Guidance component are applied to the rocket, what happens to it?*]

  

-->F[**SIMULATOR**

Propogate Simulation by a Time Increment ΔT

...

*Manages the overall simulation, advancing the rocket's simulated flight step-by-step and recording the results of each flight*]

  

-->G[**UPDATED STATE**

Position

Velocity

Orientation

Mass

...

*What will the rocket's state be some time after takeoff?*]

  

-->H[**HAS THE ROCKET REACHED ITS TARGET?**]-->I[YES]-->O[**Send successful control data to flight controller**]

H-->J[NO]

  

J-->K[**IS THE ROCKET STILL IN THE AIR?**]

K-->M[NO]-->N[END CURRENT SIMULATION]

K-->L[YES]

  

L-->C
```
