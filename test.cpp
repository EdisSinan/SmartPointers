/********************************************************
 *							                                        *
 *	      This is a simple test.cpp for testing	        *
 *	      my custom smart pointer implementation        *
 *							                                        *
 ********************************************************/

#include "shared.hpp"
#include "unique.hpp"
#include "weak.hpp"
#include <iostream>

class MyClass {
public:
  MyClass(int value) : data(value) {
    std::cout << "MyClass Constructor, Data: " << data << std::endl;
  }
  MyClass(const MyClass &other) : data(other.data) {
    std::cout << "MyClass Copy Constructor, Data: " << data << std::endl;
  }
  MyClass(MyClass &&other) noexcept : data(other.data) {
    other.data = 0;
    std::cout << "MyClass Move Constructor, Data: " << data << std::endl;
  }
  MyClass &operator=(const MyClass &other) {
    if (this != &other) {
      data = other.data;
      std::cout << "MyClass Copy Assignment, Data: " << data << std::endl;
    }
    return *this;
  }
  MyClass &operator=(MyClass &&other) noexcept {
    if (this != &other) {
      data = other.data;
      other.data = 0;
      std::cout << "MyClass Move Assignment, Data: " << data << std::endl;
    }
    return *this;
  }

  void displayData() const { std::cout << "Data: " << data << std::endl; }

  ~MyClass() { std::cout << "MyClass Destructor, Data: " << data << std::endl; }

private:
  int data;
};

int main() {
  std::cout << "*********************************************************"
            << std::endl;
  std::cout << std::endl << "\t\tUnique pointer testing" << std::endl;
  std::cout << std::endl
            << "*********************************************************"
            << std::endl;
  std::cout
      << "Construct myUniquePointer with a new MyClass object with make_unique"
      << std::endl;
  eds::uniquePointer<MyClass> myUniquePointer = eds::make_unique<MyClass>(1);
  std::cout << "myUniquePointer: ";
  myUniquePointer->displayData();
  std::cout
      << "--------------------------------------------------------------------------------------------------------------"
      << std::endl;
  std::cout << "Creating a myUniquePtr using move constructor" << std::endl;
  eds::uniquePointer<MyClass> myUniquePtr = std::move(myUniquePointer);
  std::cout << "After Move:" << std::endl;
  if (myUniquePointer) {
    std::cout << "myUniquePointer is not empty." << std::endl;
  } else {
    std::cout << "myUniquePointer is empty." << std::endl;
  }
  if (myUniquePtr) {
    std::cout << "myUniquePtr ";
    myUniquePtr->displayData();
  } else {
    std::cout << "myUniquePtr is empty." << std::endl;
  }
  std::cout << "--------------------------------------------------------------------------------------------------------------"
            << std::endl;
  std::cout << "Move assigment from an existing uniquePointer moving to myUniquePtr2" << std::endl;
  eds::uniquePointer<MyClass> myUniquePtr2 = std::move(myUniquePtr);
  std::cout << "After Move:" << std::endl;
  if (myUniquePtr) {
    std::cout << "myUniquePtr is not empty." << std::endl;
    myUniquePtr->displayData();
  } else {
    std::cout << "myUniquePtr is empty." << std::endl;
  }
  if (myUniquePtr2) {
    std::cout << "myUniquePtr2: ";
    myUniquePtr2->displayData();
  } else {
    std::cout << "myUniquePtr2 is empty." << std::endl;
  }
  std::cout << "--------------------------------------------------------------------------------------------------------------"
            << std::endl;
  std::cout << "Move construct from a temporary uniquePointer" << std::endl;
  eds::uniquePointer<MyClass> myUniquePtr3 = eds::make_unique<MyClass>(3);
  eds::uniquePointer<MyClass> myUniquePtr4 = std::move(myUniquePtr3);
  std::cout << "After Move from Temporary:" << std::endl;
  if (myUniquePtr3) {
    std::cout << "myUniquePtr3: ";
    myUniquePtr3->displayData();
  } else {
    std::cout << "myUniquePtr3 is empty." << std::endl;
  }
  if (myUniquePtr4) {
    std::cout << "myUniquePtr4: ";
    myUniquePtr4->displayData();
  } else {
    std::cout << "myUniquePtr4 is empty." << std::endl;
  }
  std::cout << "--------------------------------------------------------------------------------------------------------------"
            << std::endl;
  std::cout << "Accessing through dereference operator and modifying through "
               "dereference operator:"
            << std::endl;
  MyClass &myClassRef = *myUniquePtr4;
  std::cout << "myClassRef=*myUniquePtr : ";
  myClassRef.displayData();
  std::cout << "myClassRef=MyClass(55) : ";
  myClassRef = MyClass(55);
  myClassRef.displayData();
  std::cout
      << "--------------------------------------------------------------------------------------------------------------"
      << std::endl;
  std::cout << "Using the arrow operator:  myUniquePtr4->displayData();"
            << std::endl;
  myUniquePtr4->displayData();
  std::cout
      << "--------------------------------------------------------------------------------------------------------------"
      << std::endl;
  std::cout << "Testing the explicit bool conversion if (myUniquePtr) "
            << std::endl;
  if (myUniquePtr) {
    std::cout << "myUniquePtr is not empty." << std::endl;
  } else {
    std::cout << "myUniquePtr is empty." << std::endl;
  }
  std::cout
      << "--------------------------------------------------------------------------------------------------------------"
      << std::endl;
  myUniquePtr3 = eds::make_unique<MyClass>(91281);
  std::cout << "Resetting the uniquePointer with a new value  myUniquePtr3.reset(new MyClass(99));" << std::endl;
  myUniquePtr3.reset(new MyClass(99));
  std::cout << "After reset:" << std::endl;
  std::cout << "myUniquePtr";
  myUniquePtr3->displayData();
  std::cout
      << "--------------------------------------------------------------------------------------------------------------"
      << std::endl;
  std::cout << " Swapping uniquePointers" << std::endl;
  eds::uniquePointer<MyClass> anotherUniquePtr = eds::make_unique<MyClass>(77);
  std::cout << "Before Swap:" << std::endl;
  if (myUniquePtr) {
    std::cout << "myUniquePtr";
    myUniquePtr->displayData();
  } else {
    std::cout << "myUniquePtr is empty." << std::endl;
  }
  if (anotherUniquePtr) {
    std::cout << "anotherUniquePtr";
    anotherUniquePtr->displayData();
  } else {
    std::cout << "anotherUniquePtr is empty." << std::endl;
  }
  myUniquePtr.swap(anotherUniquePtr);
  std::cout << "After Swap:" << std::endl;
  if (myUniquePtr) {
    std::cout << "myUniquePtr";
    myUniquePtr->displayData();
  } else {
    std::cout << "myUniquePtr is empty." << std::endl;
  }
  if (anotherUniquePtr) {
    std::cout << "anotherUniquePtr";
    anotherUniquePtr->displayData();
  } else {
    std::cout << "anotherUniquePtr is empty." << std::endl;
  }
  // eds::uniquePointer<MyClass> aThirdUniquePtr = anotherUniquePtr; "Can not be
  // referenced is a deleted function"
  //  eds::uniquePointer<MyClass> aThirdUniquePtr(anotherUniquePtr); "Can not be
  //  referenced is a deleted function"
  std::cout
      << "--------------------------------------------------------------------------------------------------------------"
      << std::endl;
  std::cout << "Free function swap: " << std::endl;
  std::cout << "Before Swap:" << std::endl;
  if (myUniquePtr) {
    std::cout << "myUniquePtr";
    myUniquePtr->displayData();
  } else {
    std::cout << "myUniquePtr is empty." << std::endl;
  }
  if (anotherUniquePtr) {
    std::cout << "anotherUniquePtr";
    anotherUniquePtr->displayData();
  } else {
    std::cout << "anotherUniquePtr is empty." << std::endl;
  }
  eds::swap(myUniquePtr, anotherUniquePtr);
  std::cout << "After Swap:" << std::endl;
  if (myUniquePtr) {
    std::cout << "myUniquePtr";
    myUniquePtr->displayData();
  } else {
    std::cout << "myUniquePtr is empty." << std::endl;
  }
  if (anotherUniquePtr) {
    std::cout << "anotherUniquePtr";
    anotherUniquePtr->displayData();
  } else {
    std::cout << "anotherUniquePtr is empty." << std::endl;
  }
  std::cout
      << "--------------------------------------------------------------------------------------------------------------"
      << std::endl;
  std::cout << " Relesing anotherUniquePtr" << std::endl;
  anotherUniquePtr.release();
  if (anotherUniquePtr) {
    std::cout << "anotherUniquePtr";
    anotherUniquePtr->displayData();
  } else {
    std::cout << "anotherUniquePtr is empty." << std::endl;
  }
  std::cout
      << "--------------------------------------------------------------------------------------------------------------"
      << std::endl;
  std::cout << " Just reset myUniquePtr3.reset();" << std::endl;
  myUniquePtr3.reset();
  if (myUniquePtr3) {
    std::cout << "myUniquePtr3";
    myUniquePtr3->displayData();
  } else {
    std::cout << "myUniquePtr3 is empty." << std::endl;
  }
  std::cout
      << "--------------------------------------------------------------------------------------------------------------"
      << std::endl;
  std::cout << "Method get rawPointer = myUniquePtr5.get()->" << std::endl;
  eds::uniquePointer<MyClass> myUniquePtr5 = eds::make_unique<MyClass>(1731);
  MyClass *rawPointer = myUniquePtr5.get();
  if (rawPointer) {
    std::cout << "Using get to access MyClass data: ";
    rawPointer->displayData();
  } else {
    std::cout << "Pointer is null." << std::endl;
  }
  std::cout << "*********************************************************"
            << std::endl;
  std::cout << std::endl << "\t\tShared pointer testing" << std::endl;
  std::cout << std::endl
            << "*********************************************************"
            << std::endl;
  std::cout << "Testing constructors eds::sharedPointer<MyClass> ptr1(new MyClass(1));" << std::endl;
  eds::sharedPointer<MyClass> ptr1(new MyClass(1));
  std::cout << "Pointer 1 , ";
  ptr1->displayData();
  std::cout << "Counter: " << ptr1.use_count() << std::endl;
  std::cout << "--------------------------------------------------------------------------------------------------------------"
            << std::endl;
  std::cout << "Testing copy constructor ptr2(ptr1);" << std::endl;
  eds::sharedPointer<MyClass> ptr2(ptr1);
  std::cout << "Pointer 2 , ";
  ptr2->displayData();
  std::cout << "Counter: " << ptr2.use_count() << std::endl;
  std::cout << "--------------------------------------------------------------------------------------------------------------"
            << std::endl;
  std::cout << "Testing copy assignment operator  ptr3 = ptr2;" << std::endl;
  eds::sharedPointer<MyClass> ptr3;
  ptr3 = ptr2;
  std::cout << "Pointer 3 ,  ";
  ptr3->displayData();
  std::cout << "Counter: " << ptr3.use_count() << std::endl;
  std::cout << "--------------------------------------------------------------------------------------------------------------"
            << std::endl;
  std::cout << "Testing make_shared function ptr4 = eds::make_shared<MyClass>(4);" << std::endl;
  eds::sharedPointer<MyClass> ptr4 = eds::make_shared<MyClass>(4);
  std::cout << "Pointer 4 , ";
  ptr4->displayData();
  std::cout << "Counter: " << ptr4.use_count() << std::endl;
  std::cout << "--------------------------------------------------------------------------------------------------------------"
            << std::endl;
  std::cout << "Testing copy assignment operator   eds::sharedPointer<MyClass> ptr5 =ptr4;" << std::endl;
  eds::sharedPointer<MyClass> ptr5 =ptr4;
  std::cout << "Pointer 5 , ";
  ptr5->displayData();
  std::cout << "Counter: " << ptr5.use_count() << std::endl;
  std::cout << "--------------------------------------------------------------------------------------------------------------"
            << std::endl;
  std::cout << "Testing move assignment operator ptr6 = std::move(ptr5);" << std::endl;
  eds::sharedPointer<MyClass> ptr6;
  ptr6 = std::move(ptr5);
  std::cout << "Pointer 6 , ";
  ptr6->displayData();
  std::cout << "Counter: " << ptr6.use_count() << std::endl;
  std::cout << "--------------------------------------------------------------------------------------------------------------"
            << std::endl;
  std::cout << "Testing move  operator eds::sharedPointer<MyClass> movedPointer(std::move(pointerToBeMoved));" << std::endl;
  {
    eds::sharedPointer<MyClass> pointerToBeMoved(new MyClass(6));
    std::cout << "pointerToBeMoved data: ";
    pointerToBeMoved->displayData();
    eds::sharedPointer<MyClass> movedPointer(std::move(pointerToBeMoved));
    std::cout << "movedPointer data: ";
    movedPointer->displayData();
  }
  std::cout << "--------------------------------------------------------------------------------------------------------------"
            << std::endl;
  std::cout << "Testing use_count function" << std::endl;
  std::cout << "use_count for ptr1: " << ptr1.use_count() << std::endl;
  std::cout << "--------------------------------------------------------------------------------------------------------------"
            << std::endl;
  std::cout << "Testing get function  ptr1.get()->displayData();" << std::endl;
  std::cout << "Pointer value for ptr1: ";
  ptr1.get()->displayData();
  std::cout << "Counter: " << ptr1.use_count() << std::endl;
  std::cout << "--------------------------------------------------------------------------------------------------------------"
            << std::endl;
  std::cout << "Testing dereference operator (*ptr1).displayData();" << std::endl;
  std::cout << "Dereferencing ptr1: ";
  (*ptr1).displayData();
  std::cout << "Counter: " << ptr1.use_count() << std::endl;
  std::cout << "--------------------------------------------------------------------------------------------------------------"
            << std::endl;
  std::cout << "Testing arrow operator   ptr1->displayData();" << std::endl;
  std::cout << "Arrow operator on ptr1: ";
  ptr1->displayData();
  std::cout << "Counter: " << ptr1.use_count() << std::endl;
  std::cout << "--------------------------------------------------------------------------------------------------------------"
            << std::endl;
  std::cout << "Testing boolean conversion  std::boolalpha<< static_cast<bool>(ptr1)" << std::endl; //funn way to test that hahaha
  std::cout << "Boolean conversion for ptr1: " << std::boolalpha
            << static_cast<bool>(ptr1) << std::endl;
  std::cout << "--------------------------------------------------------------------------------------------------------------"
            << std::endl;
  std::cout << "Testing reset function ptr1.reset(new MyClass(10));" << std::endl;
  ptr1.reset(new MyClass(10));
  std::cout << "After reset, Pointer 1 data: ";
  ptr1->displayData();
  std::cout << "Counter: " << ptr1.use_count() << std::endl;
  std::cout << "After Pointer1 reset, Pointer 3 data: ";
  ptr3->displayData();
  std::cout << "Counter: " << ptr3.use_count() << std::endl;
  std::cout << "--------------------------------------------------------------------------------------------------------------"
            << std::endl;
  eds::sharedPointer<MyClass> whoknowswhatpointernumberitisnow = eds::make_shared<MyClass>(38762987655);
  std::cout << "Testing reset function whoknowswhatpointernumberitisnow.reset();" << std::endl;
  whoknowswhatpointernumberitisnow.reset();
  if(whoknowswhatpointernumberitisnow){
  std::cout << "After reset whoknowswhatpointernumberitisnow pointer still points at something" << std::endl;}
  else{
  std::cout << "After reset whoknowswhatpointernumberitisnow ain't pointing at anything" << std::endl;}
  std::cout << "--------------------------------------------------------------------------------------------------------------"
            << std::endl;
  std::cout << "Testing swap function" << std::endl;
  eds::sharedPointer<MyClass> ptr7(new MyClass(7));
  std::cout << "Before swap, Pointer 4 data: ";
  ptr4->displayData();
  std::cout << "Before swap, Pointer 7 data: ";
  ptr7->displayData();
  std::cout << "Counter for Pointer 4: " << ptr4.use_count() << std::endl;
  std::cout << "Counter for Pointer 7: " << ptr7.use_count() << std::endl;
  ptr7.swap(ptr4);
  std::cout << "After swap, Pointer 4 data: ";
  ptr4->displayData();
  std::cout << "After swap, Pointer 7 data: ";
  ptr7->displayData();
  std::cout << "Counter for Pointer 4: " << ptr4.use_count() << std::endl;
  std::cout << "Counter for Pointer 7: " << ptr7.use_count() << std::endl;
  std::cout << "--------------------------------------------------------------------------------------------------------------"
            << std::endl;
  std::cout << "*********************************************************"
            << std::endl;
  std::cout << std::endl << "\t\tWeak pointer testing" << std::endl;
  std::cout << std::endl
            << "*********************************************************"
            << std::endl;
  /************************************************************************************************
  *For "quicker" writing i have done the constructor testing with int instead of MyClass variable *
  *                  Some new type(int) for a change I guess?                                     *
  ************************************************************************************************/ 
  std::cout << "Test Default Constructor" << std::endl;
  eds::weakPointer<int> wp1; 
  std::cout << "WeakPointer use count: " << wp1.use_count() << std::endl;
  std::cout << "--------------------------------------------------------------------------------------------------------------"
            << std::endl;
  std::cout << "Test Constructor from sharedPointer" << std::endl;
  eds::sharedPointer<int> sp1(new int(42));
  eds::weakPointer<int> wp2(sp1);
  std::cout << "WeakPointer2 use count: " << wp2.use_count() << std::endl;
  std::cout << "--------------------------------------------------------------------------------------------------------------"
            << std::endl;
  std::cout << "Test Copy Constructor from weakPointer" << std::endl;
  eds::weakPointer<int> wp3(wp2);
  std::cout << "WeakPointer3 use count: " << wp3.use_count() << std::endl;
  std::cout << "--------------------------------------------------------------------------------------------------------------"
            << std::endl;
  std::cout << "Test Copy Assignment Operator" << std::endl;
  eds::weakPointer<int> wp4;
  wp4 = wp3;
  std::cout << "WeakPointer4 use count: " << wp4.use_count() << std::endl;
  std::cout << "--------------------------------------------------------------------------------------------------------------"
            << std::endl;
  std::cout << "--------------------------------------------------------------------------------------------------------------"
            << std::endl;
  std::cout << "Test Move Constructor" << std::endl;
  eds::weakPointer<int> wp6(std::move(wp3));
  std::cout << "Move wp3 use count: " << wp3.use_count()
            << ", wp6 use count: " << wp6.use_count() << std::endl;
  std::cout << "--------------------------------------------------------------------------------------------------------------"
            << std::endl;
  std::cout << "Test Move Assignment Operator" << std::endl;
  eds::weakPointer<int> wp7;
  wp7 = std::move(wp4);
  std::cout << "Move: Wp4 use count: " << wp4.use_count()
            << ", wp7 use count: " << wp7.use_count() << std::endl;
  std::cout << "--------------------------------------------------------------------------------------------------------------"
            << std::endl;
  std::cout << "Testing lock " << std::endl;
  std::cout << "Creating a shared pointer" << std::endl;
  eds::sharedPointer<MyClass> sharedPtr(new MyClass(42));
  std::cout << "Creating a weak pointer from the shared pointer" << std::endl;
  eds::weakPointer<MyClass> weakPtr(sharedPtr);
  std::cout << "Using lock to create a shared pointer from the weak pointer"
            << std::endl;
  if (!weakPtr.expired()) {
    eds::sharedPointer<MyClass> lockedPtr = weakPtr.lock();
  } else {
    std::cout << "Expired" << std::endl;
  }
  std::cout << "Is weak pointer expired? " << std::boolalpha
            << weakPtr.expired() << std::endl;
  std::cout << "Use count of the shared pointer: " << sharedPtr.use_count()
            << std::endl;
  std::cout << "The weak count is  " << weakPtr.use_count() << std::endl;
  std::cout << "Resetting the shared pointer" << std::endl;
  sharedPtr.reset();
  std::cout << "Is weak pointer expired after resetting shared pointer? "
            << std::boolalpha << weakPtr.expired() << std::endl;

  std::cout << "The weak count is  " << weakPtr.use_count() << std::endl;
  std::cout << "--------------------------------------------------------------------------------------------------------------"
            << std::endl;
  std::cout << "Testing swap" << std::endl;
  std::cout << "Creating another shared pointer" << std::endl;
  eds::sharedPointer<MyClass> anotherSharedPtr(new MyClass(1));
  std::cout << "Creating another weak pointer from the shared pointer"
            << std::endl;
  eds::weakPointer<MyClass> anotherWeakPtr(anotherSharedPtr);
  std::cout << "Creating yet another shared pointer" << std::endl;
  eds::sharedPointer<MyClass> yetAnotherSharedPtr(new MyClass(2));
  std::cout << "Creating yet another weak pointer from the shared pointer"
            << std::endl;
  eds::weakPointer<MyClass> yetAnotherWeakPtr(yetAnotherSharedPtr);
  std::cout << "Before swap: " << std::endl;
  std::cout << "Weak Pointer 1: ";
  anotherWeakPtr.lock()->displayData();
  std::cout << "Weak Pointer 2: ";
  yetAnotherWeakPtr.lock()->displayData();
  eds::swap(anotherWeakPtr, yetAnotherWeakPtr);
  std::cout << "After swap: " << std::endl;
  std::cout << "Weak Pointer 1: ";
  anotherWeakPtr.lock()->displayData();
  std::cout << "Weak Pointer 2: ";
  yetAnotherWeakPtr.lock()->displayData();
  std::cout << "--------------------------------------------------------------------------------------------------------------"
            << std::endl;
  std::cout << "Testing reset:" << std::endl;
  std::cout << "anotherWeakPtr use count: " << anotherWeakPtr.use_count()
            << " is it expired? " << anotherWeakPtr.expired() << std::endl;
  std::cout << "Reseting the weak pointer" << std::endl;
  anotherWeakPtr.reset();
  std::cout << "anotherWeakPtr use count: " << anotherWeakPtr.use_count()
            << " is it expired? " << anotherWeakPtr.expired() << std::endl;
  std::cout << "*********************************************************"
            << std::endl;
  std::cout << std::endl
            << "\tRecap of the still \"alive\" CONSTRUCTORS\n\t\t*From last "
               "created to first*"
            << std::endl;
  std::cout << std::endl
            << "*********************************************************"
            << std::endl;
  std::cout << "Yet another shared pointer: ";
  yetAnotherSharedPtr->displayData();
  std::cout << "Another shared pointer: ";
  anotherSharedPtr->displayData();
  std::cout << "Shared pointer ptr7: ";
  ptr7->displayData();
  std::cout << "Shared pointer ptr4: ";
  ptr4->displayData();
  std::cout << "Shared pointer ptr3: ";
  ptr3->displayData();
  std::cout << "Shared pointer ptr1: ";
  ptr1->displayData();
  std::cout << "Unique pointer myUniqueptr5 : ";
  myUniquePtr5->displayData();
  std::cout << "Unique pointer myUniquePtr4: ";
  myUniquePtr4->displayData();
  std::cout << "Unique pointer myUniquePtr2: ";
  myUniquePtr2->displayData();
  std::cout << "*********************************************************"
            << std::endl;
  std::cout << std::endl << "\t\tRemaining DESTRUCTORS" << std::endl;
  std::cout << std::endl
            << "*********************************************************"
            << std::endl;
  return 0;
}