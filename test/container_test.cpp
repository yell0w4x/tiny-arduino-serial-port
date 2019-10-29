#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <tiny/container.hpp>

#include <algorithm>
#include <iostream>

TEST(array_test, must_create_array_using_iterators_pair)
{
  int source[] = {1, 2, 3, 4, 5};
  constexpr auto seq_sz = sizeof(source) / sizeof(int);
  tiny::array<int, seq_sz> sut(source, source + seq_sz);
  ASSERT_EQ(sut.size, seq_sz);
  ASSERT_TRUE(std::equal(sut.begin(), sut.end(), source));
}

//------------------------------------------------------------------------
TEST(array_test, default_constructory_must_create_array_with_default_values)
{
  constexpr auto sz = 10;
  tiny::array<int, sz> sut;
  ASSERT_EQ(sut.size, sz);
  ASSERT_TRUE(std::all_of(sut.begin(), sut.end(), [](int item) { return item == 0; }));
}

//------------------------------------------------------------------------
TEST(array_test, default_constructory_must_create_array_with_specified_default_values)
{
  constexpr size_t sz = 10;
  tiny::array<int, sz> sut(1, sz);
  ASSERT_EQ(sut.size, sz);
  ASSERT_TRUE(std::all_of(sut.begin(), sut.end(), [](int item) { return item == 1; }));
}

//------------------------------------------------------------------------
TEST(array_test, must_copy_array)
{
  constexpr auto seq_sz = 5;
  tiny::array<int, seq_sz> source{1, 2, 3, 4, 5};
  tiny::array<int, seq_sz> sut = source;
  ASSERT_EQ(sut.size, seq_sz);
  ASSERT_TRUE(std::equal(sut.begin(), sut.end(), source.begin()));
}

//------------------------------------------------------------------------
TEST(array_test, subscript_operator_must_return_item_at_given_index)
{
  constexpr auto seq_sz = 5;
  tiny::array<int, seq_sz> sut{1, 2, 3, 4, 5};
  ASSERT_EQ(sut[0], 1);
  ASSERT_EQ(sut[1], 2);
  ASSERT_EQ(sut[2], 3);
  ASSERT_EQ(sut[3], 4);
  ASSERT_EQ(sut[4], 5);
}

//------------------------------------------------------------------------
TEST(array_test, at_method_must_return_item_at_given_index)
{
  constexpr auto seq_sz = 5;
  tiny::array<int, seq_sz> sut{1, 2, 3, 4, 5};
  ASSERT_EQ(sut.at(0), 1);
  ASSERT_EQ(sut.at(1), 2);
  ASSERT_EQ(sut.at(2), 3);
  ASSERT_EQ(sut.at(3), 4);
  ASSERT_EQ(sut.at(4), 5);
}

//------------------------------------------------------------------------
TEST(array_test, begin_end_must_reflects_array_size)
{
  constexpr auto seq_sz = 5;
  tiny::array<int, seq_sz> sut{1, 2, 3, 4, 5};
  ASSERT_EQ(std::distance(sut.begin(), sut.end()), seq_sz);
}

//------------------------------------------------------------------------
TEST(array_test, assign_must_fill_the_array)
{
  constexpr auto seq_sz = 5;
  tiny::array<int, seq_sz> sut{1, 2, 3, 4, 5};
  sut.assign(10);
  ASSERT_TRUE(std::all_of(sut.begin(), sut.end(), [](int item){ return item == 10; }));
}

//------------------------------------------------------------------------
TEST(queue_test, must_push_items_until_room_and_then_pop_items)
{
  constexpr auto sz = 5;
  tiny::queue<int, sz> sut;
  ASSERT_TRUE(sut.empty());
  ASSERT_EQ(sut.front(), nullptr);
  ASSERT_TRUE(sut.push(1));
  ASSERT_FALSE(sut.empty());
  ASSERT_TRUE(sut.push(2));
  ASSERT_EQ(*sut.front(), 1);
  ASSERT_TRUE(sut.push(3));
  ASSERT_TRUE(sut.push(4));
  ASSERT_FALSE(sut.push(5));
  ASSERT_EQ(sut.size(), sz - 1);
  ASSERT_EQ(*sut.front(), 1);
  ASSERT_EQ(sut.pop(), 1);
  ASSERT_EQ(*sut.front(), 2);
  ASSERT_EQ(sut.pop(), 2);
  ASSERT_EQ(sut.pop(), 3);
  ASSERT_FALSE(sut.empty());
  ASSERT_EQ(*sut.front(), 4);
  ASSERT_EQ(sut.pop(), 4);
  ASSERT_EQ(sut.front(), nullptr);
  ASSERT_TRUE(sut.empty());
  ASSERT_EQ(sut.pop(), 0);
}

//------------------------------------------------------------------------
TEST(queue_test, must_push_items_and_overwrite_tail_if_overflow_occurs_and_then_pop)
{
  constexpr auto sz = 5;
  tiny::queue<int, sz> sut(true);
  ASSERT_TRUE(sut.empty());
  sut.push(1);
  ASSERT_FALSE(sut.empty());
  sut.push(2);
  sut.push(3);
  sut.push(4);
  ASSERT_TRUE(sut.push(5));
  ASSERT_TRUE(sut.push(6));
  ASSERT_TRUE(sut.push(7));
  ASSERT_EQ(sut.size(), sz - 1);
  ASSERT_EQ(sut.pop(), 4);
  ASSERT_EQ(sut.pop(), 5);
  ASSERT_EQ(sut.pop(), 6);
  ASSERT_FALSE(sut.empty());
  ASSERT_EQ(*sut.front(), 7);
  ASSERT_EQ(sut.pop(), 7);
  ASSERT_EQ(sut.front(), nullptr);
  ASSERT_TRUE(sut.empty());
  ASSERT_EQ(sut.pop(), 0);
}

//------------------------------------------------------------------------
TEST(bitset_test, must_initialize_and_return_bits_properly)
{
	tiny::bitset<32> sut(0x80000001ul);
	ASSERT_TRUE(sut.get(0));
	ASSERT_TRUE(sut.get(31));

	sut.assign(0x81);
	ASSERT_TRUE(sut.get(0));
	ASSERT_TRUE(sut.get(7));
}

//------------------------------------------------------------------------
TEST(bitset_test, must_set_bits_properly)
{
	tiny::bitset<32> sut(0x80000001ul);
	sut.set(0, false);
	sut.set(1, true);
	ASSERT_FALSE(sut.get(0));
	ASSERT_TRUE(sut.get(1));
	ASSERT_EQ(sut.to_ulong(), 0x80000002ul);
}

//------------------------------------------------------------------------
int main(int argc, char** argv)
{
  ::testing::InitGoogleMock(&argc, argv);

  return RUN_ALL_TESTS();
}


