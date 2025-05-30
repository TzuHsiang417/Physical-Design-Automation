# Lab1 Corner Stitching
The objective of logic optimization is to improve a given combinational circuit in terms of performance or area, in order to meet design constraints. This process facilitates effective technology mapping by transforming Boolean networks—often in a non-circuit form—into optimized circuit implementations that satisfy specified cost and constraint requirements.  
  
The objective of this programming assignment is two-level logic optimization, specifically aiming to reduce the number of Sum-of-Product (SOP) terms. Given an unoptimized Boolean function, we are required to implement the Quine-McCluskey algorithm in C++ to simplify the function and minimize its logical complexity.  
  
For more details, refer to: [Lab1.pdf](Lab1.pdf) & [Lab1 Supplementary.pdf](https://github.com/TzuHsiang417/Physical-Design-Automation/blob/main/Corner%20Stitching/Lab1%20Supplementary.pdf)

## Program Structure and Algorithms
<img src="" width="50%">

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
./Lab1 [input_file] [output_file]
```

## Drawing
```sh
python3 draw_block_layout.py [LAYOUT_INFORMATION] [PICTURE_NAME]
```

## Reports
Execution Results and Report: 
[PA3_107501019_report.pdf](PA3_107501019_report.pdf)
