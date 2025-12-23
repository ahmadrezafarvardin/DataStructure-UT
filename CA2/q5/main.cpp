#include <bits/stdc++.h>
using namespace std;

using ll = long long;

class FenwickTree
{
private:
    int size;
    vector<int> tree;

    static int lowbit(int x)
    {
        return x & (-x);
    }

public:
    explicit FenwickTree(int n) : size(n), tree(n + 1, 0) {}

    void add(int index, int delta)
    {
        for (; index <= size; index += lowbit(index))
        {
            tree[index] += delta;
        }
    }

    int prefixSum(int index) const
    {
        int sum = 0;
        for (; index > 0; index -= lowbit(index))
        {
            sum += tree[index];
        }
        return sum;
    }

    int countUpTo(int index) const
    {
        return prefixSum(index);
    }
};

class CoordinateCompressor
{
private:
    vector<ll> sortedValues;

public:
    void addValue(ll value)
    {
        sortedValues.push_back(value);
    }

    void build()
    {
        sort(sortedValues.begin(), sortedValues.end());
        sortedValues.erase(
            unique(sortedValues.begin(), sortedValues.end()),
            sortedValues.end());
    }

    int compress(ll value) const
    {
        auto it = lower_bound(sortedValues.begin(), sortedValues.end(), value);
        return static_cast<int>(it - sortedValues.begin()) + 1; // 1-indexed
    }

    int size() const
    {
        return static_cast<int>(sortedValues.size());
    }
};

struct Query
{
    enum class Type
    {
        INSERT = 1,
        COUNT = 2
    };

    Type type;
    ll value;

    static Query read()
    {
        int t;
        ll v;
        cin >> t >> v;
        return {static_cast<Type>(t), v};
    }

    bool isInsert() const { return type == Type::INSERT; }
    bool isCount() const { return type == Type::COUNT; }
};

class PriceCounter
{
private:
    FenwickTree fenwick;
    const CoordinateCompressor &compressor;

public:
    PriceCounter(int size, const CoordinateCompressor &comp)
        : fenwick(size), compressor(comp) {}

    void insert(ll price)
    {
        int idx = compressor.compress(price);
        fenwick.add(idx, 1);
    }

    int countLessOrEqual(ll price) const
    {
        int idx = compressor.compress(price);
        return fenwick.countUpTo(idx);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read all queries
    int q;
    cin >> q;

    vector<Query> queries(q);
    CoordinateCompressor compressor;

    for (int i = 0; i < q; i++)
    {
        queries[i] = Query::read();
        compressor.addValue(queries[i].value);
    }

    // Build coordinate compression
    compressor.build();

    // Process queries
    PriceCounter counter(compressor.size(), compressor);

    for (const auto &query : queries)
    {
        if (query.isInsert())
        {
            counter.insert(query.value);
        }
        else
        {
            cout << counter.countLessOrEqual(query.value) << '\n';
        }
    }

    return 0;
}