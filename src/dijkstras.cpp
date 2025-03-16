#include "dijkstras.h"

struct compareweight {
    bool operator()(const pair<int,int>& pair1, const pair<int,int>& pair2) const {
        return pair1.second > pair2.second;
    }
};

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int numVertices = G.size();
    vector<int> distances(numVertices, INF);
    vector<bool> visited(numVertices, false);
    distances[source] = 0;
    previous[source] = UNDEFINED;
    priority_queue<pair<int,int>, vector<pair<int,int>>, compareweight> minHeap; 
    minHeap.push({source, 0});
    while (!minHeap.empty()) {
        int u = minHeap.top().first;
        minHeap.pop();
        if (visited[u]) continue;
        visited[u] = true;
        for (Edge edge: G[u]) {
            int v = edge.dst;
            int weight = edge.weight;
            if (!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({v, distances[v]});
            }
        }
    }
    return distances;
}
vector<int> extract_shortest_path(const vector<int>&, const vector<int>& previous, int destination) {
    vector<int> path;

    for (int i = destination; i != UNDEFINED; i = previous[i]) 
        path.push_back(i);
    reverse(path.begin(), path.end());

    return path;
}

void print_path(const vector<int>& v, int total) {
    for (int i = 0; i < total; ++i)
        std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "Total cost is " << total << std::endl;
}

string get_arg(int argc, char *argv[], string def) {
    return (argc > 1) ? argv[1] : def;
}