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

## Results
<table>
  <tr>
    <th colspan="2" style="text-align:center;">Case0</th>
  </tr>
  <tr>
    <th colspan="2" style="text-align:center;">Initial</th>
  </tr>
  <tr>
    <th colspan="2" style="text-align:center;"><img src="picture/case0_initial.png" width="500"></th>
  </tr>
  <tr>
    <td align="center"><b>Top partition</b></td>
    <td align="center"><b>Bottom partition</b></td>
  </tr>
  <tr>
    <td style="text-align:center;"><img src="picture/case0_top_partition.png" width="500"></td>
    <td style="text-align:center;"><img src="picture/case0_bottom_partition.png" width="500"></td>
  </tr>
  <tr>
    <td align="center"><b>Top result placement</b></td>
    <td align="center"><b>Bottom result placement</b></td>
  </tr>
  <tr>
    <td style="text-align:center;"><img src="picture/case0_top.png" width="500"></td>
    <td style="text-align:center;"><img src="picture/case0_bottom.png" width="500"></td>
  </tr>
</table>

<table>
  <tr>
    <th colspan="2" style="text-align:center;">Case1</th>
  </tr>
  <tr>
    <th colspan="2" style="text-align:center;">Initial</th>
  </tr>
  <tr>
    <th colspan="2" style="text-align:center;"><img src="picture/case1_initial.png" width="500"></th>
  </tr>
  <tr>
    <td align="center"><b>Top partition</b></td>
    <td align="center"><b>Bottom partition</b></td>
  </tr>
  <tr>
    <td style="text-align:center;"><img src="picture/case1_top_partition.png" width="500"></td>
    <td style="text-align:center;"><img src="picture/case1_bottom_partition.png" width="500"></td>
  </tr>
  <tr>
    <td align="center"><b>Top result placement</b></td>
    <td align="center"><b>Bottom result placement</b></td>
  </tr>
  <tr>
    <td style="text-align:center;"><img src="picture/case1_top.png" width="500"></td>
    <td style="text-align:center;"><img src="picture/case1_bottom.png" width="500"></td>
  </tr>
</table>

<table>
  <tr>
    <th colspan="2" style="text-align:center;">Case2</th>
  </tr>
  <tr>
    <th colspan="2" style="text-align:center;">Initial</th>
  </tr>
  <tr>
    <th colspan="2" style="text-align:center;"><img src="picture/case2_initial.png" width="500"></th>
  </tr>
  <tr>
    <td align="center"><b>Top partition</b></td>
    <td align="center"><b>Bottom partition</b></td>
  </tr>
  <tr>
    <td style="text-align:center;"><img src="picture/case2_top_partition.png" width="500"></td>
    <td style="text-align:center;"><img src="picture/case2_bottom_partition.png" width="500"></td>
  </tr>
  <tr>
    <td align="center"><b>Top result placement</b></td>
    <td align="center"><b>Bottom result placement</b></td>
  </tr>
  <tr>
    <td style="text-align:center;"><img src="picture/case2_top.png" width="500"></td>
    <td style="text-align:center;"><img src="picture/case2_bottom.png" width="500"></td>
  </tr>
</table>

<table>
  <tr>
    <th colspan="2" style="text-align:center;">Case3</th>
  </tr>
  <tr>
    <th colspan="2" style="text-align:center;">Initial</th>
  </tr>
  <tr>
    <th colspan="2" style="text-align:center;"><img src="picture/case3_initial.png" width="500"></th>
  </tr>
  <tr>
    <td align="center"><b>Top partition</b></td>
    <td align="center"><b>Bottom partition</b></td>
  </tr>
  <tr>
    <td style="text-align:center;"><img src="picture/case3_top_partition.png" width="500"></td>
    <td style="text-align:center;"><img src="picture/case3_bottom_partition.png" width="500"></td>
  </tr>
  <tr>
    <td align="center"><b>Top result placement</b></td>
    <td align="center"><b>Bottom result placement</b></td>
  </tr>
  <tr>
    <td style="text-align:center;"><img src="picture/case3_top.png" width="500"></td>
    <td style="text-align:center;"><img src="picture/case3_bottom.png" width="500"></td>
  </tr>
</table>
