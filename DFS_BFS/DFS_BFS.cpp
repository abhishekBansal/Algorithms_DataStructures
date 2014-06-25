#include <iostream>
#include <vector>
#include <queue>

#define NO_OF_VERTICES 8
#define START_POINT 0

int graph[NO_OF_VERTICES][NO_OF_VERTICES] = {
                {0, 0, 1, 1, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 1, 1, 0},
                {1, 1, 0, 0, 1, 0, 0, 0},
                {0, 1, 0, 0, 0, 0, 0, 1},
                {0, 0, 1, 0, 0, 0, 1, 1},
                {0, 1, 0, 1, 0, 0, 0, 1},
                {0, 0, 1, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0}
                };


class vertex
{
    public:
        bool visited;
        int vertexNo;
};

std::vector<vertex> vertexList;
std::vector<int> orderList;
std::queue<int> bfsQueue;

void performDFS(int startPoint)
{
    vertexList[startPoint].visited = true;
    std::cout << startPoint << std::endl;

    for(int i = 0; i < NO_OF_VERTICES; i++)
    {
        if(graph[startPoint][i] > 0 && vertexList[i].visited == false)
        {
            performDFS(i);
        }
    }
}

void performBFS(int startPoint)
{
    vertexList[startPoint].visited = true;
    std::cout << startPoint << std::endl;
    bfsQueue.pop();
    
    for(int i = 0; i < NO_OF_VERTICES; i++)
    {
        if(graph[startPoint][i] > 0 && vertexList[i].visited == false)
        {
            vertexList[i].visited = true;
            bfsQueue.push(i);
        }
    }
    if(!bfsQueue.empty())
    {
        performBFS(bfsQueue.front());
    }
    else
        return;
}

int main()
{
    for(int i=0; i < NO_OF_VERTICES; i++)
    {
        vertex ver;
        ver.visited = false;
        ver.vertexNo = i;
        vertexList.push_back(ver);
    }

    //performDFS(START_POINT);
    
    std::cout << "BFS Results: " << std::endl;
    bfsQueue.push(START_POINT);
    performBFS(START_POINT);

    return 1;
}