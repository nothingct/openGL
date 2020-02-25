#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <iostream>	
#include "math.h"
using namespace std;
const int width_window = 1280;
const int height_window = 960;

float circle_center_x = 0.0;
float circle_center_y = 0.0;

//call function for key input 
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
		//activate_airship();
		cout << "Key pressed" << '\n';

	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
		//activate_airship();
		circle_center_x -= 0.05;

	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
		//activate_airship();
		circle_center_x += 0.05;

	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
		//activate_airship();
		circle_center_y -= 0.05;

	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
		//activate_airship();
		circle_center_y += 0.05;

}

//call function for cursor
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	cout << xpos << " " << ypos << '\n';
} 
int main(void)
{
	GLFWwindow *window = nullptr;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width_window, height_window, "OHS", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	// callbacks here
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glClearColor(24 /255.0, 239 /255.0, 203/255.0, 0.5); // while background
	
	//default color for display buffer 

	int width, height;
	
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	//port of view we can sees in our window 
	//your frame buffer is two dimensional array x- y-
	//your frame buffer is three dimesional array x- y- z-
	const float aspect_ratio = (float)width / (float)height;  // 1.66 or 1.9
	glOrtho(-1*aspect_ratio, 1*aspect_ratio, -1, 1, -1.0, 1.0);
	// you are going to study later in viewing class.


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		//TODO: draw here
		glPointSize(10);
		//drawing trangle
		/* 
		glBegin(GL_TRIANGLES);
		glColor3f(1.0, 0.0, 0.0);//for glcolor 
		glVertex3f(0.0, 0.0, 0.0); // == glVertex2f(0.0,0.0) in 2D drawing
		
		glColor3f(0.0, 1.0, 0.0);//for glcolor
		glVertex3f(0.5, 0.0, 0.0);
		
		glColor3f(0.0, 0.0, 1.0);//for glcolor
		glVertex3f(0.25, 0.5, 0.0);

		glEnd();
		*/

		//drawing circle
		glBegin(GL_TRIANGLE_FAN);
		// center vertex
		glVertex2f(circle_center_x,circle_center_y);
		
		const int num_triangles = 1000; 
		const float dtheta = 2.0 * 3.141592 / (float)num_triangles;
		const float radius = 0.5;

		float theta = 0.0;
		for (int i = 0; i <= num_triangles; i++,theta+=dtheta) {
			glColor3f(1,0,0);
			const float x = radius * cos(theta)+circle_center_x;
			const float y = radius * sin(theta)+circle_center_y;
			
			glVertex2f(x, y);
		}
		glEnd();
		//NOote : this is an old - style OpenGL 
		/* Swap front and back buffers */
		glfwSwapBuffers(window); 

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate(); 

	return 0;
}

