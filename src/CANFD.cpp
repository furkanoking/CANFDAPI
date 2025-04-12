/**
 * @file CANFD.cpp
 * @author Furkan Ozen (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "CANFD.h"
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <linux/can.h>
#include <linux/can/raw.h>
/**
 * @brief Construct a new CANFD::CANFD object
 * 
 * 
 */

std::map<std::string, int> CANFD::m_msocket_map;

CANFD::CANFD(){
    ReceivedOriginalData.reserve(4);
}

/**
 * @brief Destroy the CANFD::CANFD object
 * 
 */

CANFD::~CANFD(){

}

/**
 * @brief 
 * 
 * @param mysocketname 
 * @param test_mode 
 * @return true 
 * @return false ıf the socket cannot be created, It will returns false
 */
bool CANFD::CreateSocket(const std::string mysocketname,const std::string Interface_name,const bool test_mode,const bool IsCANFD){
    if(int sock = socket(PF_CAN,SOCK_RAW, CAN_RAW); sock < 0) {
        perror("Socket problem");
        std::cout<<"Socket cannot be created in the name of"<<mysocketname<<"\n";
        return false;
    }

    else {
        m_msocket_map[mysocketname] = sock;
        m_isockfd = sock;
        m_btest_mode = test_mode;
        CANFDCheck(IsCANFD);
        setNetworkInterface(Interface_name);

        return true;
    }
}

void CANFD::CANFDCheck(bool CANFD){
    if(CANFD){
        int enable_canfd{1};
        // * SOL_CAN_RAW emphasizes we will use CAN protocol
        // * CAN_RAW_FD_FRAMES means we will use CANFD
        // 
        setsockopt(m_isockfd,SOL_CAN_RAW,CAN_RAW_FD_FRAMES,&enable_canfd,sizeof(int));
    
        if(m_btest_mode){
            int loopbackandreceive = 1;
            // In test mode, the socket receive what it sends 
            setsockopt(m_isockfd, SOL_CAN_RAW, CAN_RAW_LOOPBACK, &loopbackandreceive, sizeof(loopbackandreceive));
            setsockopt(m_isockfd,SOL_CAN_RAW,CAN_RAW_RECV_OWN_MSGS,&loopbackandreceive,sizeof(loopbackandreceive));
        }
    
    }

    else {
        //TODO
    }
}


void CANFD::setNetworkInterface(const std::string Interface_name){
    struct ifreq the_ifreq;
    std::strcpy(the_ifreq.ifr_name,Interface_name.c_str());

    // take the index of the Interface
    if(int interface_check = ioctl(m_isockfd, SIOCGIFINDEX, &the_ifreq);interface_check <0)
    {
        std::cout<<"There is no interface in the name of "<<Interface_name<<std::endl;
    }   
    struct sockaddr_can the_sockaddr_can = {};
    the_sockaddr_can.can_family = AF_CAN;
    the_sockaddr_can.can_ifindex = the_ifreq.ifr_ifindex;

    if(bind(m_isockfd,(struct sockaddr *)&the_sockaddr_can,sizeof(the_sockaddr_can))<0){
        std::cout<<"There is an error in the binding"<<std::endl;
    }

    else {
        std::cout<<"Binding is successfull"<<std::endl;
    }
}




void CANFD::threadSending(const std::string mysocketname, const int ID, const int frame_length,  const char* the_real_data) {
    binary_check.acquire();
    struct canfd_frame new_frame;
    new_frame.can_id=ID;
    new_frame.len = frame_length;
    new_frame.flags = NORMAL_FD_SPEED;

    int socket_value {-99};
    try {
        socket_value = m_msocket_map.at(mysocketname);
    } catch(const std::out_of_range& e){
        std::cerr<<"Important error !!! socketname is out of range. There is no name in that socket \n";
        std::cerr<<"There will be no sending \n";
        return;
    }

    for(int i = 0;i<frame_length;i++){
        new_frame.data[i] = static_cast<u_int8_t>(the_real_data[i]);
    }
    // It sends the message
    std::cout<<"Trying the sending message"<<std::endl;
    write(m_msocket_map.at(mysocketname),&new_frame,sizeof(new_frame));
    binary_check.release();
}


void CANFD::threadListening(std::string mysocketname) {


    int socket_value {-99};
    struct canfd_frame the_listening_frame;
    CANFDStruct my_CANFDStruct;

    try {
        socket_value = m_msocket_map.at(mysocketname);
    } catch(const std::out_of_range& e){
        std::cerr<<"Important error !!! socketname is out of range. There is no name in that socket \n";
        std::cerr<<"There will be no listening \n";
        CANFDStruct CANFD;
        CANFD.CANID=99;
    }

    while(1){
        int nbytes = read(socket_value,&the_listening_frame,sizeof(the_listening_frame));
        if(nbytes > 0){
            std::cout<<"There is a message came "<<std::endl;
            if(the_listening_frame.can_id != m_iID){
                std::cout<<"Receiving message is not suitable ID. It will be not read"<<std::endl;
                continue;
            }
            //char* received_Data = new char [the_listening_frame.len];
            my_CANFDStruct.CANID = the_listening_frame.can_id;
            my_CANFDStruct.length= the_listening_frame.len;
            my_CANFDStruct.flags = the_listening_frame.flags;
            for(int i = 0; i< the_listening_frame.len;i++){
                std::cout<<"0x"<<std::hex<<static_cast<int>(the_listening_frame.data[i])<<"\n";
                my_CANFDStruct.data[i] = the_listening_frame.data[i];
                //received_Data[i] = static_cast<u_int8_t>(the_listening_frame.data[i]);
            }

        }
    }
}


void CANFD::SendMessage(const std::string mysocketname, const int ID, const int frame_length,  const char* the_real_data){
    std::thread ThreadSending(&CANFD::threadSending,this,mysocketname,ID, frame_length,the_real_data);
    //ThreadSending.join(); // the reason we are doing this waiting the finish the execution of the thread
    ThreadSending.detach();
}

void CANFD::ListenSocket(const std::string mysocketname){
    std::thread threadListening(&CANFD::threadListening,this, mysocketname);
    //threadListening.join();
    threadListening.detach();
}

void CANFD::operator()() const{
    for(auto x: m_msocket_map)
    {
        std::cout<<"The socket map has "<<x.first<<" "<<x.second<<std::endl;
    }
}

CANFD::operator bool() const {
    return true;
}

void CANFD::SendMessage(const std::string mysocketname, const int ID, const int frame_length,  int the_real_data) {

    std::thread ThreadSendingintData (&CANFD::threadSendingintData,this,mysocketname,ID,frame_length,the_real_data);
    //ThreadSendingintData.join();
    ThreadSendingintData.detach();

}

void CANFD::threadSendingintData(const std::string mysocketname, const int ID, const int frame_length,  int the_real_data) {

    binary_check.acquire();

    struct canfd_frame new_frame;
    new_frame.can_id=ID;
    new_frame.len = frame_length;
    new_frame.flags = NORMAL_FD_SPEED;

    int socket_value {-99};
    try {
        socket_value = m_msocket_map.at(mysocketname);
    } catch(const std::out_of_range& e){
        std::cerr<<"Important error !!! socketname is out of range. There is no name in that socket \n";
        std::cerr<<"There will be no sending \n";
        return;
    }
    for(int i = 0;i<frame_length;i++){

        u_int8_t byte_Data = (the_real_data>>(i*8)) & 0xFF;
        new_frame.data[i] = byte_Data;
    }
    // It sends the message
    std::cout<<"Trying the sending message"<<std::endl;
    write(m_msocket_map.at(mysocketname),&new_frame,sizeof(new_frame));
    binary_check.release();
}



void CANFD::setID(u_int32_t ReceiverID) {
    m_iID = ReceiverID;
}