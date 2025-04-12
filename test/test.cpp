#include <gtest/gtest.h>
#include "CANFD.h"

int toplama(int a, int b){
    return a+b;
}

TEST(Toplama_Testi, Pozifdifgsg){
    EXPECT_EQ(toplama(2,3),5);
}


int main(){
    // The network name should be generated from the terminal.
    // Than the socketname and the 

    // In the receiver side 
    // sudo ip link add dev "Network name" type vcan
    // sudo ip link set up "Network name"

    // candump "Network name"


    // In the sender side 
    // cansend "Network Name" 123#DEADBEEF


    CANFD my_CANFD;

    bool zort = my_CANFD.CreateSocket("FurkanSocket","Aleyna",false,true);
    std::cout<<" return deger"<< zort<<std::endl;

    for(auto x: CANFD::m_msocket_map){
        std::cout<<"map"<<x.first<<" "<<x.second<<std::endl;
    }

    //my_CANFD.ListenSocket("FurkanSocket");
    int data = 0xDEAD;

    my_CANFD.ListenSocket("FurkanSocket");
    my_CANFD.SendMessage("FurkanSocket",0x12,4,data);

    std::cout<<"Bu da benim Debug laaan"<<std::endl;
    while(1){

    };



    /*
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
    */




}