#include "Move.h"
#include "gtest.h"

TEST(test_Move, can_set_get_color) {
	Move move;
	move.SetColor(1);

	EXPECT_EQ(1, move.GetColor());
}

TEST(test_Move, can_set_get_type) {
	Move move;
	move.SetType(1);

	EXPECT_EQ(1, move.GetType());
}

TEST(test_Move, can_set_get_coord) {
	Move move;
	move.SetCoord(10);

	EXPECT_EQ(10, move.GetCoord());
}

TEST(test_Move, can_set_get_numchecker) {
	Move move;
	move.SetNum(2);

	EXPECT_EQ(2, move.GetNum());
}

TEST(test_Move, can_set_get_neaten) {
	Move move;
	move.SetNEaten(5);

	EXPECT_EQ(5, move.GetNEaten());
}

TEST(test_Move, can_set_get_eaten) {
	Move move;
	move.SetEaten(3);

	EXPECT_EQ(3, move.GetEaten());
}

TEST(test_Move, can_set_get_eaten_in_arr) {
	int arr[3] = { 3,5,8 };
	Move move;
	move.SetNEaten(3);
	move.SetEaten(arr);

	int arrres[12];
	move.GetEaten(arrres);

	EXPECT_EQ(arrres[0], 3);
	EXPECT_EQ(arrres[1], 5);
	EXPECT_EQ(arrres[2], 8);
}

TEST(test_Move, can_set_get_in_general) {
	int arr[12] = { 2,1,3,4,6,5,7,8,9,11,10,12 }, arrres[12];
	Move move;
	move.SetColor(BLACK);
	move.SetCoord(4);
	move.SetNum(3);
	move.SetNEaten(12);
	move.SetType(1);
	move.SetEaten(arr);

	EXPECT_EQ(BLACK, move.GetColor());
	EXPECT_EQ(1, move.GetType());
	EXPECT_EQ(3, move.GetNum());
	EXPECT_EQ(4, move.GetCoord());
	EXPECT_EQ(12, move.GetNEaten());

	move.GetEaten(arrres);
	for (int i = 0; i < 12; i++)
		EXPECT_EQ(arrres[i], arr[i]);
}

TEST(test_Move, can_compare_if_neaten_diff) {
	Move move, move1;
	move.SetNEaten(3); move.SetNEaten(4);

	EXPECT_FALSE(move1==move);
}

TEST(test_Move, can_compare) {
	Move move, move1;
	move.SetNEaten(3); move1.SetNEaten(3);
	int eaten[3] = { 8,3,7 }, eaten1[3] = { 7,8,3 };
	move.SetEaten(eaten); move1.SetEaten(eaten1);

	EXPECT_TRUE(move1 == move);
}