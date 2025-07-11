#ifndef DATABASE_H
#define DATABASE_H

#include "vector"
#include "Arduino.h"

class Database
{
    public:
        std::vector<String> List;
        Database();
    private:
        int number;
};


#endif