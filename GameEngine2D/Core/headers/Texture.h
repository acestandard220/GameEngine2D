#pragma once
#include "pch.h"

class Texture {
    public:

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual uint32_t GetHeight() const = 0;
        virtual uint32_t GetWidth() const = 0;
        virtual unsigned int GetTextureID()const = 0;
        static Texture* CreateTexture2D(const char*);
        virtual void Reload() =0;
        virtual ~Texture() = default;

        bool isLoaded;
    private:


};


class Texture2D : public Texture {
    public:
        Texture2D(const char* path);
        virtual void Bind() override;
        virtual void Unbind() override;

        virtual uint32_t GetHeight() const override;
        virtual uint32_t GetWidth() const override;
        virtual  unsigned int GetTextureID()const
        {
            return m_TextureID;
        }

        virtual void Reload()override;
        virtual ~Texture2D() override;

    private:
        bool LoadTexture();
    private:
        unsigned int m_TextureID;

        std::string m_path;
        uint32_t m_height;
        uint32_t m_width;
        uint8_t m_nChannels;

        unsigned char* data;
};


class Texture3D :public Texture {

};