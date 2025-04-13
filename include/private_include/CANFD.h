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
#include <vector>
#include <queue>
/**
 * @brief CANFD class for implementation of the CAN function
 * 
 */
class CANFD final: public CAN  {
    public:
        explicit CANFD();
        ~CANFD();

        // For debugging
        void operator()() const;

        // converesion operator
        explicit operator bool() const;

        CANFD& operator=(const CANFD& myCANFD) = default;
        CANFD(const CANFD& myCANFD) = default;
        CANFD& operator=(CANFD&& myCANFD) = default;
    
    //private:
        [[nodiscard]] bool CreateSocket(const std::string mysocketname,const std::string Interface_name,const bool test_mode,const bool IsCANFD) override;
        void SendMessage(const std::string mysocketname, const int ID, const int frame_length,  const char* the_real_data) override;
        void ListenSocket(const std::string mysocketname, std::function<void(CANFDStruct)> customerArrivedMessageFunc) override;
        void CANFDCheck(const bool CANFD);


        void SendMessage(const std::string mysocketname, const int ID, const int frame_length,  int the_real_data) override;



        void threadListening(const std::string mysocketname,std::function<void(CANFDStruct)> customerArrivedMessageFunc);
        void threadSending(const std::string mysocketname, const int ID, const int frame_length,  const char* the_real_data);
        void threadSendingintData(const std::string mysocketname, const int ID, const int frame_length,  int the_real_data);

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


        std::binary_semaphore binary_check{1};

        virtual void setID(u_int32_t ReceiverID) override;

        u_int32_t m_iID{99};


        /**
         * @brief Set the Data object and push to the queue
         * 
         * @tparam DataType 
         * @param Data 
         */
        template < typename DataType >
        void setData(DataType Data);


        std::queue<CANFDStruct> DataQueue;

        //TODO bir fonksiyon yazılacak. Template kullanılacak !! constexpr kullanılacak !!! Gerçek datayı buraya set ediceksin!!!!! Datayı set ederken semaphore veya mutex kullan !!!
};












#endif