#pragma once

namespace jci {

class Shader
{
public:
	Shader() = default;
	Shader(const std::string& vertexShaderFilePath, const std::string& fragementShaderFilePath);
	~Shader();

	void Bind();
	void Unbind();

	// Uploades.
	void UploadUniformInt(const std::string& name, int i);
	void UploadUniformFloat4(const std::string& name, float f0, float f1, float f2, float f3);
	void UploadUniformMat4(const std::string& name, const mat4& matrix);
private:
	std::string m_vertexFilePath;
	std::string m_fragmentFilePath;
	unsigned int m_id;
	std::unordered_map<std::string, int> m_uniformLocationCache;

	std::string ParseShader(const std::string& filepath);
	void CreateShaders(const std::string& vertex, const std::string frag);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	int GetUniformLocation(const std::string& name);
};

} // Namespace jci.