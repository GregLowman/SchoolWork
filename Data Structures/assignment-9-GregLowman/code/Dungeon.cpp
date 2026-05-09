#include "Dungeon.hpp"
#include <vector>
#include <stack>
#include <iostream>

using namespace std;



static bool traverseHelper(vertex* vert, vertex* end, Dungeon* dungeon)
{
    vert->visited = true;
    if(vert == end)
    {
        return true;
    }
    for(auto adjacentVertex : vert->adj)
    {
        vertex* next = adjacentVertex.v;
        if(!next->visited && next->c != wall && next->c != radioactive && !dungeon->isContaminated(next->x, next->y))
        {
            if (traverseHelper(adjacentVertex.v, end, dungeon))
            {
                return true;
            }
        }
    }
    return false;
}



Dungeon::Dungeon(int size){
    n = size;

    dungeon = new cell_type* [n];
    for (int i = 0; i < n; i++)
        dungeon[i] = new cell_type[n];


    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            dungeon[i][j] = END;
    }
}

/**
 * @brief This function should add a new vertex to the graph
 *
 * @param x x-cordinate of the cell
 * @param y y-cordinate of the cell
 * @param typeOfCell the type of the cell
 */
void Dungeon::addVertex(int x, int y, cell_type typeOfCell){
    for(auto vert : vertices)
    {
        if (vert->x == x && vert->y == y)
        {
            return;
        }
    }

    vertex *v = new vertex;
    v->x = x;
    v->y = y;
    v->c = typeOfCell;
    v->vertexNum = findVertexNumFromPosition(x, y);
    vertices.push_back(v);

    return;
}

/**
 * @brief Finds the vertex number from the position of the open path in the maze
 *
 * @param x the x-cordinate of the cell
 * @param y the y-codinate of the cell
 * @return int the vertex number of the cell
 */
int Dungeon::findVertexNumFromPosition(int x, int y){

   int vertexNumber = (x * n) + y;
   return vertexNumber;
}

/**
 * @brief Determine whether a cell is contaminated
 */
bool Dungeon::isContaminated(int x, int y){

    int delta[3] = {-1, 0, 1};
    int a = 0;
    int b = 0;
    vector <int> vertexNumbers;

    for(auto vertex : vertices)
    {
        if(vertex->x == x && vertex->y == y)
        {
            for(auto i : delta)
            {
                a = x + i;

                for(auto j : delta)
                {
                    b = y + j;
                    if (a >= 0 && a < n && b >= 0 && b < n)
                    {
                        vertexNumbers.push_back(findVertexNumFromPosition(a, b));
                    }

                }
            }
        }
    }

    for (auto vertex : vertices)
    {
        for(auto number : vertexNumbers)
        {
            if(vertex->vertexNum == number)
            {
                if(vertex->c == radioactive)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

/**
 * @brief Given the x,y cordinates of a cell, find the vertex no.s of the cells that are adjacent and possible to visit.
 *
 * @param x
 * @param y
 * @return vector<int>
 */
vector<int> Dungeon::findOpenAdjacentPaths(int x, int y){
    vector<int> open_adj;
    vector <int> adjVertexNumbers;

    int delta[3] = {-1, 0, 1};
    int a = 0;
    int b = 0;

    for(auto vertex : vertices)
    {
        if(vertex->x == x && vertex->y == y)
        {
            for(auto i : delta)
            {
                a = x + i;

                for(auto j : delta)
                {
                    b = y + j;
                    if((0 <= b && b < n) && (0 <= a && a < n) && !(a == x && b == y))
                    {
                        adjVertexNumbers.push_back(findVertexNumFromPosition(a, b));
                    }
                }
            }
        }
    }


        for (auto vertex : vertices)
        {
            for(auto number : adjVertexNumbers)
            {
                if(vertex->vertexNum == number)
                {
                    if(vertex->c != radioactive && vertex->c != wall && !isContaminated(vertex->x, vertex->y))
                    {
                        open_adj.push_back(vertex->vertexNum);
                    }
                }
            }
        }

    return open_adj;
}

/**
 * @brief For each cell, find and store its neighbors, converting the matrix to an adjacency list representation.
 *
 */
void Dungeon::convertDungeonToAdjacencyListGraph(){

    int delta[3] = {-1, 0, 1};
    int a = 0;
    int b = 0;

    vector <vertex*> adjVerticies;
    vector <int> adjVertexNumbers;

    adjVertex connection;

    for(auto vertex : vertices)
    {
        int x = vertex->x;
        int y = vertex->y;

        for(auto i : delta)
        {
            a = x + i;

            for(auto j : delta)
            {
                b = y + j;

                if((0 <= b && b < n) && (0 <= a && a < n) && !(a == x && b == y))
                {
                    adjVertexNumbers.push_back(findVertexNumFromPosition(a, b));
                }
            }
        }

        for(auto v : vertices)
        {
            for(auto adj : adjVertexNumbers)
            {
                if(v->vertexNum == adj)
                {
                    adjVerticies.push_back(v);
                }
            }
        }

        for(auto adj : adjVerticies)
        {
            connection.v = adj;
            vertex->adj.push_back(connection);
        }

        adjVertexNumbers.clear();
        adjVerticies.clear();

    }

}

/**
 * Returns true if a path exists from the start cell to the END cell.
 */
bool Dungeon::isDungeonTraversable(){

    vertex* begin;
    vertex* finish;


    for(auto vertex : vertices)
    {
        if(vertex->c == start)
        {
            begin = vertex;
        }
        else if(vertex->c == END)
        {
            finish = vertex;
        }
    }

    if(!begin || !finish)
    {
        return false;
    }

    return(traverseHelper(begin, finish, this));

}


/**
 * @brief Destroy the Dungeon:: Dungeon object
 *
 */
Dungeon::~Dungeon(){

    for(int i = 0; i < n; i++)
    {
        delete[] dungeon[i];
    }
    delete [] dungeon;

    for(auto v : vertices)
    {
        delete v;
    }

    vertices.clear();

}
