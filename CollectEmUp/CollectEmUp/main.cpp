/* CollectEmUp Game © 2015
Created for IGME - 309 Data Structures and Algorithms for Games and Simulation II

Team Members:
Norman Greenberg: Team Manager/Design
Cathy Altenburger: Designer/Artist
L.A. Stapleford: Designer/Artist
Andrew Litfin: Designer
Andrew Knowland: Designer

Michael Lynch: Engine Lead
Matthew Fasman: Engine Developer
Ryan Mignini : Engine Developer
Hector Piñeiro: Engine Developer

This main.cpp is just to get OpenGL set up as it is can have the most difficulties
For the future we should begin to separate out different elements into their own methods and classes

I have selected Visual Studos 2013 as it is what all of the lab machines have on them. I apologize if this causes an inconvenience initially.
*/

#include <stdlib.h>
#include <stdio.h>
#include <glew.h>
#include <glfw3.h>

int main(int argc, char* argv[])
{
	if (!glfwInit())
	{
		return -1;
	}

	// Create a windowed mode window and its OpenGL context 
	GLFWwindow* windowPtr = glfwCreateWindow(800, 800, "CollectEmUp", NULL, NULL);
	if (!windowPtr)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(windowPtr);

	if (glewInit() != GLEW_OK) return false;

	while (!glfwWindowShouldClose(windowPtr))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(windowPtr);
		glfwPollEvents();
	}

	return 0;
}