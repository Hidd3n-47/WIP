#include "pch.h"
#include "Renderer.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Texture.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Scene/SceneManager.h"

namespace jci {

void Renderer::Init()
{

}

void Renderer::DrawQuad(vec2 position, vec2 size, const vec4& color, Texture* textuer) // Set texure to default to be white texture.
{
	// Bind the shader.
	// Set the shader attributes.

	//mat4 transfrom = glm::translate(mat4(1.0f), vec3(position, 0.0f)) * glm::scale(mat4(1.0f), vec3(1.0f));
	// Set shader uniform transform.

	//bind vertex array.
	// Draw indexed?
	uint32 m_vertexArray;
	glGenVertexArrays(1, &m_vertexArray);
	glBindVertexArray(m_vertexArray);

	size = size * 0.5f;
	float vertices[] =
	{
		position.x - size.x, position.y - size.y, color.r, color.g, color.b, 0.0f, 0.0f,
		position.x + size.x, position.y - size.y, color.r, color.g, color.b, 1.0f, 0.0f,
		position.x + size.x, position.y + size.y, color.r, color.g, color.b, 1.0f, 1.0f,
		position.x - size.x, position.y + size.y, color.r, color.g, color.b, 0.0f, 1.0f
	};
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

	shader.Bind();
	glBindVertexArray(m_vertexArray);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Renderer::Destroy()
{

}

} // Namespace jci.