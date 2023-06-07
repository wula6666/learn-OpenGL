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

	//��ʼ����ɣ������εĻ���


	float vertices[] = {

		0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};//�����ε�������������x,y,z����Χ(-1,1)�������ֻ�ֱ���е�

	unsigned int indices[] = {
		// ע��������0��ʼ! 
		// ����������(0,1,2,3)���Ƕ�������vertices���±꣬
		// �����������±��������ϳɾ���

		0, 1, 3, // ��һ��������
		1, 2, 3  // �ڶ���������
	};

	//����EBO
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	//����VAO��
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	//��VAO
	glBindVertexArray(VAO);

	//���嶥�㻺����󣬸ö�����OpenGL����ʹ��glGenBuffers������һ������ID����һ��VBO����1�ǻ���������
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	//���㻺�����������GL_ARRAY_BUFFER��������������ɵ�VBO����󶨵�GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);


	//glBufferData����vertices�����ݵ�GPU�ڴ���
	/*��һ�������ǻ������ͣ��ڶ������������ݴ�С�������������ݣ����ĸ�����ι���
	GL_STATIC_DRAW �����ݲ���򼸺�����ı䡣
	GL_DYNAMIC_DRAW�����ݻᱻ�ı�ܶࡣ
	GL_STREAM_DRAW ������ÿ�λ���ʱ����ı䡣
	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//���嶥����ɫ������
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//��������ɫ������󶨵�������ɫ��������
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);//��������ɫ������Դ���ַ���������Դ�룬���һ���Ȳ���
	glCompileShader(vertexShader);//���붥����ɫ������
	//�������Ƿ�ɹ�
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);//��ɫ������GL_COMPILE_STATUS��ʾ����״̬���洢����
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);//��ȡ������Ϣ
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;//���������Ϣ
	}

	//ͬ���ķ�������Ƭ����ɫ������󶨵�Դ���벢����
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);//�붥����ɫ����ͬ
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	int  success2;
	char infoLog2[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success2);//��ɫ������GL_COMPILE_STATUS��ʾ����״̬���洢����
	if (!success2)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog2);//��ȡ������Ϣ
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog2 << std::endl;//���������Ϣ
	}


	//��ɫ���������
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	//����֮ǰ����ɫ��
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	int sucess3;
	char infoLog3[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &sucess3);
	if (!sucess3)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog3);
		std::cout << "ERROR::SHADER::Program::LINK_FAILED\n" << infoLog3 << std::endl;//���������Ϣ
	}



	//���Ӷ�������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//���õ��ǵ�ǰ�󶨵�GL_ARRAY_BUFFER��VBO
	/*
	��һ������ָ������Ҫ���õĶ������ԡ����ǵ������ڶ�����ɫ����ʹ��layout(location = 0)������position�������Ե�λ��ֵ(Location)��
	�����԰Ѷ������Ե�λ��ֵ����Ϊ0����Ϊ����ϣ�������ݴ��ݵ���һ�����������У������������Ǵ���0��

	�ڶ�������ָ���������ԵĴ�С������������һ��vec3������3��ֵ��ɣ����Դ�С��3��

	����������ָ�����ݵ����ͣ�������GL_FLOAT(GLSL��vec*�����ɸ�����ֵ��ɵ�)��

	�¸��������������Ƿ�ϣ�����ݱ���׼��(Normalize)�������������ΪGL_TRUE��
	�������ݶ��ᱻӳ�䵽0�������з�����signed������-1����1֮�䡣���ǰ�������ΪGL_FALSE��

	�����������������(Stride)�������������������Ķ���������֮��ļ���������¸���λ��������3��float֮�����ǰѲ�������Ϊ3 * sizeof(float)��
	Ҫע�������������֪����������ǽ������еģ���������������֮��û�п�϶��
	����Ҳ��������Ϊ0����OpenGL�������岽���Ƕ��٣�ֻ�е���ֵ�ǽ�������ʱ�ſ��ã���

	���һ��������������void*��������Ҫ���ǽ��������ֵ�ǿ������ת��������ʾλ�������ڻ�������ʼλ�õ�ƫ����(Offset)��
	����λ������������Ŀ�ͷ������������0�����ǻ��ں�����ϸ�������������
	*/
	glEnableVertexAttribArray(0);//����ָ�������Ķ�������


	//������ɺ����ɾ��ԭ�ȵ���ɫ������
	glDeleteShader(vertexShader); glDeleteShader(fragmentShader);

	while (!glfwWindowShouldClose(window))  //ÿ��ѭ���Ŀ�ʼǰ���һ��GLFW�Ƿ�Ҫ���˳�������ǵĻ��ú�������trueȻ����Ⱦѭ��������ˣ�֮��Ϊ���ǾͿ��Թر�Ӧ�ó����ˡ�
	{
		processInput(window);               //ÿ��ѭ������ⰴ��
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   //�����Ļ������ɫ
		glClear(GL_COLOR_BUFFER_BIT);           //�����Ļ��ɫ����

		//����������
		glUseProgram(shaderProgram);//ÿ����ɫ�����ú���Ⱦ���ö���ʹ������������Ҳ����֮ǰд����ɫ��)��
		glBindVertexArray(VAO);
		//       glDrawArrays(GL_TRIANGLES, 0, 2);//ͼԪ��������������
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);            //������ɫ���壨˫���棩
		glfwPollEvents();                   //����¼����������ö�Ӧ�ص�����
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

