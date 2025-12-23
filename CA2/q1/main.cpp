#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 200005;
constexpr int LOG = 20;
constexpr int INF = INT_MAX;

//  Data Structures

struct Edge
{
    int u, v, weight;

    bool operator>(const Edge &other) const
    {
        return weight > other.weight;
    }
};

class DisjointSetUnion
{
private:
    vector<int> parent;

public:
    explicit DisjointSetUnion(int n) : parent(n + 1)
    {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x)
    {
        if (parent[x] == x)
            return x;
        return parent[x] = find(parent[x]);
    }

    bool unite(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX == rootY)
            return false;
        parent[rootX] = rootY;
        return true;
    }

    bool connected(int x, int y)
    {
        return find(x) == find(y);
    }
};

//  Maximum Spanning Tree

class MaximumSpanningTree
{
private:
    int n;
    vector<vector<pair<int, int>>> adj;

public:
    explicit MaximumSpanningTree(int nodes) : n(nodes), adj(nodes + 1) {}

    void build(vector<Edge> &edges)
    {
        sort(edges.begin(), edges.end(), greater<Edge>());
        DisjointSetUnion dsu(n);

        for (const auto &edge : edges)
        {
            if (dsu.unite(edge.u, edge.v))
            {
                adj[edge.u].emplace_back(edge.v, edge.weight);
                adj[edge.v].emplace_back(edge.u, edge.weight);
            }
        }
    }

    const vector<vector<pair<int, int>>> &getTree() const
    {
        return adj;
    }
};

//  LCA with Bottleneck

class LowestCommonAncestor
{
private:
    int n;
    const vector<vector<pair<int, int>>> &tree;

    int parent[LOG][MAXN];
    int minEdge[LOG][MAXN];
    int depth[MAXN];

public:
    LowestCommonAncestor(int nodes, const vector<vector<pair<int, int>>> &treeAdj)
        : n(nodes), tree(treeAdj)
    {

        memset(depth, 0, sizeof(depth));
        memset(parent, 0, sizeof(parent));
        for (int i = 0; i < LOG; i++)
        {
            fill(minEdge[i], minEdge[i] + MAXN, INF);
        }
    }

    void preprocess()
    {
        buildTree();
        buildBinaryLifting();
    }

    int getBottleneck(int u, int v) const
    {
        if (u == v)
            return INF;

        int bottleneck = INF;

        // Equalize depths
        if (depth[u] < depth[v])
            swap(u, v);
        bottleneck = liftToSameDepth(u, v, bottleneck);

        if (u == v)
            return bottleneck;

        // Find LCA
        return findLCA(u, v, bottleneck);
    }

private:
    void buildTree()
    {
        for (int i = 1; i <= n; i++)
        {
            if (depth[i] == 0)
            {
                dfs(i, 0, INF);
            }
        }
    }

    void dfs(int u, int par, int edgeWeight)
    {
        parent[0][u] = par;
        minEdge[0][u] = edgeWeight;

        for (auto [v, w] : tree[u])
        {
            if (v == par)
                continue;
            depth[v] = depth[u] + 1;
            dfs(v, u, w);
        }
    }

    void buildBinaryLifting()
    {
        for (int level = 1; level < LOG; level++)
        {
            for (int node = 1; node <= n; node++)
            {
                int ancestor = parent[level - 1][node];
                if (ancestor != 0)
                {
                    parent[level][node] = parent[level - 1][ancestor];
                    minEdge[level][node] = min(
                        minEdge[level - 1][node],
                        minEdge[level - 1][ancestor]);
                }
                else
                {
                    parent[level][node] = 0;
                    minEdge[level][node] = minEdge[level - 1][node];
                }
            }
        }
    }

    int liftToSameDepth(int &u, int v, int currentMin) const
    {
        int diff = depth[u] - depth[v];
        int result = currentMin;

        for (int i = 0; i < LOG; i++)
        {
            if (diff & (1 << i))
            {
                result = min(result, minEdge[i][u]);
                u = parent[i][u];
            }
        }

        return result;
    }

    int findLCA(int &u, int &v, int currentMin) const
    {
        int result = currentMin;

        for (int i = LOG - 1; i >= 0; i--)
        {
            if (parent[i][u] != parent[i][v])
            {
                result = min(result, minEdge[i][u]);
                result = min(result, minEdge[i][v]);
                u = parent[i][u];
                v = parent[i][v];
            }
        }

        result = min(result, minEdge[0][u]);
        result = min(result, minEdge[0][v]);

        return result;
    }
};

//  Truck Management

class TruckFleet
{
private:
    multiset<int> availableTrucks;

public:
    void addTruck(int height)
    {
        availableTrucks.insert(height);
    }

    void removeTruck(int height)
    {
        auto it = availableTrucks.find(height);
        if (it != availableTrucks.end())
        {
            availableTrucks.erase(it);
        }
    }

    int findLargestFitting(int heightLimit) const
    {
        if (availableTrucks.empty())
            return -1;

        auto it = availableTrucks.upper_bound(heightLimit);
        if (it == availableTrucks.begin())
            return -1;

        return *(--it);
    }

    bool isEmpty() const
    {
        return availableTrucks.empty();
    }
};

//  Query System

enum class QueryType
{
    ADD = 1,
    REMOVE = 2,
    ROUTE = 3
};

class FreightRouter
{
private:
    DisjointSetUnion connectivity;
    LowestCommonAncestor lca;
    TruckFleet fleet;

public:
    FreightRouter(int n, MaximumSpanningTree &mst)
        : connectivity(n), lca(n, mst.getTree())
    {

        lca.preprocess();

        // Build connectivity from MST
        for (int u = 1; u <= n; u++)
        {
            for (auto [v, w] : mst.getTree()[u])
            {
                connectivity.unite(u, v);
            }
        }
    }

    void addTruck(int height)
    {
        fleet.addTruck(height);
    }

    void removeTruck(int height)
    {
        fleet.removeTruck(height);
    }

    int findRoute(int source, int destination)
    {
        // Check if route exists
        if (!connectivity.connected(source, destination) || fleet.isEmpty())
        {
            return -1;
        }

        // Find the bottleneck (minimum edge on path)
        int heightLimit = lca.getBottleneck(source, destination);

        // Find tallest truck that can fit through bottleneck
        return fleet.findLargestFitting(heightLimit);
    }
};

//  Main

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    for (auto &e : edges)
    {
        cin >> e.u >> e.v >> e.weight;
    }

    // Build maximum spanning tree
    MaximumSpanningTree mst(n);
    mst.build(edges);

    // Initialize routing system
    FreightRouter router(n, mst);

    // Process queries
    int q;
    cin >> q;

    while (q--)
    {
        int type;
        cin >> type;

        switch (static_cast<QueryType>(type))
        {
        case QueryType::ADD:
        {
            int height;
            cin >> height;
            router.addTruck(height);
            break;
        }
        case QueryType::REMOVE:
        {
            int height;
            cin >> height;
            router.removeTruck(height);
            break;
        }
        case QueryType::ROUTE:
        {
            int u, v;
            cin >> u >> v;
            cout << router.findRoute(u, v) << '\n';
            break;
        }
        }
    }

    return 0;
}