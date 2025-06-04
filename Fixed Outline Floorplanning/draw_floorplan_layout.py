import sys
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as patches
from matplotlib.patches import Patch
import math
import time

def draw_block(ax,x,y,width,height,id):
    #if id>0:
    #    color = "#FCC"
    #else:
    #    color = "#BBB"

    ax.add_patch(
        patches.Rectangle( 
            (x,y),
            width,
            height,
            fill = True,
            edgecolor = "#000",
            facecolor = "#BBB",
            alpha = 1.0 #0.3 original
        )
    )
    font_size = min(width, height) / math.sqrt(area) * 160 
    ax.text(x + width / 2, y + height / 2, id, fontsize=font_size, ha='center', va='center', color='black')

print("Begin drawing")

png_size = (16,12)
input_name = sys.argv[1]
output_name = sys.argv[2] 
png_name = sys.argv[3]

in_fread = open(input_name,'r')
in_f = in_fread.read().split("\n")
fread = open(output_name,'r')
f = fread.read().split("\n")

cost = int(f[0])
wirelength = int(f[1])
area = int(f[2])
window_width = int(f[3].split(" ")[0])
window_height = int(f[3].split(" ")[1])
runtime = int(f[4])

outline_width = int(in_f[0].split(" ")[1])
outline_height = int(in_f[0].split(" ")[2])

fig = plt.figure(figsize=png_size)

ax = fig.add_subplot(111)
ax.set_xbound(0,outline_width)
ax.set_ybound(0,outline_height)


i = 5

for block in range(len(f)-5):
    ss =  f[i].split(" ")
    if len(ss) <= 1:
        continue
    draw_block(ax,int(ss[1]),int(ss[2]),int(ss[3]) - int(ss[1]),int(ss[4]) - int(ss[2]),ss[0])
    i+=1

outline = plt.Rectangle((0, 0), outline_width, outline_height, edgecolor='red', facecolor='none', lw=3, label='Fixed Outline')
ax.add_patch(outline)

floorplan = plt.Rectangle((0, 0), window_width, window_height, edgecolor='blue',  facecolor='none', lw=3, linestyle='dashed')
ax.add_patch(floorplan)

#plt.savefig(str(sys.argv[1])[:-4]+".png")

legend_elements = [
        Patch(facecolor='none', edgecolor='red', lw=2, label='Fixed Outline'),
        Patch(facecolor='none', edgecolor='blue', lw=2, linestyle='dashed', label='Floorplan Area')
    ]
    
ax.legend(handles=legend_elements, loc='upper right', bbox_to_anchor=(1.1, 1.1), fontsize = 20)

#area = window_width * window_height
#title_name = "Floorplan area = " + str(window_width) + " * " + str(window_height) + " = " + str(area)
#plt.title(title_name, fontsize = 25)


plt.savefig(png_name)

print("Finish!!!")
