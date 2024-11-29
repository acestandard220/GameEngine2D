#ifndef G_VERTEX_ARRAY_H
#define G_VERTEX_ARRAY_H
#include "pch.h"
#include "VertexBuffer.h"

class VertexArrayBuffer
{
public:
	VertexArrayBuffer();
	void Bind() const;
	void Unbind() const;

	void AddVertexbuffer(IBuffer& buffer);
	void SetIndexbuffer(IBuffer& buffer);
	uint64_t GetIndexCount() const { return m_indexCount; }

private:
	unsigned int m_vertexarrayID;

	uint64_t m_indexCount;
};

#endif // G_VERTEX_ARRAY_H
