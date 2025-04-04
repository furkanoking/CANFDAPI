#ifndef _CANFD_H_
#define _CANFD_H_

#include "CAN.h"
#include <map>
class CANFD final: public CAN  {
    public:
        CANFD();
        ~CANFD();

        CANFD& operator=(const CANFD& myCANFD) = default;
        CANFD(const CANFD& myCANFD) = default;
        CANFD& operator=(CANFD&& myCANFD) = default;
    
    private:
        [[nodiscard]] bool CreateSocket(std::string mysocketname) override;
        int SendMessage() override;
        int ListenSocket() override;

        // Store the value of the sockets with the string name
        std::map<std::string, int> socket_map;
};












#endif