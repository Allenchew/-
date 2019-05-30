#include "Texture.h"
#include "std_image\stb.h"

Texture::Texture(const std::vector<std::string>& path)
	:m_RendererID(), m_FilePath(path), m_Width(0), m_Height(0), m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	GLCall(glGenTextures(path.size(), m_RendererID));

	for (unsigned int i = 0; i < path.size(); i++) {
		m_LocalBuffer.push_back(stbi_load(path[i].c_str(), &m_Width, &m_Height, &m_BPP, 4));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID[i]));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer[i]));
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}
		/*if (m_LocalBuffer) {
			stbi_image_free(m_LocalBuffer);
		}*/
	
}

Texture::~Texture() {
	GLCall(glDeleteTextures(2, m_RendererID));
}

void Texture::Bind(unsigned int slot)const{
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID[slot]));
}
void Texture::Unbind()const {
	GLCall(glBindTexture(GL_TEXTURE_2D,0));
}