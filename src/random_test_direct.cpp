#include <iostream>
#include <stdlib.h>
#include <ctime>

#include "lrucache_direct.hpp"
#include "gtest/gtest.h"

const int NUM_OF_TEST1_RECORDS = 100;
const int NUM_OF_TEST2_RECORDS = 1000000;
const int TEST2_CACHE_CAPACITY = 500000;

TEST(CacheTest1, KeepsAllValuesWithinCapacity) {
    cache::lru_cache<int, int> cache_lru(TEST2_CACHE_CAPACITY);
    
    int num;
       for (int i = 0; i < NUM_OF_TEST2_RECORDS; ++i) {
           num = (int)rand()%NUM_OF_TEST2_RECORDS;
           cache_lru.put(num, num);
       }
       int count_t = 0;
       int count_f = 0;

       for (int i = 0; i < NUM_OF_TEST2_RECORDS; ++i) {
           num = (int)rand()%NUM_OF_TEST2_RECORDS;
           
           if(cache_lru.exists(num))
               count_t++;
           else count_f++;
       }
       EXPECT_EQ(count_t, count_f)<< "hit : "<<count_t << ", miss : "<< count_f;

}

int main(int argc, char **argv) {
    srand((unsigned int)time(NULL));

    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}
