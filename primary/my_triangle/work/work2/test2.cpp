#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>


//����һ��������ɫ���Ĵ��룬��δ��뽫�����������������ת��Ϊ�������ͣ�����֮��ļ���
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";


//����һ��Ƭ����ɫ������δ��뽫��ɫRGBAת��Ϊ��������
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FlagColor;\n"
"void main()\n"
"{\n"
"    FlagColor = vec4(1.0f,0.5f,0.2f,0.5f);\n"
"}\0";


//��Ⱦ���������ⴰ�ڴ�С�仯�Ļص�����
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

	float vertrices1[] = {
		0.0f,0.0f,0.0f,
		0.5f,1.0f,0.0f,
		1.0f,0.0f,0.0f
	};

	float vertrices2[] = {
		-1.0f,1.0f,0.0f,
		-1.0f,-1.0f,0.0f,
		-0.3f,0.0f,0.0f
	};


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

	unsigned int VBO[2], VAO[2];
	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);

	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER,VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertrices1), vertrices1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertrices2), vertrices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glClearColor(0.3f, 0.3f, 0.3f, 0.3f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(ShaderProgram);
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteBuffers(2,VBO);
	glDeleteVertexArrays(2, VAO);
	glDeleteProgram(ShaderProgram);

	glfwTerminate();
	return 0;

}


