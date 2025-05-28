import turtle as t 
import sys
import numpy as np
import math
import time
import random as rd
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import random as rd
import copy

#parameter
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
gridstyle = "--"   #ls{'-', '--', '-.', ':', '', (offset, on-off-seq), ...}
linestyle = "-"

plt_savefig = True
plt_show = True
plt_show = False

plt_aspect_equal = True
plt_label = True
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def draw_block(ax,x,y,width,height,color1):
    ax.add_patch(
        patches.Rectangle( 
            (x,y ),
            width,
            height,
            fill = True,
            edgecolor = "#000000",
            facecolor = color1,
            alpha = 1.0 #0.3 original
        )
    )
def random_color_generation(bit=6,deep_range=[7,14]):
    color_str = "#"  #ex: "#054E9F"

    for i in range(bit):
        number = rd.randint(deep_range[0],deep_range[1])
        if(number==15):
            color_str+="F"
        elif(number==14):
            color_str+="E"
        elif(number==13):
            color_str+="D"
        elif(number==12):
            color_str+="C"
        elif(number==11):
            color_str+="B"
        elif(number==10):
            color_str+="A"
        else:
            color_str+=str(number)

    return color_str

def draw_line(plt,x1,y1,x2,y2,color1):
    if(x1==x2):#verticla line
        new_x1,new_x2 = x1,x2
    else:
        new_x1,new_x2 = x1,x2
    if(y1==y2):
        new_y1,new_y2 = y1,y2
    else:
        new_y1,new_y2 = y1,y2
    
    plt.plot([new_x1, new_x2], [new_y1,new_y2],color=color1,ls=linestyle,linewidth=2)




system_arg = sys.argv
in_file = system_arg[1]
out_file = system_arg[2]
output_file = system_arg[3]

if(in_file.find("/")):
    maze_name = in_file[in_file.find("/")+1:in_file.find(".")]
else:
    maze_name = in_file[0:in_file.find(".")]




top_row = []
bottom_row = []
nets_color = {}
nets_segment = {}



# parser for in
fread = open(in_file ,'r')
f = fread.read().split("\n")
s = f[0].split()
s1 = f[1].split()
for i in range(len(s)):
    top_row.append(int(s[i]))
    bottom_row.append(int(s1[i]))


# parser for out
fread = open(out_file ,'r')
f = fread.read().split("\n")


net_name = ""
max_bound = 1
max_bound_x = 1;
max_bound_y = 1;

i=0
#screen.setup(w,h)
while(i<len(f)):
    print(f[i])
    if"begin" in f[i]:
        net_name = f[i].split()[1]
        nets_color[net_name] = random_color_generation() 
        nets_segment[net_name] = []
       
        

        i=i+1
        while(True):
            if("end" in f[i] ) or (f[i]==""):
                i=i+1
                break
            else:
                r = f[i].split(" ")
                r1 =  int(r[1])
                r2 =  int(r[2])
                r3 =  int(r[3])
                max_bound = max(max_bound,max(max(r1,r2),r3))
                if ("V" in f[i]):
                    max_bound_y = max(max_bound_y,max(r2,r3))
                    nets_segment[net_name].append([r1,r2,r1,r3])
                    
                else:   #("H" in f[i])
                    max_bound_x = max(max_bound_x,max(r1,r3))
                    nets_segment[net_name].append([r1,r2,r3,r2])
                i=i+1
    else:
        i=i+1

#----------------------------------- #construce the clean maze graph !!
maze_x_range = (0,max_bound_x)
maze_y_range = (0,max_bound_y)

fig_max_scale = max(6,int(max(maze_x_range[1],maze_y_range[1])/10)+1)

#fig = plt.figure(figsize=(10,10))
fig = plt.figure(figsize=(fig_max_scale,fig_max_scale))
ax = fig.add_subplot(111)

plt.axis([maze_x_range[0],maze_x_range[1],maze_y_range[0],maze_y_range[1]])
plt.axis("on")

plt.grid(True,ls=gridstyle) #,color="r"
plt.title(maze_name)

grid_length = 1 

plt.xticks(np.arange(0,maze_x_range[1],grid_length),fontsize=5)
plt.yticks(np.arange(0,maze_y_range[1],grid_length),fontsize=5)

plt.xlim(xmin=maze_x_range[0]-1,xmax=maze_x_range[1]*1.3)
plt.ylim(ymin=maze_y_range[0]-1,ymax=maze_y_range[1]+1)

for i in range(len(top_row)):
    
    now_color = "#666666"
    if str(top_row[i]) in nets_color:
        now_color = nets_color[str(top_row[i])]
    plt.text(i, maze_y_range[1], str(top_row[i]), fontstyle='oblique',backgroundcolor=now_color,color="#FFFFFF")
    now_color = "#666666"
    if str(bottom_row[i]) in nets_color:
        now_color = nets_color[str(bottom_row[i])]
    plt.text(i, 0, str(bottom_row[i]), fontstyle='oblique',backgroundcolor=now_color,color="#FFFFFF")
#----------------------------------- #construce the clean maze graph !!




for net_name,net_color in nets_color.items():
     plt.plot([-1,-1], [-1,-1],label=net_name,color=net_color)
     for segment in nets_segment[net_name]:
        draw_line(plt,segment[0],segment[1],segment[2],segment[3],net_color)
    


if plt_label:
    plt.legend(loc="upper right")


if plt_aspect_equal:
    plt.gca().set_aspect('equal', adjustable='box')

if plt_savefig:
    plt.savefig(output_file,dpi=300)

if plt_show:
    plt.show()



