#define STB_IMAGE_IMPLEMENTATION
#include "tool/mesh.h"
#include"tool/model.h"
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



glm::vec2 translations[100];


//就在此处导入岩石和行星模型

Model Rock("D:/LearnOpenGL/static/model/rock/rock.obj");
Model Planet("D:/LearnOpenGL/static/model/planet/planet.obj");


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


    Shader ourShader("D:/LearnOpenGL/HomeWork/18_planet/hello_triangle/vertex.glsl",
        "D:/LearnOpenGL/HomeWork/18_planet/hello_triangle/fragment.glsl");





float quadVertices[] = {
    // 位置          // 颜色
    -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
     0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
    -0.05f, -0.05f,  0.0f, 0.0f, 1.0f,

    -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
     0.05f, -0.05f,  0.0f, 1.0f, 0.0f,   
     0.05f,  0.05f,  0.0f, 1.0f, 1.0f                   
};  


int index = 0;
float offset = 0.1f;
for (int y = -10; y < 10; y += 2) {

    for (int x = -10; x < 10; x += 2)
    {
        glm::vec2 translation;
        translation.x = (float)x / 10.0f + offset;
        translation.y = (float)y / 10.0f + offset;
        translations[index++] = translation;

    }
}





    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


   //创建VBO对象用于存储大量的顶点，称作顶点缓冲对象
    unsigned int VBO, VAO, instanceVBO;
    glGenBuffers(1,&VBO);   
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);//这个用来绑定VAO对象
    //绑定缓冲
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    //填充vbo的数据
    glBufferData(GL_ARRAY_BUFFER,sizeof(quadVertices),quadVertices,GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);//这个是顶点属性
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);//这个是选择三角形的颜色
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2*sizeof(float)));




    glGenBuffers(1, &instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 100, &translations[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(2, 1);




    //要存入纹理的话要先声明纹理
    stbi_set_flip_vertically_on_load(true);

  


    glEnable(GL_DEPTH_TEST);





    //这里放置有关行星和岩石的矩阵变换
    unsigned int amount = 1000;
    glm::mat4* modelMatrices;
    modelMatrices = new glm::mat4[amount];
    srand(glfwGetTime());
    float radius = 50.0;
    float offset = 2.5f;
    for (unsigned int i = 0; i < amount; i++)
    {
        glm::mat4 model;
        // 1. 位移：分布在半径为 'radius' 的圆形上，偏移的范围是 [-offset, offset]
        float angle = (float)i / (float)amount * 360.0f;
        float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float x = sin(angle) * radius + displacement;
        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float y = displacement * 0.4f; // 让行星带的高度比x和z的宽度要小
        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float z = cos(angle) * radius + displacement;
        model = glm::translate(model, glm::vec3(x, y, z));

        // 2. 缩放：在 0.05 和 0.25f 之间缩放
        float scale = (rand() % 20) / 100.0f + 0.05;
        model = glm::scale(model, glm::vec3(scale));

        // 3. 旋转：绕着一个（半）随机选择的旋转轴向量进行随机的旋转
        float rotAngle = (rand() % 360);
        model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

        // 4. 添加到矩阵的数组中
        modelMatrices[i] = model;
    }






     while (!glfwWindowShouldClose(window))
     {

         // input
         processInput(window);



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


         ourShader.setFloat("time", terp);


         glBindVertexArray(VAO);
       
         glm::mat4 model;
         model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
         model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
         ourShader.setMat4("model", model);
         Planet.Draw(ourShader);
        
         //岩石的绘制
         for (unsigned int i = 0; i < amount; i++) {
             ourShader.setMat4("model", modelMatrices[i]);
             Rock.Draw(ourShader);
         }

     


     

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