#include <bits/stdc++.h>
using namespace std;

using ll = long long;
constexpr ll INF = 1e18;

class Graph
{
private:
    int n;
    vector<vector<pair<int, ll>>> adj;

public:
    explicit Graph(int nodes) : n(nodes), adj(nodes + 1) {}

    void addEdge(int u, int v, ll w)
    {
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    vector<ll> dijkstra(int source) const
    {
        vector<ll> dist(n + 1, INF);
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;

        dist[source] = 0;
        pq.emplace(0, source);

        while (!pq.empty())
        {
            auto [d, u] = pq.top();
            pq.pop();

            if (d > dist[u])
                continue;

            for (auto [v, w] : adj[u])
            {
                ll newDist = d + w;
                if (newDist < dist[v])
                {
                    dist[v] = newDist;
                    pq.emplace(newDist, v);
                }
            }
        }
        return dist;
    }
};

struct Input
{
    int n, m, k;
    ll startFuel, capacity;
    vector<tuple<int, int, ll>> edges;
    vector<int> stations;

    static Input read()
    {
        Input in;
        cin >> in.n >> in.m;

        in.edges.resize(in.m);
        for (auto &[u, v, w] : in.edges)
        {
            cin >> u >> v >> w;
        }

        cin >> in.k >> in.startFuel >> in.capacity;

        in.stations.resize(in.k);
        for (int &s : in.stations)
        {
            cin >> s;
        }

        return in;
    }
};

ll solve(const Input &in)
{
    // Build graph
    Graph graph(in.n);
    for (auto [u, v, w] : in.edges)
    {
        graph.addEdge(u, v, w);
    }

    // Compute shortest paths
    auto distFromStart = graph.dijkstra(1);
    auto distToEnd = graph.dijkstra(in.n);

    ll answer = INF;

    // Case 1: Direct path without refueling
    if (distFromStart[in.n] <= in.startFuel)
    {
        answer = distFromStart[in.n];
    }

    // Case 2: Path with exactly one refuel stop
    for (int station : in.stations)
    {
        bool canReachStation = distFromStart[station] <= in.startFuel;
        bool canReachEnd = distToEnd[station] <= in.capacity;

        if (canReachStation && canReachEnd)
        {
            ll totalDist = distFromStart[station] + distToEnd[station];
            answer = min(answer, totalDist);
        }
    }

    return answer;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Input input = Input::read();
    ll result = solve(input);

    if (result == INF)
    {
        cout << "nemisarfed\n";
    }
    else
    {
        cout << result << "\n";
    }

    return 0;
}