#pragma once

#include <string>
#include <vector>

namespace data
{
    enum class userType {
        admin,
        staff,
        client,
        temp
    };

    class Bin;

    class Bin
    {
        public:
            class Staff;
            class Client;

            Bin( std::string _path );

            std::string path;

            int generateID( userType _type );

            Staff getStaff( int id );
            Staff getClient( int id );

            void close();
        private:
            int currID;

            int clientCount;
            std::vector<Staff> clientList;
            int staffCount;
            std::vector<Staff> staffList;
            
    };

    class Bin::Staff
    {
        private:
            Bin &pBin;
            int id;
            std::string firstName;
            std::string lastName;

        public:
            Staff( Bin &b );

            int addFirst( std::string _name );
            int addLast( std::string _name );

            int getID();

            std::string getFirst();
            std::string getLast();

            void print();

    };

    class Bin::Client
    {
        private:
            Bin &pBin;
            int id;
            std::string firstName;
            std::string lastName;

        public:
            Client( Bin &b );

            int addFirst( std::string _name );
            int addLast( std::string _name );
    };
} // namespace data


