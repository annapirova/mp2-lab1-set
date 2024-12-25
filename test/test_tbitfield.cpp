#include "../gtest/gtest.h"
#include "tbitfield.h"


TEST(TBitField, can_create_bitfield_with_positive_length)
{
  ASSERT_NO_THROW(TBitField bf(3));
}

TEST(TBitField, can_get_length)
{
  TBitField bf(3);

  EXPECT_EQ(3, bf.GetLength());
}

TEST(TBitField, new_bitfield_is_set_to_zero)
{
  TBitField bf(10);

  int sum = 0;
  for (int i = 0; i < bf.GetLength(); i++)
  {
    sum += bf.GetBit(i);
  }

  EXPECT_EQ(0, sum);
}

TEST(TBitField, can_set_bit)
{
  TBitField bf(200);

  EXPECT_EQ(0, bf.GetBit(100));

  bf.SetBit(100);
  EXPECT_NE(0, bf.GetBit(100));
}

TEST(TBitField, can_clear_bit)
{
  TBitField bf(10);

  int bitIdx = 3;

  bf.SetBit(bitIdx);
  EXPECT_NE(0, bf.GetBit(bitIdx));

  bf.ClrBit(bitIdx);
  EXPECT_EQ(0, bf.GetBit(bitIdx));
}

TEST(TBitField, throws_when_create_bitfield_with_negative_length)
{
  ASSERT_ANY_THROW(TBitField bf(-3));
}

TEST(TBitField, throws_when_set_bit_with_negative_index)
{
  TBitField bf(10);

  ASSERT_ANY_THROW(bf.SetBit(-3));
}

TEST(TBitField, throws_when_set_bit_with_too_large_index)
{
  TBitField bf(10);

  ASSERT_ANY_THROW(bf.SetBit(11));
}

TEST(TBitField, throws_when_get_bit_with_negative_index)
{
  TBitField bf(10);

  ASSERT_ANY_THROW(bf.GetBit(-3));
}

TEST(TBitField, throws_when_get_bit_with_too_large_index)
{
  TBitField bf(10);

  ASSERT_ANY_THROW(bf.GetBit(11));
}

TEST(TBitField, throws_when_clear_bit_with_negative_index)
{
  TBitField bf(10);

  ASSERT_ANY_THROW(bf.ClrBit(-3));
}

TEST(TBitField, throws_when_clear_bit_with_too_large_index)
{
  TBitField bf(10);

  ASSERT_ANY_THROW(bf.ClrBit(11));
}

TEST(TBitField, can_assign_bitfields_of_equal_size)
{
  const int size = 100;
  TBitField bf1(size), bf2(size);
  bf1.SetBit(30);
  bf1.SetBit(90);
  bf2 = bf1;

  EXPECT_NE(0, bf2.GetBit(30));
  EXPECT_NE(0, bf2.GetBit(90));
}

TEST(TBitField, assign_operator_changes_bitfield_size)
{
  const int size1 = 2, size2 = 5;
  TBitField bf1(size1), bf2(size2);
  for (int i = 0; i < size1; i++)
  {
    bf1.SetBit(i);
  }
  bf2 = bf1;

  EXPECT_EQ(2, bf2.GetLength());
}

TEST(TBitField, can_assign_bitfields_of_non_equal_size)
{
  const int size1 = 100, size2 = 50;
  TBitField bf1(size1), bf2(size2);
  bf1.SetBit(30);
  bf1.SetBit(90);
  bf2 = bf1;

  EXPECT_NE(0, bf2.GetBit(30));
  EXPECT_NE(0, bf2.GetBit(90));
}

TEST(TBitField, compare_equal_bitfields_of_equal_size)
{
  const int size = 100;
  TBitField bf1(size), bf2(size);
  bf1.SetBit(30);
  bf1.SetBit(90);
  bf2 = bf1;

  EXPECT_EQ(bf1, bf2);
}

TEST(TBitField, or_operator_applied_to_bitfields_of_equal_size)
{
  const int size = 400;
  TBitField bf1(size), bf2(size), expBf(size);

  bf1.SetBit(200);
  bf1.SetBit(300);
  bf2.SetBit(100);
  bf2.SetBit(300);

  expBf.SetBit(100);
  expBf.SetBit(200);
  expBf.SetBit(300);

  EXPECT_EQ(expBf, bf1 | bf2);
}

TEST(TBitField, or_operator_applied_to_bitfields_of_non_equal_size)
{
  const int size1 = 400, size2 = 500;
  TBitField bf1(size1), bf2(size2), expBf(size2);
  bf1.SetBit(200);
  bf1.SetBit(300);
  bf2.SetBit(200);
  bf2.SetBit(450);

  expBf.SetBit(200);
  expBf.SetBit(300);
  expBf.SetBit(450);

  EXPECT_EQ(expBf, bf1 | bf2);
}

TEST(TBitField, and_operator_applied_to_bitfields_of_equal_size)
{
  const int size = 400;
  TBitField bf1(size), bf2(size), expBf(size);
  bf1.SetBit(200);
  bf1.SetBit(300);
  bf2.SetBit(100);
  bf2.SetBit(300);

  expBf.SetBit(300);

  EXPECT_EQ(expBf, bf1 & bf2);
}

TEST(TBitField, and_operator_applied_to_bitfields_of_non_equal_size)
{
  const int size1 = 400, size2 = 500;
  TBitField bf1(size1), bf2(size2), expBf(size2);
  bf1.SetBit(200);
  bf1.SetBit(300);
  bf2.SetBit(300);
  bf2.SetBit(450);

  // expBf = 00010
  expBf.SetBit(300);

  EXPECT_EQ(expBf, bf1 & bf2);
}

TEST(TBitField, can_invert_bitfield)
{
  const int size = 200;
  TBitField bf(size), negBf(size), expNegBf(size);

  bf.SetBit(100);
  negBf = ~bf;

  for (int i = 0; i < size; i++)
	  expNegBf.SetBit(i);
  expNegBf.ClrBit(100);

  EXPECT_EQ(expNegBf, negBf);
}

TEST(TBitField, can_invert_large_bitfield)
{
  const int size = 38;
  TBitField bf(size), negBf(size), expNegBf(size);
  bf.SetBit(35);
  negBf = ~bf;

  for(int i = 0; i < size; i++)
	expNegBf.SetBit(i);
  expNegBf.ClrBit(35);

  EXPECT_EQ(expNegBf, negBf);
}

TEST(TBitField, invert_plus_and_operator_on_different_size_bitfield)
{
  const int firstSze = 40, secondSize = 80;
  TBitField firstBf(firstSze), negFirstBf(firstSze), secondBf(secondSize), testBf(secondSize);
  firstBf.SetBit(38);
  negFirstBf = ~firstBf;
  // 101111111.....1

  secondBf.SetBit(38);
  secondBf.SetBit(70);
  //00001000.....10000000

  testBf.SetBit(70);

  EXPECT_EQ(testBf, secondBf & negFirstBf);
}

TEST(TBitField, can_invert_many_random_bits_bitfield)
{
  const int size = 38;
  TBitField bf(size), negBf(size), expNegBf(size);

  std::vector<int> bits;
  bits.push_back(0);
  bits.push_back(1);
  bits.push_back(14);
  bits.push_back(16);
  bits.push_back(33);
  bits.push_back(37);

  for (unsigned int i = 0; i < bits.size(); i++)
    bf.SetBit(bits[i]);

  negBf = ~bf;

  for(int i = 0; i < size; i++)
    expNegBf.SetBit(i);
  for (unsigned int i = 0; i < bits.size(); i++)
    expNegBf.ClrBit(bits[i]);

  EXPECT_EQ(expNegBf, negBf);
}

TEST(TBitField, bitfields_with_different_bits_are_not_equal)
{
  const int size = 4;
  TBitField bf1(size), bf2(size);

  bf1.SetBit(1);
  bf1.SetBit(3);

  bf2.SetBit(1);
  bf2.SetBit(2);

  EXPECT_NE(bf1, bf2);
}


TEST(TBitField, bitfields_with_different_bits_are_not_equal_big_sizes)
{
  const int size = 100;
  TBitField bf1(size), bf2(size);

  bf1.SetBit(1);
  bf1.SetBit(90);

  bf2.SetBit(1);
  bf2.SetBit(45);

  EXPECT_NE(bf1, bf2);
}
