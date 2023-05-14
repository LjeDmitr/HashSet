#include <algorithm>
#include <hash_set/hash_set.hpp>
#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
HashSet<T>::HashSet()
    : m_data(new Node*[DEFAULT_CAPACITY]()),
      m_capacity(DEFAULT_CAPACITY),
      m_size(0) {
}

template <typename T>
HashSet<T>::HashSet(const HashSet& other)
    : m_data(new Node*[DEFAULT_CAPACITY]()),
      m_capacity(other.m_capacity),
      m_size(0) {
  copyFrom(other);
}

template <typename T>
HashSet<T>::HashSet(HashSet&& other) noexcept
    : m_data(nullptr), m_capacity(0), m_size(0) {
  moveFrom(move(other));
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
  const size_t index = hash<T>{}(value) % m_capacity;
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
  const size_t index = hash<T>{}(value) % m_capacity;
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
  const size_t index = hash<T>{}(value) % m_capacity;
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
      size_t new_index = hash<T>{}(node->value) % new_capacity;
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

template class HashSet<int>;