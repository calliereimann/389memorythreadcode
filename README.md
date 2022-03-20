Memory Programming Assignment

Benchmark Assignment:

My program

![Memory Benchmark Graph](https://github.com/calliereimann/389memorythreadcode/blob/main/buffersize.png?raw=true)


While my testing isn't perfectly thorough, there seem to be two switchover points, which I will assume are connected to the two caches + memory. The first switchover is in the 10-100 KB range, in which time about doubles - so I think that my L1 cache is within that range, estimating probably 64 KB under the assumption that a power of 2 is easier to set up. The next jump occurs between 10 MB and 100 MB, and that seems like it's the L2 to memory (or maybe L3) gap, since the required time quintuples at best, and increases by a full order of magnitude at worst. I'd guess that it's 64 MB for the same reason as my guess in L1.

The computer I used for my tests has a	"Intel(R) Core(TM) i7-1065G7 CPU", which when I looked it up didn't specify the size of its L1 cache, but did say that it had an 8 MB "Smart Cache", which was described very similarly to an L2 cache's function. This is somewhat close to my guess - I was forced to be inaccurate by the fact that I didn't test very many sizes within that range.






Multithreading Assignment:

I had some trouble coming up with a way of testing these things at first, but the (somewhat) clunky method I came up with is the best that I have. 
