#pragma once
#include <glad/glad.h>
#include <iostream>
#include <GLFW/glfw3.h>

// ------------------------------------------------------------------------
// ��ɫ��Shader��
// ��GLSL������д����ɫ��������ж����װ��������ʹ��
// ------------------------------------------------------------------------
class Shader
{
public:
    unsigned int ID;
    // ��ɫ�����캯��
    // ------------------------------------------------------------------------
    Shader(const char* vertexSource, const char* fragmentSource)
    {

        // ������ɫ������
        unsigned int vertexShader, fragmentShader;

        // ������ɫ��
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexSource, NULL);
        glCompileShader(vertexShader);
        checkCompileErrors(vertexShader, "VERTEX");

        // Ƭ����ɫ��
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
        glCompileShader(fragmentShader);
        checkCompileErrors(fragmentShader, "FRAGMENT");

        // ��ɫ������
        ID = glCreateProgram();
        glAttachShader(ID, vertexShader);
        glAttachShader(ID, fragmentShader);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");

        // ���Ѿ����ӵ���ɫ������
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
    // ������ɫ��
    // ------------------------------------------------------------------------
    void use()
    {
        glUseProgram(ID);
    }
    // ���ֲ�ͬ������GLSL������uniform�����ĺ���
    // ------------------------------------------------------------------------
    void setBool(const std::string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }
    // ------------------------------------------------------------------------
    void setInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void setFloat(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void setVec3(const std::string& name, glm::vec3 value) const
    {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z);
    }
    // ------------------------------------------------------------------------
    void setMat4(const std::string& name, glm::mat4 value) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
    }

private:
    // ��������ɫ��Դ��������еı����������
    // ------------------------------------------------------------------------
    void checkCompileErrors(unsigned int shader, std::string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                    << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                    << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
};