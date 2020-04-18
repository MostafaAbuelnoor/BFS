// This is a C++ project from a design and algorithms class (CMP 340 in AUS) exploring the BFS(Breadth first search) traversal and how to apply it
// Mostafa Abuelnoor

#include <iostream>
#include <time.h>
#include <queue>
using namespace std;

//function to add edge into the matrix
void createMatrix(int **adjMat, int v)
{
    srand((unsigned)time(NULL)); //Used to produce a different random seed everytime you run the code
    for (int i = 0; i < v; i++)
    {
        for (int j = 0; j < v; j++)
        {
            if (i != j)
            {
                int num = rand() % 2; //Generate a random 1 or 0
                adjMat[i][j] = num;   //Enter whether the node is connected to another point or not.
                adjMat[j][i] = num;
            }
            else
            {
                adjMat[i][j] = 0; //Node can't be connected to itself
            }
        }
    }
}

//This function is to display the adjacency matrix in the command prompt
void displayMatrix(int **adjMat, int v)
{
    cout << "  ";
    for (int x = 0; x < v; x++)
    {
        cout << x << " "; //To print the x label
    }

    cout << endl;

    for (int i = 0; i < v; i++)
    {
        for (int j = 0; j < v; j++)
        {
            if (!j)
            {
                cout << i << ":"; //To print the y label
            }
            cout << adjMat[i][j] << " "; //To print the adjacency matrix to the cmd prompt
        }
        cout << endl;
    }
}

//This is the BFS function
void bfs(int **adjMat, int s, int size)
{

    int *color = new int[size];
    //0 means white(Means node is not visited yet), 1 means gray(Means node is in queue) and 2 means black(Means all children are in queue)
    int *dist = new int[size];
    //Distance between the source vertex and the node
    int *parent = new int[size];
    //The parent of the current node
    for (int i = 0; i < size; i++)
    {
        // Initializing all values of the matrix
        color[i] = 0;
        dist[i] = -1;
        parent[i] = -1;
    }
    queue<int> bfsQueue; //Initializing a queue

    color[s] = 1;     // The source vertex is labeled as gray
    dist[s] = 0;      // Distance to source is 0 because it is itself
    bfsQueue.push(s); //Push the source vertex to the queue

    while (!bfsQueue.empty()) //If the queue is not empty yet, continue traversing
    {
        int u = bfsQueue.front(); //Extract the front of the queue
        for (int i = 0; i < size; i++) //Traverse the entire matrix
        {
            if (adjMat[u][i] == 1 && color[i] == 0) //If the vertex has children and weren't visited before then start classifying
            {
                bfsQueue.push(i); //add to queue
                color[i] = 1; // color is now gray because its in the queue
                dist[i] = dist[u] + 1; //One more node away from source
                parent[i] = u; // The parent is the u node now
            }
        }
        bfsQueue.pop(); // Delete the entry when done with classifying
        color[u] = 2; // Change to color black since we are done
    }
    //Printing our results in a table similar fashion
    for (int i = 0; i < size; i++)
    {
        string col;
        if (color[i] == 0)
            col = "WHITE";
        else if (color[i] == 1)
            col = "GRAY";
        else if (color[i] == 2)
            col = "BLACK";
        cout << "Vertex " << i << ": color = " << col << "; parent = " << parent[i] << "; Distance from source = " << dist[i] << endl;
    }
}

int main()
{
    int v;
    cout << "Number of vertices? "; //asking the user for the number of vertices in the graph
    cin >> v;
    cout << endl;

    int **adjMat = new int *[v]; //Creating a dynamic array
    for (int i = 0; i < v; i++)
    {
        adjMat[i] = new int[v];
    }

    createMatrix(adjMat, v);
    displayMatrix(adjMat, v);

    int s;
    cout << "Source vertex? "; //S is the source vertex so that we can do BFS traversal through the graph
    cin >> s;
    cout << endl;

    bfs(adjMat, s, v); //Passed the adjacency matrix, source vertex and the size of the matrix
}