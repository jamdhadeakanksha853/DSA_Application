#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

const int V = 5;

struct Edge {
    int u, v, weight;
};

int parent[V];

int findParent(int x) {
    if (parent[x] == x)
        return x;

    return parent[x] = findParent(parent[x]);
}

bool compareEdges(Edge a, Edge b) {
    return a.weight < b.weight;
}

// Prim's Algorithm
void primMST(int graph[V][V]) {
    bool visited[V] = {false};
    int totalCost = 0;

    visited[0] = true;

    cout << "\nPrim's Algorithm:\n";
    cout << "Selected Edges:\n";

    for (int count = 0; count < V - 1; count++) {
        int minWeight = INT_MAX;
        int u = -1, v = -1;

        for (int i = 0; i < V; i++) {
            if (visited[i]) {
                for (int j = 0; j < V; j++) {
                    if (!visited[j] &&
                        graph[i][j] != 0 &&
                        graph[i][j] < minWeight) {
                        minWeight = graph[i][j];
                        u = i;
                        v = j;
                    }
                }
            }
        }

        if (u == -1) {
            cout << "Graph is disconnected.\n";
            return;
        }

        cout << u << " - " << v
             << " : " << minWeight << endl;

        visited[v] = true;
        totalCost += minWeight;
    }

    cout << "Total Cost = " << totalCost << endl;
}

// Kruskal's Algorithm
void kruskalMST(vector<Edge> edges) {
    sort(edges.begin(), edges.end(), compareEdges);

    for (int i = 0; i < V; i++)
        parent[i] = i;

    int totalCost = 0;
    int count = 0;

    cout << "\nKruskal's Algorithm:\n";
    cout << "Selected Edges:\n";

    for (Edge e : edges) {
        int pu = findParent(e.u);
        int pv = findParent(e.v);

        if (pu != pv) {
            cout << e.u << " - " << e.v
                 << " : " << e.weight << endl;

            parent[pu] = pv;
            totalCost += e.weight;
            count++;

            if (count == V - 1)
                break;
        }
    }

    if (count != V - 1) {
        cout << "Graph is disconnected.\n";
        return;
    }

    cout << "Total Cost = " << totalCost << endl;
}

int main() {
    int graph[V][V] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };

    vector<Edge> edges = {
        {0, 1, 2},
        {0, 3, 6},
        {1, 2, 3},
        {1, 3, 8},
        {1, 4, 5},
        {2, 4, 7},
        {3, 4, 9}
    };

    primMST(graph);
    kruskalMST(edges);

    return 0;
}
