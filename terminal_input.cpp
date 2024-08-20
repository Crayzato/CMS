#include <iostream>
#include <map>
#include <fstream>
#include <regex>

#include "data.hpp"
#include "json.hpp"
using json = nlohmann::json;

#include "terminal_input.hpp"

using namespace term;

TerminalStart::TerminalStart( data::Bin &b, std::string config_path )
:Bin{b}{
    cmd = -1;

    std::ifstream f( config_path.c_str() );
    json conf = json::parse( f );

    cmds = conf["cmds"];
    cmdsCount = conf["cmds_c"];

}

int TerminalStart::getcmd()
{
    std::cout << "Enter Command: ";
    std::string cmdString;
    std::cin >> cmdString;

    cmd = -1;
    args.clear();
    for ( int i = 0; i < cmdsCount; i++ )
    {
        std::string matchString = cmds[i]["term"];
        int commandLength = matchString.length() - 2;
        std::regex match_cmd( matchString.substr(1, commandLength) );
        if ( std::regex_match( cmdString, match_cmd ) )
        {
            cmd = i;
            std::string dump;
            std::string curr_arg;
            if ( std::cin.peek() != '\n' )
            {
                while ( std::cin >> curr_arg ) 
                {
                    args.push_back(curr_arg); 
                    if ( std::cin.peek() == '\n' ) { break; }
                }
                if ( args.size() < cmds[i]["arg_c"] )
                {
                    cmd = -1;
                    std::cout << "ERR::WRONG NUMBER OF ARGUMENTS" << std::endl;
                }
            }
        }
    }
    if ( cmd != -1 ) { std::cout << "[" << cmds[cmd]["name"] << "]" << std::endl; }
    return cmd;
}

int TerminalStart::performAction()
{
    std::regex staffR( "Staff|staff" );
    std::regex clientR( "Client|client" );

    std::regex firstR( "First|first|F|f" );
    std::regex lastR( "Last|last|L|l" );

    std::string _type;

    std::cout << "Processing Command..." << std::endl;

    switch ( cmd ) 
    {
        case -1:
        {
            std::cout << "ERR::INVALID COMMAND; Enter help command for help" << std::endl;
            break;
        }
        
        case 0:
        {
            if ( std::regex_match( args.at( 0 ), staffR ) ) 
            {
                std::cout << "Creating new Staff...";
                data::Bin::Staff newStaff(Bin);
                std::cout << "done" << std::endl;
                std::cout << "------------------------------" << std::endl;
                newStaff.print();
                std::cout << "------------------------------" << std::endl;

            }
            else if ( std::regex_match( args.at( 0 ), clientR ) ) 
            {
                //data::Bin::Client newClient(Bin);
            }
            else 
            {
                std::cout << "ERR::INVALID USER TYPE::ARG (1) OF COMMAND (create)" << std::endl;
                return 1;
            }
            break;
        }
        
        case 1:
        {
            _type = args.at( 0 );
            data::Bin::Staff s = Bin.getStaff( stoi( args.at( 1 ) ) );

            if ( std::regex_match( _type, firstR ) ) 
            {
                s.addFirst( args.at( 2 ) );
                std::cout << "------------------------------" << std::endl;
                s.print();
                std::cout << "------------------------------" << std::endl;
            }
            break;
        }
        
        case 2:
        {
            return -1;
            std::cout << "Closing..." << std::endl;
            break;
        }

    }
    return 0;
}

