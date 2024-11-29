#include "renderer.h"

void Renderer::BeginScene()
{
}

void Renderer::Submit(VertexArrayBuffer& vertexArrayBuffer)
{
	vertexArrayBuffer.Bind();
	RenderCommand::DrawIndexed(vertexArrayBuffer);

}

void Renderer::Submit(VertexArrayBuffer& vertexArrayBuffer, int count)
{
	vertexArrayBuffer.Bind();
	RenderCommand::DrawArray(vertexArrayBuffer, count);
}

void Renderer::EndScene()
{
}
