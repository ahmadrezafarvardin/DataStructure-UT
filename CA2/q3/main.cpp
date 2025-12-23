#include <bits/stdc++.h>
using namespace std;

using ll = long long;
constexpr ll INF = LLONG_MAX / 4;

struct Edge
{
    int to;
    ll weight;
};

struct TrafficLight
{
    ll greenDuration;
    ll redDuration;

    ll getCycleLength() const
    {
        return greenDuration + redDuration;
    }

    bool isGreen(ll time) const
    {
        return (time % getCycleLength()) < greenDuration;
    }

    ll getWaitTime(ll arrivalTime) const
    {
        ll cycle = getCycleLength();
        ll phaseTime = arrivalTime % cycle;

        if (phaseTime < greenDuration)
        {
            return 0; // Already green
        }
        return cycle - phaseTime; // Wait for next green
    }
};

class Graph
{
private:
    int n;
    vector<vector<Edge>> adj;
    vector<TrafficLight> lights;

public:
    explicit Graph(int nodes) : n(nodes), adj(nodes + 1), lights(nodes + 1) {}

    void addEdge(int u, int v, ll w)
    {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    void setTrafficLight(int node, ll green, ll red)
    {
        lights[node] = {green, red};
    }

    ll findShortestPath(int source, int destination) const
    {
        vector<ll> dist(n + 1, INF);
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;

        dist[source] = 0;
        pq.emplace(0, source);

        while (!pq.empty())
        {
            auto [currentTime, u] = pq.top();
            pq.pop();

            if (currentTime > dist[u])
                continue;

            for (const auto &edge : adj[u])
            {
                ll departureTime = calculateDepartureTime(u, currentTime, source);
                ll arrivalTime = departureTime + edge.weight;

                if (arrivalTime < dist[edge.to])
                {
                    dist[edge.to] = arrivalTime;
                    pq.emplace(arrivalTime, edge.to);
                }
            }
        }

        return dist[destination];
    }

private:
    ll calculateDepartureTime(int node, ll currentTime, int source) const
    {
        // No waiting at the source node
        if (node == source)
        {
            return currentTime;
        }
        return currentTime + lights[node].getWaitTime(currentTime);
    }
};

struct Input
{
    int n, m;
    vector<tuple<int, int, ll>> edges;
    vector<pair<ll, ll>> trafficLights; // {green, red} for each node

    static Input read()
    {
        Input in;
        cin >> in.n >> in.m;

        in.edges.resize(in.m);
        for (auto &[u, v, w] : in.edges)
        {
            cin >> u >> v >> w;
        }

        in.trafficLights.resize(in.n + 1);
        for (int i = 1; i <= in.n; i++)
        {
            cin >> in.trafficLights[i].first >> in.trafficLights[i].second;
        }

        return in;
    }
};

Graph buildGraph(const Input &input)
{
    Graph graph(input.n);

    for (const auto &[u, v, w] : input.edges)
    {
        graph.addEdge(u, v, w);
    }

    for (int i = 1; i <= input.n; i++)
    {
        auto [green, red] = input.trafficLights[i];
        graph.setTrafficLight(i, green, red);
    }

    return graph;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Input input = Input::read();
    Graph graph = buildGraph(input);

    ll shortestTime = graph.findShortestPath(1, input.n);
    cout << shortestTime << '\n';

    return 0;
}