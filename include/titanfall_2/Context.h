//
// Created by Vlad on 6/23/2024.
//

#pragma once
#include <functional>
#include <optional>
#include <mutex>
#include <Windows.h>
#include "titanfall_2/UserCmd.h"


class IDXGISwapChain;

namespace titanfall_2
{
    class Context
    {
        friend bool __fastcall HookedCreateMove(__int64 ThisPtr, float a2, titanfall_2::UserCmd* cmd, unsigned __int8 a4);
        friend HRESULT __fastcall hPresent(IDXGISwapChain* pSwapChain, uint32_t SyncInterval, uint32_t Flags);

    public:
        [[nodiscard]]
        static Context& Get();
        Context(const Context& other) = delete;
        void SetOnCreateMove(const std::function<void(titanfall_2::UserCmd* cmd)>& func);
        void SetOnPresent(const std::function<void(IDXGISwapChain* swapChain)>& func);
    private:
        std::mutex m_createMoveMutex;
        std::optional<std::function<void(titanfall_2::UserCmd* cmd)>> m_onCreateMovePayload;

        std::mutex m_presentMutex;
        std::optional<std::function<void(IDXGISwapChain* chain)>> m_onSwapChainPresent;

        Context(/* args */);
        ~Context();
    };
}