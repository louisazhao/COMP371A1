Introduction

The goal of this project is to draw a horse with all its parts transformed from a unit cube. A 100*100 unit grid is also drawn in the scene to work as a reference surface. At the centre of the scene a XYZ coordinate is displayed with different colours corresponding to different axises. Several functionalities are achieved through mouse callback function and keyboard callback function.

Files of the project:

1.ShaderProg.h and ShaderProg.cpp (modified from https://learnopengl.com/)

ShaderProg class takes paths of two shaders (vertex shader and fragment shader) to create a shader program. The class has function to check compiler error and link error occurred when compile shaders and link them together. This class also provides a set of functions for set "uniform" values.

2. horsevs.vs and horsefs.fs

Vertex shader and fragment shader for the horse. Colours for different parts of the horse are set through the "partColor" uniform.

3. squarevs.vs and squarefs.fs

Vertex shader and fragment shader for the ground (grid). 

4. DrawHorse.hpp

Store the data about the world transformation and scaler of all parts of the horse. With "drawHorse" function, the proper model matrix of parts will be computed.

5. main.cpp

Mouse callback function handles the behaviour of the mouse and react accordingly.

Keyboard callback function handles the input from keyboard and react accordingly. 
Please note that since I'm using MacBook, which has no "Home" button, therefore, I'm using "tab" instead. To distinguish between upper case and lower case letter input, if you press "shift" and the letter button together, the letter will be regraded as upper case. Otherwise, it will be regarded as lower case.

Main function initializes glfw, glew, configures window and camera parameters. Creates VAOs and VBOs and render the horse, the grid and the coordinate system in the game loop.
(Three shader programs, three VAOs and three VBOs are created corresponding to horse, grid and coordinate.)




