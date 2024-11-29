#pragma once
#include "pch.h"
#include "../core.h"


struct FramebufferSpecification
{
    uint32_t __width;
    uint32_t __height;
};
class Framebuffer
{
    public:
        Framebuffer(FramebufferSpecification& specs);

        void Bind();
        void UnBind();

        unsigned int GetFramebufferID()const;
        unsigned int GetColorAttachmentID()const;

        void Resize(uint32_t, uint32_t);
        void Create();
    private:
        unsigned int m_framebufferD ;
        unsigned int m_colorattachment;
        unsigned int m_depthattachment;
        
        FramebufferSpecification m_specs;
};