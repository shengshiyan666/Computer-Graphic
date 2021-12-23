#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>
#include <fstream>
#define STB_IMAGE_IMPLEMENTATION
#include <stbi/stb_image.h>
#include <shader.h>
#include <function.h>
#include <vertex.h>
#include <glsl.h>

int main()
{
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Greate GLFW window
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Xiao", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Register CallBack function
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: ���صײ�OpenGL����ָ��
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // ����ȫ�ֱ���
    // ������Ȳ���
    // ������GammaУ��
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_FRAMEBUFFER_SRGB);

    // ����Shader��(��װ�õ���ɫ������)
    Shader* cubeProgram = new Shader(vertexShaderSource, fragmentShaderSource);
    // ------------------------------------------------------------------------
    Shader* lightProgram = new Shader(lightVertexShaderSource, lightFragmentShaderSource);
    // ------------------------------------------------------------------------
    Shader* floorProgram = new Shader(vertexShaderSource, fragmentShaderSource);
    // ------------------------------------------------------------------------
    Shader* wallProgram = new Shader(vertexShaderSource, fragmentShaderSource);
    // ------------------------------------------------------------------------
    Shader* innerWallProgram = new Shader(vertexShaderSource, fragmentShaderSource);

    // �������嶥����������
    // --------------------------
    unsigned int cubeVBO, cubeVAO;
    bindVAO(&cubeVBO, &cubeVAO, vertices, sizeof(vertices));

    // �󶨵ƹⶥ����������
    // --------------------------
    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // �󶨵ذ嶥����������
    // --------------------------
    unsigned int floorVBO, floorVAO;
    bindVAO(&floorVBO, &floorVAO, floorVertices, sizeof(floorVertices));

    // ��ǽ�ڶ�����������
    // --------------------------
    unsigned int wallVBO, wallVAO;
    bindVAO(&wallVBO, &wallVAO, wallVertices, sizeof(wallVertices));

    // ����ǽ�ڶ�����������
    // --------------------------
    unsigned int innerWallVBO, innerWallVAO;
    bindVAO(&innerWallVBO, &innerWallVAO, innerWallVertices, sizeof(innerWallVertices));

    // ��ͼƬ������������
    // --------------------------
    unsigned int pictureVBO, pictureVAO;
    bindVAO(&pictureVBO, &pictureVAO, pictureVertices, sizeof(pictureVertices));

    // ���Ŷ�����������
    // --------------------------
    unsigned int doorVBO, doorVAO;
    bindVAO(&doorVBO, &doorVAO, doorVertices, sizeof(doorVertices));

    // ���ű��涥����������
    // --------------------------
    unsigned int doorBackVBO, doorBackVAO;
    bindVAO(&doorBackVBO, &doorBackVAO, doorBackVertices, sizeof(doorBackVertices));

    // ���ſ��ϲ�������������
    // --------------------------
    unsigned int doorTopFrameVBO, doorTopFrameVAO;
    bindVAO(&doorTopFrameVBO, &doorTopFrameVAO, doorTopFrameVertices, sizeof(doorTopFrameVertices));

    // ���ſ��ϲ����涥����������
    // --------------------------
    unsigned int doorTopFrameBackVBO, doorTopFrameBackVAO;
    bindVAO(&doorTopFrameBackVBO, &doorTopFrameBackVAO, doorTopFrameBackVertices, sizeof(doorTopFrameBackVertices));

    // ��������
    // ----------------------------------------------------------------------------
    cubeProgram->use();
    unsigned int texture1 = loadTexture("resources\\textures\\container2.png");
    unsigned int texture2 = loadTexture("resources\\textures\\container2_specular.png");
    unsigned int tableTexture = loadTexture("resources\\textures\\table.jpg");
    unsigned int pillowTexture = loadTexture("resources\\textures\\pillow.jpg");
    // ----------------------------------------------------------------------------

    // ----------------------------------------------------------------------------
    floorProgram->use();
    unsigned int floorTexture = loadTexture("resources\\textures\\floor2.jpg");
    unsigned int pictureFrameTexture = loadTexture("resources\\textures\\frame.jpg");
    unsigned int pictureTexture1 = loadTexture("resources\\textures\\picture1.jpg");
    unsigned int pictureTexture2 = loadTexture("resources\\textures\\picture2.jpg");
    unsigned int pictureTexture3 = loadTexture("resources\\textures\\picture3.jpg");
    unsigned int pictureTexture4 = loadTexture("resources\\textures\\picture4.jpg");
    unsigned int pictureTexture5 = loadTexture("resources\\textures\\picture5.jpg");
    unsigned int doorTexture = loadTexture("resources\\textures\\Mercator-projection.jpg");
    // ----------------------------------------------------------------------------

    // ----------------------------------------------------------------------------
    wallProgram->use();
    unsigned int wallTexture = loadTexture("resources\\textures\\brickwall.jpg");
    // ----------------------------------------------------------------------------

    // ----------------------------------------------------------------------------
    innerWallProgram->use();
    unsigned int innerWallTexture = loadTexture("resources\\textures\\innerwall2.jpg");
    // ----------------------------------------------------------------------------

    // �¼���ѭ��
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // �����������֮֡���ʱ��
        // ------------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // �����������
        // ------------------------
        lastTime = lastTime + deltaTime * fanSpeed;

        // ���������¼��Ĵ���
        // ------------------------
        processInput(window);

        // ���������������Ӧ������
        // -----------------------------
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, floorTexture);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, wallTexture);
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, innerWallTexture);
        glActiveTexture(GL_TEXTURE5);
        glBindTexture(GL_TEXTURE_2D, tableTexture);
        glActiveTexture(GL_TEXTURE6);
        glBindTexture(GL_TEXTURE_2D, pictureFrameTexture);
        glActiveTexture(GL_TEXTURE7);
        glBindTexture(GL_TEXTURE_2D, pictureTexture1);
        glActiveTexture(GL_TEXTURE8);
        glBindTexture(GL_TEXTURE_2D, pictureTexture2);
        glActiveTexture(GL_TEXTURE9);
        glBindTexture(GL_TEXTURE_2D, pictureTexture3);
        glActiveTexture(GL_TEXTURE10);
        glBindTexture(GL_TEXTURE_2D, pictureTexture4);
        glActiveTexture(GL_TEXTURE11);
        glBindTexture(GL_TEXTURE_2D, pictureTexture5);
        glActiveTexture(GL_TEXTURE12);
        glBindTexture(GL_TEXTURE_2D, doorTexture);
        glActiveTexture(GL_TEXTURE14);
        glBindTexture(GL_TEXTURE_2D, pillowTexture);

        // ѭ�����
        // --------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // ������������س���
        // -----------------------------
        cubeProgram->use();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

        // �����ֵ�Ͳ��Դ
        // -----------------------------
        cubeProgram->setVec3("spotLight.position", cameraPos);
        cubeProgram->setVec3("spotLight.direction", cameraFront);
        cubeProgram->setFloat("spotLight.innerCutOff", glm::cos(glm::radians(12.5f)));
        cubeProgram->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(17.5f)));
        cubeProgram->setFloat("spotLight.constant", 1.0f);
        cubeProgram->setFloat("spotLight.linear", 0.09f);
        cubeProgram->setFloat("spotLight.quadratic", 0.02f);
        cubeProgram->setVec3("spotLight.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
        cubeProgram->setVec3("spotLight.diffuse", spotLight);
        cubeProgram->setVec3("spotLight.specular", spotLight);

        // ����ֱ�չ�Դ
        // -----------------------------
        cubeProgram->setVec3("dirLight.direction", glm::vec3(0.0f, 1.0f, 0.0f));
        cubeProgram->setVec3("dirLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
        cubeProgram->setVec3("dirLight.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
        cubeProgram->setVec3("dirLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));

        // ���õ��Դ
        // -----------------------------
        for (int i = 0; i < 6; ++i)
        {
            std::string index = std::to_string(i);
            cubeProgram->setVec3("pointLights[" + index + "].position", pointLightPositions[i]);
            cubeProgram->setFloat("pointLights[" + index + "].constant", 1.0f);
            cubeProgram->setFloat("pointLights[" + index + "].linear", 0.09f);
            cubeProgram->setFloat("pointLights[" + index + "].quadratic", 0.02f);
            cubeProgram->setVec3("pointLights[" + index + "].ambient", glm::vec3(0.1f, 0.1f, 0.1f));
            cubeProgram->setVec3("pointLights[" + index + "].diffuse", glm::vec3(0.9648f, 0.9297f, 0.8359f) * glm::vec3(brightness * 0.5));
            cubeProgram->setVec3("pointLights[" + index + "].specular", glm::vec3(0.9648f, 0.9297f, 0.8359f) * glm::vec3(brightness));
        }

        // ���ò����Լ��۲��
        // -----------------------------
        cubeProgram->setVec3("viewPos", cameraPos);
        cubeProgram->setInt("material.diffuse", 0);
        cubeProgram->setInt("material.specular", 1);
        cubeProgram->setFloat("material.shininess", 64.0f);

        // ����ģ�ͱ任����, �۲����, ͸��ͶӰ����
        // ----------------------------------------
        cubeProgram->setMat4("model", model);
        cubeProgram->setMat4("view", view);
        cubeProgram->setMat4("projection", projection);

        // ������Χ�ĸ�ľ����
        // -----------------------------
        glBindVertexArray(cubeVAO);
        for (int i = 0; i < 4; ++i)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            cubeProgram->setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // ��������
        // -----------------------------
        cubeProgram->setInt("material.diffuse", 5);
        cubeProgram->setInt("material.specular", 5);

        for (int i = 0; i < 3; ++i)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, tablePositions[i]);
            model = glm::scale(model, tableVolumes[i]); // Make it a smaller cube
            cubeProgram->setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // ��������
        // -----------------------------
        for (int i = 0; i < 10; ++i)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(-0.7f * chairOutDis, 0.0f, 0.0f));
            model = glm::translate(model, chairPositions[i]);
            model = glm::scale(model, chairVolumes[i]); // Make it a smaller cube
            cubeProgram->setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // ���ƴ�
        // -----------------------------
        for (int i = 0; i < 2; ++i)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, bedPositions[i]);
            model = glm::scale(model, bedVolumes[i]); // Make it a smaller cube
            cubeProgram->setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // ������ͷ
        // -----------------------------
        cubeProgram->setInt("material.diffuse", 14);
        cubeProgram->setInt("material.specular", 14);
        model = glm::mat4(1.0f);
        model = RotateArbitraryLine(glm::vec3(-3.625f, -0.1f, 0.0f), glm::vec3(-3.625f, -0.1f, 1.0f), pillowRotate);
        model = glm::translate(model, glm::vec3(-3.7f, -0.025f, -0.7f));
        model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.6f)); // Make it a smaller cube
        cubeProgram->setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // ���Ƶ�����Ҷ
        // -----------------------------
        glBindVertexArray(cubeVAO);
        cubeProgram->setInt("material.diffuse", 4);
        cubeProgram->setInt("material.specular", 4);
        glm::mat4 route;
        for (int i = 0; i < 4; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, fanPositions[i]);
            model = glm::scale(model, fanVolumes[i]); // Make it a smaller cube
            route = RotateArbitraryLine(glm::vec3(0.0f), glm::vec3(0.0f, 0.1f, 0.0f), lastTime);
            model = route * model;
            cubeProgram->setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // �����ƹ���س���
        // -----------------------------
        lightProgram->use();

        // ����ģ�ͱ任����, �۲����, ͸��ͶӰ����
        // ----------------------------------------
        model = glm::mat4(1.0f);
        lightProgram->setMat4("view", view);
        lightProgram->setMat4("projection", projection);
        lightProgram->setVec3("lightColor", glm::vec3(0.9648f, 0.9297f, 0.8359f) * glm::vec3(brightness));

        // ���Ƶƹ�
        // ----------------------------------------
        glBindVertexArray(lightVAO);
        for (unsigned int i = 0; i <= 30; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            glm::mat4 route;

            // ������Χ�ĸ��ƹ�
            // ----------------------------------------
            if (i > 0 && i < 6)
            {
                model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
                model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
            }

            // ���Ƶ���
            // ----------------------------------------
            else if (i == 0)
            {
                model = glm::scale(model, pointLightVolumes[i]); // Make it a smaller cube
                route = RotateArbitraryLine(glm::vec3(0.0f), glm::vec3(0.0f, 0.1f, 0.0f), lastTime);
                model = route * model;
            }

            // ������Ȧװ�εƹ�
            // ----------------------------------------
            else if (i > 5 && i < 18)
            {
                model = glm::scale(model, glm::vec3(0.4f));
                route = RotateArbitraryLine(glm::vec3(0.0f, 6.0f, 0.0f), glm::vec3(0.0f, 6.0f, 1.0f), lastFrame);
                model = route * model;
            }

            // ���ƴ���Ȧװ�εƹ�
            // ----------------------------------------
            else if (i >= 18 && i < 26)
            {
                model = glm::scale(model, glm::vec3(0.4f));
                route = RotateArbitraryLine(glm::vec3(0.0f, 6.0f, 0.0f), glm::vec3(0.0f, 6.0f, 1.0f), -0.8 * lastFrame);
                model = route * model;
            }

            // ���ƴδ���Ȧװ�εƹ�
            // ----------------------------------------
            else if (i >= 26 && i < 30)
            {
                model = glm::scale(model, glm::vec3(0.4f));
                route = RotateArbitraryLine(glm::vec3(0.0f, 6.0f, 0.0f), glm::vec3(0.0f, 6.0f, 1.0f), 0.6 * lastFrame);
                model = route * model;
            }

            // ��������װ�εƹ�
            // ----------------------------------------
            else if (i == 30)
            {
                model = glm::scale(model, glm::vec3(0.4f));
                route = RotateArbitraryLine(glm::vec3(0.0f, 6.0f, 0.0f), glm::vec3(0.0f, 6.0f, 1.0f), -0.4 * lastFrame);
                model = route * model;
            }

            lightProgram->setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // ����ƽ����س���
        // ----------------------------------------
        floorProgram->use();

        glBindVertexArray(floorVAO);

        // ���ֵ�Ͳ�ƹ�Դ
        // ----------------------------------------
        floorProgram->setVec3("spotLight.position", cameraPos);
        floorProgram->setVec3("spotLight.direction", cameraFront);
        floorProgram->setFloat("spotLight.innerCutOff", glm::cos(glm::radians(12.5f)));
        floorProgram->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(17.5f)));
        floorProgram->setFloat("spotLight.constant", 1.0f);
        floorProgram->setFloat("spotLight.linear", 0.09f);
        floorProgram->setFloat("spotLight.quadratic", 0.02f);
        floorProgram->setVec3("spotLight.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
        floorProgram->setVec3("spotLight.diffuse", spotLight);
        floorProgram->setVec3("spotLight.specular", spotLight);

        // ��ֱ���ƹ�Դ
        // ----------------------------------------
        floorProgram->setVec3("dirLight.direction", glm::vec3(0.0f, 1.0f, 0.0f));
        floorProgram->setVec3("dirLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
        floorProgram->setVec3("dirLight.diffuse", glm::vec3(0.9f, 0.9f, 0.9f));
        floorProgram->setVec3("dirLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));

        // �󶨵��Դ
        // ----------------------------------------
        for (int i = 0; i < 6; ++i)
        {
            std::string index = std::to_string(i);
            floorProgram->setVec3("pointLights[" + index + "].position", pointLightPositions[i]);
            floorProgram->setFloat("pointLights[" + index + "].constant", 1.0f);
            floorProgram->setFloat("pointLights[" + index + "].linear", 0.09f);
            floorProgram->setFloat("pointLights[" + index + "].quadratic", 0.02f);
            floorProgram->setVec3("pointLights[" + index + "].ambient", glm::vec3(0.1f, 0.1f, 0.1f));
            floorProgram->setVec3("pointLights[" + index + "].diffuse", glm::vec3(0.9648f, 0.9297f, 0.8359f) * glm::vec3(brightness * 0.5));
            floorProgram->setVec3("pointLights[" + index + "].specular", glm::vec3(0.9648f, 0.9297f, 0.8359f) * glm::vec3(brightness));
        }

        // ����ģ�ͱ任����, �۲����, ͸��ͶӰ����
        // ----------------------------------------
        floorProgram->setVec3("viewPos", cameraPos);
        floorProgram->setInt("material.diffuse", 2);
        floorProgram->setInt("material.specular", 2);
        floorProgram->setFloat("material.shininess", 4.0f);

        // ������ݵ���
        // ----------------------------------------
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 14.5f, 0.0f));
        model = glm::scale(model, glm::vec3(30.0f));

        floorProgram->setMat4("model", model);
        floorProgram->setMat4("view", view);
        floorProgram->setMat4("projection", projection);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // ��������ͼƬ
        // ----------------------------------------
        glBindVertexArray(pictureVAO);
        floorProgram->setInt("material.diffuse", pictureIndex + 7);
        floorProgram->setInt("material.specular", pictureIndex + 7);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 1.3f, -3.4f));
        model = glm::scale(model, glm::vec3(3.2f, 1.8f, 1.0f));
        floorProgram->setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // ����ͼƬ�߿�
        // ----------------------------------------
        floorProgram->setInt("material.diffuse", 6);
        floorProgram->setInt("material.specular", 6);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 1.3f, -3.4005f));
        model = glm::scale(model, glm::vec3(3.65f, 2.15f, 1.0f));
        floorProgram->setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // ������
        // ----------------------------------------
        glBindVertexArray(doorVAO);
        floorProgram->setInt("material.diffuse", 12);
        floorProgram->setInt("material.specular", 12);

        model = glm::mat4(1.0f);
        model = RotateArbitraryLine(glm::vec3(0.0f, 2.0f, 4.0f), glm::vec3(1.0f, 2.0f, 4.0f), doorRotate);
        model = glm::translate(model, glm::vec3(0.0f, 0.75f, 0.0f));
        model = glm::scale(model, glm::vec3(5.0f, 2.5f, 8.0f));
        floorProgram->setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // �����ű���
        // ----------------------------------------
        glBindVertexArray(doorBackVAO);
        floorProgram->setInt("material.diffuse", 12);
        floorProgram->setInt("material.specular", 12);

        model = glm::mat4(1.0f);
        model = RotateArbitraryLine(glm::vec3(0.0f, 2.0f, 4.0f), glm::vec3(1.0f, 2.0f, 4.0f), doorRotate);
        model = glm::translate(model, glm::vec3(0.0f, 0.75f, -0.0001f));
        model = glm::scale(model, glm::vec3(5.0f, 2.5f, 8.0f));
        floorProgram->setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // �����ű߿�
        // ----------------------------------------
        glBindVertexArray(doorVAO);
        floorProgram->setInt("material.diffuse", 3);
        floorProgram->setInt("material.specular", 3);

        // ��������߿�
        // ----------------------------------------
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-3.25f, 0.5, 0.0f));
        model = glm::scale(model, glm::vec3(1.5f, 3.0f, 8.0f));
        floorProgram->setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // �������ұ߿�
        // ----------------------------------------
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(3.25f, 0.5, 0.0f));
        model = glm::scale(model, glm::vec3(1.5f, 3.0f, 8.0f));
        floorProgram->setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // �����ű߿�����
        // ----------------------------------------
        glBindVertexArray(doorBackVAO);
        floorProgram->setInt("material.diffuse", 3);
        floorProgram->setInt("material.specular", 3);

        // ������߿�����
        // ----------------------------------------
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-3.25f, 0.5, -0.0001f));
        model = glm::scale(model, glm::vec3(1.5f, 3.0f, 8.0f));
        floorProgram->setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // �����ұ߿�����
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(3.25f, 0.5, -0.0001f));
        model = glm::scale(model, glm::vec3(1.5f, 3.0f, 8.0f));
        floorProgram->setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // �������ϱ߿�
        // ----------------------------------------
        glBindVertexArray(doorTopFrameVAO);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 2.5f, 0.0f));
        model = glm::scale(model, glm::vec3(8.0f, 1.0f, 8.0f));
        floorProgram->setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // �������ϱ߿�����
        // ----------------------------------------
        glBindVertexArray(doorTopFrameBackVAO);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 2.5f, -0.0001f));
        model = glm::scale(model, glm::vec3(8.0f, 1.0f, 8.0f));
        floorProgram->setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // ����ǽ�ڼ��س���
        // ----------------------------------------
        wallProgram->use();

        glBindVertexArray(wallVAO);

        // �����ֵ�Ͳ��Դ
        // ----------------------------------------
        wallProgram->setVec3("spotLight.position", cameraPos);
        wallProgram->setVec3("spotLight.direction", cameraFront);
        wallProgram->setFloat("spotLight.innerCutOff", glm::cos(glm::radians(12.5f)));
        wallProgram->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(17.5f)));
        wallProgram->setFloat("spotLight.constant", 1.0f);
        wallProgram->setFloat("spotLight.linear", 0.09f);
        wallProgram->setFloat("spotLight.quadratic", 0.02f);
        wallProgram->setVec3("spotLight.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
        wallProgram->setVec3("spotLight.diffuse", spotLight);
        wallProgram->setVec3("spotLight.specular", spotLight);

        // ����ֱ���Դ
        // ----------------------------------------
        wallProgram->setVec3("dirLight.direction", glm::vec3(0.0f, 1.0f, 0.0f));
        wallProgram->setVec3("dirLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
        wallProgram->setVec3("dirLight.diffuse", glm::vec3(0.9f, 0.9f, 0.9f));
        wallProgram->setVec3("dirLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));

        // ���õ��Դ
        // ----------------------------------------
        for (int i = 0; i < 6; ++i)
        {
            std::string index = std::to_string(i);
            wallProgram->setVec3("pointLights[" + index + "].position", pointLightPositions[i]);
            wallProgram->setFloat("pointLights[" + index + "].constant", 1.0f);
            wallProgram->setFloat("pointLights[" + index + "].linear", 0.09f);
            wallProgram->setFloat("pointLights[" + index + "].quadratic", 0.02f);
            wallProgram->setVec3("pointLights[" + index + "].ambient", glm::vec3(0.1f, 0.1f, 0.1f));
            wallProgram->setVec3("pointLights[" + index + "].diffuse", glm::vec3(0.9648f, 0.9297f, 0.8359f) * glm::vec3(brightness * 0.5));
            wallProgram->setVec3("pointLights[" + index + "].specular", glm::vec3(0.9648f, 0.9297f, 0.8359f) * glm::vec3(brightness));
        }

        // ����ģ�ͱ任����, �۲����, ͸��ͶӰ����
        // ----------------------------------------
        wallProgram->setVec3("viewPos", cameraPos);
        wallProgram->setInt("material.diffuse", 3);
        wallProgram->setInt("material.specular", 3);
        wallProgram->setFloat("material.shininess", 4.0f);

        // ������ǽ��
        // ----------------------------------------
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(8.0f, 4.0f, 8.0f));

        wallProgram->setMat4("model", model);
        wallProgram->setMat4("view", view);
        wallProgram->setMat4("projection", projection);
        glDrawArrays(GL_TRIANGLES, 0, 24);

        // ������ǽ�ڼ��س���
        // ----------------------------------------
        innerWallProgram->use();

        glBindVertexArray(innerWallVAO);

        // �����ֵ�Ͳ��Դ
        // ----------------------------------------
        innerWallProgram->setVec3("spotLight.position", cameraPos);
        innerWallProgram->setVec3("spotLight.direction", cameraFront);
        innerWallProgram->setFloat("spotLight.innerCutOff", glm::cos(glm::radians(12.5f)));
        innerWallProgram->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(17.5f)));
        innerWallProgram->setFloat("spotLight.constant", 1.0f);
        innerWallProgram->setFloat("spotLight.linear", 0.09f);
        innerWallProgram->setFloat("spotLight.quadratic", 0.02f);
        innerWallProgram->setVec3("spotLight.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
        innerWallProgram->setVec3("spotLight.diffuse", spotLight * glm::vec3(0.5));
        innerWallProgram->setVec3("spotLight.specular", spotLight * glm::vec3(0.5));

        // ����ֱ���Դ
        // ----------------------------------------
        innerWallProgram->setVec3("dirLight.direction", glm::vec3(0.0f, 1.0f, 0.0f));
        innerWallProgram->setVec3("dirLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
        innerWallProgram->setVec3("dirLight.diffuse", glm::vec3(0.9f, 0.9f, 0.9f));
        innerWallProgram->setVec3("dirLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));

        // ���õ��Դ
        // ----------------------------------------
        for (int i = 0; i < 6; ++i)
        {
            std::string index = std::to_string(i);
            innerWallProgram->setVec3("pointLights[" + index + "].position", pointLightPositions[i]);
            innerWallProgram->setFloat("pointLights[" + index + "].constant", 1.0f);
            innerWallProgram->setFloat("pointLights[" + index + "].linear", 0.09f);
            innerWallProgram->setFloat("pointLights[" + index + "].quadratic", 0.02f);
            innerWallProgram->setVec3("pointLights[" + index + "].ambient", glm::vec3(0.1f, 0.1f, 0.1f));
            innerWallProgram->setVec3("pointLights[" + index + "].diffuse", glm::vec3(0.9648f, 0.9297f, 0.8359f) * glm::vec3(brightness * 0.5));
            innerWallProgram->setVec3("pointLights[" + index + "].specular", glm::vec3(0.9648f, 0.9297f, 0.8359f) * glm::vec3(brightness));
        }

        // ����ģ�ͱ任����, �۲����, ͸��ͶӰ����
        // ----------------------------------------
        innerWallProgram->setVec3("viewPos", cameraPos);
        innerWallProgram->setInt("material.diffuse", 4);
        innerWallProgram->setInt("material.specular", 4);
        innerWallProgram->setFloat("material.shininess", 4.0f);

        // ���ƹ�������ǽ��
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(7.9f, 3.95f, 7.9f));

        innerWallProgram->setMat4("model", model);
        innerWallProgram->setMat4("view", view);
        innerWallProgram->setMat4("projection", projection);
        glDrawArrays(GL_TRIANGLES, 0, 24);

        // glfw: ��������������ˢ��
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteVertexArrays(1, &floorVAO);
    glDeleteVertexArrays(1, &wallVAO);
    glDeleteVertexArrays(1, &innerWallVAO);
    glDeleteVertexArrays(1, &pictureVAO);
    glDeleteVertexArrays(1, &doorVAO);
    glDeleteVertexArrays(1, &doorBackVAO);
    glDeleteVertexArrays(1, &doorTopFrameVAO);
    glDeleteVertexArrays(1, &doorTopFrameBackVAO);

    glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &floorVBO);
    glDeleteBuffers(1, &wallVBO);
    glDeleteBuffers(1, &innerWallVBO);
    glDeleteBuffers(1, &pictureVBO);
    glDeleteBuffers(1, &doorVBO);
    glDeleteBuffers(1, &doorBackVBO);
    glDeleteBuffers(1, &doorTopFrameVBO);
    glDeleteBuffers(1, &doorTopFrameBackVBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}