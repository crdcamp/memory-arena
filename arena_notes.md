# Arena Notes

Before we can even start thinking about creating a memory arena, we need to cover some basics on bitwise mapping, computer architecture, memory addressing, and memory alignment.

They really made this whole "create an arena" thing sound like less of an endeavor than it really is. So many prerequisites!

# Textbook Chapters to Focus On

* **Chapter 2, Representing and Manipulating Information**. Start here. It covers bitwise ops, masking, shifts, and two’s complement, which is exactly the ~(align - 1) material.
* **Section 3.9.3, Data Alignment**. Short, and directly on topic. Chapter 3 (assembly) is useful but not required for the arena. Skim it, and don’t let it become a rabbit hole.
* **Chapter 6, The Memory Hierarchy**. Explains why alignment and locality matter for performance.
* **Section 9.9, Dynamic Memory Allocation**. This is the most relevant part of the book. It walks through building a malloc, including alignment, headers, and fragmentation, and an arena is a simplified version of the same ideas.

# Representing

The following information comes from [Chapter 2 of Computer Systems: A Programmer's Perspective](https://www.cs.sfu.ca/~ashriram/Courses/CS295/assets/books/CSAPP_2016.pdf).

# Sources

* [Computer Systems: A Programmer's Perspective](https://www.cs.sfu.ca/~ashriram/Courses/CS295/assets/books/CSAPP_2016.pdf)
* [IBM - Data alignment: Straighten up and fly right](https://developer.ibm.com/articles/pa-dalign/)
