// Disjoint Set Union (DSU) with Path Compression
// Supports union by size OR union by rank
// Author : Samin Yasar

#include <bits/stdc++.h>
using namespace std;

class DSU
{
    vector<int> parent;
    vector<int> size;              // Size of each set (for union by size)
    vector<int> rank;              // Approx height of tree (for union by rank)

public:
    // Constructor: initialize DSU with n elements (0 to n-1)
    DSU(int n)
    {
        parent.resize(n);
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;           // each element is its own parent initially
        }
        size.assign(n, 1);           // each set has size 1 initially
        rank.assign(n, 0);           // height (rank) is 0 initially
    }

    // Find the representative (leader) of set containing u
    // Uses path compression for efficiency
    int findSet(int u)
    {
        if (u != parent[u])
        {
            parent[u] = findSet(parent[u]);    // path compression
        }
        return parent[u];
    }

    // Union by size: attach smaller set to larger set
    void unionSetBySize(int u, int v)
    {
        int a = findSet(u), b = findSet(v);
        if (a != b)
        {
            if (size[a] < size[b])
            {
                swap(a, b);              // ensure a is bigger
            }
            parent[b] = a;
            size[a] += size[b];
        }
    }

    // Union by rank: attach shorter tree under taller tree
    void unionSetByRank(int u, int v)
    {
        int a = findSet(u), b = findSet(v);
        if (a != b)
        {
            if (rank[a] < rank[b])
            {
                swap(a, b);              // ensure a has larger/equal rank
            }
            parent[b] = a;
            if (rank[a] == rank[b])
            {
                rank[a]++;               // if same height, increase rank
            }
        }
    }

    // Check if two nodes are in the same set
    bool connected(int u, int v)
    {
        return findSet(u) == findSet(v);
    }
};

int main()
{
    DSU dsu(7); // 7 elements (0 to 6)

    // Test union by size
    cout << "Using union by size:\n";
    dsu.unionSetBySize(0, 1);
    dsu.unionSetBySize(1, 2);
    dsu.unionSetBySize(3, 4);

    cout << "Are 0 and 2 connected? " << (dsu.connected(0, 2) ? "Yes" : "No") << "\n"; // Yes
    cout << "Are 0 and 4 connected? " << (dsu.connected(0, 4) ? "Yes" : "No") << "\n"; // No

    dsu.unionSetBySize(2, 4); // Merge sets {0,1,2} and {3,4}
    cout << "After merging 2 and 4, are 0 and 4 connected? "
         << (dsu.connected(0, 4) ? "Yes" : "No") << "\n"; // Yes

    // Test union by rank (fresh DSU)
    cout << "\nUsing union by rank:\n";
    DSU dsu2(5);
    dsu2.unionSetByRank(0, 1);
    dsu2.unionSetByRank(2, 3);
    dsu2.unionSetByRank(1, 2);

    cout << "Are 0 and 3 connected? " << (dsu2.connected(0, 3) ? "Yes" : "No") << "\n"; // Yes
    cout << "Are 0 and 4 connected? " << (dsu2.connected(0, 4) ? "Yes" : "No") << "\n"; // No

    return 0;
}


// Output :
// Using union by size:
// Are 0 and 2 connected? Yes
// Are 0 and 4 connected? No
// After merging 2 and 4, are 0 and 4 connected? Yes

// Using union by rank:
// Are 0 and 3 connected? Yes
// Are 0 and 4 connected? No