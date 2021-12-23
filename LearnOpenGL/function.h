#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string.h>

// ��ʼ��Ļ��С
// ------------
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 800;

// ------------------------------------------------------------------------
// Ϊ�˷�����������¼��������ٴ˶���һЩȫ�ֱ��������û����е�һЩ����
// ------------------------------------------------------------------------

// ����ƶ�������
// ------------------------------------------------------------------------
const float sensitivity = 0.05;

// 1. ������ƶ�����
// 2. �����λ��
// 3. ���������
// 4. ��������Ϸ���
// ------------------------------------------------------------------------
const float speed = 3.0f;
// ------------------------------------------------------------------------
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 15.0f);
// ------------------------------------------------------------------------
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
// ------------------------------------------------------------------------
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

// 1. ��ǰ֡����һ֡��ʱ���
// 2. ��һ֡��ʱ��
// ------------------------------------------------------------------------
float deltaTime = 0.0f;
// ------------------------------------------------------------------------
float lastFrame = 0.0f;

// 1. ����ʼλ��
// 2. ȫ��������Ƕ�
// 3. ����һ�μ�¼��ʱ��
// ------------------------------------------------------------------------
float lastX = SCR_WIDTH / 2, lastY = SCR_HEIGHT / 2;
// ------------------------------------------------------------------------
float yaw = -90.0f, pitch = 0;
// ------------------------------------------------------------------------
int firstMouse = 1;

// ͸��ͶӰ�����ӽǣ����ֵ���������Ƕ�
// ------------------------------------------------------------------------
float fov = 45.0f;

// �Ƿ�������·���
// ------------------------------------------------------------------------
bool isFPS = 1;

// 1. �ֵ�Ͳ����
// 2. �ֵ�Ͳ����ǿ��
// ------------------------------------------------------------------------
bool enSpotLight = false;
// ------------------------------------------------------------------------
glm::vec3 spotLight = glm::vec3(1.0f, 1.0f, 1.0f);

// ���Դ����
// ------------------------------------------------------------------------
float brightness = 0.6;

// ����ϳ����ľ���
// ------------------------------------------------------------------------
float chairOutDis = 0.0;

// �����ٶ�(һ��5��)
// ------------------------------------------------------------------------
float fanSpeed = 1.0f;
float lastTime = 0.0f;

// �л���(һ��5����)
// ------------------------------------------------------------------------
int pictureIndex = 0;

// 1. �����ŵ���ת�Ƕ�
// 2. �����ŵ���ת����
// ------------------------------------------------------------------------
float doorRotate = 0.0f;
// ------------------------------------------------------------------------
bool doorFont = 1;

// 1. ��ͷ��ת�Ƕ�
// 2. ��ͷ��ת����
// ------------------------------------------------------------------------
float pillowRotate = 0.0f;
// ------------------------------------------------------------------------
bool pillowFont = 1;

/***************************************************************
 * �ص�����ר��
 * 1. ���ڴ�С�ı�
 * 2. ��ѭ���н��д����������
 * 3. ���̼�������
 * 4. ��갴����������
 * 5. ����ƶ���������
 * 6. �����ּ�������
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
// ������غ���
// funct: ������·����Ϊ�������룬�ɷ���sample2D���͵������ַ
// ------------------------------------------------------------------------
unsigned int loadTexture(const char* path);

// ------------------------------------------------------------------------
// ����������ת����
// funct: ������ת�������������Լ���ת�Ƕȣ����ɸ�����ת����
// ------------------------------------------------------------------------
glm::mat4 RotateArbitraryLine(glm::vec3 v1, glm::vec3 v2, float theta);

/*
* Read File from .vert and .frage
*/
char* readTheFile(std::string strSource);

// ------------------------------------------------------------------------
// ��VAO����
// funct: ����Ӧ�Ķ�������󶨶�Ӧ��VAO
// ------------------------------------------------------------------------
void bindVAO(unsigned int* VBO, unsigned int* VAO, float vertices[], int size);

/**
 * @method �������¼�
 * @description ��ŷ������������������ӽ�����
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
 * @method ������ּ����¼�
 * @description �������������������
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
 * @method ������غ���
 * @description ������·����Ϊ�������룬�ɷ���sample2D���͵������ַ
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
 * @method ����������ת����
 * @description ������ת�������������Լ���ת�Ƕȣ����ɸ�����ת����
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
 * @method ��VAO����
 * @description ����Ӧ�Ķ�������󶨶�Ӧ��VAO
 */
void bindVAO(unsigned int* VBO, unsigned int* VAO, float vertices[], int size)
{
    glGenVertexArrays(1, VAO);
    glGenBuffers(1, VBO);

    glBindVertexArray(*VAO);

    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    // ��λ������
    // --------------------------------------------------------------------------
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // �󶨷�������
    // --------------------------------------------------------------------------
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // ����������
    // --------------------------------------------------------------------------
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

/**
 * @method ���̼����ص�����
 * @description ���ڰ����л������Լ�����ɨ�裬ʹ���ͷŰ����¼���Ϊtrigger�����¼�
 */
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // �л�����ģʽ
    // -------------------------------------------------
    if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
    {
        isFPS = !isFPS;
        if (isFPS)
            std::cout << "Landing~" << std::endl;
        else
            std::cout << "Take Off������" << std::endl;
    }

    // �л�ͼƬ
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

    // �����ֿ���
    // -------------------------------------------------
    if (key == GLFW_KEY_X && action == GLFW_RELEASE)
    {
        doorFont = !doorFont;
        if (doorFont)
            std::cout << "Close Door" << std::endl;
        else
            std::cout << "Open Door" << std::endl;
    }

    // �л���ͷ����
    // -------------------------------------------------
    if (key == GLFW_KEY_R && action == GLFW_RELEASE)
    {
        pillowFont = !pillowFont;
        std::cout << "Pillow Rotate������" << std::endl;
    }
}

/**
 * @method ��갴����������
 * @description ������갴��, ����л��ֵ�Ͳ�ƹ�(����)
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
 * @method ��ѭ�����¼�������
 * @description ���ڴ���ÿ��ѭ���е��¼���
 */
void processInput(GLFWwindow* window)
{

    // �˳�����
    // ---------------------------------------------------
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // ������ƶ�
    // W ǰ��
    // S ����
    // A ����
    // D ����
    // left shift ����
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

    // UP �ϵ��ƹ�����
    // -------------------------------------------------------------------
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && brightness <= 1.0)
        brightness += 0.002;

    // DOWN �µ��ƹ�����
    // -------------------------------------------------------------------
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && brightness >= 0.0)
        brightness -= 0.002;

    // Q �����ƶ�����
    // --------------------------------------------------------------------
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS && chairOutDis <= 1.0)
        chairOutDis += 0.003;

    // E �����ƶ�����
    // --------------------------------------------------------------------
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && chairOutDis >= 0.0)
        chairOutDis -= 0.003;

    // �����ȵ���
    // 1 2 3 4 5 ���ٵ�λ
    // 0 ����ֹͣ
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

    // ���������������е��¼�
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