# Arena Notes

Before we can even start thinking about creating a memory arena, we need to cover some basics on bitwise mapping, computer architecture, memory addressing, and memory alignment.

They really made this whole "create an arena" thing sound like less of an endeavor than it really is. So many prerequisites!

# Textbook Chapters to Focus On

* **Chapter 2, Representing and Manipulating Information**. Start here. It covers bitwise ops, masking, shifts, and two’s complement, which is exactly the ~(align - 1) material.
* **Section 3.9.3, Data Alignment**. Short, and directly on topic. Chapter 3 (assembly) is useful but not required for the arena. Skim it, and don’t let it become a rabbit hole.
* **Chapter 6, The Memory Hierarchy**. Explains why alignment and locality matter for performance.
* **Section 9.9, Dynamic Memory Allocation**. This is the most relevant part of the book. It walks through building a malloc, including alignment, headers, and fragmentation, and an arena is a simplified version of the same ideas.

# Representing and Manipulating Information

The following information comes from [Chapter 2 of Computer Systems: A Programmer's Perspective](https://www.cs.sfu.ca/~ashriram/Courses/CS295/assets/books/CSAPP_2016.pdf).

## Information Storage

Rather than accessing individual bits in memory, most computers use blocks of 8 bits, or bytes, as the smallest addressable unit of memory. This is why `char` is used to represent the arena buffer in [GingerBill's code](https://www.gingerbill.org/article/2019/02/08/memory-allocation-strategies-002/):

```c
typedef struct Arena Arena;
struct Arena {
	unsigned char *buf;
	size_t         buf_len;
	size_t         prev_offset;
	size_t         curr_offset;
};
```

A machine-level program views memory as a very large array of bytes, referred to as **virtual memory**. Every byte of memory is identified by a unique number, known as its **address**, and the set of all possible addresses is known as the **virtual address space**. As indicated by its name, this virtual address space is just a conceptual image presented to the machine-level program. The actual implementation uses a combination of dynamic random access memory (DRAM), flash memory, disk storage, special hardware, and operating system software to provide the program with what appears to be a monolithic byte array.

Essentially, there's a BUNCH of abstracted-away operations that are used to allocate and manage the storage for different parts of a program. This management is all performed in the virtual address space.

For example, **the value of a pointer in C is the virtual address of the first byte of some block of storage**. The C compiler also associates type information with each pointer, so that it can generate different machine-level code to access the value stored at the location designated by the pointer.

# Sources

* [Computer Systems: A Programmer's Perspective](https://www.cs.sfu.ca/~ashriram/Courses/CS295/assets/books/CSAPP_2016.pdf)
* [IBM - Data alignment: Straighten up and fly right](https://developer.ibm.com/articles/pa-dalign/)
