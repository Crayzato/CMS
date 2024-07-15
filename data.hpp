#include <string>

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
        private:
            class Staff;

            int currID;

            int clientCount;
            int staffCount;
        public:
            Bin();

            int generateID( userType _type );
            
    };

    class Bin::Staff
    {
        private:
            Bin &pBin;
            int id;
            std::string name;

        public:
            Staff( Bin &b );


    };
} // namespace data


