/* Dijkstra’s algorithm - shortest path problem*/
/* Monte Carlo Problem*/

/* Turn in:  Printout of program, 200 words on what you learned, and output showing the average path length 
calculation. Use densities: 20% and 40% on a graph of 50 nodes with a distance range of 1.0 to 10.0.   
To get an average path length, compute the 49 paths:

1 to 2, 1 to 3, 1 to 4, …, 1 to 50. 

[In an instance where there is no path between 1 and n, omit that value from the average. This should be very 
rare for the chosen density and size in this homework.]

Keep in mind: good style – choice of identifiers, short functions, good documentation, correctness and efficiency.
 Cite any references in creating this program.*/


// MonteCarloDijkstra.cpp
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;

class Graph {
private:
    int V;
    vector<vector<pair<int, double>>> adjList;

public:
    Graph(int vertices) : V(vertices), adjList(vertices) {}

    void addEdge(int u, int v, double weight) {
        adjList[u].emplace_back(v, weight);
        adjList[v].emplace_back(u, weight); // undirected
    }

    const vector<pair<int, double>>& neighbors(int u) const {
        return adjList[u];
    }

    int vertices() const {
        return V;
    }
};

class Dijkstra {
public:
    static vector<double> shortestPaths(const Graph& graph, int src) {
        int V = graph.vertices();
        vector<double> dist(V, numeric_limits<double>::infinity());
        vector<bool> visited(V, false);

        using P = pair<double, int>; // (distance, node)
        priority_queue<P, vector<P>, greater<P>> pq;

        dist[src] = 0.0;
        pq.emplace(0.0, src);

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if (visited[u]) continue;
            visited[u] = true;

            for (const auto& neighbor : graph.neighbors(u)) {
                int v = neighbor.first;
                double weight = neighbor.second;

                if (!visited[v] && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.emplace(dist[v], v);
                }
            }
        }

        return dist;
    }
};

class MonteCarloSimulator {
private:
    int nodeCount;
    double density;
    double minDist, maxDist;

public:
    MonteCarloSimulator(int nodes, double dens, double minD, double maxD)
        : nodeCount(nodes), density(dens), minDist(minD), maxDist(maxD) {
        srand(time(nullptr));
    }

    Graph generateRandomGraph() {
        Graph g(nodeCount);
        for (int i = 0; i < nodeCount; ++i) {
            for (int j = i + 1; j < nodeCount; ++j) {
                double prob = (double)rand() / RAND_MAX;
                if (prob < density) {
                    double weight = minDist + ((double)rand() / RAND_MAX) * (maxDist - minDist);
                    g.addEdge(i, j, weight);
                }
            }
        }
        return g;
    }

    double averageShortestPath() {
        Graph g = generateRandomGraph();
        vector<double> distances = Dijkstra::shortestPaths(g, 0);

        double sum = 0.0;
        int count = 0;
        for (int i = 1; i < nodeCount; ++i) {
            if (distances[i] < numeric_limits<double>::infinity()) {
                sum += distances[i];
                ++count;
            }
        }

        return count > 0 ? sum / count : 0.0;
    }
};

int main() {
    int nodes = 50;
    double minDist = 1.0, maxDist = 10.0;

    MonteCarloSimulator sim1(nodes, 0.2, minDist, maxDist);
    double avg1 = sim1.averageShortestPath();
    cout << "Average shortest path (density = 0.2): " << avg1 << endl;

    MonteCarloSimulator sim2(nodes, 0.4, minDist, maxDist);
    double avg2 = sim2.averageShortestPath();
    cout << "Average shortest path (density = 0.4): " << avg2 << endl;

    return 0;
}


/* 200 word explanation of what was learned.*/

/* In this project, a Monte Carlo simulation was conducted to compute the average shortest path length from
randomly generated graphs using Dijkstra’s algorithm. The graph is represented using an adjacency 
list for efficiency, like sparse graphs. A Graph class manages vertex data structures and 
an edge list with weights. Dijkstra’s algorithm was implemented in a static method that uses a priority queue to 
find the shortest paths efficiently. The MonteCarloSimulator class generates random graphs based on a given edge 
density and distance range. It computes the path lengths from node 0 to other reachable nodes. If a node 
is unreachable, it is excluded from the average path length. The simulation was tested using 50 nodes with densities 
of 0.2 and 0.4. From this project, I learned about the balance between graph density and connectivity and how it affects 
pathfinding algorithms. Additionally, I understood the importance of class design, random number generation, 
and efficient data structures in C++. It was insightful to see how graph structure impacts algorithm 
performance and connectivity in real-world applications.*/
