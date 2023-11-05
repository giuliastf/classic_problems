#include <bits/stdc++.h>

using namespace std;

// complexitate O(V+E)
void dfs(vector < vector < int >> & graf, int src,
    vector < int > & dfs_nodes,
    vector < int > & descendants) {
    static int idx = 0;
    dfs_nodes[idx] = src;
    idx++;
    vector < int > neigh = graf[src];
    if (!neigh.empty()) {
        for (int n : neigh) {
            dfs(graf, n, dfs_nodes, descendants);
            descendants[src] += descendants[n] + 1;
        }
    }
    return;
}

int main() {
    ifstream fin("magazin.in");
    ofstream fout("magazin.out");

    int N, Q;
    fin >> N >> Q;

    vector < int > parents(N - 1);
    for (int i = 0; i < N - 1; i++) {
        fin >> parents[i];
    }

    vector < vector < int >> adj(N + 1);
    for (int i = 2; i <= N; i++) {
        int dad = parents[i - 2];
        adj[dad].push_back(i);
    }

    vector < int > dfs_nodes(N + 1);  // retin ordinea nodurilor dupa dfs
    vector < int > descendants(N + 1);

    dfs(adj, 1, dfs_nodes, descendants);

    vector < int > dfs_nodes_reversed_indexes(N + 1);
    for (int i = 0; i < N + 1; i++) {
        dfs_nodes_reversed_indexes[dfs_nodes[i]] = i;
    }

    // O(Q)
    for (int i = 0; i < Q; i++) {
        int node, index;
        fin >> node >> index;

        int exp = -1;
        if (index <= descendants[node]) {
            exp = dfs_nodes_reversed_indexes[node] + 1;
            if (exp + index < dfs_nodes.size()) {
                int aux = dfs_nodes[exp + index - 1];
                fout << aux << "\n";
            } else {
                fout << -1 << "\n";
            }
        } else {
            fout << exp << "\n";
        }
    }
    return 0;
}
