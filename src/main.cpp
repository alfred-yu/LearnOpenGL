#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <shader_s.h>

using namespace std;

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;
const string WINDOW_TITLE = "OpenGL";

void framebuffersizefun(GLFWwindow *context, int width, int height);
void keyEventCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

#if 1
float vertices[] = {
	// 位置              // 颜色
	 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
	 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
};
#else
float vertices[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
};

unsigned int indices[] = {
	// 注意索引从0开始! 
	// 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
	// 这样可以由下标代表顶点组合成矩形

	0, 1, 3, // 第一个三角形
	1, 2, 3  // 第二个三角形
};
#endif

#if 0
const char *vertexShaderSource = "#version 330 core\n"
"layout (location=0) in vec3 aPos;\n"
"layout (location=1) in vec3 aColor;\n"
"\n"
"out vec3 ourColor;\n"
"\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"ourColor = aColor;\n"
"}\n";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"\n"
"void main()\n"
"{\n"
"	FragColor = vec4(ourColor, 1.0);\n"
"}\n";
#endif

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
	glfwSetKeyCallback(context, keyEventCallback);

	// init glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to init GLAD" << endl;
		return -1;
	}

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);

#if 0
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
#endif
	glBindVertexArray(0);

#if 0
	int success;
	char infoLog[512];

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, sizeof(infoLog), NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
	}

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, sizeof(infoLog), NULL, infoLog);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
	}

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, sizeof(infoLog), NULL, infoLog);
		cout << "ERROR::SHADER::PROGRAM::LINKFAILED\n" << infoLog << endl;
	}

	// delete shader object
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
#endif
	Shader shader("shader.vs", "shader.fs");

	while (!glfwWindowShouldClose(context))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.use();
#if 0
		glUseProgram(shaderProgram);
#endif
		glBindVertexArray(VAO);
#if 1
		glDrawArrays(GL_TRIANGLES, 0, 3);
#else
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
#endif
		glfwSwapBuffers(context);
		glfwPollEvents();
	}

	// dealloc resource
#if 0
	glDeleteProgram(shaderProgram);
#endif
	glfwTerminate();

	return 0;
}

void framebuffersizefun(GLFWwindow* context, int width, int height)
{
	glViewport(0, 0, width, height);
}

void keyEventCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	static bool showPolyonMode = false;

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	else if (key == GLFW_KEY_P && action == GLFW_PRESS)
	{
		showPolyonMode = !showPolyonMode;
		cout << "showPolyonMode:" << showPolyonMode << endl;
		glPolygonMode(GL_FRONT_AND_BACK, showPolyonMode ? GL_LINE : GL_FILL);
	}
}
