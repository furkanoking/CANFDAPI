#include <gtest/gtest.h>
#include "CANFD.h"

int toplama(int a, int b){
    return a+b;
}

TEST(Toplama_Testi, Pozifdifgsg){
    EXPECT_EQ(toplama(2,3),5);
}


int main(){


    // In the receiver side 
    // sudo ip link add dev "Network name" type vcan
    // sudo ip link set up "Network name"

    // candump "Network name"


    // In the sender side 
    // cansend "Network Name" 123#DEADBEEF


    CANFD my_CANFD;

    bool zort = my_CANFD.CreateSocket("FurkanSocket","FurkanInterface",false,true);
    std::cout<<" return deger"<< zort;
    while(1){

    };

    /*
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
    */




}