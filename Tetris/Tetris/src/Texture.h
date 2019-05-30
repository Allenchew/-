#pragma once
#include<GL/glew.h>
#include<vector>
#include "RenderDebug.h"
class Texture {
private:
	unsigned int m_RendererID[2];
	std::vector<std::string> m_FilePath;
	std::vector<unsigned char*> m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
public:
	Texture(const std::vector<std::string>& path);
	~Texture();

	void Bind(unsigned int slot =0)const;
	void Unbind() const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
};