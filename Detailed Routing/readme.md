# Lab4 Detailed Routing
This lab focuses on the implementation of partitioning and placement. Initially, we are given the global placement results of a chip design along with cell information. The task is to partition the cells into two separate chips, and then perform standard cell placement for each chip within feasible rows while avoiding any overlaps. The objective is to minimize the movement of cells from their original global placement positions.
  
For more details, refer to: [Lab4.pdf](Lab4.pdf)

## Compilation
Run the following command to compile the project:
```sh
make
```

## Clean
The following command removes all files generated during the compilation process:
```sh
make clean
```

## How to excecute
Run the program: 
```sh
./Lab4 [input.txt] [output] 
```

## Checker
```sh
./verifier [input.txt] [output]
```

## Drawing
```sh
python3 channel_routing_draw.py [INPUT] [OUTPUT] [PICTURE_NAME]
```
