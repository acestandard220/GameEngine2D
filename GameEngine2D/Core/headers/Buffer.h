#ifndef G_BUFFER_H
#define G_BUFFER_H
#include "pch.h"
#include "../core.h"


class Vertexbuffer;

enum BUFFER_TYPE
{
	BUFFER_TYPE_VERTEX, BUFFER_TYPE_INDEX
};
enum ShaderDataType
{
	FLOAT,FLOAT2,FLOAT3,FLOAT4,
	INT,INT2,INT3,INT4,
	BOOL, SHADER_DATA_TYPE_UNKNOWN
};

enum AttributeTag {
	POSITION =0,NORMAL=1, TEXTURE = 2, UNKNOWN=3
};
enum DefinedLayout
{
	POS3_COL3,
	POS3_TEX2,
	POS3_COL3_NOR3git
};

struct BufferElement {
	BufferElement(std::string name, ShaderDataType type,AttributeTag tag, bool normalised = false)
		:Name(name), 
		Type(type), 
		att_tag(tag),
		Normalized(normalised), 
		Offset(0), Size(DeriveSize(type))
	{
	}
	std::string Name;
	ShaderDataType Type;
	uint16_t Offset;
	uint16_t Size;
	AttributeTag att_tag;
	bool Normalized;
	uint16_t GetComponentCount(ShaderDataType typee)
	{
		switch (typee)
		{
		case FLOAT:
		case INT:
		case BOOL:
			return 1;
		case FLOAT2:
		case INT2:
			return 2;
		case FLOAT3:
		case INT3:
			return 3;
		case FLOAT4:
		case INT4:
			return 4;
		}
	}
	GLenum GetGLType(ShaderDataType typee)
	{
		switch (typee)
		{
			case FLOAT:
		    case FLOAT2:
		    case FLOAT3:
			case FLOAT4:
				return GL_FLOAT;
		    case INT:
		    case INT2:
		    case INT3:
		    case INT4:
				return GL_INT;
		    case BOOL:
				return GL_BOOL;
		}
		return SHADER_DATA_TYPE_UNKNOWN;
	}
private:
	uint16_t DeriveSize(ShaderDataType typee)
	{
		switch (typee)
		{
		    case FLOAT:    return 4;
		    case FLOAT2:   return 4 * 2;
			case FLOAT3:   return 4 * 3;
		    case FLOAT4:   return 4 * 4;
		    case INT:      return 4;
		    case INT2:     return 4 * 2;
		    case INT3:     return 4 * 3;
		    case INT4:     return 4 * 4;
		    case BOOL:     return 1;
		}
		return 0;
	}
};
class BufferLayout {
    public:
		BufferLayout() = default;
	    BufferLayout(std::initializer_list<BufferElement> list) :m_element(list)
		{
	    	Calc_StrideOffset();
	    }
		uint16_t GetStride() const
		{
			return Stride;
		}
		static BufferLayout* UseDefaultLayout(DefinedLayout layout);

		std::vector<BufferElement>::iterator begin() { return m_element.begin(); }
		std::vector<BufferElement>::iterator end() { return m_element.end(); }
		const std::vector<BufferElement>::const_iterator begin()const { return m_element.begin(); }
		const std::vector<BufferElement>::const_iterator end() const{ return m_element.end(); }

		
private:
	void Calc_StrideOffset() {
		uint16_t t_offset = 0;
		Stride = 0;
		for (auto& element : m_element)
		{
			element.Offset = t_offset;
			t_offset += element.Size;
			Stride += element.Size;
		}
	}
	std::vector<BufferElement> m_element;
	uint16_t Stride;
};

class IBuffer
{
public:
	virtual void Bind() = 0;
	virtual void Unbind() = 0;

	static IBuffer* CreateBuffer(float* data, size_t size, BUFFER_TYPE buffertype);
	static IBuffer* CreateVertexBuffer(float* data, size_t size);
	static IBuffer* CreateVertexBuffer(size_t size);
	static IBuffer* CreateIndexBuffer(unsigned int* indices, int count);
	
	virtual void SetData(void* data, size_t size) = 0;

	static void FlushBufferState();

	virtual void SetBufferLayout(BufferLayout& layout) {}
	virtual BufferLayout GetBufferLayout() { return BufferLayout({}); }
	inline uint64_t GetCount() const {
		return m_count;
	}
	uint64_t m_count;

};

#endif // !G_BUFFER_H


