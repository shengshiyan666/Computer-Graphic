#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string.h>

// 初始屏幕大小
// ------------
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 800;

// ------------------------------------------------------------------------
// 为了方便监听流程事件，我们再此定义一些全局变量来设置环境中的一些参数
// ------------------------------------------------------------------------

// 鼠标移动灵敏度
// ------------------------------------------------------------------------
const float sensitivity = 0.05;

// 1. 摄像机移动速率
// 2. 摄像机位置
// 3. 摄像机朝向
// 4. 摄像机正上方向
// ------------------------------------------------------------------------
const float speed = 3.0f;
// ------------------------------------------------------------------------
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 15.0f);
// ------------------------------------------------------------------------
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
// ------------------------------------------------------------------------
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

// 1. 当前帧与上一帧的时间差
// 2. 上一帧的时间
// ------------------------------------------------------------------------
float deltaTime = 0.0f;
// ------------------------------------------------------------------------
float lastFrame = 0.0f;

// 1. 鼠标初始位置
// 2. 全局摄像机角度
// 3. 鼠标第一次记录的时候
// ------------------------------------------------------------------------
float lastX = SCR_WIDTH / 2, lastY = SCR_HEIGHT / 2;
// ------------------------------------------------------------------------
float yaw = -90.0f, pitch = 0;
// ------------------------------------------------------------------------
int firstMouse = 1;

// 透视投影矩阵视角，滚轮调整摄像机角度
// ------------------------------------------------------------------------
float fov = 45.0f;

// 是否可以上下飞行
// ------------------------------------------------------------------------
bool isFPS = 1;

// 1. 手电筒开关
// 2. 手电筒关照强度
// ------------------------------------------------------------------------
bool enSpotLight = false;
// ------------------------------------------------------------------------
glm::vec3 spotLight = glm::vec3(1.0f, 1.0f, 1.0f);

// 点光源亮度
// ------------------------------------------------------------------------
float brightness = 0.6;

// 板凳拖出来的距离
// ------------------------------------------------------------------------
float chairOutDis = 0.0;

// 风扇速度(一共5档)
// ------------------------------------------------------------------------
float fanSpeed = 1.0f;
float lastTime = 0.0f;

// 切换画(一共5幅画)
// ------------------------------------------------------------------------
int pictureIndex = 0;

// 1. 升降门的旋转角度
// 2. 升降门的旋转方向
// ------------------------------------------------------------------------
float doorRotate = 0.0f;
// ------------------------------------------------------------------------
bool doorFont = 1;

// 1. 枕头旋转角度
// 2. 枕头旋转方向
// ------------------------------------------------------------------------
float pillowRotate = 0.0f;
// ------------------------------------------------------------------------
bool pillowFont = 1;

/***************************************************************
 * 回调函数专区
 * 1. 窗口大小改变
 * 2. 主循环中进行处理的主函数
 * 3. 键盘监听函数
 * 4. 鼠标按键监听函数
 * 5. 鼠标移动监听函数
 * 6. 鼠标滚轮监听函数
****************************************************************/
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// ------------------------------------------------------------------------
void processInput(GLFWwindow* window);
// ------------------------------------------------------------------------
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
// ------------------------------------------------------------------------
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
// ------------------------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
// ------------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// ------------------------------------------------------------------------
// 纹理加载函数
// funct: 将纹理路径作为参数传入，可返回sample2D类型的纹理地址
// ------------------------------------------------------------------------
unsigned int loadTexture(const char* path);

// ------------------------------------------------------------------------
// 绕任意轴旋转函数
// funct: 给定旋转轴上任意两点以及旋转角度，即可给出旋转矩阵
// ------------------------------------------------------------------------
glm::mat4 RotateArbitraryLine(glm::vec3 v1, glm::vec3 v2, float theta);

/*
* Read File from .vert and .frage
*/
char* readTheFile(std::string strSource);

// ------------------------------------------------------------------------
// 绑定VAO函数
// funct: 给对应的顶点数组绑定对应的VAO
// ------------------------------------------------------------------------
void bindVAO(unsigned int* VBO, unsigned int* VAO, float vertices[], int size);

/**
 * @method 鼠标监听事件
 * @description 用欧拉角来处理摄像机的视角问题
 */
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

/**
 * @method 处理滚轮监听事件
 * @description 调整摄像机的视域问题
 */
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (fov >= 1.0f && fov <= 45.0f)
        fov -= yoffset;
    if (fov <= 1.0f)
        fov = 1.0f;
    if (fov >= 45.0f)
        fov = 45.0f;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

/**
 * @method 纹理加载函数
 * @description 将纹理路径作为参数传入，可返回sample2D类型的纹理地址
 */
unsigned int loadTexture(char const* path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

/**
 * @method 绕任意轴旋转函数
 * @description 给定旋转轴上任意两点以及旋转角度，即可给出旋转矩阵
 */
glm::mat4 RotateArbitraryLine(glm::vec3 v1, glm::vec3 v2, float theta)
{
    glm::mat4 rmatrix;
    float a = v1.x;
    float b = v1.y;
    float c = v1.z;

    glm::vec3 p1 = v2 - v1;
    glm::vec3 p = glm::normalize(p1);

    float u = p.x;
    float v = p.y;
    float w = p.z;

    float uu = u * u;
    float uv = u * v;
    float uw = u * w;
    float vv = v * v;
    float vw = v * w;
    float ww = w * w;
    float au = a * u;
    float av = a * v;
    float aw = a * w;
    float bu = b * u;
    float bv = b * v;
    float bw = b * w;
    float cu = c * u;
    float cv = c * v;
    float cw = c * w;

    float costheta = glm::cos(theta);
    float sintheta = glm::sin(theta);

    rmatrix[0][0] = uu + (vv + ww) * costheta;
    rmatrix[0][1] = uv * (1 - costheta) + w * sintheta;
    rmatrix[0][2] = uw * (1 - costheta) - v * sintheta;
    rmatrix[0][3] = 0;

    rmatrix[1][0] = uv * (1 - costheta) - w * sintheta;
    rmatrix[1][1] = vv + (uu + ww) * costheta;
    rmatrix[1][2] = vw * (1 - costheta) + u * sintheta;
    rmatrix[1][3] = 0;

    rmatrix[2][0] = uw * (1 - costheta) + v * sintheta;
    rmatrix[2][1] = vw * (1 - costheta) - u * sintheta;
    rmatrix[2][2] = ww + (uu + vv) * costheta;
    rmatrix[2][3] = 0;

    rmatrix[3][0] = (a * (vv + ww) - u * (bv + cw)) * (1 - costheta) + (bw - cv) * sintheta;
    rmatrix[3][1] = (b * (uu + ww) - v * (au + cw)) * (1 - costheta) + (cu - aw) * sintheta;
    rmatrix[3][2] = (c * (uu + vv) - w * (au + bv)) * (1 - costheta) + (av - bu) * sintheta;
    rmatrix[3][3] = 1;

    return rmatrix;
}

/**
 * @method 绑定VAO函数
 * @description 给对应的顶点数组绑定对应的VAO
 */
void bindVAO(unsigned int* VBO, unsigned int* VAO, float vertices[], int size)
{
    glGenVertexArrays(1, VAO);
    glGenBuffers(1, VBO);

    glBindVertexArray(*VAO);

    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    // 绑定位置属性
    // --------------------------------------------------------------------------
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 绑定法线属性
    // --------------------------------------------------------------------------
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // 绑定纹理属性
    // --------------------------------------------------------------------------
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

/**
 * @method 键盘监听回调函数
 * @description 鉴于案件切换功能以及键盘扫描，使用释放按键事件作为trigger触发事件
 */
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // 切换飞行模式
    // -------------------------------------------------
    if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
    {
        isFPS = !isFPS;
        if (isFPS)
            std::cout << "Landing~" << std::endl;
        else
            std::cout << "Take Off！！！" << std::endl;
    }

    // 切换图片
    // -------------------------------------------------
    if (key == GLFW_KEY_Z && action == GLFW_RELEASE)
    {
        pictureIndex = (pictureIndex + 1) % 5;
        std::cout << "Next Picture" << std::endl;
    }
    if (key == GLFW_KEY_C && action == GLFW_RELEASE)
    {
        pictureIndex = (pictureIndex == 0) ? 4 : pictureIndex - 1;
        std::cout << "Previous Picture" << std::endl;
    }

    // 开启仓库门
    // -------------------------------------------------
    if (key == GLFW_KEY_X && action == GLFW_RELEASE)
    {
        doorFont = !doorFont;
        if (doorFont)
            std::cout << "Close Door" << std::endl;
        else
            std::cout << "Open Door" << std::endl;
    }

    // 切换枕头翻滚
    // -------------------------------------------------
    if (key == GLFW_KEY_R && action == GLFW_RELEASE)
    {
        pillowFont = !pillowFont;
        std::cout << "Pillow Rotate！！！" << std::endl;
    }
}

/**
 * @method 鼠标按键监听函数
 * @description 监听鼠标按键, 左键切换手电筒灯光(开关)
 */
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        enSpotLight = !enSpotLight;
        if (enSpotLight)
            std::cout << "Open Flashlight" << std::endl;
        else
            std::cout << "Close Flashlight" << std::endl;
    }
}

/**
 * @method 主循环中事件处理函数
 * @description 用于处理每次循环中的事件流
 */
void processInput(GLFWwindow* window)
{

    // 退出窗口
    // ---------------------------------------------------
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // 摄像机移动
    // W 前进
    // S 后退
    // A 左移
    // D 右移
    // left shift 加速
    // -------------------------------------------------------------------
    float cameraSpeed = deltaTime * speed; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        cameraPos += cameraSpeed * cameraFront;
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            cameraPos += cameraSpeed * cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        cameraPos -= cameraSpeed * cameraFront;
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            cameraPos -= cameraSpeed * cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }

    // UP 上调灯光亮度
    // -------------------------------------------------------------------
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && brightness <= 1.0)
        brightness += 0.002;

    // DOWN 下调灯光亮度
    // -------------------------------------------------------------------
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && brightness >= 0.0)
        brightness -= 0.002;

    // Q 向右移动椅子
    // --------------------------------------------------------------------
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS && chairOutDis <= 1.0)
        chairOutDis += 0.003;

    // E 向左移动椅子
    // --------------------------------------------------------------------
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && chairOutDis >= 0.0)
        chairOutDis -= 0.003;

    // 给风扇调速
    // 1 2 3 4 5 风速档位
    // 0 风扇停止
    // ----------------------------------------------
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        fanSpeed = 2.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        fanSpeed = 4.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        fanSpeed = 6.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
    {
        fanSpeed = 8.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
    {
        fanSpeed = 10.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
    {
        fanSpeed = 0.0f;
    }

    // 处理按键监听函数中的事件
    // ------------------------
    if (isFPS)
        cameraPos.y = 0.7f;
    if (enSpotLight)
        spotLight = glm::vec3(1.0f, 1.0f, 1.0f);
    else
        spotLight = glm::vec3(0.0f, 0.0f, 0.0f);

    if (doorRotate < 0.0 && doorFont)
    {
        doorRotate += deltaTime * 0.8;
    }
    else if (doorRotate > -1.57 && !doorFont)
    {
        doorRotate -= deltaTime * 0.8;
    }

    if (pillowRotate < 0.0 && pillowFont)
    {
        pillowRotate += deltaTime * 3.0;
    }
    else if (pillowRotate > -1.57 && !pillowFont)
    {
        pillowRotate -= deltaTime * 3.0;
    }
}

/*
 * @method Read the file from .vert and .frage function 
*/
char* readTheFile(std::string strSource) {
    std::ifstream t(strSource);
    std::string str((std::istreambuf_iterator<char>(t)),
        std::istreambuf_iterator<char>());

    int len = str.length();
    char* result = new char[len];
    strcpy_s(result, len + 1, str.c_str());
    return result;
}