#pragma once
#include "../core.h"
#include "ComponentArray.h"

namespace GE2D
{
    namespace ECS
    {
        

        static Signature BASE_SIGNATURE{ 0b0000000000 };

        class ISystem
        {
        public:
            virtual void OnUpdate(void*) = 0;
            std::set<Entity> enitites;
        };


        class SystemManager
        {
        public:
            template <typename T>
            inline std::shared_ptr<T> RegisterSystem()
            {

                const char* name = typeid(T).name();

                GAME_ENGINE_2D_ASSERT(mSystems.find(name) == mSystems.end() && "System has already been registered");
                auto system = std::make_shared<T>();
                mSystems.insert({ name, system });

                mSignatures.insert({ name, BASE_SIGNATURE });
                mSignatures[name].reset();

                return system;
            }

            template <typename T>
            inline void SetSignature(Signature signature)
            {
                const char* name = typeid(T).name();
                GAME_ENGINE_2D_ASSERT(mSignatures.find(name) != mSignatures.end() && "System has not been registered");

                mSignatures[name] = signature;

            }

            template <typename T>
            inline Signature GetSignature()
            {
                const char* name = typeid(T).name();
                if (mSignatures.find(name) == mSignatures.end())
                    return std::bitset<MAX_COMPONENT_SUPPORTED>(0b0000000000);
                return mSignatures[name];
            }

            template <typename T>
            inline std::shared_ptr<ISystem> GetSystem()
            {
                const char* name = typeid(T).name();
                auto it = mSystems.find(name);
                if (it == mSystems.end())
                    return nullptr;
                return mSystems[name];
            }
            
            void OnEntityDestroued(Entity e);
            void OnEntitySignatureUpdate(Entity e, Signature signature);

            inline void OnUpdate(void* co)
            {
                for (auto& pair : mSystems)
                {
                    auto& system = pair.second;
                    system->OnUpdate(co);
                }
            }

        private:
            uMapping<const char*, Signature> mSignatures{};
            uMapping<const char*, std::shared_ptr<ISystem>> mSystems{};
        };

    }
 }