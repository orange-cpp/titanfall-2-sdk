//
// Created by Vlad on 6/23/2024.
//

#pragma once
#include <cstddef>


namespace titanfall2
{
    class Object
    {
    protected:
        template<class type>
        [[nodiscard]] inline type& GetByOffset(const std::ptrdiff_t offset) const
        {
            return *reinterpret_cast<type*>((uintptr_t)this + offset);
        }
        template<size_t id, typename ReturnType, typename... TArgs>
        ReturnType inline CallVirtual(TArgs... ArgList)
        {
            using func = ReturnType(__thiscall*)(void*, decltype(ArgList)...);
            return (*static_cast<func**>(this))[id](this, ArgList...);
        }
    };
}