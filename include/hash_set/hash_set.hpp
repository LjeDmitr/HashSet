#ifndef HASHSET_HPP
#define HASHSET_HPP

template <typename T>
class HashSet {
 public:
  class iterator;

  HashSet();
  HashSet(const HashSet& other);
  HashSet(HashSet&& other) noexcept;
  HashSet(std::initializer_list<T> values);
  ~HashSet();

  HashSet& operator=(const HashSet& other);
  HashSet& operator=(HashSet&& other) noexcept;
  bool operator==(const HashSet<T>& other) const;
  bool operator!=(const HashSet<T>& other) const;
  bool operator<(const HashSet<T>& other) const;
  bool operator>(const HashSet<T>& other) const;
  bool operator<=(const HashSet<T>& other) const;
  bool operator>=(const HashSet<T>& other) const;

  void insert(const T& value);
  void clear() noexcept;
  bool contains(const T& value) const;
  bool empty() const noexcept;
  void erase(const T& value);
  std::size_t size() const noexcept;

  iterator begin() noexcept;
  iterator begin() const noexcept;
  iterator end() noexcept;
  iterator end() const noexcept;

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

 public:
  class iterator {
    friend class HashSet<T>;

   public:
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;

    iterator() noexcept;
    iterator(Node** data, std::size_t capacity, std::size_t index) noexcept;
    iterator(const iterator& other)
        : m_data(other.m_data),
          m_capacity(other.m_capacity),
          m_index(other.m_index),
          m_node(other.m_node) {
    }

    reference operator*() const;
    pointer operator->() const;
    iterator& operator++();
    iterator& operator--();
    iterator operator++(int);
    iterator operator--(int);
    iterator operator+(difference_type n);
    iterator operator-(difference_type n);
    difference_type operator-(const iterator& other) const;
    iterator operator=(const iterator& other);
    iterator& operator-=(difference_type n);
    iterator& operator+=(difference_type n);
    bool operator==(const iterator& other) const noexcept;
    bool operator!=(const iterator& other) const noexcept;
    bool operator<(const iterator& other) const noexcept;
    bool operator>(const iterator& other) const noexcept;
    bool operator<=(const iterator& other) const noexcept;
    bool operator>=(const iterator& other) const noexcept;

   private:
    Node** m_data;
    std::size_t m_capacity;
    std::size_t m_index;
    Node* m_node;

    void findNextNode();
  };
};

#endif