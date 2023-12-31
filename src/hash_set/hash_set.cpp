#include <algorithm>
#include <hash_set/hash_set.hpp>
#include <stdexcept>

template <typename T>
HashSet<T>::HashSet()
    : m_data(new Node*[DEFAULT_CAPACITY]()),
      m_capacity(DEFAULT_CAPACITY),
      m_size(0) {
}

template <typename T>
HashSet<T>::HashSet(const HashSet& other)
    : m_data(nullptr), m_capacity(other.m_capacity), m_size(0) {
  copyFrom(other);
}

template <typename T>
HashSet<T>::HashSet(HashSet&& other) noexcept
    : m_data(nullptr), m_capacity(0), m_size(0) {
  moveFrom(std::move(other));
}

template <typename T>
HashSet<T>::HashSet(std::initializer_list<T> values)
    : m_data(new Node*[DEFAULT_CAPACITY]()),
      m_capacity(DEFAULT_CAPACITY),
      m_size(0) {
  for (const auto& value : values) {
    insert(value);
  }
}

template <typename T>
HashSet<T>::~HashSet() {
  clear();
  delete[] m_data;
}

template <typename T>
void HashSet<T>::insert(const T& value) {
  if (contains(value)) {
    return;
  }
  if (m_size >= m_capacity * LOAD_FACTOR) {
    rehash();
  }
  const size_t index = std::hash<T>{}(value) % m_capacity;
  m_data[index] = new Node(value, m_data[index]);
  ++m_size;
}

template <typename T>
void HashSet<T>::clear() noexcept {
  for (size_t i = 0; i < m_capacity; ++i) {
    Node* current = m_data[i];
    while (current != nullptr) {
      Node* next = current->next;
      delete current;
      current = next;
    }
    m_data[i] = nullptr;
  }
  m_size = 0;
}

template <typename T>
bool HashSet<T>::contains(const T& value) const {
  const size_t index = std::hash<T>{}(value) % m_capacity;
  Node* current = m_data[index];
  while (current != nullptr) {
    if (current->value == value) {
      return true;
    }
    current = current->next;
  }
  return false;
}

template <typename T>
bool HashSet<T>::empty() const noexcept {
  return m_size == 0;
}

template <typename T>
void HashSet<T>::erase(const T& value) {
  const size_t index = std::hash<T>{}(value) % m_capacity;
  Node* current = m_data[index];
  Node* previous = nullptr;
  while (current != nullptr) {
    if (current->value == value) {
      if (previous != nullptr) {
        previous->next = current->next;
      } else {
        m_data[index] = current->next;
      }
      delete current;
      current = nullptr;
      --m_size;
      return;
    }
    previous = current;
    current = current->next;
  }
}

template <typename T>
size_t HashSet<T>::size() const noexcept {
  return m_size;
}

template <typename T>
void HashSet<T>::rehash() {
  size_t new_capacity = m_capacity * 2;
  Node** new_data = new Node*[new_capacity]();
  size_t new_size = 0;

  for (size_t i = 0; i < m_capacity; ++i) {
    Node* node = m_data[i];
    while (node != nullptr) {
      size_t new_index = std::hash<T>{}(node->value) % new_capacity;
      Node* new_node = new_data[new_index];
      new_data[new_index] = new Node(node->value, new_node);
      ++new_size;
      node = node->next;
    }
  }

  clear();
  m_data = new_data;
  m_capacity = new_capacity;
  m_size = new_size;
}

template <typename T>
void HashSet<T>::copyFrom(const HashSet& other) {
  m_data = new Node*[other.m_capacity]();
  m_capacity = other.m_capacity;
  m_size = other.m_size;

  for (size_t i = 0; i < other.m_capacity; ++i) {
    Node* other_node = other.m_data[i];
    Node** node_ptr = &m_data[i];
    while (other_node != nullptr) {
      *node_ptr = new Node(other_node->value);
      node_ptr = &((*node_ptr)->next);
      other_node = other_node->next;
    }
  }
}

template <typename T>
void HashSet<T>::moveFrom(HashSet&& other) noexcept {
  m_data = other.m_data;
  m_capacity = other.m_capacity;
  m_size = other.m_size;

  other.m_data = nullptr;
  other.m_capacity = 0;
  other.m_size = 0;
}

template <typename T>
HashSet<T>& HashSet<T>::operator=(const HashSet& other) {
  if (this != &other) {
    clear();
    delete[] m_data;
    m_data = nullptr;
    copyFrom(other);
  }
  return *this;
}

template <typename T>
HashSet<T>& HashSet<T>::operator=(HashSet&& other) noexcept {
  if (this != &other) {
    clear();
    delete[] m_data;
    m_data = nullptr;
    m_capacity = 0;
    moveFrom(std::move(other));
  }
  return *this;
}

template <typename T>
bool HashSet<T>::operator==(const HashSet<T>& other) const {
  if (m_size != other.m_size) {
    return false;
  }

  for (const auto& value : other) {
    if (!contains(value)) {
      return false;
    }
  }

  return true;
}

template <typename T>
bool HashSet<T>::operator!=(const HashSet<T>& other) const {
  return !(*this == other);
}

template <typename T>
bool HashSet<T>::operator<(const HashSet<T>& other) const {
  auto it1 = begin();
  auto it2 = other.begin();

  while (it1 != end() && it2 != other.end()) {
    if (*it1 < *it2) {
      return true;
    } else if (*it2 < *it1) {
      return false;
    }
    ++it1;
    ++it2;
  }

  return it1 == end() && it2 != other.end();
}

template <typename T>
bool HashSet<T>::operator>(const HashSet<T>& other) const {
  return other < *this;
}

template <typename T>
bool HashSet<T>::operator<=(const HashSet<T>& other) const {
  return !(other < *this);
}

template <typename T>
bool HashSet<T>::operator>=(const HashSet<T>& other) const {
  return !(*this < other);
}

template <typename T>
typename HashSet<T>::iterator HashSet<T>::begin() noexcept {
  size_t index = 0;
  while (index < m_capacity && m_data[index] == nullptr) {
    ++index;
  }
  if (index < m_capacity) {
    return iterator(m_data, m_capacity, index);
  } else {
    return end();
  }
}

template <typename T>
typename HashSet<T>::iterator HashSet<T>::begin() const noexcept {
  size_t index = 0;
  while (index < m_capacity && m_data[index] == nullptr) {
    ++index;
  }
  if (index < m_capacity) {
    return iterator(m_data, m_capacity, index);
  } else {
    return end();
  }
}

template <typename T>
typename HashSet<T>::iterator HashSet<T>::end() noexcept {
  return iterator(m_data, m_capacity, m_capacity);
}

template <typename T>
typename HashSet<T>::iterator HashSet<T>::end() const noexcept {
  return iterator(m_data, m_capacity, m_capacity);
}

template <typename T>
typename HashSet<T>::iterator::reference HashSet<T>::iterator::operator*()
    const {
  return m_node->value;
}

template <typename T>
typename HashSet<T>::iterator::pointer HashSet<T>::iterator::operator->()
    const {
  return &m_node->value;
}

template <typename T>
typename HashSet<T>::iterator& HashSet<T>::iterator::operator++() {
  findNextNode();
  return *this;
}

template <typename T>
typename HashSet<T>::iterator HashSet<T>::iterator::operator++(int) {
  iterator temp(std::move(*this));
  ++(*this);
  return temp;
}

template <typename T>
typename HashSet<T>::iterator& HashSet<T>::iterator::operator--() {
  if (m_node != nullptr) {
    Node* tmp = m_node;
    m_node = m_data[m_index];
    if (tmp != m_node) {
      while (m_node->next != tmp) {
        m_node = m_node->next;
      }
      return *this;
    }
  }
  std::size_t i = m_index - 1;
  while (i < m_capacity && m_data[i] == nullptr) {
    --i;
  }
  if (i != 0 && m_data[i] != nullptr) {
    m_node = m_data[i];
    while (m_node->next != nullptr) {
      m_node = m_node->next;
    }
    m_index = i;
  } else {
    m_node = nullptr;
    m_index = m_capacity;
  }
  return *this;
}

template <typename T>
typename HashSet<T>::iterator HashSet<T>::iterator::operator--(int) {
  iterator tmp = *this;
  --(*this);
  return tmp;
}

template <typename T>
void HashSet<T>::iterator::findNextNode() {
  m_node = m_data[m_index];
  if (m_node != nullptr) {
    if (m_node->next != nullptr) {
      m_node = m_node->next;
      return;
    }
  }
  for (std::size_t i = m_index + 1; i < m_capacity; ++i) {
    if (m_data[i] != nullptr) {
      m_node = m_data[i];
      m_index = i;
      return;
    }
  }
  m_node = nullptr;
  m_index = m_capacity;
}

template <typename T>
HashSet<T>::iterator::iterator() noexcept
    : m_data(nullptr), m_capacity(0), m_index(0), m_node(nullptr) {
}

template <typename T>
HashSet<T>::iterator::iterator(
    Node** data,
    std::size_t capacity,
    std::size_t index) noexcept
    : m_data(data), m_capacity(capacity), m_index(index), m_node(nullptr) {
  if (index < capacity) {
    m_node = m_data[index];
  }
}

template <typename T>
typename HashSet<T>::iterator HashSet<T>::iterator::operator+(
    difference_type n) {
  iterator result(*this);
  result += n;
  return result;
}

template <typename T>
typename HashSet<T>::iterator HashSet<T>::iterator::operator-(
    difference_type n) {
  iterator result(*this);
  result -= n;
  return result;
}

template <typename T>
typename HashSet<T>::iterator& HashSet<T>::iterator::operator-=(
    difference_type n) {
  for (difference_type i = 0; i < n; ++i) {
    --(*this);
  }
  return *this;
}

template <typename T>
typename HashSet<T>::iterator& HashSet<T>::iterator::operator+=(
    difference_type n) {
  for (difference_type i = 0; i < n; ++i) {
    ++(*this);
  }
  return *this;
}

template <typename T>
bool HashSet<T>::iterator::operator==(const iterator& other) const noexcept {
  return m_node == other.m_node;
}

template <typename T>
bool HashSet<T>::iterator::operator!=(const iterator& other) const noexcept {
  return !(*this == other);
}

template <typename T>
bool HashSet<T>::iterator::operator<(const iterator& other) const noexcept {
  return m_data == other.m_data && m_index == other.m_index &&
      m_node < other.m_node;
}
template <typename T>
bool HashSet<T>::iterator::operator>(const iterator& other) const noexcept {
  return m_data == other.m_data && m_index == other.m_index &&
      m_node > other.m_node;
}

template <typename T>
bool HashSet<T>::iterator::operator<=(const iterator& other) const noexcept {
  return m_data == other.m_data && m_index == other.m_index &&
      m_node <= other.m_node;
}

template <typename T>
bool HashSet<T>::iterator::operator>=(const iterator& other) const noexcept {
  return m_data == other.m_data && m_index == other.m_index &&
      m_node >= other.m_node;
}

template <typename T>
typename HashSet<T>::iterator& HashSet<T>::iterator::operator=(
    const iterator& other) {
  if (this != &other) {
    m_data = other.m_data;
    m_capacity = other.m_capacity;
    m_index = other.m_index;
    m_node = other.m_node;
  }
  return *this;
}

template <typename T>
typename HashSet<T>::iterator::difference_type HashSet<T>::iterator::operator-(
    const iterator& other) const {
  return m_index - other.m_index;
}

template class HashSet<int>;
template class HashSet<std::string>;
template class HashSet<double>;
template class HashSet<char>;
template class HashSet<float>;
template class HashSet<bool>;
template class HashSet<long>;
template class HashSet<short>;