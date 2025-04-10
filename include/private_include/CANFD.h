/**
 * @file CANFD.h
 * @author Furkan Ozen (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef _CANFD_H_
#define _CANFD_H_


#define NORMAL_FD_SPEED 0

#include "CAN.h"
#include <map>
#include <thread>
#include <semaphore>
#include <iostream>

/**
 * @brief CANFD class for implementation of the CAN function
 * 
 */
class CANFD final: public CAN  {
    public:
        CANFD();
        ~CANFD();

        CANFD& operator=(const CANFD& myCANFD) = default;
        CANFD(const CANFD& myCANFD) = default;
        CANFD& operator=(CANFD&& myCANFD) = default;
    
    private:
        [[nodiscard]] bool CreateSocket(const std::string mysocketname,const std::string Interface_name,const bool test_mode,const bool IsCANFD) override;
        void SendMessage(const std::string mysocketname, const int ID, const int frame_length,  const char* the_real_data) override;
        CANFDStruct ListenSocket(const std::string mysocketname) override;
        void CANFDCheck(const bool CANFD);

        CANFDStruct threadListening(const std::string mysocketname);
        void threadSending(const std::string mysocketname, const int ID, const int frame_length,  const char* the_real_data);

        /**
         * @brief Set the Network Interface object
         * 
         * @param Interface_name The network interface name we created
         * @return * void 
         */
        void setNetworkInterface(const std::string Interface_name);

        /**
         * @brief The test mode parameter. Initiliazed with a test false
         * 
         */
        bool m_btest_mode{false};

        /**
         * @brief the sock id. Initilazed with a -1
         * 
         */
        int m_isockfd{-1};

        /**
         * @brief Store the value of the sockets with the string name
         * 
         */
        static std::map<std::string, int> m_msocket_map;


        std::binary_semaphore ghdj{1};
};












#endif