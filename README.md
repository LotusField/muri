# Muri
Simulation program for 3D heat and vapor static diffusion in orthogonal construction details in building science

### Disclaimer:
This readme file is missing a lot of important informations in order to fully understand the goals and scope of the project, as well as how to build it, run it and contribute to it. Also, I am only an enthusiast programmer and have never been a professional. I have a full-time job and this project and even though I have high ambitions for this project, it remains something that I develop in my spare time. Any help from an experienced programmer is therefore greatly appreciated.

## The program
### Goal
This program is design for architects and engineers to simulate static 3D diffusion of heat and vapor in construction details. The results allows one to check for the safety of the construction detail with regard to condensation and mould growth.

## The development project
The project would have 4 main code directories:
- pre-processor
  - receives input from the user and generates an input for the solver
  - allows to save the input to retrieve it later
- solver
  - uses the arguments created by the pre-processor
- post-processor
  - allows to print, display and save the results
- gui
  - graphical interface for the pre-processor, solver and post-processor

### Used libraries and tools
- Compilation commands: **CMake** (https://cmake.org/)
- Windows: **Qt** (https://www.qt.io/)
- Graphics: **OpenGL** (https://www.opengl.org/)
- Code documentation: **doxygen** (https://doxygen.nl/)
- Linear algebra: **Eigen** (https://eigen.tuxfamily.org/)
- Unit testing: **Catch2** (https://github.com/catchorg/Catch2)

## How to contribute
There are many ways to contribute to this projects:
- Writing code
- Reviewing code and suggesting modifications/improvments
- Creating unit testing and running them
- Writing and refining the documentation
- Providing arts for the software illustrations

Do not hesitate to reach out in case you would like to contribute in a different manner than the ones above.
