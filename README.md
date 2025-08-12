# Muri
Simulation program for 3D heat and vapor static diffusion in orthogonal construction details in building science

## The program
### Goal
This program is design for architects and engineers to simulate static 3D diffusion of heat and vapor in construction details. The results allows one to check for the safety of the construction detail with regard to condensation and mould growth.

## The development project
The project would have 4 main code directory:
- pre-processor
  - receives input from the user and create arguments for the solver
  - allows to save the input
- solver
  - uses the arguments created by the pre-processor
- post-processor
  - allows to print, display and save the results
- gui
  - graphical interface for the pre-processor, solver and post-processor
