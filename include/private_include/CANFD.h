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
        [[nodiscard]] bool CreateSocket(std::string mysocketname,std::string Interface_name,bool test_mode, bool IsCANFD) override;
        void SendMessage(std::string mysocketname, int ID, int frame_length,  const char* the_real_data) override;
        CANFDStruct ListenSocket(std::string mysocketname) override;
        void CANFDCheck(bool CANFD);

        /**
         * @brief Set the Network Interface object
         * 
         * @param Interface_name The network interface name we created
         * @return * void 
         */
        void setNetworkInterface(std::string Interface_name);

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
};












#endif