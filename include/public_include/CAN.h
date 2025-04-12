#ifndef _CAN_H_
#define _CAN_H_
/**
 * @file CAN.h
 * @author Furkan Ozen
 * @brief 
 * @version 0.1
 * @date 2025-04-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */


 #define MAX_CANFD_LENGTH 64
#include <iostream>


struct CANFDStruct {
    u_int32_t CANID;
    u_int8_t length;
    u_int8_t flags;
    u_int8_t data[MAX_CANFD_LENGTH] __attribute__((aligned(8)));
};


/**
 * @brief CAN Interface 
 * 
 */
class CAN {

    public:
        /**
         * @brief Create a Socket object
         * 
         * @param mysocketname Enter the socketname you want to create
         * @param test_mode    If you want to receive the message you sent, make it true
         * @return true        If the socket is created successfully, return true
         * @return false 
         */
        virtual bool CreateSocket(const std::string mysocketname, const std::string Interface_name, const bool test_mode, const bool IsCANFD) = 0;
        
        /**
         * @brief This function is for sending a message to a specific 
         * 
         * @param socketname  The socket name
         * @param ID The Message ID
         * @param frame_length The data length in bytes
         * @param the_real_data The real data
         */

        virtual void SendMessage(const std::string mysocketname, const int ID, const int frame_length,  const char* the_real_data) = 0;


        virtual void SendMessage(const std::string mysocketname, const int ID, const int frame_length,  int the_real_data) = 0;
        
        /**
         * @brief Listen a 
         * 
         * @param mysocketname 
         */
        virtual void ListenSocket(const std::string mysocketname) = 0;
 
};

void ActivateCAN(CAN** myCAN);
#endif