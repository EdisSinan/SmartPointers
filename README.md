# Smart pointers 
## Please note that the size of the test.cpp file, with its extensive number of lines and the separation of all components, was intentional and in accordance with my mentor's requirements. It was not my personal decision; he specifically requested an old-school testing approach with such detailed segmentation.

## C++ Smart Pointers Implementation

Welcome to the C++ Smart Pointers Implementation project! 🚀 We hope you find our custom smart pointer implementation both educational and useful. Feel free to explore the code, run the tests, and incorporate these smart pointers into your own C++ projects. Happy coding! 🖥️✨

## 1. What's the Project About

This C++ project provides a custom implementation of smart pointers, including unique_ptr(In our case uniquePointer), shared_ptr(In our case sharedPointer), and weak_ptr(In our case weakPointer). Smart pointers are crucial in modern C++ for safer and more convenient memory management compared to raw pointers.

## 2. What's in the Repository

- **unique.hpp**: Header file with the custom uniquePointer implementation.
  - List of Methods and functions :
    1. `reset(T* ptr)` ->   Resets the pointer to a new value or to the default vaules if called reset()
    2. `get()` ->   Returns a raw pointer of the unique pointer
    3. `operator->()` ->Overloaded arrow operator for accessing members of the object.
                        Return Type: Raw pointer (T*) to the object.
    4. `operator*()`->  Overloaded dereference operator for accessing the object.
                    Return Type: Reference (T&) to the object.
    5. `operator bool()`->Explicit conversion operator to bool for checking if the pointer is valid.
                    Return Type: bool. Returns true if the pointer is not null, false otherwise.
    6. `reset(ptr)`->   Resets the pointer to a new value or to the default values if called with no arguments.
                    Parameters:ptr: New pointer value. Defaults to nullptr.
    7. `release()` ->   Releasing ownership of the pointer and returning it.
                    Return Type: Raw pointer (T*) to the released object.
    8. `swap(other)`->  Swapping method that swaps the contents of two uniquePointer objects.
                    Parameters: other: The uniquePointer to swap contents with.
    9. `void swap(one,other)`-> Free function swap that calls upon the swap method of uniquePointer.
                            Parameters:one, other: The uniquePointer objects to swap.
    10. `make_unique(arg)`-> Free function for creating unique pointers.

- **shared.hpp**: Header file with the custom sharedPointer implementation.
  - List of Methods and Functions:
    1. `use_count()` -> Function to get the current use count.
    2. `get()` -> Function to get the raw pointer.
    3. `&operator*()`  -> Dereference operator.
    4. `operator->()`  -> Member access operator.
    5. `operator bool()`  -> Explicit conversion operator to bool.
    6. `reset(ptr)` -> Function to reset the shared pointer with a new raw pointer.
    7. `make_shared(args)` -> Make shared function to create a shared pointer with dynamic allocation.
    8. `swap(other)` -> Swap function to exchange contents with another shared pointer.
    9. `swap(one,other) `-> Free function swap that calls upon the swap method of sharedPointer.

- **weak.hpp**: Header file with the custom weakPointer implementation.
  - List of Methods and Functions:    
    1. `use_count()` -> Function to get the current use count.
    2. `reset()`-> Reset function.
    3. `expired()` -> Expired function.
    4. `lock()` -> Lock function to convert to sharedPointer.
    5. `swap(other)` -> Method to swap contents with another weak pointer.
    6. `swap(one, other)` -> Free function swap that calls upon the swap method of weakPointer.
- **test.cpp**: Test file demonstrating the usage and functionality of the implemented smart pointers.
- **makefile**: Makefile for easy compilation and execution of test.cpp.

**Note**: All the classes, namely "unique," "shared," and "weak," are within a namespace similar to std, but it is named eds (after the creator of the hpp files, Edis).

## 3. How to Start the Makefile

To compile and run the test.cpp file, follow these steps:
Inside the cloned folder in your terminal type the following line:
``make``
Make sure you have a C++ compiler installed on your system. The provided makefile simplifies the compilation process and ensures a smooth execution of the test file.
To remove the made 'test.o' and executable 'test' type:
``make clean``

**Suggestion:** Save the test output in an output.txt or output.log file for easier reading of the test results.
~``./test >> output.log``

**If any bugs are identified, or if there are instances of unexplained memory leaks or flawed implementations, we encourage you to promptly reach out to us, providing details about the observed issues. Your feedback is valuable in enhancing the quality and reliability of the implementation.The mail for contacting us: edis.sinanovic@fet.ba**
