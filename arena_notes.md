# Arena Notes

Before we can even start thinking about creating a memory arena, we need to cover some basics on computer architecture, memory addressing, and memory alignment.

# Memory Addressing

Computers commonly address their memory in word-sized chunks. A **word** is a computer's natural unit for data. Its size is defined by the computer's architecture. You can determine your computer's architecture with the following commands:

```bash
getconf WORD_BIT # Tells us the word size (32 bit on this Macbook M4)
getconf LONG_BIT # Tells us the `int long` size (64 bit on this Maxbook M4)
```

# Sources

[Alignment in C](https://hps.vi4io.org/_media/teaching/wintersemester_2013_2014/epc-14-haase-svenhendrik-alignmentinc-paper.pdf)
