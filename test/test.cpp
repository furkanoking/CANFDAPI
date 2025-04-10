#include <gtest/gtest.h>

int toplama(int a, int b){
    return a+b;
}

TEST(Toplama_Testi, Pozifdifgsg){
    EXPECT_EQ(toplama(2,3),5);
}


int main(){
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}