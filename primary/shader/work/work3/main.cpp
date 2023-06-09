#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


//�������ڴ�С�Ļص�����
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

//��ⰴ���Ƿ񱻰��µĻص�����
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {    //���ESC��
		glfwSetWindowShouldClose(window, true);                 //���ô����˳�
	}

}

//����һ��������ɫ���Ĵ��룬��δ��뽫�����������������ת��Ϊ�������ͣ�����֮��ļ���
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"out vec3 color;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"	color = aPos;\n"
"}\0";

//����һ��Ƭ����ɫ������δ��뽫��ɫRGBAת��Ϊ��������
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FlagColor;\n"
"in vec3 color;\n"
"void main()\n"
"{\n"
"    FlagColor = vec4(color,1.0);\n"
"}\0";


int main()
{
	//��ʼ��...
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL_Demo", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//������ɫ��
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//����ɫ��
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//������ɫ��
	glCompileShader(vertexShader);
	int sucess;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &sucess);
	if (!sucess)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Vertex Shader Complie Failed : \n" << infoLog << std::endl;
	}

	//Ƭ����ɫ��
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//����ɫ��
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//������ɫ��
	glCompileShader(fragmentShader);
	int sucess2;
	char infoLog2[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &sucess2);
	if (!sucess2)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog2);
		std::cout << "Fragment Shader Complie Failed : \n" << infoLog2 << std::endl;
	}

	//��ɫ������
	unsigned int ShaderProgram;
	ShaderProgram = glCreateProgram();

	glAttachShader(ShaderProgram, vertexShader);
	glAttachShader(ShaderProgram, fragmentShader);
	glLinkProgram(ShaderProgram);

	int sucess3;
	char infoLog3[512];
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &sucess3);
	if (!sucess3)
	{
		glGetProgramInfoLog(ShaderProgram, 512, NULL, infoLog3);
		std::cout << "Program Shader Link Failed : \n" << infoLog3 << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	float vertrices[] = {
		//��һ��������
		0.0f,0.5f,0.0f,
		-0.5f,0.0f,0.0f,
		0.5f,0.0f,0.0f
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertrices), vertrices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(0);

	glUseProgram(ShaderProgram);


	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glClearColor(0.3f, 0.3f, 0.3f, 0.4f);
		glClear(GL_COLOR_BUFFER_BIT);


		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(ShaderProgram);

	glfwTerminate();
	return 0;

}
