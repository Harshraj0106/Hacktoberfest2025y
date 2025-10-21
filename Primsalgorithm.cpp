#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Structure to represent an edge in the graph
struct Edge {
    int to;
    int weight;

    // Custom comparator for priority queue (min-heap)
    bool operator>(const Edge& other) const {
        return weight > other.weight;
    }
};

// Function to implement Prim's algorithm
void primMST(int V, const vector<vector<Edge>>& adj) {
    // Priority queue to store edges, ordered by weight (min-heap)
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;

    // Vector to keep track of visited vertices
    vector<bool> visited(V, false);

    // Vector to store the parent of each node in the MST
    vector<int> parent(V, -1);

    // Vector to store the minimum weight to reach a vertex
    vector<int> key(V, INT_MAX);

    // Start Prim's algorithm from vertex 0
    key[0] = 0;
    pq.push({0, 0}); // {weight, to_node}

    int mstWeight = 0;

    while (!pq.empty()) {
        int u = pq.top().to;
        int weight_u = pq.top().weight;
        pq.pop();

        if (visited[u]) {
            continue;
        }

        visited[u] = true;
        mstWeight += weight_u;

        // Explore neighbors of u
        for (const Edge& edge : adj[u]) {
            int v = edge.to;
            int weight_uv = edge.weight;

            if (!visited[v] && weight_uv < key[v]) {
                key[v] = weight_uv;
                parent[v] = u;
                pq.push({v, key[v]}); // Push {to_node, weight}
            }
        }
    }

    cout << "Minimum Spanning Tree Edges:" << endl;
    for (int i = 1; i < V; ++i) { // Start from 1 as 0 is the root
        if (parent[i] != -1) {
            cout << parent[i] << " - " << i << " (Weight: " << key[i] << ")" << endl;
        }
    }
    cout << "Total MST Weight: " << mstWeight << endl;
}

int main() {
    int V = 5; // Number of vertices
    vector<vector<Edge>> adj(V);

    // Add edges to the graph (example)
    adj[0].push_back({1, 2});
    adj[1].push_back({0, 2});

    adj[0].push_back({2, 1});
    adj[2].push_back({0, 1});

    adj[1].push_back({2, 1});
    adj[2].push_back({1, 1});

    adj[2].push_back({3, 2});
    adj[3].push_back({2, 2});

    adj[3].push_back({4, 1});
    adj[4].push_back({3, 1});

    adj[4].push_back({2, 2});
    adj[2].push_back({4, 2});

    primMST(V, adj);

    return 0;
}
