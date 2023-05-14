#include <algorithm>
#include <hash_set/hash_set.hpp>
#include <iostream>

int main() {
  HashSet<int> set;

  set.insert(1);
  set.insert(2);
  set.insert(3);
  set.insert(4);
  set.insert(5);

  std::cout << "Size of set is: " << set.size() << std::endl;

  std::cout << "Set contains 3: " << std::boolalpha << set.contains(3)
            << std::endl;
  std::cout << "Set contains 6: " << std::boolalpha << set.contains(6)
            << std::endl;

  std::cout << "Elements in set are: ";
  for (const auto& element : set) {
    std::cout << element << " ";
  }
  std::cout << std::endl;

  set.erase(3);

  std::cout << "Elements in set after removing 3 are: ";
  for (auto it = set.begin(); it != set.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;

  set.clear();
  std::cout << "Size of set after clearing is: " << set.size() << std::endl;

  return 0;
}