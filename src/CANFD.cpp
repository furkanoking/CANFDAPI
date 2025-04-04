#include "CANFD.h"
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <linux/can.h>
#include <linux/can/raw.h>

CANFD::CANFD(){
    if(!socket_map.empty()){
        socket_map.clear();
    }
}

CANFD::~CANFD(){
    if(!socket_map.empty()){
        socket_map.clear();
    }
}

bool CANFD::CreateSocket(std::string mysocketname){
    if(int sock = socket(PF_CAN,SOCK_RAW, CAN_RAW); sock < 0) {
        perror("Socket problem");
        std::cout<<"Socket cannot be created in the name of"<<mysocketname<<"\n";
        return false;
    }

    else {
        socket_map[mysocketname] = sock;
        return true;
    }
}