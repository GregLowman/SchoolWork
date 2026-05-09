#ifndef DUNGEON_H
#define DUNGEON_H
#include<vector>
#include<iostream>
using namespace std;

enum cell_type { start, END, radioactive, wall, open };

struct vertex;
struct adjVertex{
    vertex *v;
};

struct vertex{
    int vertexNum;
	int x, y;
	cell_type c = END;
    bool visited = false;
    vector<adjVertex> adj;
};

class Dungeon
{
    public:
        cell_type ** dungeon; 
        Dungeon(int n = 0); 
        ~Dungeon(); 

        void addVertex(int x, int y, cell_type c);
        int findVertexNumFromPosition(int x, int y);
        bool isContaminated(int x, int y);
        vector<int> findOpenAdjacentPaths(int x, int y);
        void convertDungeonToAdjacencyListGraph(); 
        bool isDungeonTraversable(); 
        vector<vertex*> vertices;

    private:
        int n;
};

#endif // DUNGEON_H
