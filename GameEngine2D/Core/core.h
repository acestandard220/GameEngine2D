#ifndef G_DEFINES_H
#define G_DEFINES_H
#include <cassert>
#include <cmath>
#include <memory>

#ifdef GAME_ENGINE_2D_BUILD_DLL
#define GAME_ENGINE_2D_API __declspec(dllexport)
#else
#define GAME_ENGINE_2D_API __declspec(dllexport)
#endif 

template <typename T>
using Ref = std::shared_ptr<T>;




#define GAME_ENGINE_2D_ASSERT(x) assert((x))

#define GAME_ENGINE_2D_BIND_FN(fn) std::bind(&fn,this,std::placeholder::_1)

#define GAME_ENGINE_2D_UNUSED(x) void(x)

#define GAME_ENGINE_2D_FUNC_DEPRECATED __declspec(deprecated)

#define GAME_ENGINE_2D_FORCE_INLINE __forceinline

#define GAME_ENGINE_2D_NO_RETURN __declspec(noreturn)


#define GEM_CMP(x,y) ((x == y) ? true :false) 
#define GEM_SQR(x) sqrtf(x)

#define GEM_SIN(x) sin(x)
#define GEM_COS(x) cos(x)
#define GEM_TAN(x) tan(x)

#define GEM_ASIN(x) asin(x)
#define GEM_ACOS(x) acos(x)
#define GEM_ATAN(x) tan(x)

#define GEM_RAD2DEG(x) ((x) * 57.295754f)
#define GEM_DEG2RAD(x) ((x) * 0.0174533f)

#define GAME_ENGINE_2D_OPENGL_ERROR()  \
    { \
        GLenum error = glGetError(); \
        if (error != GL_NO_ERROR) { \
            std::cout << "OpenGL error in function " << __FUNCTION__ \
                      << ": " << error << std::endl; \
        } \
    }
#define GAME_ENGINE_2D_OPEGNL_ERROR_PARAM(x)  \
    { \
        GLenum error = glGetError(); \
        if (error != GL_NO_ERROR) { \
            std::cout << "OpenGL error in function " << __FUNCTION__ \
                      << ": " << error << std::endl<<x<<std::endl; \
        } \
    }

#define GAME_ENGINE_2D_OPENGL_LOCATION_ERROR(x)\
    { \
      if(x == -1){\
          std::cout << "The uniform was not found\n";\
      }\
    }

#define GAME_ENGINE_2D_STRINGIFY(x) #x
#define GAME_ENGINE_2D_COMPILER_WARN(x) _Pragma(GAME_ENGINE_2D_STRINGIFY(message(x)))











/// PATHS
#define GAME_ENGINE_2D_QUAD_VERTEX "P:/Projects/VS/GameEngine2D/GameEngine2D/Core/assets/builtin_shaders/quads_vertex.glsl"

#define GAME_ENGINE_2D_QUAD_FRAGMENT "P:/Projects/VS/GameEngine2D/GameEngine2D/Core/assets/builtin_shaders/quads_fragment.glsl"

#endif
