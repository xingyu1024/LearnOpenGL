#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

// ��������
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// ����
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
	// ��ʼ��GLFW
	glfwInit();
	// glfwWindowHint������������OpenGL���ڵ�һЩ����
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // ָ���������OpenGL�����ĵ����汾�� 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // ָ���������OpenGL�����ĵĴΰ汾�� 3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //GLFW_OPENGL_PROFILEָ����OpenGL�������ļ�����������ΪGLFW_OPENGL_CORE_PROFILE����ʾҪʹ�ú��������ļ���

	// ����һ������Ϊ LearnOpenGL ��800��600�Ĵ���
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "HelloTriangle", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// �����ڵ�����������Ϊ��ǰ�̵߳���������
	glfwMakeContextCurrent(window);
	// ע�����ô��ڵ�֡�����С�ص�����
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// ��ʼ��GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	unsigned int vertexShader;
	// ����һ����ɫ����Shader��
	vertexShader = glCreateShader(GL_VERTEX_SHADER); // ������ɫ�����ͣ������Ƕ�����ɫ��
	// ����ɫ��Դ�븽�ӵ���ɫ��������
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	// ������ɫ��
	glCompileShader(vertexShader);
	// ��鶥����ɫ���Ƿ����ɹ�
	int success;
	char infoLog[512];
	// ���ڲ�ѯ��ɫ��������ض�����ֵ, GL_COMPILE_STATUS ��ʾ����״̬��
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		// ��ȡ��ɫ���������Ϣ��־
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // ������ɫ�����ͣ�������Ƭ����ɫ��
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		// ��ȡ��ɫ���������Ϣ��־
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// ������ɫ������
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	// �Ѷ�����ɫ�����󸽼ӵ���ɫ������
	glAttachShader(shaderProgram, vertexShader);
	// ��Ƭ����ɫ�����󸽼ӵ���ɫ������
	glAttachShader(shaderProgram, fragmentShader);
	// ������ɫ������
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		// ��ȡ��ɫ���������Ϣ��־
		glGetProgramInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	// ɾ����ɫ������
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	float vertices[] = {
		 0.5f,  0.5f, 0.0f,  // ���Ͻ�
		 0.5f, -0.5f, 0.0f,  // ���½�
		-0.5f, -0.5f, 0.0f,  // ���½�
		-0.5f,  0.5f, 0.0f   // ���Ͻ�
	};

	unsigned int indices[] = {
		// ע��������0��ʼ! 
		// ����������(0,1,2,3)���Ƕ�������vertices���±꣬
		// �����������±��������ϳɾ���

		0, 1, 3, // ��һ��������
		1, 2, 3  // �ڶ���������
	};

	// ���㻺�����(Vertex Buffer Objects, VBO)
	// �����������(Vertex Array Object, VAO)
	unsigned int VBO, VAO, EBO;
	// ����һ�������������
	glGenVertexArrays(1, &VAO);
	// ����һ���������
	glGenBuffers(1, &VBO); // ��һ��������ʾҪ���ɵĻ��������������ڶ�����Ҫ���������洢����������Ƶ�����
	glGenBuffers(1, &EBO); // ��һ��������ʾҪ���ɵĻ��������������ڶ�����Ҫ���������洢����������Ƶ�����
	
	// �󶨶�������
	glBindVertexArray(VAO);

	// ���´����Ļ���󶨵� GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// �Ѷ������ݸ��Ƶ�������ڴ���
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// ���´����Ļ���󶨵� GL_ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// �Ѷ������ݸ��Ƶ�������ڴ���
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// ָ�������������ݵĸ�ʽ��λ�á�
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// ����ָ�������Ķ�����������
	glEnableVertexAttribArray(0);
	// ���VBO��VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	// ��Ⱦѭ��
	while (!glfwWindowShouldClose(window)) // ���һ��GLFW�Ƿ�Ҫ���˳�������ǵĻ����ú�������true
	{
		// ��Ⱦָ��
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// ������ɫ����
		glfwSwapBuffers(window);
		// �����û���¼�����
		glfwPollEvents();
	}

	// �ͷ���Դ
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