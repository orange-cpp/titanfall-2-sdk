#pragma once
#include <cstdint>
#include <uml/Vector3.h>

#pragma warning(push)
#pragma warning(disable: 4820)

namespace titanfall_2
{
    class UserCmd
    {
    public:
        int command_number;
        int tick_count;
        float command_time;
        uml::Vector3 worldViewAngles;
    private: uint8_t gap18[4];
    public:
        uml::Vector3 localViewAngles;
        uml::Vector3 attackangles;
        uml::Vector3 move;
        int buttons;
        uint8_t impulse;
        short weaponselect;
        int meleetarget;
    private:uint8_t gap4C[24];
        char headoffset;
    private:uint8_t gap65[11];
        uml::Vector3 cameraPos;
        uml::Vector3 cameraAngles;
    private:uint8_t gap88[4];
    public:
        int tickSomething;
        int dword90;
        int predictedServerEventAck;
        int dword98;
        float frameTime;
     private:uint8_t gap[9];
    public:
        float time;
    };
}
#pragma warning(pop)