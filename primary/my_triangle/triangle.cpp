#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>


//定义一个顶点着色器的代码，这段代码将输入的三个顶点坐标转换为向量类型，用于之后的计算
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";


//定义一个片段着色器，这段代码将颜色RGBA转换为向量类型
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FlagColor;\n"
"void main()\n"
"{\n"
"    FlagColor = vec4(1.0f,0.5f,0.2f,0.5f);\n"
"}\0";


//渲染窗口随主题窗口大小变化的回调函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

//监测按键是否被按下的回调函数
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {    //监测ESC键
		glfwSetWindowShouldClose(window, true);                 //设置窗口退出
	}

}


int main()
{
	//初始化...
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

	//初始化完成，三角形的绘制


	float vertices[] = {

		0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};//三角形的三个顶点坐标x,y,z，范围(-1,1)超过部分会直接切掉

	unsigned int indices[] = {
		// 注意索引从0开始! 
		// 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
		// 这样可以由下标代表顶点组合成矩形

		0, 1, 3, // 第一个三角形
		1, 2, 3  // 第二个三角形
	};

	//定义EBO
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	//定义VAO，
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	//绑定VAO
	glBindVertexArray(VAO);

	//定义顶点缓冲对象，该对象是OpenGL对象，使用glGenBuffers函数和一个缓冲ID生成一个VBO对象，1是缓冲对象个数
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	//顶点缓冲对象类型是GL_ARRAY_BUFFER，这个函数将生成的VBO对象绑定到GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);


	//glBufferData复制vertices的数据到GPU内存中
	/*第一个参数是缓冲类型，第二个参数是数据大小，第三个是数据，第四个是如何管理
	GL_STATIC_DRAW ：数据不会或几乎不会改变。
	GL_DYNAMIC_DRAW：数据会被改变很多。
	GL_STREAM_DRAW ：数据每次绘制时都会改变。
	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//定义顶点着色器对象
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//将顶点着色器代码绑定到顶点着色器对象上
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);//参数：着色器对象、源码字符串数量、源码，最后一个先不管
	glCompileShader(vertexShader);//编译顶点着色器代码
	//检测编译是否成功
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);//着色器对象、GL_COMPILE_STATUS表示编译状态、存储对象
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);//获取错误信息
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;//输出错误信息
	}

	//同样的方法创建片段着色器对象绑定到源代码并编译
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);//与顶点着色器不同
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	int  success2;
	char infoLog2[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success2);//着色器对象、GL_COMPILE_STATUS表示编译状态、存储对象
	if (!success2)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog2);//获取错误信息
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog2 << std::endl;//输出错误信息
	}


	//着色器程序对象
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	//附加之前的着色器
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	int sucess3;
	char infoLog3[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &sucess3);
	if (!sucess3)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog3);
		std::cout << "ERROR::SHADER::Program::LINK_FAILED\n" << infoLog3 << std::endl;//输出错误信息
	}



	//连接顶点属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//调用的是当前绑定到GL_ARRAY_BUFFER的VBO
	/*
	第一个参数指定我们要配置的顶点属性。还记得我们在顶点着色器中使用layout(location = 0)定义了position顶点属性的位置值(Location)吗？
	它可以把顶点属性的位置值设置为0。因为我们希望把数据传递到这一个顶点属性中，所以这里我们传入0。

	第二个参数指定顶点属性的大小。顶点属性是一个vec3，它由3个值组成，所以大小是3。

	第三个参数指定数据的类型，这里是GL_FLOAT(GLSL中vec*都是由浮点数值组成的)。

	下个参数定义我们是否希望数据被标准化(Normalize)。如果我们设置为GL_TRUE，
	所有数据都会被映射到0（对于有符号型signed数据是-1）到1之间。我们把它设置为GL_FALSE。

	第五个参数叫做步长(Stride)，它告诉我们在连续的顶点属性组之间的间隔。由于下个组位置数据在3个float之后，我们把步长设置为3 * sizeof(float)。
	要注意的是由于我们知道这个数组是紧密排列的（在两个顶点属性之间没有空隙）
	我们也可以设置为0来让OpenGL决定具体步长是多少（只有当数值是紧密排列时才可用）。

	最后一个参数的类型是void*，所以需要我们进行这个奇怪的强制类型转换。它表示位置数据在缓冲中起始位置的偏移量(Offset)。
	由于位置数据在数组的开头，所以这里是0。我们会在后面详细解释这个参数。
	*/
	glEnableVertexAttribArray(0);//启用指定索引的顶点数组


	//连接完成后可以删除原先的着色器对象
	glDeleteShader(vertexShader); glDeleteShader(fragmentShader);

	while (!glfwWindowShouldClose(window))  //每次循环的开始前检查一次GLFW是否被要求退出，如果是的话该函数返回true然后渲染循环便结束了，之后为我们就可以关闭应用程序了。
	{
		processInput(window);               //每个循环都监测按键
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   //清空屏幕所用颜色
		glClear(GL_COLOR_BUFFER_BIT);           //清空屏幕颜色缓冲

		//激活程序对象
		glUseProgram(shaderProgram);//每个着色器调用和渲染调用都会使用这个程序对象（也就是之前写的着色器)了
		glBindVertexArray(VAO);
		//       glDrawArrays(GL_TRIANGLES, 0, 2);//图元，索引，顶点数
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);            //交换颜色缓冲（双缓存）
		glfwPollEvents();                   //检查事件触发，调用对应回调函数
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

