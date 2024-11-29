#include "rendererAPI.h"

void RendererAPI::DrawIndexed(VertexArrayBuffer& vertexarray)
{
	glDrawElements(GL_TRIANGLES, vertexarray.GetIndexCount(), GL_UNSIGNED_INT, 0);
}

void RendererAPI::DrawArray(VertexArrayBuffer& vertexarray,int count)
{
	glDrawArrays(GL_TRIANGLES, 0,count);
}

void RendererAPI::SetClearColor(glm::vec4& color)
{
	glClearColor(color.x, color.y, color.z, color.w);
}

void RendererAPI::ClearColorBuffer()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void RendererAPI::ClearDepthBuffer()
{
	glClear(GL_DEPTH_BUFFER_BIT);
}

void RendererAPI::ClearColourDepthStencil()
{
	//To add stencil buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}
