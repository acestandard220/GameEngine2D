#include <Buffer.h>
#include <VertexBuffer.h>


IBuffer* IBuffer::CreateBuffer(float* data,size_t size,BUFFER_TYPE buffertype)
{
	switch (buffertype)
	{
		case BUFFER_TYPE_VERTEX:
		{
			IBuffer* buffer = new Vertexbuffer(data, size);
			return buffer;
		}
		case BUFFER_TYPE_INDEX:
		{

		}
		default:
		{
			return nullptr;
		}
	}
	return nullptr;
}

IBuffer* IBuffer::CreateVertexBuffer(float* data, size_t size)
{
	if (!data || 0)
		return NULL;
	IBuffer* buffer = new Vertexbuffer(data, size);
	return buffer;
}

IBuffer* IBuffer::CreateIndexBuffer(unsigned int* indices,int count)
{
	if (indices == NULL)
	{
		return nullptr;
	}
	IBuffer* buffer = new Indexbuffer(indices, count);
	return buffer;
}

void IBuffer::FlushBufferState()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

BufferLayout* BufferLayout::UseDefaultLayout(DefinedLayout layout)
{
	switch (layout)
	{
	    case DefinedLayout::POS3_COL3:
	    {
			return new BufferLayout{ { "POSITION",FLOAT3,POSITION}, { "COLOUR",FLOAT3,TEXTURE } };
		}
		case DefinedLayout::POS3_TEX2:
		{
			return new BufferLayout{ { "POSITION",FLOAT3,POSITION },{"TEXTURE",FLOAT2,TEXTURE}};
		}
		default :
		{
			std::cout << "Be serious with your life\n";
			break;
		}
	};
	return nullptr;	
}
