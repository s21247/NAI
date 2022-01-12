#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <climits>
#include <functional>

using namespace std;

class Graph {
    vector<vector<int>> matrix;
public:
    Graph(int size = 5) : matrix(size, vector<int>(size, 0)) {

    }


    void add_edge(int u, int v, int weight = 1) {
        matrix.at(u).at(v) = weight;
        matrix.at(v).at(u) = weight;
    }

    static void printSolution(vector<int> &dist) {

        cout << "Vertex \t Distance from Source" << endl;
        for (int i = 0; i < dist.size(); i++)
            cout << i << " \t\t" << dist[i] << endl;
    }

    //dijkstra
    static int minDistance(vector<int> &dist, vector<bool> &visit) // finding minimum distance
    {
        int min = INT_MAX, min_index;

        for (int v = 0; v < dist.size(); v++)
            if (!visit[v] && dist[v] <= min)
                min = dist[v], min_index = v;

        return min_index;
    }

    void dijkstra(int src, int target) {
        int visitNodes = 0;
        int len = matrix.size();
        vector<int> dist(len, INT_MAX);
        vector<bool> visit(len, false);
        dist[src] = 0;
        for (int count = 0; count < len - 1; count++) {
            int u = minDistance(dist, visit);
            if (u == target) {
                break;
            }
            visit[u] = true;
            for (int v = 0; v < len; v++)
                if (!visit[v] && matrix[u][v] && dist[u] != INT_MAX
                    && dist[u] + matrix[u][v] < dist[v])
                    dist[v] = dist[u] + matrix[u][v];
        }
        for (auto &&i: visit) {
            if (i) {
                visitNodes++;
            }
        }
        cout << "\nDijkstra" << endl;
        cout << "Visited nodes:" << visitNodes << endl;
        printSolution(dist);
    }

    //A*
    static int minDistanceAStar(vector<int> &dist, vector<bool> &visit, int target, function<int(int, int)> f) {
        int min = INT_MAX, min_index;

        for (int v = 0; v < dist.size(); v++)
            if (!visit[v] && dist[v] <= min - f(v, target))
                min = dist[v], min_index = v;

        return min_index;
    }

    void A_star(int src, int target, function<int(int, int)> f) {
        int visitNodes = 0;
        int len = matrix.size();
        vector<int> dist(len, INT_MAX);
        vector<bool> visit(len, false);

        dist[src] = 0;
        for (int count = 0; count < len - 1; count++) {
            int u = minDistanceAStar(dist, visit, target, f);
            if (u == target) {
                break;
            }
            visit[u] = true;
            for (int v = 0; v < len; v++) {
                if (!visit[v] && matrix[u][v] && dist[u] != INT_MAX
                    && dist[u] + matrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + matrix[u][v];
                }

            }
        }
        for (auto &&i: visit) {
            if (i) {
                visitNodes++;
            }
        }
        cout << "\nA star" << endl;
        cout << "Visited nodes:" << visitNodes << endl;
        printSolution(dist);
    }

};

Graph readFromFile(const string &filename) {
    ifstream inputdata;

    inputdata.open(filename);
    if (!inputdata) {
        cerr << "Error: file could not be opened" << endl;
        exit(1);
    }
    string s;
    getline(inputdata, s);
    Graph graph(25);
    while (true) {
        getline(inputdata, s);
        if (s[0] == '}') {
            break;
        } else {
            regex linePattern(R"( +(\d+)--(\d+) \[weight=(\d+)\])");
            smatch matches;

            if (regex_search(s, matches, linePattern)) {
                graph.add_edge(stoi(matches[1]), stoi(matches[2]), stoi(matches[3]));
            } else {
                throw invalid_argument("Nothing matches");
            }
        }
    }
    inputdata.close();
    return graph;
}

int main() {
    string filename;
    cout << "File name: " << endl;
    cin >> filename;
    Graph graph = readFromFile(filename);
    if (filename == "demo.dot") {
        graph.dijkstra(0, 2);
        graph.A_star(0, 2, [](int, int) { return 0; });
    } else if (filename == R"(C:\Users\wojte\Desktop\cos\NAI\Zaj11\a_demo.dot)") {
        graph.dijkstra(0, 24);
        graph.A_star(0, 24, [](int v1, int v2) {
            int x = v1 / 5;
            int y = v1 % 5;
            int x2 = v2 / 5;
            int y2 = v2 % 5;
            return abs(x - x2) + abs(y - y2);
        });
    }
    return 0;
}

