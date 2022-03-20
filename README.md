Memory Programming Assignment

Benchmark Assignment:

My program (compilation instructions: type make, and then use ./benchmark) had some bumps getting into a place where it would work properly. However, after switching to using the clock_gettime rather than clock() everything just seemed to click into place.

While there's pretty significant overhead added due to the loop, this system still allows for analysis without having every single time measurement get rounded away to nothing.

![Memory Benchmark Graph](https://github.com/calliereimann/389memorythreadcode/blob/main/betterimage.png?raw=true)


While my testing isn't perfectly thorough, there seem to be two switchover points, which I will assume are connected to the two caches + memory. The first switchover is in the 10-100 KB range, in which time about doubles - so I think that my L1 cache is within that range, estimating probably 64 KB under the assumption that a power of 2 is easier to set up. The next jump occurs between 10 MB and 100 MB, and that seems like it's the L2 to memory (or maybe L3) gap, since the required time quintuples at best, and increases by a full order of magnitude at worst. I'd guess that it's 64 MB for the same reason as my guess in L1.

The computer I used for my tests has a	"Intel(R) Core(TM) i7-1065G7 CPU", which when I looked it up didn't specify the size of its L1 cache, but did say that it had an 8 MB "Smart Cache", which was described very similarly to an L2 cache's function. This is somewhat close to my guess - I was forced to be inaccurate by the fact that I didn't test very many sizes within that range.






Multithreading Assignment:

I had some trouble coming up with a way of testing these things at first, but the (somewhat) clunky method I came up with is the best that I have.
I apologize for the incompleteness: this is my literal first time using the <thread> library, and so a lot of time I would have had to work on the assignment was spent instead trying to understand how anything actually worked in the first place.

Note: I do not optimize any of these threaded files - the optimization completely breaks them by smoothing away spinning and thus preventing the barriers from functioning properly.

The central barrier was implemented essentially identically to how we set it up in class - I needed to make sense also considered "atomic" in order to get the code to compile, but once I did (and I figured out how to pass references into threads) it worked quite well.

The central barrier is correct - in testing, there has never been any out-of-order effects. This is because every variable related to the behavior of the barrier is an atomic and so there's no effects which could lead to disasters. Note: The printing might get screwed up from time to time, that's just the fault of cout transmitting each chunk in pieces. notably, the first chunk of any line in the second barrier will always appear after the last chunk in the first barrier.

The dissemination barrier is also correct. I needed to move sense and parity to be local per thread in order to make it work, since there's not really a priveliged "last one to arrive" to flip them, so i just had everyone have their own that they personally flipped. As per the reasoning in the slides, this barrier is now totally correct.

I don't have a good graph available because I don't know how to measure this sort of thing, but if I had to guess, central barrier has essentially a flat line overhead as it's all down to a single value, while dissemination barrier has n log n overhead because it creates THREAD * log(THREAD) * 2 different flags in a bool array.
