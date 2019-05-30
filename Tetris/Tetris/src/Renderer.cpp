#include "Renderer.h"

void Renderer::Clear() const{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray& va,const IndexBuffer& ib,const Shader& shader,const Texture& texture, unsigned int index) const{
	shader.Bind();
	texture.Bind(index);
	va.Bind();
	ib.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}