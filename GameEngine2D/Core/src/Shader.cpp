#include "Shader.h"
#include "../core.h"

uint32_t Shader::boundShader = -1;
ShaderSource::ShaderSource(const char* vp, const char* fp) : vertexPath(vp),fragmentPath(fp)
{
	GAME_ENGINE_2D_ASSERT(GrabShader());
}

bool ShaderSource::GrabShader()
{
	if (!vertexPath || !fragmentPath)
		return false;

	std::ifstream inV(vertexPath, std::ios::in | std::ios::binary);
	if (inV)
	{
		inV.seekg(0, std::ios::end);
		vertexSource.resize(inV.tellg());
		inV.seekg(0, std::ios::beg);
		inV.read(&vertexSource[0], vertexSource.size());
		inV.close();
		
	}
	else {
		std::cout << "Could not open file!\n";
		return false;
	}

	std::ifstream inF(fragmentPath, std::ios::in | std::ios::binary);
	if (inF)
	{
		inF.seekg(0, std::ios::end);
		fragmentSource.resize(inF.tellg());
		inF.seekg(0, std::ios::beg);
		inF.read(&fragmentSource[0], fragmentSource.size());
		inF.close();
		
	}
	else {
		std::cout << "Could not open file!\n";
		return false;
	}
	return true;
}

Shader::Shader(ShaderSource& source)
{
	m_source = new ShaderSource(source);
	Compile(m_source->vertexSource.c_str(),m_source->fragmentSource.c_str());
}

Shader::Shader(const char* vP, const char* fP)
{
	m_source = new ShaderSource(vP, fP);
	Compile(m_source->vertexSource.c_str(), m_source->fragmentSource.c_str());
}

Shader::~Shader()
{
	delete m_source;
	m_source = nullptr;
}

void Shader::Recompile()
{
	m_source->GrabShader();
	Compile(m_source->vertexSource.c_str(), m_source->fragmentSource.c_str());
}

int Shader::GetUniformLocation(const char* var) const 
{
	return glGetUniformLocation(ID,var);
}

bool Shader::SetMatrix4(const char* var, glm::mat4 value) const
{
	int x = GetUniformLocation(var);
	GAME_ENGINE_2D_OPENGL_LOCATION_ERROR(x);
	if (x == -1)
		return false;
	glUniformMatrix4fv(x, 1, GL_FALSE, &value[0][0]);

	GAME_ENGINE_2D_OPENGL_ERROR();

	return true;
}

bool Shader::SetVec3(const char* var, glm::vec3 value) const
{
	int x = GetUniformLocation(var);
	GAME_ENGINE_2D_OPENGL_LOCATION_ERROR(x);
	if (x == -1)
		return false;
	glUniform3fv(x, 1, &value[0]);

	GAME_ENGINE_2D_OPENGL_ERROR();

	return true;
}


bool Shader::SetInt(const char* var, int value) const
{
	int x = GetUniformLocation(var);
	GAME_ENGINE_2D_OPENGL_LOCATION_ERROR(x);
	if (x == -1)
		return false;
	glUniform1i(x, value);

	GAME_ENGINE_2D_OPENGL_ERROR();

	return true;
}

bool Shader::SetFloat(const char* var, float value) const
{
	int x = GetUniformLocation(var);
	GAME_ENGINE_2D_OPENGL_LOCATION_ERROR(x);
	if (x == -1)
		return false;
	glUniform1f(x, value);

	GAME_ENGINE_2D_OPENGL_ERROR();

	return true; 
}
bool Shader::SetBool(const char* var, bool value) const
{
	GAME_ENGINE_2D_OPENGL_ERROR();

	return SetInt(var, value);
}
void Shader::Compile(const char* _v, const char* _f)
{
	vertexID = glCreateShader(GL_VERTEX_SHADER);
	fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
	GAME_ENGINE_2D_OPEGNL_ERROR_PARAM("Shader Creation");

	glShaderSource(vertexID, 1, &_v, nullptr);
	glShaderSource(fragmentID, 1, &_f, nullptr);
	GAME_ENGINE_2D_OPEGNL_ERROR_PARAM("Shader Sourcing");

	glCompileShader(vertexID);
	glCompileShader(fragmentID);
	GAME_ENGINE_2D_OPEGNL_ERROR_PARAM("Shader Compilation");

	ID = glCreateProgram();
	GAME_ENGINE_2D_OPEGNL_ERROR_PARAM("Program Creation");

	glAttachShader(ID, vertexID);
	glAttachShader(ID, fragmentID);
	GAME_ENGINE_2D_OPEGNL_ERROR_PARAM("Shader attach");

	CheckShader(vertexID);
	CheckShader(fragmentID);

	glLinkProgram(ID);
	GAME_ENGINE_2D_OPEGNL_ERROR_PARAM("Linkage");
	CheckProgram(ID);

	GAME_ENGINE_2D_OPENGL_ERROR();
	
}

bool Shader::CheckProgram(GLuint  program)
{
	int success;
	char infoLog[512];
	glGetShaderiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		return false;
	};
	return true;
}

bool Shader::CheckShader(GLuint  shader)
{
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		return false;
	};
	return true;
}
