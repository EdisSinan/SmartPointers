#pragma once
#include "shared.hpp"
#include <utility>

namespace eds {
template <typename T> class sharedPointer;
template <typename T> class weakPointer {
public:
  // Default constructor
  weakPointer() noexcept;
  // Constructor from sharedPointer of a different type
  template <typename U> weakPointer(const sharedPointer<U> &other) noexcept;
  // Copy constructor from weakPointer of a different type
  template <typename U> weakPointer(const weakPointer<U> &other) noexcept;
  // Copy constructor from weakPointer
  weakPointer(const weakPointer &other) noexcept;
  // Copy assignment operator
  weakPointer &operator=(const weakPointer &other) noexcept;
  // Copy assignment operator from nullptr
  weakPointer &operator=(std::nullptr_t) noexcept;
  //Move constructor 
  weakPointer(weakPointer&& other) noexcept;   
  //Move assigment operator
  weakPointer &operator=(weakPointer&& other) noexcept; 
  // Destructor
  ~weakPointer();
  // Reset function
  void reset() noexcept;
  // Use count function
  std::size_t use_count() const noexcept;
  // Expired function
  bool expired() const noexcept;
  // Lock function to convert to sharedPointer
  sharedPointer<T> lock() const noexcept;
  //Swap method
  void swap(weakPointer &other);

private:
  std::size_t *weakCounter_;
  std::size_t *sharedCounter_;
  T *pointer_;
  // Helper function to increment the weak counter
  void increment_weak();
  // Helper function to decrement the weak counter
  void decrement_weak();
  template <typename U> friend class sharedPointer;
};

// Default constructor
template <typename T>
weakPointer<T>::weakPointer() noexcept
    : weakCounter_(nullptr), sharedCounter_(nullptr), pointer_(nullptr) {}

// Constructor from sharedPointer of a different type
template <typename T>
template <typename U>
weakPointer<T>::weakPointer(const sharedPointer<U> &other) noexcept
    : weakCounter_(other.weakCounter_), sharedCounter_(other.counter_),pointer_(other.pointer_) {
  increment_weak();
}

// Copy constructor from weakPointer of a different type
template <typename T>
template <typename U>
weakPointer<T>::weakPointer(const weakPointer<U> &other) noexcept
    : weakCounter_(other.weakCounter_), sharedCounter_(other.sharedCounter_),pointer_(other.pointer_) {
  increment_weak();
}
// Copy constructor from weakPointe
template <typename T>
weakPointer<T>::weakPointer(const weakPointer &other) noexcept
    : weakCounter_(other.weakCounter_), sharedCounter_(other.sharedCounter_),pointer_(other.pointer_) {
  increment_weak();
}


// Copy assignment operator
template <typename T>
weakPointer<T> &weakPointer<T>::operator=(const weakPointer &other) noexcept {
  if (this != &other) {
    reset();
    weakCounter_ = other.weakCounter_;
    sharedCounter_ = other.sharedCounter_;
    pointer_ = other.pointer_;
    increment_weak();
  }
  return *this;
}

// Copy assignment operator from nullptr
template <typename T>
weakPointer<T> &weakPointer<T>::operator=(std::nullptr_t) noexcept {
  reset();
  return *this;
}
// Move constructor
template <typename T>
weakPointer<T>::weakPointer(weakPointer&& other) noexcept
  :weakCounter_{other.weakCounter_},sharedCounter_{other.sharedCounter_},pointer_{other.pointer_}{
        other.pointer_=nullptr;
        other.sharedCounter_=nullptr;
        other.weakCounter_=nullptr;
}

// Move assignment operator
template <typename T>
weakPointer<T>& weakPointer<T>::operator=(weakPointer&& other) noexcept {
 if(pointer_==other.pointer_)
            {return *this;} 
        delete pointer_;
        delete sharedCounter_;
        delete weakCounter_;

        pointer_=other.pointer_;
        sharedCounter_=other.sharedCounter_;
        weakCounter_=other.weakCounter_;

        other.pointer_=nullptr;
        other.sharedCounter_=nullptr;
        other.weakCounter_=nullptr;

        return *this;
}

// Destructor
template <typename T> weakPointer<T>::~weakPointer() {
  if (weakCounter_ != nullptr) {
    if (--(*weakCounter_) == 0) {
      delete weakCounter_;
      weakCounter_ = nullptr;
    }
  }
}

// Reset function
template <typename T> void weakPointer<T>::reset() noexcept {
  decrement_weak();
  if (use_count() == 0) {
    weakCounter_ = nullptr;
  }
}

// Use count function
template <typename T> std::size_t weakPointer<T>::use_count() const noexcept {
  return (weakCounter_ != nullptr) ? *weakCounter_ : 0;
}

// Expired function
template <typename T> bool weakPointer<T>::expired() const noexcept {
  return use_count() == 0;
}

template <typename T> sharedPointer<T> weakPointer<T>::lock() const noexcept {
  if (!expired()) {
    // If the weak pointer is not expired, create and return a shared pointer
    // std::cout << "Test1" << std::endl;
    return sharedPointer<T>(*this);
  } else {
    // If the weak pointer is expired, return an empty shared pointer
    return sharedPointer<T>();
  }
}
// method swap
template <typename T> void weakPointer<T>::swap(weakPointer &other) {
  std::swap(pointer_, other.pointer_);
}
// free function swap
template <typename T> void swap(weakPointer<T> &one, weakPointer<T> &other) {
  one.swap(other);
}

// Helper function to increment the weak counter
template <typename T> void weakPointer<T>::increment_weak() {
  if (weakCounter_ != nullptr) {
    ++(*weakCounter_);
  }
}

template <typename T> void weakPointer<T>::decrement_weak() {
  if (weakCounter_ != nullptr) {
    if (--(*weakCounter_) == 0) {
      delete weakCounter_;
      weakCounter_ = nullptr; // Set to null after deletion
    }
  }
}

} // namespace eds
