#pragma once

class IndexBuffer {
private:
	unsigned int m_RendererID;
	
public:
	unsigned int m_Count;
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Rebuff(const unsigned int* data, unsigned int count);
	void Bind() const ;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_Count; }
};