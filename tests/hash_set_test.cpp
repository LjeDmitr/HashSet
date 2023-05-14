#include <gtest/gtest.h>
#include <algorithm>
#include <hash_set/hash_set.hpp>
#include <iterator>
#include <vector>

TEST(HashSetTest, InsertTest) {
  HashSet<int> set;

  set.insert(5);
  set.insert(7);
  set.insert(3);

  EXPECT_TRUE(set.contains(5));
  EXPECT_TRUE(set.contains(7));
  EXPECT_TRUE(set.contains(3));
}

TEST(HashSetTest, EraseTest) {
  HashSet<int> set;

  set.insert(5);
  set.insert(7);
  set.insert(3);
  set.erase(7);

  EXPECT_TRUE(set.contains(5));
  EXPECT_FALSE(set.contains(7));
  EXPECT_TRUE(set.contains(3));
}

TEST(HashSetTest, ClearTest) {
  HashSet<int> set;

  set.insert(5);
  set.insert(7);
  set.insert(3);
  set.clear();

  EXPECT_FALSE(set.contains(5));
  EXPECT_FALSE(set.contains(7));
  EXPECT_FALSE(set.contains(3));
}

TEST(HashSetTest, SizeTest) {
  HashSet<int> set;

  EXPECT_EQ(set.size(), 0);

  set.insert(5);
  set.insert(7);
  set.insert(3);

  EXPECT_EQ(set.size(), 3);

  set.erase(7);

  EXPECT_EQ(set.size(), 2);

  set.clear();

  EXPECT_EQ(set.size(), 0);
}

TEST(HashSetTest, IteratorTest) {
  HashSet<int> set;

  set.insert(5);
  set.insert(7);
  set.insert(3);

  int sum = 0;
  for (const auto& element : set) {
    sum += element;
  }

  EXPECT_EQ(sum, 15);
}

TEST(HashSetTest, CopyConstructorTest) {
  HashSet<int> set1;
  set1.insert(5);
  set1.insert(7);
  set1.insert(3);

  HashSet<int> set2(set1);

  EXPECT_TRUE(set2.contains(5));
  EXPECT_TRUE(set2.contains(7));
  EXPECT_TRUE(set2.contains(3));
}

TEST(HashSetTest, MoveConstructorTest) {
  HashSet<int> set1;
  set1.insert(5);
  set1.insert(7);
  set1.insert(3);

  HashSet<int> set2(std::move(set1));

  EXPECT_TRUE(set2.contains(5));
  EXPECT_TRUE(set2.contains(7));
  EXPECT_TRUE(set2.contains(3));
  EXPECT_TRUE(set1.empty());
}

TEST(HashSetTest, CopyAssignmentTest) {
  HashSet<int> set1;
  set1.insert(5);
  set1.insert(7);
  set1.insert(3);

  HashSet<int> set2;
  set2.insert(2);
  set2.insert(4);

  set2 = set1;

  EXPECT_TRUE(set2.contains(5));
  EXPECT_TRUE(set2.contains(7));
  EXPECT_TRUE(set2.contains(3));
  EXPECT_FALSE(set2.contains(2));
  EXPECT_FALSE(set2.contains(4));
}

TEST(HashSetTest, Duplication) {
  HashSet<int> set;
  set.insert(1);
  set.insert(1);
  EXPECT_EQ(1, set.size());
  EXPECT_TRUE(set.contains(1));
}

TEST(HashSetOperatorTest, OperatorEqual) {
  HashSet<int> set1{1, 2, 3, 4, 5};
  HashSet<int> set2{5, 4, 3, 2, 1};
  HashSet<int> set3{1, 2, 3, 4};

  EXPECT_TRUE(set1 == set2);
  EXPECT_FALSE(set1 == set3);
}

TEST(HashSetOperatorTest, OperatorNotEqual) {
  HashSet<int> set1{1, 2, 3, 4, 5};
  HashSet<int> set2{5, 4, 3, 2, 1};
  HashSet<int> set3{1, 2, 3, 4};

  EXPECT_FALSE(set1 != set2);
  EXPECT_TRUE(set1 != set3);
}

TEST(HashSetOperatorTest, OperatorLessThan) {
  HashSet<int> set1{1, 2, 3, 4, 5};
  HashSet<int> set2{1, 2, 3, 4};
  HashSet<int> set3{1, 2, 3, 4, 6};

  EXPECT_FALSE(set1 < set2);
  EXPECT_TRUE(set2 < set1);
  EXPECT_TRUE(set2 < set3);
}

TEST(HashSetOperatorTest, OperatorGreaterThan) {
  HashSet<int> set1{1, 2, 3, 4, 5};
  HashSet<int> set2{1, 2, 3, 4};
  HashSet<int> set3{1, 2, 3, 4, 6};

  EXPECT_TRUE(set1 > set2);
  EXPECT_FALSE(set2 > set1);
  EXPECT_FALSE(set2 > set3);
}

TEST(HashSetOperatorTest, OperatorLessThanOrEqual) {
  HashSet<int> set1{1, 2, 3, 4, 5};
  HashSet<int> set2{1, 2, 3, 4};
  HashSet<int> set3{1, 2, 3, 4, 6};

  EXPECT_FALSE(set1 <= set2);
  EXPECT_TRUE(set2 <= set1);
  EXPECT_TRUE(set2 <= set3);
  EXPECT_TRUE(set1 <= set1);
}

TEST(HashSetOperatorTest, OperatorGreaterThanOrEqual) {
  HashSet<int> set1{1, 2, 3, 4, 5};
  HashSet<int> set2{1, 2, 3, 4};
  HashSet<int> set3{1, 2, 3, 4, 6};

  EXPECT_TRUE(set1 >= set2);
  EXPECT_FALSE(set2 >= set1);
  EXPECT_FALSE(set2 >= set3);
  EXPECT_TRUE(set1 >= set1);
}

TEST(HashSetSTLTest, StandardAlgorithmFind) {
  HashSet<int> set{1, 2, 3, 4, 5};

  auto it = std::find(set.begin(), set.end(), 3);
  EXPECT_NE(it, set.end());
  EXPECT_EQ(*it, 3);
}

TEST(HashSetSTLTest, StandardAlgorithmFor_each) {
  HashSet<int> set{1, 2, 3, 4, 5};

  int sum = 0;
  std::for_each(set.begin(), set.end(), [&sum](int x) { sum += x; });
  EXPECT_EQ(sum, 15);
}

TEST(HashSetSTLTest, StandardAlgorithmCount_if) {
  HashSet<int> set{1, 2, 3, 4, 5};

  auto count =
      std::count_if(set.begin(), set.end(), [](int x) { return x % 2 == 0; });
  EXPECT_EQ(count, 2);
}

TEST(HashSetSTLTest, StandardAlgorithmTransform) {
  HashSet<int> set{1, 2, 3, 4, 5};

  std::vector<int> doubled;
  std::transform(set.begin(), set.end(), back_inserter(doubled), [](int x) {
    return 2 * x;
  });
  EXPECT_EQ(doubled, std::vector<int>({2, 4, 6, 8, 10}));
}

TEST(HashSetTypeTest, IntTest) {
  HashSet<int> set;

  EXPECT_TRUE(set.empty());

  set.insert(1);
  set.insert(2);
  set.insert(3);

  EXPECT_FALSE(set.empty());
  EXPECT_EQ(3, set.size());

  set.erase(2);

  EXPECT_EQ(2, set.size());
  EXPECT_TRUE(set.contains(1));
  EXPECT_FALSE(set.contains(2));
  EXPECT_TRUE(set.contains(3));
}

TEST(HashSetTypeTest, DoubleTest) {
  HashSet<double> set;

  EXPECT_TRUE(set.empty());

  set.insert(1.1);
  set.insert(2.2);
  set.insert(3.3);

  EXPECT_FALSE(set.empty());
  EXPECT_EQ(3, set.size());

  set.erase(2.2);

  EXPECT_EQ(2, set.size());
  EXPECT_TRUE(set.contains(1.1));
  EXPECT_FALSE(set.contains(2.2));
  EXPECT_TRUE(set.contains(3.3));
}

TEST(HashSetTypeTest, StringTest) {
  HashSet<std::string> set;

  EXPECT_TRUE(set.empty());

  set.insert("hello");
  set.insert("world");
  set.insert("!");

  EXPECT_FALSE(set.empty());
  EXPECT_EQ(3, set.size());

  set.erase("world");

  EXPECT_EQ(2, set.size());
  EXPECT_TRUE(set.contains("hello"));
  EXPECT_FALSE(set.contains("world"));
  EXPECT_TRUE(set.contains("!"));
}

TEST(HashSetTypeTest, CharTest) {
  HashSet<char> set;

  EXPECT_TRUE(set.empty());

  set.insert('c');
  set.insert('a');
  set.insert('1');

  EXPECT_FALSE(set.empty());
  EXPECT_EQ(3, set.size());

  set.erase('a');

  EXPECT_EQ(2, set.size());
  EXPECT_TRUE(set.contains('c'));
  EXPECT_FALSE(set.contains('a'));
  EXPECT_TRUE(set.contains('1'));
}

TEST(HashSetTypeTest, BoolTest) {
  HashSet<char> set;

  EXPECT_TRUE(set.empty());

  set.insert(true);
  set.insert(false);

  EXPECT_FALSE(set.empty());
  EXPECT_EQ(2, set.size());

  set.erase(false);

  EXPECT_EQ(1, set.size());
  EXPECT_TRUE(set.contains(true));
  EXPECT_FALSE(set.contains(false));
}

TEST(HashSetTypeTest, FloatTest) {
  HashSet<float> set;

  EXPECT_TRUE(set.empty());

  set.insert(1.1);
  set.insert(2.2);
  set.insert(3.3);

  EXPECT_FALSE(set.empty());
  EXPECT_EQ(3, set.size());

  set.erase(2.2);

  EXPECT_EQ(2, set.size());
  EXPECT_TRUE(set.contains(1.1));
  EXPECT_FALSE(set.contains(2.2));
  EXPECT_TRUE(set.contains(3.3));
}

TEST(HashSetTypeTest, ShortTest) {
  HashSet<short> set;

  EXPECT_TRUE(set.empty());

  set.insert(1);
  set.insert(2);
  set.insert(3);

  EXPECT_FALSE(set.empty());
  EXPECT_EQ(3, set.size());

  set.erase(2);

  EXPECT_EQ(2, set.size());
  EXPECT_TRUE(set.contains(1));
  EXPECT_FALSE(set.contains(2));
  EXPECT_TRUE(set.contains(3));
}

TEST(HashSetTypeTest, LongTest) {
  HashSet<long> set;

  EXPECT_TRUE(set.empty());

  set.insert(10979679679);
  set.insert(28547547457548);
  set.insert(354845646345321);

  EXPECT_FALSE(set.empty());
  EXPECT_EQ(3, set.size());

  set.erase(354845646345321);

  EXPECT_EQ(2, set.size());
  EXPECT_TRUE(set.contains(10979679679));
  EXPECT_FALSE(set.contains(354845646345321));
  EXPECT_TRUE(set.contains(28547547457548));
}