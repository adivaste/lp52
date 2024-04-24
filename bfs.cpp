// BFS

#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
#include <omp.h>

#define NUM_NODES 10000

using namespace std;

vector<int> graph[NUM_NODES];
bool visited[NUM_NODES];

void generateRandomGraph() {
    srand(time(NULL));
    for (int i = 0; i < NUM_NODES; ++i) {
        for (int j = i + 1; j < NUM_NODES; ++j) {
            if (rand() % 10 == 0) { // Adjust the probability for edge creation as needed
                graph[i].push_back(j);
                graph[j].push_back(i);
            }
        }
    }
}

void parallelBFS(int startNode) {
    queue<int> q;
    q.push(startNode);
    visited[startNode] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        // Process node 'current' here
        cout << "Visited node: " << current << endl; // Print visited node
        #pragma omp parallel for
        for (size_t i = 0; i < graph[current].size(); ++i) {
            int next = graph[current][i];
            if (!visited[next]) {
                visited[next] = true;
                q.push(next);
            }
        }
    }
}

int main() {
    generateRandomGraph();

    // Start BFS from node 0 in parallel
    #pragma omp parallel
    {
        #pragma omp single
        parallelBFS(0);
    }

    cout << "BFS completed.\n";
    return 0;
}