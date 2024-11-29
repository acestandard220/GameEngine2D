#pragma once
#include "VertexArray.h"
#include "rendererAPI.h"

class RenderCommand {
	public:
	    inline static void DrawIndexed(VertexArrayBuffer& vertexarray,int count =0)
	    {
	    	s_RendererAPI->DrawIndexed(vertexarray,count);
		}

		inline static void DrawArray(VertexArrayBuffer& vertexarray,int count) {
			s_RendererAPI->DrawArray(vertexarray, count);
		}
		inline static void SetClearColor(glm::vec4 color)
		{
			s_RendererAPI->SetClearColor(color);
		}
		inline static void ClearColorBuffer()
		{
			s_RendererAPI->ClearColorBuffer();
		}
		inline static void ClearDepthBuffer()
		{
			s_RendererAPI->ClearDepthBuffer();
		}
		inline static void ClearCDS()
		{
			s_RendererAPI->ClearColourDepthStencil();
		}

	    static RendererAPI* s_RendererAPI;	    
};