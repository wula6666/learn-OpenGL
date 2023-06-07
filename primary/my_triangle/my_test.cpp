#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int my_width = 800;
int my_height = 600;



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


int main()
{

    //glfw����
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//���汾��
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//�ΰ汾��
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//����OpenGL�汾��Ϊ3.3
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);//mac os ϵͳȡ��ע��

    GLFWwindow* window = glfwCreateWindow(my_width, my_height, "LearnOpenGL", NULL, NULL);//��������ʵ��,���ߡ���������
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);//����glfwMakeContextCurrent���������Ѵ������ڵ�ContextΪ��ǰ�̵߳���Context
    //������⣺�±ߵĲ�������window�����Ͻ���

    //�ڵ���OpenGL����ǰҪ��ʼ��GLAD����ʼ����ɺ�ʼ��Ⱦ
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    //������Ⱦ�Ĵ��ڴ�С�����ӿ�(Viewport)
    glViewport(0, 0, 800, 600);//glViewport����ǰ�����������ƴ������½ǵ�λ�á��������͵��ĸ�����������Ⱦ���ڵĿ�Ⱥ͸߶ȣ����أ�
    //����ʵ����Ҳ���Խ��ӿڵ�ά������Ϊ��GLFW��ά��С
    //֮�����е�OpenGL��Ⱦ������һ����С�Ĵ�������ʾ�������Ļ�����Ҳ���Խ�һЩ����Ԫ����ʾ��OpenGL�ӿ�֮�⡣
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//ע��ص�����

    //��Ⱦѭ��
    while (!glfwWindowShouldClose(window))  //ÿ��ѭ���Ŀ�ʼǰ���һ��GLFW�Ƿ�Ҫ���˳�������ǵĻ��ú�������trueȻ����Ⱦѭ��������ˣ�֮��Ϊ���ǾͿ��Թر�Ӧ�ó����ˡ�
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   //�����Ļ������ɫ
        glClear(GL_COLOR_BUFFER_BIT);           //�����Ļ��ɫ����

        processInput(window);               //ÿ��ѭ������ⰴ��
        glfwSwapBuffers(window);            //������ɫ���壨˫���棩
        glfwPollEvents();                   //����¼����������ö�Ӧ�ص�����
    }

    glfwTerminate();                        //�ͷ���Դ���˳�
    return 0;
}