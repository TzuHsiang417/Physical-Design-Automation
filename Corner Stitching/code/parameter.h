#ifndef _PARAMETER_H
#define _PARAMETER_H

#define TOP(a) (a->coordinate.y + a->height)
#define BOTTOM(a) (a->coordinate.y)
#define LEFT(a) (a->coordinate.x)
#define RIGHT(a) (a->coordinate.x + a->width)
#define LB(a) (a->LB)
#define BL(a) (a->BL)
#define RT(a) (a->RT)
#define TR(a) (a->TR)
#define BLOCK 1
#define SPACE 0

#endif