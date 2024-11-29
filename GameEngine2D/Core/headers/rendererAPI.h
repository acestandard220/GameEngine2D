#pragma once
#include <VertexArray.h>



class RendererAPI {
	public:
	    void DrawIndexed(VertexArrayBuffer& vertexarray);
		void DrawArray(VertexArrayBuffer& vertexarray,int count);

		void SetClearColor(glm::vec4& color);
		void ClearColorBuffer();
		void ClearDepthBuffer();
		void ClearColourDepthStencil();
    private:
};