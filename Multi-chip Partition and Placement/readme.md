# Lab3 Multi-chip Partition and Placement
This lab focuses on the implementation of partitioning and placement. Initially, we are given the global placement results of a chip design along with cell information. The task is to partition the cells into two separate chips, and then perform standard cell placement for each chip within feasible rows while avoiding any overlaps. The objective is to minimize the movement of cells from their original global placement positions.
  
For more details, refer to: [Lab3.pdf](Lab3.pdf) & [Lab3_Supplementary.pdf](Lab3_Supplementary.pdf)

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
./Lab3 [input.txt] [output] 
```

## Checker
```sh
./verifier [input.txt] [output]
```

## Drawing
```sh
python3 draw.py [INPUT] [OUTPUT] [PICTURE_NAME] (-i) (-p)
```
#-i would also draw initial graph
#-p would also draw partition graph (the cell distribution on 2 chips before doing legalization) 

### Example:
```sh
python3 draw.py Case/case0.txt output.txt drawing/layout0
python3 draw.py Case/case0.txt output.txt drawing/layout0 -i
python3 draw.py Case/case0.txt output.txt drawing/layout0 -i -p
python3 draw.py Case/case0.txt output.txt drawing/layout0 -p
```
