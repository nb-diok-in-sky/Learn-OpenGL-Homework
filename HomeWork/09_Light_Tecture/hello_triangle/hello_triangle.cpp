#define GLM_FORCE_PURE 
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

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);//这里是光源的位置的全局变量



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


    Shader ourShader("D:/LearnOpenGL/HomeWork/09_Light_Tecture/hello_triangle/vertex.glsl",
        "D:/LearnOpenGL/HomeWork/09_Light_Tecture/hello_triangle/fragment.glsl");

    Shader lightingShader("D:/LearnOpenGL/HomeWork/09_Light_Tecture/hello_triangle/light_object_vert.glsl",
        "D:/LearnOpenGL/HomeWork/09_Light_Tecture/hello_triangle/light_object_frag.glsl");




    // render loop
    // -----------
    //在渲染前要先定义顶点数组
    float vertices[] = {
        // ----位置----          - 法线坐标 -        - 纹理坐标 -
         -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f

    };//因为要渲染的三角形是2d的所以所有三角形的顶
    //点z轴都把他设为0 这样看起来就是一个2d的三角形了

    unsigned int indexes[]{ 0,1,2, 3,4,5,
                            6,7,8, 9,10,11,
                            12,13,14, 15,16,17,
                            18,19,20, 21,22,23,
                            24,25,26, 27,28,29,
                            30,31,32, 33,34,35 };


    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    //创建VBO对象用于存储大量的顶点，称作顶点缓冲对象
    unsigned int VBO, VAO, EBO;

    unsigned int lightVAO;

    //先绑定主要的vao
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);//这个用来绑定VAO对象
    //绑定缓冲
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //填充vbo的数据
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//绑定ebo对象
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);//传入数据

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);//这个是顶点属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);//这个是法线指向
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);  //这个是纹理坐标uv
    glBindVertexArray(0);






    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(0);
    glBindVertexArray(0);





    ourShader.use();

    //这里放材质的参数
    ourShader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
    ourShader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
    ourShader.setInt("material.specular", 1);
    ourShader.setFloat("material.shininess", 32.0f);
    ourShader.setInt("material.diffuse", 0);
    ourShader.setVec3("lightPos", lightPos);
    ourShader.setInt("texture1",0);



    //这里放纹理板块

    unsigned int diffuseMap;
    unsigned int specularMap;

    glGenTextures(1, &diffuseMap);
    glGenTextures(1,&specularMap);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    int width, height, nrChannels;//分别是纹理的宽高和通道数量（rgb or  rgba）
    unsigned char* data1 = stbi_load("D:/LearnOpenGL/static/texture/container2.png", &width, &height, &nrChannels, 0);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuseMap);

    if (data1) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data1);
        glGenerateMipmap(GL_TEXTURE_2D);

    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;

    }
    stbi_image_free(data1);



    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, specularMap);





    unsigned char* data2 = stbi_load("D:/LearnOpenGL/static/texture/container2_specular.png",&width,&height,&nrChannels,0);
    if (data2) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture_specular" << std::endl;

    }
    stbi_image_free(data2);

    



     glEnable(GL_DEPTH_TEST);
     //设置光源位置
     while (!glfwWindowShouldClose(window))
     {

         float timeValue = glfwGetTime();

         //这里来搞daletatime   帧时间
         deltaTime = timeValue - lastFrame;
         lastFrame = timeValue;
         // input
         processInput(window);

         // ------
         glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//这是背景颜色

         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         // render;//这是每次必须执行的清除上一帧画面

       
         //下面生成一个获取屏幕的鼠标的位置的东西
         double xpos, ypos;
         glfwGetCursorPos(window, &xpos, &ypos);

         float terp = abs(sin(timeValue));
  
         //传递摄像机的位置
         ourShader.setVec3("viewPos", cameraPos);//用来搞镜面反射


         //这里放3d板块
         //模型矩阵
         glm::mat4 model = glm::mat4(1.0f);
         //观察矩阵
         glm::mat4 view = glm::mat4(1.0f);;

         float radius = 10.0f;
         float camX = sin(timeValue) * radius;
         float camY = cos(timeValue) * radius;
         view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

         //投影矩阵
         glm::mat4 projection = glm::mat4(1.0f);
         projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);



         //   接下来先绘制橙色的箱子  先把颜色传进去
         ourShader.use(); 
         //然后把位置传入进去
         ourShader.setMat4("projection", projection);
         ourShader.setMat4("view", view);
         ourShader.setMat4("model", model);


         //这里放光源的控制 漫反射的控制
         glm::vec3 lightColor;
         lightColor.x = sin(timeValue * 2.0f);
         lightColor.y = sin(timeValue * 0.7f);
         lightColor.z = sin(timeValue * 1.3f);

         glm::vec3 diffuseColor = lightColor * glm::vec3(1.0f);
         glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);


      /*   ourShader.setVec3("light.ambient", ambientColor);
         ourShader.setVec3("light.diffuse", diffuseColor);
         ourShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
*/
         ourShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
         ourShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
         ourShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);



         glBindVertexArray(VAO);
         glDrawArrays(GL_TRIANGLES, 0, 36);
         glBindVertexArray(0);



         //   接下来先绘制白色的的光源 这个只需要关注一下位置就行了
         //然后把位置传入进去
         model = glm::mat4(1.0f);
         model = glm::translate(model, lightPos);
         model = glm::scale(model, glm::vec3(0.2f));

         lightingShader.use();
         lightingShader.setVec4("lightColor",glm::vec4(lightColor,1.0f));
         lightingShader.setMat4("projection", projection);
         lightingShader.setMat4("view", view);
         lightingShader.setMat4("model", model);
         glBindVertexArray(lightVAO);

         glDrawArrays(GL_TRIANGLES, 0, 36);
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