# My First Memory Arena

"Oh, just make a memory arena! It's almost like a *garbage collector*! **It's so easy!**"

"Dude, I like almost never use `malloc` and `free` after discovering memory arenas. One day I just decided to make one! **It was so easy!**"

"Why don't you just use a memory arena? They're **so easy** to implement"

If you started learning C about two months ago and don't have a decade of game engine development under your belt... it actually turns out to be *pretty difficult*.

# Getting to the Point

My idols Casey Muratori and Jonathan Blow have led me down the path to systems programming (despite them being game developers... although there's a lot of overlap). So, in this repository, I create a *simple* memory arena that I can use as a basis for other projects. Rather than creating a "pointer jungle" for every C application I create, I want the memory of my future programs to be structured, maintainable, and minimally fragmented.

What was presented to me as a simple project that's easy to implement turned out to be a bit more involved than I initially thought. So, contained within this repository are some [extremely extensive notes](notes/1_arena_notes.md) on bitwise mapping, computer architecture, memory addressing, and memory alignment. Not only is this a useful tool, but it's forced me to learn some deeper topics I thought I'd never truly study.

Due to my tendencies, copying and pasting the code found in these tutorials is unacceptable. I must understand every aspect of this programming topic. Otherwise, how could I ever create and specialize my own arena?

## Resources

A big thank you to "GingerBill", the creator of the Odin language, for a really solid guide on helping me get started with all of this.

### Primary

* [GingerBill - Arena Allocator Guide](https://www.gingerbill.org/article/2019/02/08/memory-allocation-strategies-002/)
* [Textbook - Computer Systems: A Programmer's Perspective](https://www.cs.sfu.ca/~ashriram/Courses/CS295/assets/books/CSAPP_2016.pdf)

### Secondary

* [How to actually use arenas (and program in C pain free)](https://alonsozamorano.me/how-to-actually-use-arenas-and-program-in-c/)
* [The Arena - Custom Memory Allocators in C](https://www.bytesbeneath.com/p/the-arena-custom-memory-allocators)

### Inspiration

* [Untangling Lifetimes](https://www.dgtlgrove.com/p/untangling-lifetimes-the-arena-allocator)
* [Tsoding's Arena Example](https://github.com/tsoding/arena/blob/master/arena.h)
