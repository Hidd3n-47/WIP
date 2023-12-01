#include "pch.h"
#include "Renderer.h"

#include <glm/gtc/matrix_transform.hpp>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Scene/SceneManager.h"
#include "Graphics/Texture/Texture.h"

namespace jci {

void Renderer::Init()
{

}

void Renderer::DrawQuad(vec2 position, vec2 size, vec2 scale, const vec4& color, Texture* texture) // Set texure to default to be white texture.
{
	uint32 m_vertexArray;
	glGenVertexArrays(1, &m_vertexArray);
	glBindVertexArray(m_vertexArray);

	/*float vertices[] =
	{
		position.x - size.x, position.y - size.y, color.r, color.g, color.b, 0.0f, 0.0f,
		position.x + size.x, position.y - size.y, color.r, color.g, color.b, 1.0f, 0.0f,
		position.x + size.x, position.y + size.y, color.r, color.g, color.b, 1.0f, 1.0f,
		position.x - size.x, position.y + size.y, color.r, color.g, color.b, 0.0f, 1.0f
	};*/
	float vertices[] =
	{
		0.0f * scale.x, 0.0f * scale.y, color.r, color.g, color.b, 0.0f, 0.0f,
		size.x * scale.x, 0.0f * scale.y, color.r, color.g, color.b, 1.0f, 0.0f,
		size.x * scale.x, size.y * scale.y, color.r, color.g, color.b, 1.0f, 1.0f,
		0.0f * scale.x, size.y * scale.y, color.r, color.g, color.b, 0.0f, 1.0f
	};

	size *= 0.5f;

	VertexBuffer vertexBuffer(vertices, sizeof(vertices));
	vertexBuffer.Bind();

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertices) / sizeof(float), nullptr);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertices) / sizeof(float), (void*)(sizeof(float) * 2));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertices) / sizeof(float), (void*)(sizeof(float) * 5));

	uint32 indices[] =
	{
		0, 1, 2, 2, 3, 0
	};
	IndexBuffer indexBuffer(indices, 6);
	indexBuffer.Bind();

	Shader shader = Shader("Assets/Shader/shader.vert", "Assets/Shader/shader.frag");
	shader.Bind();
	
	shader.UploadUniformInt("u_texture", 0);

	shader.UploadUniformMat4("u_orthoProjMatrix", SceneManager::Instance()->GetCurrentScene()->GetCamera()->GetViewProjMat());
	shader.UploadUniformVec2("u_position", position - size * scale);

	//shader.Bind();
	glBindVertexArray(m_vertexArray);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	glDeleteVertexArrays(1, &m_vertexArray);
}

void Renderer::Destroy()
{

}

} // Namespace jci.