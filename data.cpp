#include <string>
#include <iostream>
#include <fstream>

#include "data.hpp"
#include "json.hpp"
using json = nlohmann::json;

using namespace data;

// Bin Root
Bin::Bin( std::string _path )
{
    currID = 0;
    path = _path;

    std::ifstream f(_path);
    if ( f ) 
    {
        json fileData = json::parse( f );
        for ( int i = 0; i < fileData["staff"].size(); i++ )
        {
            Bin::Staff s(*this);
        }
    }

    f.close();
}

int Bin::generateID( userType _type )
{
    std::string ret = std::to_string(currID);
    currID++;
    return std::stoi(std::to_string(static_cast<int>(_type)) + ret);
}

Bin::Staff Bin::getStaff( int id )
{
    for ( int i = 0; i < staffList.size(); i++ )
    {
        if ( staffList.at(i).getID() == id ) { return staffList.at(i); }
    }
}

void Bin::close()
{
    std::ifstream f(path);
    if ( f )
    { 
        f.close();
        remove( path.c_str() );
    }
    
    json saveData;
    saveData["staff"] = {};
    for ( int i = 0; i < staffList.size(); i++ )
    {
        saveData["staff"][i]["id"] = staffList.at(i).getID();
        saveData["staff"][i]["first"] = staffList.at(i).getFirst();
        saveData["staff"][i]["last"] = staffList.at(i).getLast();
    }
    std::ofstream o(path);
    o << std::setw(4) << saveData << std::endl;
}

// Admin

// Staff
Bin::Staff::Staff( Bin &b )
:pBin{b}{
    id = b.generateID( userType::staff );
    firstName = "Empty";
    lastName = "Empty";
    b.staffList.push_back(*this);
}

int Bin::Staff::addFirst( std::string _name )
{
    firstName = _name;
    return id;
}

int Bin::Staff::addLast( std::string _name )
{
    lastName = _name;
    return id;
}

int Bin::Staff::getID()
{
    return id;
}

std::string Bin::Staff::getFirst()
{
    return firstName;
}

std::string Bin::Staff::getLast()
{
    return lastName;
}

void Bin::Staff::print()
{
    std::cout << "Staff: " << firstName << std::endl;
    std::cout << " - (ID: " << id << ")" << std::endl; 
}


// Client


