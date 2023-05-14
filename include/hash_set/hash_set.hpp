#ifndef HASHSET_HPP
#define HASHSET_HPP

template <typename T>
class HashSet {
 public:

  HashSet();
  HashSet(const HashSet& other);
  HashSet(HashSet&& other) noexcept;
  HashSet(std::initializer_list<T> values);
  ~HashSet();

  void insert(const T& value);
  void clear() noexcept;
  bool contains(const T& value) const;
  bool empty() const noexcept;
  void erase(const T& value);
  std::size_t size() const noexcept;

 private:
  struct Node {
    T value;
    Node* next;
    Node(const T& value, Node* next = nullptr) : value(value), next(next) {
    }
    Node(T&& value, Node* next = nullptr)
        : value(std::move(value)), next(next) {
    }
  };

  static constexpr std::size_t DEFAULT_CAPACITY = 16;
  static constexpr double LOAD_FACTOR = 0.75;

  Node** m_data;
  std::size_t m_capacity;
  std::size_t m_size;

  void rehash();
  void copyFrom(const HashSet& other);
  void moveFrom(HashSet&& other) noexcept;

};

#endif