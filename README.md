# RMM
Region Based Memory Management Library - Context:

Garbage collection tends to have unpredictable timing and high memory overhead. Real-time collectors exist, but are uncommon and have significant design implications for applications using them. Manual memory management (malloc) is too error prone. Region-based memory management aims for a middle ground between the two approaches:

  a) Safe, predictable timing 
  b) Limited impact on application design 

Basic Ideas of RMM:

  a) Hierarchy of regions corresponding to call stack
  b) Variables live within regions, and are deallocated at end of region scope

RMM extends the stack-based memory management scheme to apply to allocations on the heap. It has the following advantages:

  a) Fast Allocation and Deallocation - from deallocation of the stack
  b) Simplified Memory Overhead - Not as simple as GC, but easier to handle than malloc
  c) Different Ways to group memory - Size, scope, etc. Kind of like generational GCs

The disadvantages include:

  a) No direct control over individual pieces of memory - can only delete regions, not individual data
  b) Not as hands-off as GC - Programmer still needs to manage some memory
  c) Need a larger overall knowledge of your program - Sizes of regions, number of regions, total memory used, etc.

Overall, for RMM to be effective, the programmer needs to consider inferring regions based on their code and design and use it thoughtfully:

  a) Allocate objects with lifetimes corresponding to regions 
  b) Track object ownership, and changes of ownership: What region owns each object at any time. Ownership of objects can move between regions 
  c) Deallocate objects at the end of the lifetime of their owning region - Use scoping rules to ensure objects are not referenced after deallocation 

Benefits of using Region Inference: 

  Type system tracks ownership, turning runtime bugs into compile-time errors: 
    a) Prevents memory leaks and use-after-free bugs 
    b) Prevents iterator invalidation 
    c) Prevents race conditions with multiple threads – borrowing rules prevent two threads from getting references to a mutable object 
    d) Efficient run-time behaviour – timing and memory usage are predictable

USAGE HINTS:

Many potential use cases are indicated in the test programs. A summary follows:

a) Allocating, Doing some Work, and Deallocating Arrays using RMM - TestArrays.cpp and TestMultipleArrays.cpp
b) Allocating, Doing some Work, and Deallocating Objects using RMM - TestObjects.cpp and TestMultipleObjects.cpp
c) Allocating, Doing some Work, and Deallocating Nested Regions using RMM - TestNestedRegions.cpp

For more details on the test programs, please see the Test_Coverage.txt file under the src sub-directory.
