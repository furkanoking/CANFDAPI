#ifndef _CAN_H_
#define _CAN_H_

#include <iostream>

class CAN {

    public:
        virtual bool CreateSocket(std::string mysocketname) = 0;
        virtual int SendMessage() = 0;
        virtual int ListenSocket() = 0;
};

void ActivateCAN(CAN* myCAN);



#endif