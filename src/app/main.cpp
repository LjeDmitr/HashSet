#include <algorithm>
#include <hash_set/hash_set.hpp>
#include <iostream>

using namespace std;

int main() {
  HashSet<int> set;

  set.insert(1);
  set.insert(2);
  set.insert(3);
  set.insert(4);
  set.insert(5);

  cout << "Size of set is: " << set.size() << endl;

  cout << "Set contains 3: " << boolalpha << set.contains(3) << endl;
  cout << "Set contains 6: " << boolalpha << set.contains(6) << endl;

  set.erase(3);

  set.clear();
  cout << "Size of set after clearing is: " << set.size() << endl;

  return 0;
}