#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;
const string WINDOW_TITLE = "OpenGL";

void framebuffersizefun(GLFWwindow *context, int width, int height);
void processInput(GLFWwindow* context);

int main(int argc, char* argv[])
{
	// init glfw library
	glfwInit();

	// configure context parameters
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow* context = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE.c_str(), NULL, NULL);
	if (!context)
	{
		cout << "Create GLFW window failed" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(context);
	glfwSetFramebufferSizeCallback(context, framebuffersizefun);

	// init glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to init GLAD" << endl;
		return -1;
	}

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	while (!glfwWindowShouldClose(context))
	{
		processInput(context);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(context);
		glfwPollEvents();
	}
	
	// dealloc resource
	glfwTerminate();

	return 0;
}

void framebuffersizefun(GLFWwindow* context, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* context)
{
	if (glfwGetKey(context, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(context, GL_TRUE);
}