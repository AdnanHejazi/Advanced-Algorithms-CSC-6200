#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <unordered_map>

using namespace std;

const int INF = numeric_limits<int>::max();

class Graph {
public:
    unordered_map<char, vector<pair<char, int>>> adjList;
    
    void addEdge(char u, char v, int weight) {
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight}); // Ensure undirected graph
    }
    
    void displayGraph() {
        cout << "Graph representation:\n";
        for (const auto& node : adjList) {
            cout << node.first << " -> ";
            for (const auto& neighbor : node.second) {
                cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
            }
            cout << "\n";
        }
        cout << "\n";
    }
    
    void dijkstra(char start, char end) {
        if (adjList.find(start) == adjList.end() || adjList.find(end) == adjList.end()) {
            cout << "Error: One or both of the specified nodes do not exist in the graph.\n";
            return;
        }

        unordered_map<char, int> dist;
        unordered_map<char, char> parent;
        priority_queue<pair<int, char>, vector<pair<int, char>>, greater<pair<int, char>>> pq;
        
        for (auto& node : adjList) {
            dist[node.first] = INF;
        }
        
        dist[start] = 0;
        pq.push({0, start});
        
        while (!pq.empty()) {
            char u = pq.top().second;
            int currDist = pq.top().first;
            pq.pop();
            
            if (currDist > dist[u]) continue;
            
            for (auto& neighbor : adjList[u]) {
                char v = neighbor.first;
                int weight = neighbor.second;
                
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
        
        // Print shortest path
        if (dist[end] == INF) {
            cout << "No path from " << start << " to " << end << "\n";
            return;
        }
        
        cout << "Shortest path cost from " << start << " to " << end << " is " << dist[end] << endl;
        cout << "Path: " << endl;
        vector<char> path;
        char at = end;
        while (at != start) {
            path.push_back(at);
            at = parent[at];
        }
        path.push_back(start);
        
        for (int i = path.size() - 1; i >= 0; --i) {
            cout << path[i] << (i == 0 ? "\n" : " -> ");
        }
    }
};

int main() {
    Graph g;
    g.addEdge('A', 'B', 10);
    g.addEdge('A', 'E', 3);
    g.addEdge('E', 'B', 1);
    g.addEdge('E', 'D', 2);
    g.addEdge('B', 'C', 2);
    g.addEdge('D', 'C', 7);
    g.addEdge('E', 'C', 8);
    g.addEdge('B', 'E', 4);
    g.addEdge('D', 'B', 9);
    
    g.displayGraph();
    
    while (true) {
        char start, end;
        cout << "Enter 'X' to terminate the program" << endl;
        cout << "Enter starting node (Uppercase):" << endl;
        cin >> start;
        if (start == 'X') break;
        cout << "Enter ending node (Uppercase):" << endl;
        cin >> end;
        
        g.dijkstra(start, end);
    }
    
    cout << "Program exited.\n";
    return 0;
}
