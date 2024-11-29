#include <VertexArray.h>

VertexArrayBuffer::VertexArrayBuffer()
{
	glGenVertexArrays(1, &m_vertexarrayID);
	GAME_ENGINE_2D_OPENGL_ERROR();
}

void VertexArrayBuffer::Bind() const
{
	glBindVertexArray(m_vertexarrayID);
	
	GAME_ENGINE_2D_OPENGL_ERROR();
}

void VertexArrayBuffer::Unbind() const
{
	glBindVertexArray(0);
}

void VertexArrayBuffer::AddVertexbuffer(IBuffer& buffer)
{
	glBindVertexArray(m_vertexarrayID);
	buffer.Bind();
	for (auto& element : buffer.GetBufferLayout())
	{ 
		glEnableVertexAttribArray(element.att_tag);
		glVertexAttribPointer(element.att_tag,
			element.GetComponentCount(element.Type),
			element.GetGLType(element.Type),
			element.Normalized ? GL_TRUE : GL_FALSE,
			buffer.GetBufferLayout().GetStride(),
			(void*)element.Offset);
		
	}
	GAME_ENGINE_2D_OPENGL_ERROR();
	glBindVertexArray(0);
}

void VertexArrayBuffer::SetIndexbuffer(IBuffer& buffer)
{
	Bind();
	buffer.Bind();
	glBindVertexArray(0);
	m_indexCount = buffer.GetCount();
	
	GAME_ENGINE_2D_OPENGL_ERROR();

	return;
}
