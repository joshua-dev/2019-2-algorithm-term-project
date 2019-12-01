#ifndef _SOLVER_H_
#define _SOLVER_H_

#include<string>
#include<vector>
#include<map>
#include<unordered_map>
#include<queue>
#include "Definition.h"
#include "PushBox.h"

class Solver
{
private:
    vector<vector<int>> map1;
    vector<vector<int>> map2;
    std::map <pair<vector<vector<int>>, Coordinates>, bool> visited;
    string finalSol;
    Coordinates userPos;

public:
    Solver(int, string&);
    void run(PushBox *pushBox);
    string getSol();
    bool gameWin(vector<vector<int>> map);
    bool getSolution(vector<vector<int>> map, Coordinates userPos, string sol);
};

#endif