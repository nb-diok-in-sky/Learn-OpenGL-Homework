#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const char* vertexShaderSource = 
"#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"layout(location = 1) in vec3 aColor\n;"
"out vec3 ourColor;"//这个out啊 就是输出的意思 代表从这里会向外面传递一个数据啊 叫vec4
"void main()\n"
"{\n"
"gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
"ourColor = aColor;\n"
"}\0";//这么一大串都是顶点着色器的源码硬编码 这个是最简单得了额 原理是 把传入进来的三维向量变成一个w为一的四维向量
  
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"

"void main(){\n"
"FragColor = vec4 (ourColor,1.0f);}\0";//这里是自己定义了一个输出变量 用于表示最终的输出颜色


const char* fragmentShaderSource222 = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 uColor;\n"
"void main(){\n"
"FragColor = uColor;\n"
" }\0";//这里是自己定义了一个输出变量 用于表示最终的输出颜色




int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // render loop
    // -----------
    //在渲染前要先定义顶点数组
    float vertices[] = {
  0.5f,-0.5f,0.0f,1.0f,0.0f,0.0f,
  -0.5f,-0.5f,0.0f,0.0f,1.0f,0.0f,
  0.0f,0.5f,0.0f,0.0f,0.0f,1.0f
    };//因为要渲染的三角形是2d的所以所有三角形的顶
    //点z轴都把他设为0 这样看起来就是一个2d的三角形了

    float another[] = { 
    0.1f,0.3f,0.0f,
    0.1f,-0.3f,0.0f,
    -0.1f,-0.3f,0.0f,
    -0.1f,0.3f,0.0f
    }; 

    unsigned int indexes[]{ 0,1,2,
                    1,2,3 };


   //创建VBO对象用于存储大量的顶点，称作顶点缓冲对象
    unsigned int VBO[2], VAO[2], EBO[2];
    glGenBuffers(2,VBO);
    glGenBuffers(2, EBO);
    glGenVertexArrays(2, VAO);



    glBindVertexArray(VAO[0]);//这个用来绑定VAO对象
    //绑定缓冲
    glBindBuffer(GL_ARRAY_BUFFER,VBO[0]);
    //填充vbo的数据
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);//绑定ebo对象
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);//传入数据

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);




    //因为做了几个着色器 所以需要有多套的vbo绑定缓冲区
    glBindVertexArray(VAO[1]);
    //绑定缓冲
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    //填充vbo的数据
    glBufferData(GL_ARRAY_BUFFER, sizeof(another), another, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);//绑定ebo对象
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);//传入数据
    glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);





    //为了让opengl能够使用顶点着色器 首先 我们需要创建一个着色器对象 使用id 来引用 所以我们储存这个顶点着色器 为 unsignint
    //  创建着色器的化用的是glcreate
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);




    //c创建了着色器类型就要把他当成参数送给别的方法  刚刚的参数里面
    //包含的是 gl vertex shader类
    //glshadersource方法会把要编译的着色器对象作为第一个参数 第二个参数指定了传递的源码字符串数量 第三个参数是顶点着色器真正的源码
    glShaderSource(vertexShader,1,&vertexShaderSource, NULL);//这个是将源码赋予这个vertext相当于初始化一下他
    glCompileShader(vertexShader);// 拿去编译 compile是编译的意思


//下面是检测是否成功的代码 
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS,&success);

    //下面是片段着色器的编译
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);//这里是片段着色器的编译
    //和顶点着色器一样 先int 声明 然后再用glcreate创建shader对象 最后用源码带入编译
    glCompileShader(fragmentShader);

    //第二个片段着色器 
    unsigned int fragmentShader222;
    fragmentShader222 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader222, 1, &fragmentShaderSource222, NULL);
    glCompileShader(fragmentShader222);





    //着色器都做完之后要做的是着色器的程序 也就是多个着色器合并后连接起来的版本 一个接着一个
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram(); //也是创建一个程序   然后就是用之前的着色器附加上去
    //最后用glinkprogram链接
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram, fragmentShader);//attach本身就是依附的意思
    glLinkProgram(shaderProgram);
    //这里也可以看看链接着色器程序是否失败 并且获取日志  
    glGetProgramiv(shaderProgram,GL_LINK_STATUS,&success);
    if (!success) {
        glGetShaderInfoLog(shaderProgram,512,NULL,infoLog);
        std::cout << "ERROR::SHADER::VERTEX:COMPILATION_FAILED\n" << infoLog << std::endl;
    }


    unsigned int shaderProgram222;
    shaderProgram222 = glCreateProgram();
    glAttachShader(shaderProgram222, vertexShader);
    glAttachShader(shaderProgram222, fragmentShader222);
    glLinkProgram(shaderProgram222);
    glGetProgramiv(shaderProgram222, GL_LINK_STATUS, &success);






    //刚刚已经创建完了程序对象给shaderprogram 现在要用的话 就需要用gluseprogram函数来激活
    glUseProgram(shaderProgram);
    //此时已经用完了那些着色器对象 所以已经不需要他们俩，此时可以删除
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(fragmentShader222);
    //刚刚只是吧顶点数据发送了出去并且告知让顶点着色器和片段着色器出列他 但是opengl还不知道怎么
    //使用 也就是我们需要解释一下这些顶点坐标


    int vertexColorLocation = glGetUniformLocation(shaderProgram222, "uColor");




    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO[0]);
        // glDrawArrays(GL_TRIANGLES,0,6);//这个是绘制三角形 6代表有6个点进行绘制，虽然有两个三角形重叠了
         //特别的浪费 所以就衍生出特别的手段比如选择某些顶点来进行绘制
        glDrawArrays(GL_TRIANGLES, 0,3);
        glBindVertexArray(0);

        //交替使用着色器
        glUseProgram(shaderProgram222);
        glBindVertexArray(VAO[1]);


        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);


        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


