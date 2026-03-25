#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <string>
using namespace std;
const int V = 5; // Number of landmarks
string landmarks[] = {"Main Gate", "Library", "Cafeteria", "Sports Complex", 
"Tech Park"};
// --- DFS using Adjacency Matrix --
void DFS(int adjMatrix[V][V], int startNode) {
    bool visited[V] = {false};
    stack<int> s;
    s.push(startNode);
    cout << "DFS Traversal (Matrix): ";
    while (!s.empty()) {
        int curr = s.top();
        s.pop();
        if (!visited[curr]) {
            cout << landmarks[curr] << " -> ";
            visited[curr] = true;
        }
        // Push neighbors in reverse to maintain order
        for (int i = V - 1; i >= 0; i--) {
            if (adjMatrix[curr][i] == 1 && !visited[i]) {
                s.push(i);
            }
        }
    }
    cout << "END" << endl;
}
// --- BFS using Adjacency List --
void BFS(vector<int> adjList[], int startNode) {
    bool visited[V] = {false};
    queue<int> q;
    visited[startNode] = true;
    q.push(startNode);
    cout << "BFS Traversal (List):   ";
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        cout << landmarks[curr] << " -> ";
        for (int neighbor : adjList[curr]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    cout << "END" << endl;
}
int main() {
    // 1. Initialize Adjacency Matrix (for DFS)
    int adjMatrix[V][V] = {0};
    auto addEdgeMatrix = [&](int u, int v) { adjMatrix[u][v] = 1; adjMatrix[v]
[u] = 1; };
    // 2. Initialize Adjacency List (for BFS)
    vector<int> adjList[V];
    auto addEdgeList = [&](int u, int v) { adjList[u].push_back(v); 
adjList[v].push_back(u); };
    // Define connections around college
    int edges[][2] = {{0,1}, {0,2}, {1,4}, {2,3}, {3,4}};
    for(auto& edge : edges) {
        addEdgeMatrix(edge[0], edge[1]);
        addEdgeList(edge[0], edge[1]);
    }
    DFS(adjMatrix, 0); // Start from Main Gate
    BFS(adjList, 0);   // Start from Main Gate
    return 0;
}