#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int my_width = 800;
int my_height = 600;



//调整窗口大小的回调函数
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

    //glfw设置
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//主版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//次版本号
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//设置OpenGL版本号为3.3
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);//mac os 系统取消注释

    GLFWwindow* window = glfwCreateWindow(my_width, my_height, "LearnOpenGL", NULL, NULL);//创建窗口实例,宽、高、窗口名称
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);//调用glfwMakeContextCurrent函数设置已创建窗口的Context为当前线程的主Context
    //个人理解：下边的操作均在window对象上进行

    //在调用OpenGL函数前要初始化GLAD，初始化完成后开始渲染
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    //设置渲染的窗口大小，即视口(Viewport)
    glViewport(0, 0, 800, 600);//glViewport函数前两个参数控制窗口左下角的位置。第三个和第四个参数控制渲染窗口的宽度和高度（像素）
    //我们实际上也可以将视口的维度设置为比GLFW的维度小
    //之后所有的OpenGL渲染将会在一个更小的窗口中显示，这样的话我们也可以将一些其它元素显示在OpenGL视口之外。
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//注册回调函数

    //渲染循环
    while (!glfwWindowShouldClose(window))  //每次循环的开始前检查一次GLFW是否被要求退出，如果是的话该函数返回true然后渲染循环便结束了，之后为我们就可以关闭应用程序了。
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   //清空屏幕所用颜色
        glClear(GL_COLOR_BUFFER_BIT);           //清空屏幕颜色缓冲

        processInput(window);               //每个循环都监测按键
        glfwSwapBuffers(window);            //交换颜色缓冲（双缓存）
        glfwPollEvents();                   //检查事件触发，调用对应回调函数
    }

    glfwTerminate();                        //释放资源，退出
    return 0;
}