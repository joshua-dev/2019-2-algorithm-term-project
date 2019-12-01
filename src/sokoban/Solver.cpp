#include "Solver.h"

Solver::Solver(int lev, string &give)
{
    finalSol = "";
}

void Solver::run(PushBox *pushBox)
{
    map1.resize(10);
    map2.resize(10);
    for(int i = 0; i < 10; i++)
    {
        map1[i].resize(10);
        map2[i].resize(10);
    }
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            map1[i][j] = pushBox -> getMap(i,j);
            map2[i][j] = pushBox -> getMap(i,j);
        }

    }

    this -> userPos = pushBox -> getUserPos();

    string sol = "";
    getSolution(map2, userPos, sol);
}
string Solver::getSol()
{
    return finalSol;
}
bool Solver::getSolution(vector<vector<int>> mapi, Coordinates userPosi, string soli)
{
    queue< pair< pair<vector <vector<int> >, string>, Coordinates>> q;
    pair< pair <vector <vector<int> >, string>, Coordinates> initial;

    initial.first.first = mapi;
    initial.first.second = soli;
    initial.second.x = userPos.x;
    initial.second.y = userPos.y;

    q.push(initial);

    while(!q.empty())
    {
        pair< pair< vector<vector<int> >, string>, Coordinates> top = q.front();
        vector< vector<int>> map = top.first.first;
        string sol = top.first.second;
        int userX = top.second.x;
        int userY = top.second.y;

        q.pop();
        if(gameWin(map))
        {
            finalSol = sol;
            return true;
        }

        pair<vector<vector<int>>, Coordinates> cur;
        cur.first = map;
        cur.second.x = userX;
        cur.second.y = userY;

        if(visited[cur])
        {
            continue;
        }
        visited[cur] = true;

        if(userX < 9)
        {
            if(map1[userY][userX + 1] != WALL) //Right
            {
                if(map[userY][userX + 1] == BOX)
                {
                    if(userX < 8)
                    {
                        if(map1[userY][userX + 2] != WALL && map[userY][userX + 2] != BOX)
                        {
                            swap(map[userY][userX + 1], map[userY][userX + 2]);
                            if(!visited[make_pair(map, Coordinates(userX + 1, userY))])
                            {
                                q.push(make_pair(make_pair(map, sol + "R"), Coordinates(userX+1, userY)));
                            }
                            swap(map[userY][userX + 1], map[userY][userX + 2]);
                        }
                    }
                } else
                {
                    if(!visited[make_pair(map, Coordinates(userX + 1, userY))])
                    {
                       q.push(make_pair(make_pair(map, sol + "R"), Coordinates(userX+1, userY)));
                    }
                }
            }
        }

        if(userX > 0)
        {
            if(map1[userY][userX - 1] != WALL) //Left
            {
                if(map[userY][userX - 1] == BOX)
                {
                    if(userX > 1)
                    {
                        if(map1[userY][userX - 2] != WALL && map[userY][userX - 2] != BOX)
                        {
                            swap(map[userY][userX - 1], map[userY][userX - 2]);
                            if(!visited[make_pair(map, Coordinates(userX - 1, userY))])
                            {
                                q.push(make_pair(make_pair(map, sol + "L"), Coordinates(userX-1, userY)));
                            }
                            swap(map[userY][userX - 1], map[userY][userX - 2]);
                        }
                    }
                } else
                {
                    if(!visited[make_pair(map, Coordinates(userX - 1, userY))])
                    {
                       q.push(make_pair(make_pair(map, sol + "L"), Coordinates(userX-1, userY)));
                    }
                }
            }
        }

        if(userY > 0)
        {
            if(map1[userY - 1][userX] != WALL) //Up
            {
                if(map[userY - 1][userX] == BOX)
                {
                    if(userY > 1)
                    {
                        if(map1[userY - 2][userX] != WALL && map[userY - 2][userX] != BOX)
                        {
                            swap(map[userY - 1][userX], map[userY - 2][userX]);
                            if(!visited[make_pair(map, Coordinates(userX, userY - 1))])
                            {
                                q.push(make_pair(make_pair(map, sol + "U"), Coordinates(userX, userY - 1)));
                            }
                            swap(map[userY - 1][userX], map[userY - 2][userX]);
                        }
                    }
                } else
                {
                    if(!visited[make_pair(map, Coordinates(userX, userY - 1))])
                    {
                       q.push(make_pair(make_pair(map, sol + "U"), Coordinates(userX, userY - 1)));
                    }
                }
            }
        }

        if(userY < 9)
        {
            if(map1[userY + 1][userX] != WALL) //Down
            {
                if(map[userY + 1][userX] == BOX)
                {
                    if(userY < 8)
                    {
                        if(map1[userY + 2][userX] != WALL && map[userY + 2][userX] != BOX)
                        {
                            swap(map[userY + 2][userX], map[userY + 2][userX]);
                            if(!visited[make_pair(map, Coordinates(userX, userY + 1))])
                            {
                                q.push(make_pair(make_pair(map, sol + "D"), Coordinates(userX, userY + 1)));
                            }
                            swap(map[userY + 1][userX], map[userY + 2][userX]);
                        }
                    }
                } else
                {
                    if(!visited[make_pair(map, Coordinates(userX, userY + 1))])
                    {
                       q.push(make_pair(make_pair(map, sol + "D"), Coordinates(userX, userY + 1)));
                    }
                }
            }
        }
    }

    return false;
}

bool Solver::gameWin(vector<vector<int>> map2)
{
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            if(map1[i][j] == GOAL)
                return false;
        }
    }
    return true;
}