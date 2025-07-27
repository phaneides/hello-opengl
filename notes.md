The Screen is a discrete 2D space, because is a 2d array or pixels. 
Our 'sensors' can be thinking always disposed in a 2D array, an clearly, wee see 2D images only. 
But we live in a 3D space, so a projection is what happends when we see. 
An analagy can be stablished in OpenGL, everything is in 3D space in OpenGL also, and 
a projection to this abstract 3D space must be done in order that we can see something in our screens. 

Transforming 3D coordiantes to 2D colored pixels on the screen is an important part 
of the work done by OpenGL, thiw process is handdled by the 'graphics pipeline'.  This task can be devided in two greate ones, the conversion of 3D coordinates in the space to the 2D coordinates in the 'image space' and the transformation between this 2D coordinates to colored pixels.


Graphics Pipeline: 3D coordinates (positions in space) -> colored pixels (representation on the screen).



## Vertex Array Object 
