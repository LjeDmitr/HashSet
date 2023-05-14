#include <gtest/gtest.h>
#include <algorithm>
#include <hash_set/hash_set.hpp>
#include <iterator>
#include <vector>

using namespace std;

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

  HashSet<int> set2(move(set1));

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

  auto it = find(set.begin(), set.end(), 3);
  EXPECT_NE(it, set.end());
  EXPECT_EQ(*it, 3);
}

TEST(HashSetSTLTest, StandardAlgorithmFor_each) {
  HashSet<int> set{1, 2, 3, 4, 5};

  int sum = 0;
  for_each(set.begin(), set.end(), [&sum](int x) { sum += x; });
  EXPECT_EQ(sum, 15);
}

TEST(HashSetSTLTest, StandardAlgorithmCount_if) {
  HashSet<int> set{1, 2, 3, 4, 5};

  auto count =
      count_if(set.begin(), set.end(), [](int x) { return x % 2 == 0; });
  EXPECT_EQ(count, 2);
}

TEST(HashSetSTLTest, StandardAlgorithmTransform) {
  HashSet<int> set{1, 2, 3, 4, 5};

  vector<int> doubled;
  transform(set.begin(), set.end(), back_inserter(doubled), [](int x) {
    return 2 * x;
  });
  EXPECT_EQ(doubled, vector<int>({2, 4, 6, 8, 10}));
}