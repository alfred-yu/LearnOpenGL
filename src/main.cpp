#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

using namespace std;

void framebufferSizeChangedCallback(GLFWwindow*, int width, int height);

int main(int argc, char* argv[])
{
	// init GLFW library
	glfwInit();

	// init env
	glfwInitHint(GLFW_VERSION_MAJOR, 3);
	glfwInitHint(GLFW_VERSION_MINOR, 3);
	glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create context
	GLFWwindow* context = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
	if (!context)
	{
		cout << "Init context failed" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(context);
	glfwSetFramebufferSizeCallback(context, framebufferSizeChangedCallback);

	// init glad library
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "init GLAD failed\n" << endl;
		glfwTerminate();
		return -1;
	}

	// set viewport parameter
	glViewport(0, 0, 800, 600);
	
	while (!glfwWindowShouldClose(context))
	{
		glfwSwapBuffers(context);
		glfwPollEvents();
	}

	// terminate GLFW library
	glfwTerminate();
	return 0;
}

void framebufferSizeChangedCallback(GLFWwindow*, int width, int height)
{
	glViewport(0, 0, width, height);
}
