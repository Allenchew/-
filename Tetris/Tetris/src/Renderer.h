#pragma once
#include<GL/glew.h>

#include "RenderDebug.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"


class Renderer {
private:

public:
	void Clear()const;
	void Draw(const VertexArray& va,const IndexBuffer& ib,const Shader& shader,const Texture& texture,unsigned int index)const;
	
};