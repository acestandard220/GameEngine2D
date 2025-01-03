#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H
#include "Buffer.h"

class Vertexbuffer : public IBuffer
{
public:
	Vertexbuffer(float* vertex, size_t size, GLenum bufferusage = GL_STATIC_DRAW);
	Vertexbuffer(size_t size,GLenum bufferusage = GL_DYNAMIC_DRAW);
	virtual void Bind() override;
	virtual void Unbind() override;
	virtual void SetBufferLayout(BufferLayout& layout) override;
	BufferLayout GetBufferLayout() override;

	virtual void SetData(void* data, size_t size) override;
private:
	unsigned int bufferID;
	GLenum m_bufferusage;
	BufferLayout m_bufferlayout;
};


class Indexbuffer : public IBuffer
{
public:
	Indexbuffer(unsigned int*,int);

	virtual void Bind() override;
	virtual void Unbind() override;

	virtual void SetData(void* data, size_t size) override;


	
private:
	unsigned int EBO;
	
};
#endif // !VERTEX_BUFFER_H

