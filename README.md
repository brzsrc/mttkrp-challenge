#Mttkrp Challenge

This codebase is a stripped down version of the mttkrp benchmark in PASTA (https://gitlab.com/tensorworld/pasta)

To compile and test the benchmark navigate to the root of the project then run:
```
cmake -DCMAKE_BUILD_TYPE=Release ./
make
./mttkrp -i ./tensors/3D_12031.tns -o output.tns
```

The 'Release' build type in cmake intentionally uses -01 since using higher levels of optimisation will make it
more difficult for you to find improvements and reason about how architecture and program are interacting. 
To see what -O3 can do use the build type 'FAST'.

The aim of the challenge is to reduce the average mttkrp time as much as possible while justifying the changes
you make: 
```
[Average CooMTTKRP]: 0.000388425 s
Performance: 2.95 GFlop/s, Bandwidth: 1.04 GB/s
```

You will primarily be looking at `mttkrp.c` to make optimisations though changes in other parts of the code base are
absolutely fine as long as they are within the spirit of the challenge.  
You should choose an input tensor that suits the machine you have chosen to optimise for.
Some are very large and some are so small as to make getting a consistent time difficult.
You should also adjust `int niters` on line `57` of `main.c` to achieve a more consistent average time on your system.
The output is not automatically tested for correctness so you should take care not to inadvertently break the algorithm.

If you would like to test correctness by fixing the random seed for matrix creation replace line `74` of `matrix.c`:

```srand(time(NULL) + i + j);```

with:

```srand(i + j);```

Then compare the output files of the original algorithm code and your modified code. 

The header files in this project have had minimal adjustment and so contain declarations for many functions that are not defined.
If you would like to use these functions feel free to find them in the original PASTA repo and use them.

Once you have chosen your input tensor you may make observations about it and use the patterns there in to help your optimisations.