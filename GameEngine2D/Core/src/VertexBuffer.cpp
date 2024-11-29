#include <VertexBuffer.h>

Vertexbuffer::Vertexbuffer(float* vertex, size_t size,GLenum bufferusage) : m_bufferusage(bufferusage)
{
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ARRAY_BUFFER, size, vertex,bufferusage);
	m_count = 0;

	GAME_ENGINE_2D_OPENGL_ERROR();
}

Vertexbuffer::Vertexbuffer(size_t size,GLenum bufferusage) :m_bufferusage(bufferusage)
{
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, bufferusage);

	m_count = 0;
}

void Vertexbuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
}

void Vertexbuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
}

void Vertexbuffer::SetBufferLayout(BufferLayout& layout)
{
	m_bufferlayout = layout;
}

BufferLayout Vertexbuffer::GetBufferLayout()
{
	 return m_bufferlayout; 
}

void Vertexbuffer::SetData(void* data, size_t size)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

Indexbuffer::Indexbuffer(unsigned int* indices,int count)
{
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * count, indices, GL_STATIC_DRAW);
	m_count = count;

	GAME_ENGINE_2D_OPENGL_ERROR();
}

void Indexbuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	GAME_ENGINE_2D_OPENGL_ERROR();
}

void Indexbuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Indexbuffer::SetData(void* data, size_t size)
{
}
