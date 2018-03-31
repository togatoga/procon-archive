#include <algorithm>
#include <bitset>
#include <cassert>
#include <cfloat>
#include <climits>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>

// c++11
#include <array>
#include <tuple>
#include <unordered_map>
#include <unordered_set>

#define mp make_pair
#define mt make_tuple
#define rep(i, n) for (int i = 0; i < (n); i++)

using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

const int INF = 1 << 29;
const ll LL_INF = 1LL << 60;
const double EPS = 1e-9;
const ll MOD = 1000000007;

const int dx[] = {1, 0, -1, 0}, dy[] = {0, -1, 0, 1};
const int MAX_N = 100010;
int N, M, Q;
bool visited[MAX_N];
//@verified http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=2757242#1
//LowestCommonAncestor
//init -> lca(a, b)
template <typename T>
class LowestCommonAncestor
{
  public:
    static const int MAX_LOG_V = 30;
    static const int NONE_NODE = -1;
    vector<int> parents[MAX_LOG_V]; // follow parents 2^k times node index (ex parents[k][v] start v follow parents 2^k times)
    vector<int> depths;             //the depth from root.
    vector<int> values[MAX_LOG_V];
    T edges;
    void dfs(int pos, int pre, int depth = 0, int pre_val = 0)
    {

        values[0][pos] = max(values[0][pos], pre_val);
        parents[0][pos] = pre;
        visited[pos] = true;
        depths[pos] = depth;
        for (const auto &nxt : edges[pos])
        {
            if (nxt.first != pre)
            {
                dfs(nxt.first, pos, depth + 1, nxt.second);
            }
        }
    }

    void init(int root_idx, int V, const T &edges)
    {
        this->depths.resize(V);
        this->edges = edges;
        for (int i = 0; i < MAX_LOG_V; i++)
        {
            parents[i].resize(V);
            values[i].resize(V);
        }

        for (int i = 0; i < N; i++)
        {
            if (!visited[i])
            {
                dfs(i, NONE_NODE, 0);
            }
        }

        for (int k = 0; k + 1 < MAX_LOG_V; k++)
        {
            for (int v = 0; v < V; v++)
            {
                if (parents[k][v] == NONE_NODE)
                {
                    parents[k + 1][v] = NONE_NODE;
                    // values[k + 1][v] = max(values[k + 1][v], values[k][v]);
                }
                else
                {
                    parents[k + 1][v] = parents[k][parents[k][v]];
                    int tmp = values[k][parents[k][v]];
                    values[k + 1][v] = max(values[k][v], tmp);
                }
            }
        }
    }
    //O(logN)
    int lca(int u, int v)
    {

        if (depths[u] > depths[v])
        {
            swap(u, v);
        }
        int result = 0;
        // cerr << values[1][2] << endl;
        // cerr << u << " " << v << " " << depths[u] << " " << depths[v] << endl;
        //follow parents by same level.
        for (int k = 0; k < MAX_LOG_V; k++)
        {
            int diff = depths[v] - depths[u];
            if ((diff >> k) & 1)
            {
                result = max(result, values[k][v]);
                // cerr << k << " " << v << " " << values[k][v] << " " << result << endl;
                v = parents[k][v];
                // cerr << u << " " << v << " " << depths[u] << " " << depths[v] << endl;

                // cerr << "depth = " << depths[v] << endl;
            }
        }

        if (u == v)
        {

            // result = max(result, values[0][v]);
            // result = max(result, values[0][u]);
            return result;
        }

        //binary search to find lcm(u, v)
        for (int k = MAX_LOG_V - 1; k >= 0; k--)
        {
            if (parents[k][u] != parents[k][v])
            {
                result = max(result, values[k][v]);
                result = max(result, values[k][u]);
                u = parents[k][u];
                v = parents[k][v];
            }
        }
        result = max(result, values[0][v]);
        result = max(result, values[0][u]);
        return result;
    }
};
//UnionFind
class UnionFind
{
  public:
    UnionFind(int size_) : parent(size_, -1), __size(size_) {}
    void unite(int x, int y)
    {
        if ((x = find(x)) != (y = find(y)))
        {
            if (parent[y] < parent[x])
                std::swap(x, y);
            parent[x] += parent[y];
            parent[y] = x;
            __size--;
        }
    }
    bool is_parent(int x) { return find(x) == x; }
    bool is_same(int x, int y) { return find(x) == find(y); }
    int find(int x) { return parent[x] < 0 ? x : parent[x] = find(parent[x]); }
    int size(int x) { return -parent[find(x)]; }
    int size() const { return __size; }

  private:
    std::vector<int> parent;
    int __size;
};
//UnionFind

vector<vector<pii>> edges;

int main()
{
    cin >> N >> M;
    UnionFind ut(N);
    edges.resize(MAX_N);
    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        a--, b--;
        if (!ut.is_same(a, b))
        {
            edges[a].emplace_back(mp(b, i + 1));
            edges[b].emplace_back(mp(a, i + 1));
            ut.unite(a, b);
        }
    }

    cin >> Q;
    LowestCommonAncestor<vector<vector<pii>>> lca;
    lca.init(0, N, edges);

    for (int i = 0; i < Q; i++)
    {
        int x, y;
        cin >> x >> y;
        x--, y--;
        if (!ut.is_same(x, y))
        {
            cout << -1 << endl;
            continue;
        }
        int res = lca.lca(x, y);
        cout << res << endl;
    }
    return 0;
}
