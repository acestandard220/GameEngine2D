#pragma once
#include "pch.h"

struct ShaderSource 
{
    const char* vertexPath = nullptr;
    const char* fragmentPath = nullptr;

    std::string vertexSource;
    std::string fragmentSource;
    ShaderSource(const char*, const char*);

    bool GrabShader();
};

class Shader 
{
    public:
        Shader() = default;
        Shader(ShaderSource& source);
        Shader(const char*, const char*);
        ~Shader();
         
        void Recompile(); 
    public:
        inline void Use() const {
            boundShader = ID;
            glUseProgram(ID); 
        }
        int  GetUniformLocation(const char*) const;
        bool SetMatrix4(const char* var, glm::mat4 value) const;
        bool SetVec3(const char* var, glm::vec3 value) const;
        bool SetInt(const char* var, int value) const;
        bool SetFloat(const char* var, float value) const;
        bool SetBool(const char* var, bool value) const;
        static uint32_t boundShader;
    private:
        void Compile(const char*,const char*);
        bool CheckProgram(GLuint  program);
        bool CheckShader(GLuint  shader);
    private:
        ShaderSource* m_source;
        unsigned int  vertexID;
        unsigned int  fragmentID;
        
        unsigned int ID;


};