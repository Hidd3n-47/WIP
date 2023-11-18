#include "pch.h"
#include "Shader.h"

#include <sstream>
#include <fstream>
#include <gl/glew.h>

namespace jci {

Shader::Shader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath) :
	m_vertexFilePath(vertexShaderFilePath),
	m_fragmentFilePath(fragmentShaderFilePath),
	m_id(0)
{
	std::string vertexShader = ParseShader(m_vertexFilePath);
	std::string fragmentShader = ParseShader(m_fragmentFilePath);

	//CompileShader(GL_VERTEX_SHADER, vertexShader);
	//CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	CreateShaders(vertexShader, fragmentShader);
}

Shader::~Shader()
{
	glDeleteProgram(m_id);
}

void Shader::Bind()
{
	glUseProgram(m_id);
}
void Shader::Unbind()
{
	glUseProgram(0);

}

void Shader::UploadUniformInt(const std::string& name, int i)
{
	glUniform1i(GetUniformLocation(name), i);
}

void Shader::UploadUniformFloat4(const std::string& name, float f0, float f1, float f2, float f3)
{
	glUniform4f(GetUniformLocation(name), f0, f1, f2, f3);
}

void Shader::UploadUniformMat4(const std::string& name, const mat4& matrix)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

std::string Shader::ParseShader(const std::string& file)
{
	std::ifstream fin(file);
	std::stringstream ss;
	std::string line;
	while (getline(fin, line))
	{
		ss << line << '\n';
	}

	return ss.str();
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();

	glShaderSource(id, 1, &src, 0);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		DLOG("Failed to complie Shader at: " + source);
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

void Shader::CreateShaders(const std::string& vertex, const std::string frag)
{
	m_id = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertex);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, frag);

	glAttachShader(m_id, vs);
	glAttachShader(m_id, fs);

	glLinkProgram(m_id);

	int result;
	glGetProgramiv(m_id, GL_LINK_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(m_id, length, &length, message);
		DLOG("Failed to link the shader to the program.");
		std::cout << message << std::endl;
		glDeleteShader(m_id);
		ASSERT(0, "Could not link the shader to the program.")
	}
	//glValidateProgram(m_id);

	/*glDeleteShader(vs);
	glDeleteShader(fs);*/
	glDetachShader(m_id, vs);
	glDetachShader(m_id, fs);
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
	{
		return m_uniformLocationCache[name];
	}

	int location = glGetUniformLocation(m_id, name.c_str());

	if (location == -1)
	{
		DLOG("Warning: uniform '" + name + "' does not exist.");
	}

	m_uniformLocationCache[name] = location;

	return location;
}

} // Namespace jci.