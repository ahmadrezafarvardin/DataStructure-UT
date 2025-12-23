#include <bits/stdc++.h>
using namespace std;

using ll = long long;
constexpr ll INF = LLONG_MAX / 4;

// State for Dijkstra: has the path visited a fuel station?
enum class FuelState
{
    NOT_VISITED = 0,
    VISITED = 1
};

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

    ll getWaitTime(ll arrivalTime) const
    {
        ll cycle = getCycleLength();
        ll phaseTime = arrivalTime % cycle;

        if (phaseTime < greenDuration)
        {
            return 0;
        }
        return cycle - phaseTime;
    }
};

struct State
{
    ll time;
    int node;
    int fuelVisited; // 0 or 1

    bool operator>(const State &other) const
    {
        return time > other.time;
    }
};

class Graph
{
private:
    int n;
    int destination;
    vector<vector<Edge>> adj;
    vector<TrafficLight> lights;
    vector<bool> isFuelStation;

public:
    explicit Graph(int nodes)
        : n(nodes), destination(nodes), adj(nodes + 1), lights(nodes + 1), isFuelStation(nodes + 1, false) {}

    void addEdge(int u, int v, ll w)
    {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    void setTrafficLight(int node, ll green, ll red)
    {
        lights[node] = {green, red};
    }

    void markAsFuelStation(int node)
    {
        isFuelStation[node] = true;
    }

    ll findShortestPathThroughFuelStation() const
    {
        // dist[node][fuelVisited] = minimum time
        vector<array<ll, 2>> dist(n + 1, {INF, INF});
        priority_queue<State, vector<State>, greater<State>> pq;

        int startState = isFuelStation[1] ? 1 : 0;
        dist[1][startState] = 0;
        pq.push({0, 1, startState});

        while (!pq.empty())
        {
            auto [currentTime, u, fuelVisited] = pq.top();
            pq.pop();

            if (currentTime > dist[u][fuelVisited])
                continue;

            for (const auto &edge : adj[u])
            {
                auto [newTime, newFuelState] = computeTransition(
                    edge, currentTime, fuelVisited);

                if (newTime < dist[edge.to][newFuelState])
                {
                    dist[edge.to][newFuelState] = newTime;
                    pq.push({newTime, edge.to, newFuelState});
                }
            }
        }

        return dist[destination][1];
    }

private:
    pair<ll, int> computeTransition(const Edge &edge, ll currentTime, int fuelVisited) const
    {
        int v = edge.to;
        ll arrivalTime = currentTime + edge.weight;

        // Apply traffic light delay (except at destination)
        if (v != destination)
        {
            arrivalTime += lights[v].getWaitTime(arrivalTime);
        }

        // Update fuel station state
        int newFuelState = fuelVisited | static_cast<int>(isFuelStation[v]);

        return {arrivalTime, newFuelState};
    }
};

class InputReader
{
public:
    struct ProblemInput
    {
        int n, m, k;
        vector<tuple<int, int, ll>> edges;
        vector<int> fuelStations;
        vector<pair<ll, ll>> trafficLights;
    };

    static ProblemInput read()
    {
        ProblemInput input;

        // Read graph structure
        cin >> input.n >> input.m;
        input.edges.resize(input.m);
        for (auto &[u, v, w] : input.edges)
        {
            cin >> u >> v >> w;
        }

        // Read fuel stations
        cin >> input.k;
        input.fuelStations.resize(input.k);
        for (int &station : input.fuelStations)
        {
            cin >> station;
        }

        // Read traffic lights
        input.trafficLights.resize(input.n + 1);
        for (int i = 1; i <= input.n; i++)
        {
            cin >> input.trafficLights[i].first >> input.trafficLights[i].second;
        }

        return input;
    }
};

Graph buildGraph(const InputReader::ProblemInput &input)
{
    Graph graph(input.n);

    // Add edges
    for (const auto &[u, v, w] : input.edges)
    {
        graph.addEdge(u, v, w);
    }

    // Mark fuel stations
    for (int station : input.fuelStations)
    {
        graph.markAsFuelStation(station);
    }

    // Set traffic lights
    for (int i = 1; i <= input.n; i++)
    {
        auto [green, red] = input.trafficLights[i];
        graph.setTrafficLight(i, green, red);
    }

    return graph;
}

void printResult(ll shortestTime)
{
    if (shortestTime == INF)
    {
        cout << -1 << '\n';
    }
    else
    {
        cout << shortestTime << '\n';
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    auto input = InputReader::read();
    Graph graph = buildGraph(input);

    ll result = graph.findShortestPathThroughFuelStation();
    printResult(result);

    return 0;
}