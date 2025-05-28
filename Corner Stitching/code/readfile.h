#ifndef  _READFILE_H
#define  _READFILE_H
#include <vector>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include "block.h"

using namespace std;

void Get_File(char *, vector<vector<string> > &);
void create_file(char *, vector<pair<int, TILE*> >&, vector<POINT>&);

#endif