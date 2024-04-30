#pragma once
#include "Command.h"
#include "SoundLocator.h"
namespace bdnG
{
    class WakaCommand final : public bdnE::Command
    {
    public:
        WakaCommand() : Command() 
        {
            //Register waka sound
            bdnE::SoundLocator::get_sound_system().LoadSound("waka.mp3",1);
        }

        void Execute() override {
            bdnE::SoundLocator::get_sound_system().PlaySound(1, 1, 100, 0);
        }
    private:

    };
}