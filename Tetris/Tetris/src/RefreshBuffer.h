#pragma once
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "GameLoader.h"
#include "GameSystem.h"
#include "VertexBufferLayout.h"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include "Texture.h"
#include "Renderer.h"


class RefreshBuffer {
private:
public:
	RefreshBuffer();
	~RefreshBuffer();

	VertexArray RefreshBuff(bool rebuff);
};