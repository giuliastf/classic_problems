// A C++ program to find strongly connected components in a
// given directed graph using Tarjan's algorithm (single
// DFS)
#include <bits/stdc++.h>

#define NIL - 1
using namespace std;

// A class that represents an directed graph
class Graph {
 public:
    int V;  // No. of vertices
    list < int > * adj;  // A dynamic array of adjacency lists
    vector < vector < int >> parents;
    // A Recursive DFS based function used by SCC()
    void SCCUtil(int u, int disc[], int low[],
        stack < int > * st, bool stackMember[],
		vector < vector < int >> * tarjan);

 public:
    explicit Graph(int V);  // Constructor
    vector < vector < int >> SCC();  // prints strongly connected components
    void addEdge(int v, int w);
    int findMinEdges(int source, vector < vector < int >> tarjan,
	vector < vector < int >> parents);  // New function to find minimum edges
};

Graph::Graph(int V) {
    this -> V = V;
    adj = new list < int > [V];
    parents.resize(V);
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
    parents[w].push_back(v);
}

void Graph::SCCUtil(int u, int disc[], int low[], stack < int > * st,
	bool stackMember[], vector < vector < int >> * tarjan) {
    // A static variable is used for simplicity, we can
    // avoid use of static variable by passing a pointer.
    static int time = 0;

    // Initialize discovery time and low value
    disc[u] = low[u] = ++time;
    st -> push(u);
    stackMember[u] = true;

    // Go through all vertices adjacent to this
    list < int > ::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i) {
        int v = * i;
        if (disc[v] == -1) {
            SCCUtil(v, disc, low, st, stackMember, tarjan);
            low[u] = min(low[u], low[v]);
        } else if (stackMember[v] == true) {
            low[u] = min(low[u], disc[v]);
		}
    }

    int w = 0;  // To store stack extracted vertices
    if (low[u] == disc[u]) {
        vector < int > scc;
        while (st -> top() != u) {
            w = (int) st -> top();
            scc.push_back(w);
            stackMember[w] = false;
            st -> pop();
        }
        w = (int) st -> top();
        scc.push_back(w);
        stackMember[w] = false;
        st -> pop();
        tarjan -> push_back(scc);
    }
}

// The function to do DFS traversal. It uses SCCUtil()
vector < vector < int >> Graph::SCC() {
    int * disc = new int[V];
    int * low = new int[V];
    bool * stackMember = new bool[V];
    stack < int > * st = new stack < int > ();

    // Initialize disc and low, and stackMember arrays
    for (int i = 0; i < V; i++) {
        disc[i] = NIL;
        low[i] = NIL;
        stackMember[i] = false;
    }

    // Call the recursive helper function to find strongly
    // connected components in DFS tree with vertex 'i'
    vector < vector < int >> tarjan;
    for (int i = 0; i < V; i++)
        if (disc[i] == NIL)
            SCCUtil(i, disc, low, st, stackMember, & tarjan);
    return tarjan;
}

int Graph::findMinEdges(int source, vector < vector < int >> tarjan,
	vector < vector < int >> parents) {
    int min = tarjan.size() - 1;
    // O(V) in cel mai rau caz, SCCuri de un nod
    // cele 2 for uri se compenseaza
    for (int i = 0; i < tarjan.size(); i++) {
        if (find(tarjan[i].begin(), tarjan[i].end(), source) != tarjan[i].end())
            continue;
        int found = 0;
        for (int j = 0; j < tarjan[i].size() && found == 0; j++) {
            int node = tarjan[i][j];
            for (int k = 0; k < parents[node].size(); k++) {
                if (find(tarjan[i].begin(), tarjan[i].end(),
				parents[node][k]) == tarjan[i].end()) {
                    min--;
                    found = 1;
                    break;
                }
			}
        }
    }
    return min;
}
int main() {
    ifstream fin("ferate.in");
    ofstream fout("ferate.out");

    int N, M, S;
    fin >> N >> M >> S;

    Graph graph(N);

    for (int i = 0; i < M; i++) {
        int x, y;
        fin >> x >> y;

        graph.addEdge(x - 1, y - 1);
    }
    vector < vector < int >> tarjan = graph.SCC();

    int minEdges = graph.findMinEdges(S - 1, tarjan, graph.parents);
    fout << minEdges;

    return 0;
}
