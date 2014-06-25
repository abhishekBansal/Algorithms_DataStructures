/*
PROBLEM STATEMENT: 
You have V jobs to complete. A set of prerequisite relations are enforced with the jobs; some job can start only after some other job(s) has(have) been completed. You are given a graph to represent these relations. 
In this graph, each job corresponds to a vertex and a prerequisite relation corresponds to a directed edge. There can be a cycle in this graph. (A cycle is a path starting from a vertex and returning to the same vertex.) 
The following is an example graph. 
 
In this graph, job 1 can start only after job 4. Job 6 can start only after jobs 5 and 7 both have been completed. You can see that there is no cycle in the graph. 

You have to complete all the jobs one by one not violating the prerequisite relations. A possible sequence with respect to the above graph is 

8, 9, 4, 1, 5, 2, 3, 7, 6.

Another sequence is also valid:
4, 1, 2, 3, 8, 5, 7, 6, 9.

It is usual that there exists more than one valid sequence for a given graph. The following is an invalid sequence:

4, 1, 5, 2, 3, 7, 6, 8, 9.

Job 5 precedes job 8 in this sequence; in the prerequisite graph, however, job 5 can start only after job 8 has been completed; thus, the sequence is not possible. 

Given V jobs and a set of prerequisite relations, generate a program that finds a valid sequence of jobs. When there is more than one valid sequence, you only have to provide one of them.
Since it is not possible to have a valid sequence for a graph with a cycle, your program has to detect such graphs. In case of a graph with no cycle, there exists at least a valid sequence. 

[Constraints]
The number of jobs: 5<=V<=1000.
Time limit: 1 second in total for 10 test cases. 

[Input]
10 test cases are given. Each case occupies two lines; thus there are 20 lines in total. For each case, the first line has V and E, the numbers of jobs and edges, respectively. The next line enumerates E (directed) edges. 
An edge is represented by two jobs. For example, an edge from job 5 to job 28 is represented by 5 28. The indices of jobs are 1 through V. Each number in a line is separated by a space. 
[Output]
You print 10 answers in 10 lines. Each line starts with #x where x means the index of a test case. Then, it puts a space and enumerates a job sequence in the same line. Each member in the line is separated by a space. 
If the graph has a cycle, you just print 0.
*/

/*
Notes:

# Directed graph problem.
# Graph is made using adjacency matrix
# TODO: cycle detection as in that case jobs cant be done

*/

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <list>
#include <ctime>

class FileReader
{

private:
    
    std::string _fileName;

    std::ifstream fp;

public:
    FileReader(std::string name)
        :_fileName(name)
    {
        fp.open(_fileName);

        if (!fp.is_open())
            std::cout << "Error while opening input file";
    }

    std::string readNextLine();

    ~FileReader()
    {
        fp.close();
    }

};

std::string
FileReader::readNextLine()
{
    std::string line("");
    if(!fp.eof())
    {
        getline(fp, line);
    }
    return line;
}

void mLog(std::string logStr)
{
    //std::cout << std::endl << logStr;
}

int** adjMatrix = NULL;
int noOfVertices = 0;
std::list<int> jobList;

void doTopologicalSort(std::stack<int>& zeroIndegreeStack, int *indegArray)
{
    if(zeroIndegreeStack.size() == 0)
        return;
    else
    {
        int job = zeroIndegreeStack.top();
        jobList.push_back(job);

        zeroIndegreeStack.pop();
        // find neighbours of this vertex and decrement indegree by one
        for (int i = 0; i < noOfVertices; i++)
        {
            if (adjMatrix[job][i] > 0)
            {
                --indegArray[i];
                if(indegArray[i] == 0)
                {
                    zeroIndegreeStack.push(i);
                }
            }
        }

        if(zeroIndegreeStack.size() == 0)
            return;
        else
            doTopologicalSort(zeroIndegreeStack, indegArray);
    }
}

void main()
{
    std::clock_t start;
    double duration;

    start = std::clock();

    FileReader fileReader("sample_input.txt");
    std::string line;
    do
    {
        // clear global buffers
        jobList.clear();
        adjMatrix = NULL;
        noOfVertices = 0;

        line = fileReader.readNextLine();
        //std::cout << std::endl << line;
        // this line contains input size
        std::string verticesString = line.substr(0, line.find_first_of(' '));
        noOfVertices = atoi(verticesString.c_str());
        mLog("No of vertices: ");
        std::cout << noOfVertices;

        // now create adjacency matrix for given directed graph
        mLog("Allocating memory for adjacancy matrix !");
        adjMatrix = new int*[noOfVertices];
        for(int i=0; i < noOfVertices; i++)
        {
            adjMatrix[i] = new int [noOfVertices];
            std::fill_n(adjMatrix[i], noOfVertices, 0);
        }

        // now get graph from file also simultaneosly build indegree array
        int* indegrees = new int[noOfVertices];
        std::fill_n(indegrees, noOfVertices, 0);

        line = fileReader.readNextLine();
        int pos = 0;
        while(pos < line.length())
        {
            int nextPos = line.find_first_of(' ', pos);
           // int nextToNextPos = line.find_first_of(' ', nextPos + 1);
            std::string startPointStr = line.substr(pos, nextPos - pos);
            int startPoint = atoi(startPointStr.c_str());

            int nextToNextPos = line.find_first_of(' ', nextPos + 1);

            std::string endPointStr = line.substr(nextPos, nextToNextPos - nextPos);
            int endPoint = atoi(endPointStr.c_str());
            
            // fill this infromation
            // remember to add one at time of writing file in final output
            adjMatrix[startPoint - 1][endPoint - 1] = 1;
            // increment in degree of end point
            ++indegrees[endPoint -1 ];

            if(nextToNextPos == -1)
                break;

            pos = nextToNextPos + 1;
        }

        //mLog("Printing matrix !!");
        //std::cout << std::endl;
        //for(int i=0; i < noOfVertices; i++)
        //{
        //    for(int j = 0; j < noOfVertices; j++)
        //    {
        //        std::cout << adjMatrix[i][j] << " ";
        //    }

        //    std::cout<<std::endl;
        //}
        // make a stack to store 0 indegree vertices
        std::stack<int> zeroIndegreeStack;
        for(int i=0; i < noOfVertices; i++)
        {
            if(indegrees[i] == 0)
            {
                zeroIndegreeStack.push(i);
            }
        }

        doTopologicalSort(zeroIndegreeStack, indegrees);

        mLog("Deallocating memory !");
        for(int i=0; i < noOfVertices; i++)
        {
            delete [] adjMatrix[i];
        }
        delete [] adjMatrix;
        adjMatrix = NULL;

    }while(!line.empty());

    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    std::cout<<"printf: "<< duration <<'\n';
}

