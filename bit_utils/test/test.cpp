#include <gtest/gtest.h>

#include "../bit_utils.h"

class FindTest: public ::testing::TestWithParam<int(*)(const u32&,const u32&,unsigned)>{};

TEST_P(FindTest, U32){
	EXPECT_EQ(12, GetParam()(0x000f'0f0fU, 0x8000'0000U, 1));
	EXPECT_EQ(28, GetParam()(0x0f0f'0f0fU, 0x8000'0000U, 5));
	EXPECT_EQ(11, GetParam()(0x0f1f'0f0fU, 0x8000'0000U, 5));
	EXPECT_EQ(-1, GetParam()(0x0f0f'0f0eU, 0x8000'0000U, 5));
	EXPECT_EQ(-1, GetParam()(0x0f0f'0f0eU, 0x800f'8000U, 5));
	EXPECT_EQ(-1, GetParam()(0x0000'0000U, 0x0000'0000U, 5));
	EXPECT_EQ(16, GetParam()(0x0000'ffffU, 0xffff'0000U, 32));
}

INSTANTIATE_TEST_SUITE_P(FindSuite, FindTest, ::testing::Values(index_1, index_2));
