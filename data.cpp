#include <string>

#include "data.hpp"

using namespace data;

// Bin Root
Bin::Bin()
{
    currID = 0;
}

int Bin::generateID( userType _type )
{
    std::string ret = std::to_string(currID);
    currID++;
    return std::stoi(std::to_string(static_cast<int>(_type)) + ret);
}

// Admin

// Staff
Bin::Staff::Staff( Bin &b )
:pBin{b}{
    id = b.generateID( userType::staff );
}


// Clients


