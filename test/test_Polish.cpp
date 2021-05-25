#include "../gtest/gtest.h"
#include"Polish.h"

TEST(Polish, can_create_Polish)
{
	ASSERT_NO_THROW(TPolish P);
}

TEST(Polish, operation_plus)
{
	char* s;
	s = "2+3";
	TPolish P;
	EXPECT_EQ(P.Calculation(s), 5);
}

TEST(Polish, operation_minus)
{
	char* s;
	s = "5-2";
	TPolish P;
	EXPECT_EQ(P.Calculation(s), 3);
}

TEST(Polish, operation_multiply)
{
	char* s;
	s = "5*2";
	TPolish P;
	EXPECT_EQ(P.Calculation(s), 10);
}

TEST(Polish, operation_division)
{
	char* s;
	s = "6/2";
	TPolish P;
	EXPECT_EQ(P.Calculation(s), 3);
}

TEST(Polish, division_by_zero_exception)
{
	char* s;
	s = "5/0";
	TPolish P;
	ASSERT_ANY_THROW(P.Calculation(s));
}

TEST(Polish, operation_order)
{
	char* s;
	s = "2+2*5";
	TPolish P;

	EXPECT_EQ(P.Calculation(s), 12);
}

TEST(Polish, operation_order_conversely)
{
	char* s;
	s = "2*5+2";
	TPolish P;

	EXPECT_EQ(P.Calculation(s), 12);
}
