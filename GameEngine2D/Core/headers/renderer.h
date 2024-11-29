#ifndef RENDERER_H 
#define RENDERER_H
#include "VertexArray.h"
#include "rendercommand.h"


class Renderer {
	public:
		Renderer() = default;

		static void BeginScene();
		static void Submit(VertexArrayBuffer& vertexArrayBuffer);
		static void Submit(VertexArrayBuffer& vertexArrayBuffer, int count);
		static void EndScene();

};



#endif // 
