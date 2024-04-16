#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

// 函数声明
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// 设置
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	// 初始化GLFW
	glfwInit();
	// glfwWindowHint函数用来设置OpenGL窗口的一些属性
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 指定了所需的OpenGL上下文的主版本号 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 指定了所需的OpenGL上下文的次版本号 3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //GLFW_OPENGL_PROFILE指定了OpenGL的配置文件，这里设置为GLFW_OPENGL_CORE_PROFILE，表示要使用核心配置文件。
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// 创建一个标题为 LearnOpenGL 宽800高600的窗口
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// 将窗口的上下文设置为当前线程的主上下文
	glfwMakeContextCurrent(window);
	// 注册设置窗口的帧缓冲大小回调函数
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// 初始化GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// 渲染循环
	while (!glfwWindowShouldClose(window)) // 检查一次GLFW是否被要求退出，如果是的话，该函数返回true
	{
		// 输入
		processInput(window);

		// 渲染指令


		// 交换颜色缓冲
		glfwSwapBuffers(window);
		// 检查有没有触发什么事件
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

// 窗口大小被调整时调用的回调函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// 处理输入
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}