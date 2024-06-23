//
// Created by Vlad on 6/23/2024.
//

#pragma once

namespace titanfall_2::signatures
{
    inline auto createMove = "48 89 5C 24 ? 57 48 83 EC 30 48 8B 0D ? ? ? ? 0F 29 74 24 ? 41 0F";
    inline auto present = "? ? ? ? ? 55 56 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 37 41 8B F0";
}