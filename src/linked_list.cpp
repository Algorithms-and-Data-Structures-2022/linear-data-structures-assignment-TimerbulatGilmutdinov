#include "assignment/linked_list.hpp"

namespace assignment {

  LinkedList::~LinkedList() {
    LinkedList::Clear();
  }

  void LinkedList::Add(int value) {
    Node* node = new Node(value);
    size_++;
    if (front_ == nullptr) {
      front_ = node;
    } else {
      back_->next = node;
    }
    back_ = node;
  }

  bool LinkedList::Insert(int index, int value) {
    if (index < 0 || index > size())
      return false;
    int curIndex = 0;
    Node* node = new Node(value);
    if (index == 0) {
      if (size() != 0) {
        node->next = front_;
      } else {
        back_ = node;
      }
      front_ = node;
      size_++;
      return true;
    }
    if (index == size()) {
      back_->next = node;
      back_ = node;
      size_++;
      return true;
    }
    Node* pointer = front_;
    while (curIndex != index - 1) {
      pointer = pointer->next;
      curIndex++;
    }
    node->next = pointer->next;
    pointer->next = node;
    size_++;
    return true;
  }

  bool LinkedList::Set(int index, int new_value) {
    if (index < 0 || index >= size())
      return false;
    Node* node = front_;
    for (int i = 0; i < index; i++) {
      node = node->next;
    }
    node->value = new_value;
    return true;
  }

  std::optional<int> LinkedList::Remove(int index) {
    if (index < 0 || index >= size())
      return std::nullopt;
    if (index == 0) {
      int val = front_->value;
      front_ = front_->next;
      size_--;
      return val;
    }
    int curIndex = 0;
    Node* node = front_;
    while (curIndex != index - 1) {
      node = node->next;
      curIndex++;
    }
    if (index == size() - 1) {
      int val = back_->value;
      node->next = nullptr;
      back_ = node;
      size_--;
      return val;
    }
    int tempValue = node->next->value;
    node->next = node->next->next;
    size_--;
    return tempValue;
  }

  void LinkedList::Clear() {
    front_ = nullptr;
    back_ = nullptr;
    size_ = 0;
  }

  std::optional<int> LinkedList::Get(int index) const {
    if (index < 0 || index >= size())
      return std::nullopt;
    Node* node = front_;
    for (int i = 0; i < index; i++) {
      node = node->next;
    }
    return node->value;
  }

  std::optional<int> LinkedList::IndexOf(int value) const {
    Node* node = front_;
    for (int i = 0; i < size_; i++) {
      if (node->value == value) {
        return i;
      }
      node = node->next;
    }
    return std::nullopt;
  }

  bool LinkedList::Contains(int value) const {
    Node* node = front_;
    while (node != nullptr) {
      if (node->value == value)
        return true;
      node = node->next;
    }
    return false;
  }

  bool LinkedList::IsEmpty() const {
    return size() == 0;
  }

  int LinkedList::size() const {
    return size_;
  }

  std::optional<int> LinkedList::front() const {
    if (size() == 0)
      return std::nullopt;
    return front_->value;
  }

  std::optional<int> LinkedList::back() const {
    if (size() == 0)
      return std::nullopt;
    return back_->value;
  }

  Node* LinkedList::FindNode(int index) const {
    if (index < 0 || index >= size())
      return nullptr;
    Node* node = front_;
    for (int i = 0; i < index; i++) {
      node = node->next;
    }
    return node;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  LinkedList::LinkedList(const std::vector<int>& values) {

    if (values.empty()) {
      return;
    }

    auto* curr_node = new Node(values.front());
    front_ = curr_node;

    for (int index = 1; index < values.size() - 1; ++index) {
      curr_node->next = new Node(values[index]);
      curr_node = curr_node->next;
    }

    if (values.size() == 1) {
      back_ = front_;
    } else {
      curr_node->next = new Node(values.back());
      back_ = curr_node->next;
    }

    size_ = static_cast<int>(values.size());
  }

  std::vector<int> LinkedList::toVector() const {

    if (front_ == nullptr || size_ == 0) {
      return {};
    }

    std::vector<int> array;
    array.reserve(size_);

    for (auto* node = front_; node != nullptr; node = node->next) {
      array.push_back(node->value);
    }

    return array;
  }

}  // namespace assignment