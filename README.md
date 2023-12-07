# 3D-solar-system
## Complex Object Modeling Program

### Overview

This project is designed to showcase the complexities and intricacies involved in modeling complex objects, particularly focusing on elements with multiple moving parts such as a robotic arm. The main challenge addressed by this project is the implementation of a series of transformations to accurately represent the motion and interaction of various components in a 3D space. Additionally, it demonstrates the rendering of a dynamic planetary system, offering a comprehensive view of real-time computer graphics and simulation.

### Problem Description

Modeling complex objects with moving parts, like robotic arms, in a 3D environment is a challenging task. It requires a deep understanding of geometric transformations and how they apply to different components. The primary issue is to ensure that movements and rotations of individual parts are coherent and synchronized to achieve realistic motion. Moreover, implementing an interactive camera view that allows users to observe the model from different perspectives adds to the complexity.

### Solution Approach

The project tackles these challenges using OpenGL and the GLUT library in C++. It involves:

* Hierarchical Modeling: Utilizing parent-child relationships among different components to ensure coherent movements.
* Transformation Stacking: Applying a series of translation, rotation, and scaling transformations to simulate motion.
* Interactive Input Handling: Capturing and processing user input for real-time interaction with the model.
* Dynamic Rendering: Continuously updating the scene to reflect changes in the model and camera perspective.
  
### Features

* Robotic Arm Simulation: A detailed model of a robotic arm with articulated joints and movable parts.
* Planetary System: A dynamic representation of a solar system with orbiting planets and moons.
* User Interaction: Control over the robotic arm movements and camera orientation.
* Real-Time 3D Rendering: Leveraging OpenGL for immersive and interactive 3D graphics.
  
### Prerequisites

* C++ Compiler (GCC recommended)
* OpenGL and GLUT libraries

### Installation

* Clone the repository to your local machine.
* Ensure you have the necessary libraries (OpenGL and GLUT) installed on your system.
* Compile the program using a C++ compiler. For GCC, use the command: g++ -o robot_simulation main.cpp -lGL -lGLU -lglut

  
### Usage

* Run the compiled program.
* Use the keyboard controls to interact with the simulation:
* Arrow Keys: Change the camera orientation.
* Keys 2/@, 3/#, 4/$: Control the rotation of different parts of the robotic arm.
* Keys 5/%: Adjust the spacing of the robotic arm's grippers.
* Keys o/p: Zoom in and out of the scene.
* Keys z/Z: Rotate the view around the Z-axis.
  
### Documentation

In-depth comments within the code provide a detailed explanation of each function, variable, and the logic behind the transformations.
