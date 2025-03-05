#pragma once

#include <utility> // For std::move

namespace eds {

template <typename T> class uniquePointer {
public:
  explicit uniquePointer(T *ptr = nullptr);
  // Template constructor for variadic arguments, creating a new T object usingperfect forwarding
  template <typename... Args>
  uniquePointer(Args &&...args)
      : pointer_{new T{std::forward<Args>(args)...}} {}
  // Copy constructor deleted to enforce unique ownership
  uniquePointer(const uniquePointer &other) = delete;
  // Copy assignment operator deleted to enforce unique ownership
  uniquePointer &operator=(const uniquePointer &other) = delete;
  uniquePointer(uniquePointer &&other) noexcept;
  uniquePointer &operator=(uniquePointer &&other) noexcept;
  ~uniquePointer();
  T *get() const;
  T &operator*() const;
  T *operator->() const;
  explicit operator bool() const;
  void reset(T *ptr = nullptr);
  T *release();
  void swap(uniquePointer &other);

private:
  T *pointer_;
};
// Explicit constructor initializing the pointer with a default value ofnullptr
template <typename T> uniquePointer<T>::uniquePointer(T *ptr) : pointer_(ptr) {}
// Move constructor with noexcept specifier for optimized move semantics
template <typename T>
uniquePointer<T>::uniquePointer(uniquePointer &&other) noexcept
    : pointer_(other.release()) {}
// Move assignment operator with noexcept specifier for optimized move semantics
template <typename T>
uniquePointer<T> &uniquePointer<T>::operator=(uniquePointer &&other) noexcept {
  if (this != &other) {
    reset(other.release());
  }
  return *this;
}
// Destructor for releasing the allocated memory
template <typename T> uniquePointer<T>::~uniquePointer() { delete pointer_; }
// Make_unique function for creating unique pointers
template <typename T, typename... Args>
uniquePointer<T> make_unique(Args &&...args) {
  return uniquePointer<T>(new T(std::forward<Args>(args)...));
}
// Getter function to retrieve the raw pointer
template <typename T> T *uniquePointer<T>::get() const { return pointer_; }
// Overloaded dereference operator (*) for accessing the object
template <typename T> T &uniquePointer<T>::operator*() const {
  return *pointer_;
}
// Overloaded arrow operator (->) for accessing members of the object
template <typename T> T *uniquePointer<T>::operator->() const {
  return pointer_;
}
// Explicit conversion operator to bool for checking if the pointer is valid
template <typename T> uniquePointer<T>::operator bool() const {
  return pointer_ != nullptr;
}
// Resetting the pointer to a new value or nullptr
template <typename T> void uniquePointer<T>::reset(T *ptr) {
  if (pointer_ != ptr) {
    delete pointer_;
    pointer_ = ptr;
  }
}
// Releasing ownership of the pointer and returning it
template <typename T> T *uniquePointer<T>::release() {
  T *released = pointer_;
  pointer_ = nullptr;
  return released;
}
// Swapping method that swaps the contents of two uniquePointers
template <typename T> void uniquePointer<T>::swap(uniquePointer &other) {
  std::swap(pointer_, other.pointer_);
}
// Free function swap that calls upon the swap method...
template <typename T>
void swap(uniquePointer<T> &one, uniquePointer<T> &other) {
  one.swap(other);
}

} // namespace eds