#define STB_IMAGE_IMPLEMENTATION
#include <tool/stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <tool/shader.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

void mouse_callback(GLFWwindow*window,double xpos,double ypos);//这里的的xpos 和ypos就代表了鼠标现在的位置

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
std::string Shader::dirName = "";
void scroll_Callback(GLFWwindow* window, double xoffset, double yoffset);

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);//摄像机位置   
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);//这个是摄像机的指向方向
glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);//用场景远点减去摄像机位置的向量的结果就是
//摄像机的指向向量 但是摄像机指向z轴负方向  但是我们要的是放i昂向量指向摄像机的z轴正方向  i所以取负就行了

//还需要搞一个右向量 用来代表摄像机空间的x轴的正方向  这里有个小妙招
glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);//先定义一个上方向
glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));//再用之前的摄像机指向方向 叉乘一下 就会得到一个
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);



float deltaTime = 0.0f;//当前帧和上一帧的时间差
float lastFrame = 0.0f;//上一帧的时间


float lastX = SCR_WIDTH / 2,
lastY = SCR_HEIGHT/2; //这两个是鼠标的初始位置。将他设置成窗口的中心好了
float yaw = -90.0f;
float pitch = 0.0f;
bool firstMouse = true;//这个是用来更新鼠标初始位置为把鼠标挪进去的位置的一个变量
float fov = 20.0f;



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


    //这里放鼠标移动视角的逻辑  鼠标移动视角是通过检测 这一帧鼠标和上一帧鼠标所在位置的差别，然后转换摄像机位置
    glfwSetCursorPosCallback(window, mouse_callback);//这里是检测鼠标移动 每次移动就callback函数就会欸调用

    glfwSetScrollCallback(window, scroll_Callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    Shader ourShader("D:/LearnOpenGL/HomeWork/07_3D_mvp/hello_triangle/vertex.glsl",
        "D:/LearnOpenGL/HomeWork/07_3D_mvp/hello_triangle/fragment.glsl");
    // render loop
    // -----------
    //在渲染前要先定义顶点数组
    float vertices[] = {
    // ----位置----      - 纹理坐标 -
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };//因为要渲染的三角形是2d的所以所有三角形的顶
    //点z轴都把他设为0 这样看起来就是一个2d的三角形了

    unsigned int indexes[]{ 0,1,2, 3,4,5,
                            6,7,8, 9,10,11,
                            12,13,14, 15,16,17,
                            18,19,20, 21,22,23,
                            24,25,26, 27,28,29,
                            30,31,32, 33,34,35};

    glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
    };//这次一口气整10个立方体



    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);//这个是颜色属性


    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE , 5*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);//这个是纹理坐标属性
    glBindVertexArray(0);





    //要存入纹理的话要先声明纹理
    stbi_set_flip_vertically_on_load(true);

    //引入那个纹理库需要先声明箱子的位置宽度 高度 和颜色通道
    int width, height, nrChannels;
    unsigned char* data = stbi_load("D:/LearnOpenGL/static/texture/container.jpg", &width, &height, &nrChannels, 0);
    unsigned int  texture,texture2,texture3;
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
     ourShader.setInt("texture1", 0);
     ourShader.setInt("texture2",1);
     ourShader.setInt("texture3", 2);




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




     data = stbi_load("C:/Users/夏禹铭/Desktop/u=2433523210,4234610678&fm=253&fmt=auto&app=138&f=JPEG.png", &width, &height, &nrChannels, 0);
     glGenTextures(1, &texture3);
     glBindTexture(GL_TEXTURE_2D, texture3);//这是吧纹理绑定成2d的纹理

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









     //这里是矩阵变换的部分
     unsigned int transform = glGetUniformLocation(ourShader.ID, "transform");

   

     while (!glfwWindowShouldClose(window))
     {

         // input
         processInput(window);



         glEnable(GL_DEPTH_TEST);
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         // render
         // ------
         glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//这是背景颜色
         glClear(GL_COLOR_BUFFER_BIT);//这是每次必须执行的清除上一帧画面

         ourShader.use();
         float timeValue = glfwGetTime();
         float xOffset = sin(timeValue);
         int texIndex = 0;

         //这里来搞daletatime   帧时间
         deltaTime = timeValue - lastFrame;
         lastFrame = timeValue;


         //下面生成一个获取屏幕的鼠标的位置的东西
         double xpos, ypos;
         glfwGetCursorPos(window, &xpos, &ypos);

         float terp = abs(sin(timeValue));
         ourShader.setFloat("xOffset", xOffset);
         ourShader.setFloat("terp", terp);
         ourShader.setInt("texIndex", texIndex);


         
         for (unsigned int i = 0;i < 10;i++)
         {


             //这里放3d板块
             //模型矩阵
             glm::mat4 model = glm::mat4(1.0f);
             model = glm::translate(model, cubePositions[i]);

             if (i == 0 || i % 3 == 0) {
             model = glm::rotate(model, timeValue * 5, glm::vec3(0.5f, 1.0f, 0.0f));
         }

         //观察矩阵
         glm::mat4 view = glm::mat4(1.0f);;
   
         float radius = 10.0f;
         float camX = sin(timeValue) * radius;
         float camY = cos(timeValue) * radius;
         view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

         //投影矩阵
         glm::mat4 projection = glm::mat4(1.0f);
         projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

         int modelLoc = glGetUniformLocation(ourShader.ID, "model");
         glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


         int viewLoc = glGetUniformLocation(ourShader.ID, "view");
         glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

         int projectionLoc = glGetUniformLocation(ourShader.ID, "projection");
         glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));




         glm::mat4 trans = glm::mat4(1.0f);

         float chaos = sin(timeValue * 1.7f) + sin(timeValue * 3.13f) + sin(timeValue * 7.43f);

         trans = glm::scale(trans, glm::vec3(terp*chaos, terp*chaos*2, terp*chaos*0.6));

         glUniformMatrix4fv(transform, 1, GL_FALSE, glm::value_ptr(trans));//这里是自己将声明好的矩阵送给shader

         // glDrawArrays(GL_TRIANGLES,0,6);//这个是绘制三角形 6代表有6个点进行绘制，虽然有两个三角形重叠了
          //特别的浪费 所以就衍生出特别的手段比如选择某些顶点来进行绘制
         //交替使用着色器

         glActiveTexture(GL_TEXTURE0);
         glBindTexture(GL_TEXTURE_2D, texture);

         glActiveTexture(GL_TEXTURE1);
         glBindTexture(GL_TEXTURE_2D, texture2);

         glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
     }
        texIndex = 1;

        ourShader.setInt("texIndex", texIndex);

        // ---- 绘制texture3 ----
        glm::mat4 transManba = glm::mat4(1.0f);

        transManba = glm::translate(transManba, glm::vec3(0.5f, 0.0f, 0.0f)); // 平移到右边
        transManba = glm::scale(transManba, glm::vec3(terp, terp, terp));    

        glUniformMatrix4fv(transform, 1, GL_FALSE, glm::value_ptr(transManba));

        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, texture3);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);


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
void processInput(GLFWwindow* window)//这里用来检测按了哪些按键
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = 2.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


void mouse_callback(GLFWwindow* window, double xpos, double ypos){//这个是放了鼠标之后的逻辑 里面放着旋转视角的逻辑
 
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;

    }


    glm::vec3 direction;

    direction.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    direction.y = sin(glm::radians(pitch));
    direction.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos ;
    lastX = xpos;
    lastY = ypos;
    float sensitivity = 0.05f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    yaw += xoffset;
    pitch += yoffset;
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    front.y = sin(glm::radians(pitch));
    front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    cameraFront = glm::normalize(front);



}

void scroll_Callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (fov >= 1.0f && fov <= 45.0f)
        fov -= yoffset;
    if (fov <= 1.0f)
        fov = 1.0f;
    if (fov >= 45.0f)
        fov = 45.0f;
}