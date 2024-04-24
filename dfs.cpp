i#include <iostream>
#include <vector>
#include <stack>
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

void parallelDFS(int startNode) {
    stack<int> stk;
    stk.push(startNode);
    visited[startNode] = true;

    while (!stk.empty()) {
        int current = stk.top();
        stk.pop();
        // Process node 'current' here
        cout << "Visited node: " << current << endl; // Print visited node
        #pragma omp parallel for
        for (size_t i = 0; i < graph[current].size(); ++i) {
            int next = graph[current][i];
            if (!visited[next]) {
                visited[next] = true;
                stk.push(next);
            }
        }
    }
}

int main() {
    generateRandomGraph();

    // Start DFS from node 0 in parallel
    #pragma omp parallel
    {
        #pragma omp single
        parallelDFS(0);
    }

    cout << "DFS completed.\n";
    return 0;
}