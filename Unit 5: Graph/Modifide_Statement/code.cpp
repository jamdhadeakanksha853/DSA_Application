#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

struct Edge {
    int u, v, weight;
};

int findParent(vector<int>& parent, int x) {
    if (parent[x] == x)
        return x;
    return parent[x] = findParent(parent, parent[x]);
}

void primMST(int V, vector<Edge> edges, string title) {
    vector<vector<pair<int, int>>> adj(V);

    for (auto e : edges) {
        adj[e.u].push_back({e.v, e.weight});
        adj[e.v].push_back({e.u, e.weight});
    }

    vector<bool> visited(V, false);
    int total = 0, count = 0;
    visited[0] = true;

    cout << "\n" << title << " - Prim's Algorithm\n";

    while (count < V - 1) {
        int mn = INT_MAX, u = -1, v = -1;

        for (int i = 0; i < V; i++) {
            if (visited[i]) {
                for (auto p : adj[i]) {
                    if (!visited[p.first] && p.second < mn) {
                        mn = p.second;
                        u = i;
                        v = p.first;
                    }
                }
            }
        }

        if (u == -1) {
            cout << "Graph is disconnected. MST not possible.\n";
            return;
        }

        cout << u << " - " << v << " : " << mn << endl;
        visited[v] = true;
        total += mn;
        count++;
    }

    cout << "Total Cost = " << total << endl;
}

void kruskalMST(int V, vector<Edge> edges, string title) {
    sort(edges.begin(), edges.end(),
         [](Edge a, Edge b) {
             return a.weight < b.weight;
         });

    vector<int> parent(V);
    for (int i = 0; i < V; i++)
        parent[i] = i;

    int total = 0, count = 0;

    cout << "\n" << title << " - Kruskal's Algorithm\n";

    for (auto e : edges) {
        int a = findParent(parent, e.u);
        int b = findParent(parent, e.v);

        if (a != b) {
            cout << e.u << " - " << e.v
                 << " : " << e.weight << endl;

            parent[a] = b;
            total += e.weight;
            count++;

            if (count == V - 1)
                break;
        }
    }

    if (count != V - 1) {
        cout << "Graph is disconnected. MST not possible.\n";
        return;
    }

    cout << "Total Cost = " << total << endl;
}

int main() {
    int V = 5;

    vector<Edge> edges = {
        {0, 1, 2},
        {0, 3, 6},
        {1, 2, 3},
        {1, 3, 8},
        {1, 4, 5},
        {2, 4, 7},
        {3, 4, 9}
    };

    cout << "ORIGINAL GRAPH\n";
    primMST(V, edges, "Original");
    kruskalMST(V, edges, "Original");

    int u, v, w;

    cout << "\nEnter new edge (u v weight): ";
    cin >> u >> v >> w;

    if (u < 0 || u >= V || v < 0 || v >= V || u == v || w <= 0) {
        cout << "Invalid edge input.\n";
        return 0;
    }

    edges.push_back({u, v, w});

    cout << "\nUPDATED GRAPH EDGES\n";
    for (auto e : edges)
        cout << e.u << " - " << e.v
             << " : " << e.weight << endl;

    primMST(V, edges, "Updated");
    kruskalMST(V, edges, "Updated");

    return 0;
}
