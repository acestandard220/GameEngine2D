#include "Framebuffer.h"

Framebuffer::Framebuffer(FramebufferSpecification& specs):m_specs(specs)
{
	Create();
}

void Framebuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER,m_framebufferD);
	glViewport(0, 0, m_specs.__width, m_specs.__height);
}

void Framebuffer::UnBind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

unsigned int Framebuffer::GetFramebufferID() const
{
	return m_framebufferD;
}

unsigned int Framebuffer::GetColorAttachmentID() const
{
	return m_colorattachment;
}

void Framebuffer::Resize(uint32_t w, uint32_t h)
{
	m_specs.__width = w;
	m_specs.__height = h;
	
	glDeleteFramebuffers(1, &m_framebufferD);
	glDeleteTextures(1, &m_colorattachment);
	glDeleteTextures(1, &m_depthattachment);
	
	Create();
	
}

void Framebuffer::Create()
{
	glGenFramebuffers(1, &m_framebufferD);
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferD);

	glGenTextures(1, &m_colorattachment);
	glBindTexture(GL_TEXTURE_2D, m_colorattachment);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_specs.__width, m_specs.__height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorattachment, 0);


	glGenTextures(1, &m_depthattachment);
	glBindTexture(GL_TEXTURE_2D, m_depthattachment);
	//glTextureStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_specs.__width, m_specs.__height);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_specs.__width, m_specs.__height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depthattachment, 0);


	GAME_ENGINE_2D_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}