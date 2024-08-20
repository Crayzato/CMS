#pragma once

#include <map>

#include "data.hpp"
#include "json.hpp"
using json = nlohmann::json;

namespace term
{
    class TerminalStart
    {
        private:
            data::Bin &Bin;
            int cmd;

            json cmds;
            int cmdsCount;

            std::vector<std::string> args;
        
        public:
            TerminalStart( data::Bin &b, std::string config_path = "cmd_config.json" );

            std::string fetchcmd();
            int getcmd();

            int performAction();
    };
} // namespace term

