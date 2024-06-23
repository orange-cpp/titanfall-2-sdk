//
// Created by Vlad on 6/23/2024.
//

#include <MinHook.h>
#include <Sig/Sig.h>
#include <stdexcept>

#include "titanfall_2/Context.h"
#include "titanfall_2/Signatures.h"
#include <Windows.h>
#include <psapi.h>
#include "titanfall_2/UserCmd.h"

typedef bool(__fastcall* ClientmodeCreateMoveFn)(__int64, float, titanfall_2::UserCmd*, unsigned __int8);
typedef HRESULT(__fastcall* PresentFn)(IDXGISwapChain*, UINT, UINT);

ClientmodeCreateMoveFn originalClientmodeCreateMove = nullptr;
PresentFn originalPresent = nullptr;

namespace titanfall_2
{
    Context& Context::Get()
    {
        static Context obj;

        return obj;
    }
    bool __fastcall HookedCreateMove(const __int64 ThisPtr, const float a2, UserCmd* cmd, const uint8_t a4)
    {
        const auto Ret = originalClientmodeCreateMove(ThisPtr, a2, cmd, a4);
        static auto& context = Context::Get();
        {
            std::scoped_lock lock(context.m_createMoveMutex);

            if (context.m_onCreateMovePayload.has_value())
                context.m_onCreateMovePayload.value()(cmd);
        }
        return Ret;
    }
    HRESULT hPresent(IDXGISwapChain* pSwapChain, uint32_t SyncInterval, uint32_t Flags)
    {
        static auto& context = Context::Get();
        {
            std::scoped_lock lock(context.m_presentMutex);

            if (context.m_onSwapChainPresent.has_value())
                context.m_onSwapChainPresent.value()(pSwapChain);
        }
        return originalPresent(pSwapChain, SyncInterval, Flags);
    }
    Context::Context()
    {
        MH_Initialize();

        const auto clientModuleHandle = GetModuleHandleA("client.dll");
        const auto dxgiModuleHandle = GetModuleHandleA("dxgi.dll");

        MODULEINFO clientModuleInfo;
        MODULEINFO dxgiModuleInfo;

        GetModuleInformation(GetCurrentProcess(), clientModuleHandle, &clientModuleInfo, sizeof(MODULEINFO));
        GetModuleInformation(GetCurrentProcess(), clientModuleHandle, &dxgiModuleInfo, sizeof(MODULEINFO));

        const auto createMove = Sig::find(clientModuleHandle,
                                          clientModuleInfo.SizeOfImage, signatures::createMove);

        auto createMoveHookRes = MH_CreateHook(const_cast<void*>(createMove),
                                 &HookedCreateMove,
                                 reinterpret_cast<void **>(&originalClientmodeCreateMove));

        if (createMoveHookRes != MH_STATUS::MH_OK)
            throw std::runtime_error("Failed to hook CreateMove");

        const auto present = Sig::find(dxgiModuleHandle,
                                       dxgiModuleInfo.SizeOfImage, signatures::present);

        auto presentHookRes = MH_CreateHook(const_cast<void*>(present),&hPresent,
                                            reinterpret_cast<void **>(&originalPresent));

        if (presentHookRes != MH_STATUS::MH_OK)
            throw std::runtime_error("Failed to hook Present");

        // ReSharper disable once CppZeroConstantCanBeReplacedWithNullptr
        MH_EnableHook(MH_ALL_HOOKS);
    }
    Context::~Context()
    {
        // ReSharper disable once CppZeroConstantCanBeReplacedWithNullptr
        MH_DisableHook(MH_ALL_HOOKS);
        MH_Uninitialize();
    }

    void Context::SetOnCreateMove(const std::function<void(UserCmd*)> &func)
    {
        std::scoped_lock lock(m_createMoveMutex);

        m_onCreateMovePayload = func;
    }

    void Context::SetOnPresent(const std::function<void(IDXGISwapChain *swapChain)> &func)
    {
        std::scoped_lock lock(m_presentMutex);

        m_onSwapChainPresent = func;
    }
}
