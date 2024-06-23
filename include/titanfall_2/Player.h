//
// Created by Vlad on 6/23/2024.
//

#pragma once

#include "titanfall_2/Object.h"
#include <cstdint>


namespace titanfall2
{
    enum class LifeState : int
    {
        ALIVE = 0,
        DYING,
        DEAD,
        RESPAWNABLE,
        DISCARDBODY,
    };
    enum class Flags : uint32_t
    {
        FL_ONGROUND = 1 << 0,
        FL_DUCKING = 1 << 1,
        FL_WATERJUMP = 1 << 2,
        FL_ONTRAIN = 1 << 3,
        FL_INRAIN = 1 << 4,
        FL_FROZEN = 1 << 5,
        FL_ATCONTROLS = 1 << 6,
        FL_CLIENT = 1 << 7,
        FL_FAKECLIENT = 1 << 8,
        FL_INWATER = 1 << 9,
    };

    class Player : public Object
    {
    public:
        static Player* GetByIndex(size_t index);

        Player() = delete;
        Player(Player& other) = delete;

        [[nodiscard]]
        int Health() const;

        [[nodiscard]]
        int MaxHealth() const;

        [[nodiscard]]
        bool Alive() const;

        [[nodiscard]]
        LifeState LifeState() const;

        [[nodiscard]]
        Flags Flags() const;

        [[nodiscard]]
        int TeamNumber() const;

        [[nodiscard]]
        bool InTitan() const;
    };

}