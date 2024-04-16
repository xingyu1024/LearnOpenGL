#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

// ��������
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// ����
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	// ��ʼ��GLFW
	glfwInit();
	// glfwWindowHint������������OpenGL���ڵ�һЩ����
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // ָ���������OpenGL�����ĵ����汾�� 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // ָ���������OpenGL�����ĵĴΰ汾�� 3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //GLFW_OPENGL_PROFILEָ����OpenGL�������ļ�����������ΪGLFW_OPENGL_CORE_PROFILE����ʾҪʹ�ú��������ļ���
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// ����һ������Ϊ LearnOpenGL ��800��600�Ĵ���
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
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

	// ��Ⱦѭ��
	while (!glfwWindowShouldClose(window)) // ���һ��GLFW�Ƿ�Ҫ���˳�������ǵĻ����ú�������true
	{
		// ����
		processInput(window);

		// ��Ⱦָ��


		// ������ɫ����
		glfwSwapBuffers(window);
		// �����û�д���ʲô�¼�
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

// ���ڴ�С������ʱ���õĻص�����
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// ��������
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}