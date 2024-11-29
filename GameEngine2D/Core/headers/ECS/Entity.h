#pragma once
#include "pch.h"
#include "../core.h"
namespace GE2D
{
    namespace ECS
    {
        constexpr uint32_t MAX_ENTITIES_SUPPORTED = 10;
        constexpr uint32_t MAX_COMPONENT_SUPPORTED = 10;

        using Entity = uint32_t;
        using Signature = std::bitset<MAX_COMPONENT_SUPPORTED>;


        template <typename T>
        using Queue = std::queue<T>;

        template <typename T, typename F>
        using uMapping = std::unordered_map<T, F>;

        /// @brief 
        /// Responsible Creation and Destruction of Entities
        /// @brief 


        class EntityManager
        {
        public:
            EntityManager();

            Entity CreateEntity();
            bool DestroyEntity(Entity e);


            bool SetSignature(Entity e, Signature signature);
            Signature GetSignature(Entity e);

        private:
            Queue<int> mAvailableIDS;
            uint32_t nIDUse;
            std::array<Signature, MAX_ENTITIES_SUPPORTED> mSignatures;
        };

    }
}
