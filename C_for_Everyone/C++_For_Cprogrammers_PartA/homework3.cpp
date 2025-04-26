#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v;
    int weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

class UnionFind {
    vector<int> parent, rank;
public:
    UnionFind(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);  // Path compression
        return parent[x];
    }
    bool unite(int x, int y) {
        int xr = find(x), yr = find(y);
        if (xr == yr) return false;
        if (rank[xr] < rank[yr]) parent[xr] = yr;
        else if (rank[xr] > rank[yr]) parent[yr] = xr;
        else {
            parent[yr] = xr;
            rank[xr]++;
        }
        return true;
    }
};

int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    vector<Edge> edges(E);
    cout << "Enter each edge in format: u v weight\n";
    for (int i = 0; i < E; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    sort(edges.begin(), edges.end());  // Sort edges by weight

    UnionFind uf(V);
    vector<Edge> mst;
    int totalCost = 0;

    for (const Edge& edge : edges) {
        if (uf.unite(edge.u, edge.v)) {
            mst.push_back(edge);
            totalCost += edge.weight;
        }
    }

    cout << "\nMinimum Spanning Tree cost: " << totalCost << "\n";
    cout << "Edges in the MST:\n";
    for (const Edge& e : mst) {
        cout << e.u << " - " << e.v << " (weight " << e.weight << ")\n";
    }

    return 0;
}
