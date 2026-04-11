#define STB_IMAGE_IMPLEMENTATION
#include <tool/stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <tool/shader.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
std::string Shader::dirName = "";



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


    Shader ourShader("D:/LearnOpenGL/HomeWork/05_Texture/hello_triangle/vertex.glsl",
        "D:/LearnOpenGL/HomeWork/05_Texture/hello_triangle/fragment.glsl");
    // render loop
    // -----------
    //在渲染前要先定义顶点数组
    float vertices[] = {
    // ----位置----       ----颜色---- - 纹理坐标 -
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f,   // 右上
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f,   // 右下
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f    // 左上
    };//因为要渲染的三角形是2d的所以所有三角形的顶
    //点z轴都把他设为0 这样看起来就是一个2d的三角形了

    unsigned int indexes[]{ 0,1,3,
        1,2,3
                   };

        
   //创建VBO对象用于存储大量的顶点，称作顶点缓冲对象
    unsigned int VBO, VAO,EBO;
    glGenBuffers(1,&VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);//这个用来绑定VAO对象
    //绑定缓冲
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    //填充vbo的数据
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//绑定ebo对象
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);//传入数据

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);//这个是颜色属性


    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);//这个是位置属性


    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE , 8*sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);//这个是纹理坐标属性
    glBindVertexArray(0);


    //要存入纹理的话要先声明纹理
    stbi_set_flip_vertically_on_load(true);

    //引入那个纹理库需要先声明箱子的位置宽度 高度 和颜色通道
    int width, height, nrChannels;
    unsigned char* data = stbi_load("D:/LearnOpenGL/static/texture/container.jpg", &width, &height, &nrChannels, 0);
    unsigned int  texture,texture2;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);//这是吧纹理绑定成2d的纹理

    //然后是要为了绑定的纹理对象设置环绕和过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //现在就可以用之前绑定的图片来圣道行纹理了
     if(data) {
         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
         glGenerateMipmap(GL_TEXTURE_2D);
     }
     else {
         std:: cout<< "Failed to load texture" << std::endl;
     }
     stbi_image_free(data);

     ourShader.use();
     ourShader.setInt("texture2", 0);
     ourShader.setInt("texture2",1);




     data = stbi_load("D:/LearnOpenGL/static/texture/awesomeface.png", &width, &height, &nrChannels, 0);
     glGenTextures(1, &texture2);
     glBindTexture(GL_TEXTURE_2D, texture2);//这是吧纹理绑定成2d的纹理

     //然后是要为了绑定的纹理对象设置环绕和过滤方式
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
     //现在就可以用之前绑定的图片来圣道行纹理了
     if (data) {
         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
         glGenerateMipmap(GL_TEXTURE_2D);
     }
     else {
         std::cout << "Failed to load texture" << std::endl;
     }
     stbi_image_free(data); 







    while (!glfwWindowShouldClose(window))
    {

        // input
        processInput(window);


        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.use();
        float timeValue = glfwGetTime();
        
        float xOffset = sin(timeValue);

        float terp = abs(sin(timeValue));
        ourShader.setFloat("xOffset", xOffset);
        ourShader.setFloat("terp", terp);




        // glDrawArrays(GL_TRIANGLES,0,6);//这个是绘制三角形 6代表有6个点进行绘制，虽然有两个三角形重叠了
         //特别的浪费 所以就衍生出特别的手段比如选择某些顶点来进行绘制
        //交替使用着色器

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glBindVertexArray(VAO);


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


