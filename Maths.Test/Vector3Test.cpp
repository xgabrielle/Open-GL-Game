#include "pch.h"
#include "../Maths/Vector3.h"


TEST(Vector3_Constructor, AssignAllComponments) 
{
	Vector3 v(3, 4, 5);
	EXPECT_EQ(v.x, 3);
	EXPECT_EQ(v.y, 4);
	EXPECT_EQ(v.z, 5);

}



//TEST(Vector3_EqualityComparison, Returns_Equal_Vectors) {
//	EXPECT_TRUE(Vector3(3, 4, 5) == Vector3(3, 4, 5));
//}
//
//TEST(Vector3_EqualityComparison, Returns_Inequal_Vectors)
//{
//	EXPECT_TRUE(Vector3(3, 4, 5) != Vector3(2, 4, 5));
//	EXPECT_TRUE(Vector3(3, 4, 5) != Vector3(3, 2, 5));
//	EXPECT_TRUE(Vector3(3, 4, 5) != Vector3(3, 4, 2));
//	EXPECT_TRUE(Vector3(3, 4, 5) != Vector3(2, 2, 2));
//}

TEST(Vector3_Negate, InvertsPositiveValues) 
{
	EXPECT_EQ(-Vector3(3, 4, 5), Vector3(- 3, -4, -5));
    EXPECT_TRUE(true);
}
TEST(Vector3_Subtraction, Subtract_Vector3)
{
	
	Vector3 a(2, 4, 6);
	Vector3 b(1, 1, 1);
	
	Vector3 result(a - b);

	EXPECT_EQ(result.x, 1.0);
	EXPECT_EQ(result.y, 3.0);
	EXPECT_EQ(result.z, 5.0);
	

	
}

TEST(Vector3_Addition, _Vector3)
{
	Vector3 a(2, 4, 6);
	Vector3 b(1, 1, 1);

	Vector3 result(a + b);

	EXPECT_EQ(result.x, 3);
	EXPECT_EQ(result.y, 5);
	EXPECT_EQ(result.z, 7);

}

TEST(Vector3_ScalarMultiplication, ScalesAllValues) 
{
	EXPECT_EQ(Vector3(3, 4, 5)*2, Vector3(6, 8, 10));
}

TEST(Vector3_ScalarDivision, Divide)
{
	EXPECT_EQ(Vector3(6, 8, 10) / 2, Vector3(3, 4, 5));
}

TEST(Vector3_SquarMag, Calculate_Something_SquarMag)
{
	Vector3 v{ 2,3,4 };

	float result = v.sqreMag();
}
