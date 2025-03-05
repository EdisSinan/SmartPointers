#pragma once
#include <utility> // For std::move

namespace eds {
// Forward declaration of weakPointer
template <typename T> class weakPointer;

// Shared Pointer class template
template <typename T> class sharedPointer {
public:
  // Constructor for nullptr
  sharedPointer(std::nullptr_t) noexcept;
  // Explicit constructor taking a raw pointer
  explicit sharedPointer(T *ptr = nullptr);
  // Copy constructor
  sharedPointer(const sharedPointer &other) noexcept;
  // Copy assignment operator
  sharedPointer &operator=(const sharedPointer &other) noexcept;
  // Move constructor
  sharedPointer(sharedPointer &&other) noexcept;
  // Move assignment operator
  sharedPointer &operator=(sharedPointer &&other) noexcept;
  // Destructor
  ~sharedPointer();
  // Function to get the current use count
  std::size_t use_count() const;
  // Function to get the raw pointer
  T *get() const;
  // Dereference operator
  T &operator*() const;
  // Member access operator
  T *operator->() const;
  // Explicit conversion operator to bool
  explicit operator bool() const;
  // Function to reset the shared pointer with a new raw pointer
  void reset(T *ptr = nullptr);
  // Swap function to exchange the contents with another shared pointer
  void swap(sharedPointer &other);
  template <typename U> sharedPointer(const weakPointer<U> &weakPtr);
  // Variadic template constructor for perfect forwarding of arguments
  //template <typename... Args> sharedPointer(Args &&...args);

private:
  // Counter for shared ownership
  std::size_t *counter_;
  // Counter for weak ownership
  std::size_t *weakCounter_;

  // Raw pointer to the owned resource
  T *pointer_;

  // Adding weakPointer as a frinedclass
  template <typename U> friend class weakPointer;
};

// Constructor for nullptr
template <typename T>
sharedPointer<T>::sharedPointer(std::nullptr_t) noexcept
    : counter_(nullptr), weakCounter_(nullptr), pointer_(nullptr) {}

// Constructor taking a raw pointer
template <typename T>
sharedPointer<T>::sharedPointer(T *ptr)
    : counter_(new std::size_t(1)), weakCounter_(new std::size_t(0)),
      pointer_(ptr) {}

// Copy constructor
template <typename T>
sharedPointer<T>::sharedPointer(const sharedPointer &other) noexcept
    : counter_{other.counter_},
      weakCounter_{other.weakCounter_}, pointer_{other.pointer_} {
  ++(*counter_);
}

// Copy assignment operator
template <typename T>
sharedPointer<T> &
sharedPointer<T>::operator=(const sharedPointer &other) noexcept {
  if (this != &other) {
    if (--(*counter_) == 0) {
      delete counter_;
      delete weakCounter_;
      delete pointer_;
    }
    counter_ = other.counter_;
    weakCounter_ = other.weakCounter_;
    pointer_ = other.pointer_;
    ++(*counter_);
  }

  return *this;
}

// Move constructor
template <typename T>
sharedPointer<T>::sharedPointer(sharedPointer &&other) noexcept
    : counter_{other.counter_},
      weakCounter_{other.weakCounter_}, pointer_{other.pointer_} {
  other.counter_ = nullptr;
  other.weakCounter_ = nullptr;
  other.pointer_ = nullptr;
}

// Move assignment operator
template <typename T>
sharedPointer<T> &sharedPointer<T>::operator=(sharedPointer &&other) noexcept {
  if (this != &other) {
    if (--(*counter_) == 0) {
      delete counter_;
      delete weakCounter_;
      delete pointer_;
    }
    counter_ = other.counter_;
    weakCounter_ = other.weakCounter_;
    pointer_ = other.pointer_;
    other.counter_ = nullptr;
    weakCounter_ = nullptr;
    other.pointer_ = nullptr;
  }

  return *this;
}

// Destructor
template <typename T> sharedPointer<T>::~sharedPointer() {
  if (counter_ != nullptr) {
    if (--(*counter_) == 0) {
      delete counter_;
      counter_=nullptr;

      if (pointer_ != nullptr) {
        delete pointer_;
        pointer_=nullptr;
        // Decrement the weak counter only if it's not null
        if (weakCounter_ != nullptr) {
          --(*weakCounter_);
        }
      }
    }
  }
}

// Make shared function to create a shared pointer with dynamic allocation
template <typename T, typename... Args>
sharedPointer<T> make_shared(Args &&...args) {
  return sharedPointer<T>(new T(std::forward<Args>(args)...));
}

// Function to get the current use count
template <typename T> std::size_t sharedPointer<T>::use_count() const {
  return (counter_ != nullptr) ? *counter_ : 0;
}

// Function to get the raw pointer
template <typename T> T *sharedPointer<T>::get() const { return pointer_; }

// Dereference operator
template <typename T> T &sharedPointer<T>::operator*() const {
  return *pointer_;
}

// Member access operator
template <typename T> T *sharedPointer<T>::operator->() const {
  return pointer_;
}

// Explicit conversion operator to bool
template <typename T> sharedPointer<T>::operator bool() const {
  return pointer_ != nullptr;
}

template <typename T> void sharedPointer<T>::reset(T *ptr) {
  if (ptr != nullptr) {
    if (--(*counter_) == 0) {
      delete counter_;
      delete pointer_;
      pointer_=nullptr;
      counter_=nullptr;
      --(*weakCounter_);
    }
    counter_ = new std::size_t(1);
    weakCounter_ = new std::size_t(0);
    pointer_ = ptr;
  } else {
    if (--(*counter_) == 0) {
      delete counter_;
      delete pointer_;
      --(*weakCounter_);
      pointer_=nullptr;
      counter_=nullptr;
    }
  }
}

// Swap function to exchange the contents with another shared pointer
template <typename T> void sharedPointer<T>::swap(sharedPointer &other) {
  std::swap(counter_, other.counter_);
  std::swap(pointer_, other.pointer_);
  std::swap(weakCounter_, other.weakCounter_);
}

// free function swap
template <typename T>
void swap(sharedPointer<T> &one, sharedPointer<T> &other) {
  one.swap(other);
}

/****************************************************************************
*If Variadic Template were uncommented the code would work but the initiali-*
*-zation of copy constructors would never bee called it would forward to the*
*Variadic template construcor as it is a better match example:              *
*sharedPointer<MyClass> ptr2(ptr1) would call Variadic template instead of  *
*the usual copy constructor that is defined in this header file             *
*Have no clue why it is a better candidate for that than copy constructor   *
****************************************************************************/

// // Variadic template constructor for perfect forwarding of arguments
// template <typename T>
// template <typename... Args>
// sharedPointer<T>::sharedPointer(Args &&...args) : pointer_(nullptr) {
//   if constexpr ((std::is_same<sharedPointer<T>, std::decay_t<Args>>::value ||
//                  ...)) {
//     // If any argument is a sharedPointer, initialize counter_ and pointer_
//     ((counter_ = args.counter_, weakCounter_ = args.weakCounter_,
//       pointer_ = args.pointer_, ++(*counter_)),
//      ...);
//   } else {
//     // Otherwise, initialize pointer_ with new T and counter_ with 1
//     pointer_ = new T(std::forward<Args>(args)...);
//     counter_ = new std::size_t(1);
//     weakCounter_ = new std::size_t(0);
//   }
// }

//Creating a shared pointer from a weakPointer(used for lock method in weakPointer....)
template <typename T>
template <typename U>
sharedPointer<T>::sharedPointer(const weakPointer<U> &weakPtr) {
  if (weakPtr.weakCounter_ != nullptr) {
    counter_ = weakPtr.sharedCounter_;
    weakCounter_ = weakPtr.weakCounter_;
    pointer_ = weakPtr.pointer_;
    ++(*counter_);
  } else {
    // Handle the case where the weak pointer is invalid
    counter_ = nullptr;
    weakCounter_ = nullptr;
    pointer_ = nullptr;
  }
}

} // namespace eds