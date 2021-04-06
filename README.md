# Serial-Optimization

### Part 1 includes serial optimization of a complex algorithm
### Part 2 includes serial optimization for a matrix matrix multiplication

## Introduction:
This Homework mainly focuses on different serial optimization techniques for two different kinds of programs. The goal is to find effective ways to serially optimize two tasks while maintaining the accuracy of the results. 

## System Model:
Every task is run on the RHEL7 interactive desktop. Each test run is executed with 20 cores.

## Problem Statement:
The first task requires us to optimize code consisting of several mathematical operations. The goal here is to test the code with different optimization methods and observe the most influential methods that can result in best performance. 

The second task requires us to optimize the basic matrix multiply algorithm. The goal here is to find effective data access optimizations so the cache system can be fully utilized. Since the matrix size is so big------each matrix has size of 2000 by 2000, the other aspects of the system don't matter anymore.

## Task 1:
On ACI clusters, the original code has a running time of 20.8 seconds. Along with each optimization method mentioned below, Figure A shows the performance of each method. 

![Figure A](https://github.com/FrankYufeiYang/Serial-Optimization/blob/main/figures/fa.jpg)
### _A. Temporary variable_
The first thing I notice is that we can replace “j*length” with a temporary variable since it is a constant in the range of the inner loop.  We initialize a temporary variable at the beginning. For each iteration of the outer loop, assign the variable the value of “j * length”. The temporary variable will remain a constant for each iteration of the inner loop since its value doesn’t associate with i. This saves the program from calculating “j * length” two times for each iteration. This is not a big deal to the whole picture but it manages to drop the running time to 19.5 seconds. It is an improvement one can notice. 
### _B. Lookup table_

We know that v(input2) is an integer array and using the fmod method on two integers is the same as using % operation. Since everything is integer, the round method has no use here as well, We can easily rewrite the code to val = v[i] % 256. Since array v doesn’t change, we can make a lookup table for val. So now, We calculate val N times outside of the loops instead of calculating it N*N inside the loop.

Furthermore, with the same understanding of array v being unchanged, we can move the calculations of the sin and cos out of the loops, and into the lookup table since the calculations only rely on val not i. 

This has a tremendous impact on code performance since the inner loop only needs to lookup a value according to iterator i. This alone brings the run time down 0.531 second.

### _C. Loop unrolling_

After running getconf LEVEL1_DCACHE_LINESIZE in the terminal, we find out that the cache line size of the system is 64 bytes. Since we are mostly dealing with double typed numbers here, we unroll the loop by 8.  Despite the fact that this method will cause the sin and cos calculation running 8 times more, it still drops the run time from originally 20 seconds to 10.8 seconds.

### _D. Everything_

So now, we optimize task 1 with every mentioned method, we get a running time of 0.3 seconds which is a significant improvement from original code. 

### _E. O3 flag_

This is very interesting, because, compiling the original code with the O3 flag, we can already see a huge improvement. The running time of Original code with the O3 flag is 13.5 seconds.
And if we include every optimization with the O3 flag, we will get a running time of 0.255 seconds. 

## Task 2:
Like before, we first provide an overview of different optimizations. We see the basic matrix multiply algorithm has a running time of 67.7 sec. We cannot wait that long for a matrix multiplication in the real world, so we have to optimize it. 

![Figure B](https://github.com/FrankYufeiYang/Serial-Optimization/blob/main/figures/fb.jpg)

### _A. Transpose _

In C/C++ programming, a 2D array is stored in a row based and contiguous fashion. It would make sense to transpose the array B first, so that during the calculation, array B would be accessed in the natural way of C programming. This effectively cut the running time by half, to 36.06 seconds.

### _B. Loop reordering_

Observe the original code, matrix B access the next row base on k for each innermost loop. This means, for each innermost loop, the system will pull a row of B into the cache line, only to flush them out and pull the next row of B into the cache line for the next iteration. So it would make sense if we reorder the loop. 

From observing the matrix accessing pattern, we can conclude that, in order to achieve locality on cache, the column iterator needs to be inside of the row iterator. Matrix A and C fulfill this pattern but B’s row iterator k is inside its column iterator j. So we exchange loop j with loop k which will make j the innermost iterator. 

Now all three matrices fulfill our observed pattern. If we compare loop reordering with the transpose optimization on memory accessing level, we see that they are basically performing the same improvement. This is further verified by the running time of loop recording, 37 seconds, which is very similar to transpose. 
### _C.Loop unrolling_

Since we have already discussed loop unrolling in task 1, we will just add this optimization directly on top of loop reordering. Like before, we unroll the loop 8 times here. The running time is 27.8 seconds. We can see a good improvement on top of loop reordering.
### _D.O3 flag_
Like before, we first test our original code with the O3 flag, we get a running time of 17.5 seconds. Then we compile our final code with the O3 flag, we get a running time of 2.8s. For task 2, the O3 flag brings a huge improvement. This might be because the compiler has the ability of further optimizing the memory accessing and further unrolling the loop.
 
## Conclusion:
Serial optimization and data accessing optimization have a huge impact on algorithm performance. Meanwhile, we should always utilize the right compiler flags to make our code run faster.
