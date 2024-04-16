#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

// 函数声明
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// 设置
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// shader
const char* vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\n\0";

const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

int main()
{
	// 初始化GLFW
	glfwInit();
	// glfwWindowHint函数用来设置OpenGL窗口的一些属性
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 指定了所需的OpenGL上下文的主版本号 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 指定了所需的OpenGL上下文的次版本号 3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //GLFW_OPENGL_PROFILE指定了OpenGL的配置文件，这里设置为GLFW_OPENGL_CORE_PROFILE，表示要使用核心配置文件。

	// 创建一个标题为 LearnOpenGL 宽800高600的窗口
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "HelloTriangle", nullptr, nullptr);
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

	unsigned int vertexShader;
	// 创建一个着色器（Shader）
	vertexShader = glCreateShader(GL_VERTEX_SHADER); // 传递着色器类型，这里是顶点着色器
	// 把着色器源码附加到着色器对象上
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	// 编译着色器
	glCompileShader(vertexShader);
	// 检查顶点着色器是否编译成功
	int success;
	char infoLog[512];
	// 用于查询着色器对象的特定参数值, GL_COMPILE_STATUS 表示编译状态。
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		// 获取着色器对象的信息日志
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // 传递着色器类型，这里是片段着色器
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		// 获取着色器对象的信息日志
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// 创建着色器程序
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	// 把顶点着色器对象附加到着色器程序
	glAttachShader(shaderProgram, vertexShader);
	// 把片段着色器对象附加到着色器程序
	glAttachShader(shaderProgram, fragmentShader);
	// 链接着色器程序
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		// 获取着色器程序的信息日志
		glGetProgramInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	// 删除着色器对象
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	float vertices[] = {
		 0.5f,  0.5f, 0.0f,  // 右上角
		 0.5f, -0.5f, 0.0f,  // 右下角
		-0.5f, -0.5f, 0.0f,  // 左下角
		-0.5f,  0.5f, 0.0f   // 左上角
	};

	unsigned int indices[] = {
		// 注意索引从0开始! 
		// 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
		// 这样可以由下标代表顶点组合成矩形

		0, 1, 3, // 第一个三角形
		1, 2, 3  // 第二个三角形
	};

	// 顶点缓冲对象(Vertex Buffer Objects, VBO)
	// 顶点数组对象(Vertex Array Object, VAO)
	unsigned int VBO, VAO, EBO;
	// 生成一个顶点数组对象
	glGenVertexArrays(1, &VAO);
	// 生成一个缓冲对象
	glGenBuffers(1, &VBO); // 第一个参数表示要生成的缓冲对象的数量。第二个是要输入用来存储缓冲对象名称的数组
	glGenBuffers(1, &EBO); // 第一个参数表示要生成的缓冲对象的数量。第二个是要输入用来存储缓冲对象名称的数组
	
	// 绑定顶点数组
	glBindVertexArray(VAO);

	// 把新创建的缓冲绑定到 GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// 把顶点数据复制到缓冲的内存中
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 把新创建的缓冲绑定到 GL_ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// 把顶点数据复制到缓冲的内存中
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 指定顶点属性数据的格式和位置。
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// 启用指定索引的顶点属性数组
	glEnableVertexAttribArray(0);
	// 解绑VBO和VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	// 渲染循环
	while (!glfwWindowShouldClose(window)) // 检查一次GLFW是否被要求退出，如果是的话，该函数返回true
	{
		// 渲染指令
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// 交换颜色缓冲
		glfwSwapBuffers(window);
		// 检查有没有事件触发
		glfwPollEvents();
	}

	// 释放资源
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}