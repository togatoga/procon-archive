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
template <class T>
using max_priority_queue = priority_queue<T>;
template <class T>
using min_priority_queue = priority_queue<T, std::vector<T>, std::greater<T>>;

const int INF = 1 << 29;
const ll LL_INF = 1LL << 60;
const double EPS = 1e-9;
const ll MOD = 1000000007;

const int dx[] = {1, 0, -1, 0}, dy[] = {0, -1, 0, 1};
const int MAX_N = 100010;

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

int N;
vector<tuple<pii, int>> YX, XY;
set<int> Y, X;
int get_cost(const pii p, const pii q)
{
    return min(abs(p.first - q.first), abs(p.second - q.second));
}
int main()
{
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        int x, y;
        cin >> x >> y;
        YX.emplace_back(mt(mp(y, x), i));
        XY.emplace_back(mt(mp(x, y), i));
    }
    sort(YX.begin(), YX.end());
    sort(XY.begin(), XY.end());
    min_priority_queue<pair<int, pii>> min_que;
    for (int i = 0; i < N; i++)
    {

        const pii yx_p = get<0>(YX[i]);
        const int yx_idx = get<1>(YX[i]);

        const pii xy_p = get<0>(XY[i]);
        const int xy_idx = get<1>(XY[i]);
        if (i - 1 >= 0)
        {
            int yx_c1 = get_cost(yx_p, get<0>(YX[i - 1]));
            min_que.emplace(mp(yx_c1, mp(yx_idx, get<1>(YX[i - 1]))));
            int xy_c1 = get_cost(xy_p, get<0>(XY[i - 1]));
            min_que.emplace(mp(xy_c1, mp(xy_idx, get<1>(XY[i - 1]))));
        }
        if (i + 1 < N)
        {
            int yx_c2 = get_cost(yx_p, get<0>(YX[i + 1]));
            min_que.emplace(mp(yx_c2, mp(yx_idx, get<1>(YX[i + 1]))));
            int xy_c2 = get_cost(xy_p, get<0>(XY[i + 1]));
            min_que.emplace(mp(xy_c2, mp(xy_idx, get<1>(XY[i + 1]))));
        }
    }
    UnionFind ut(N);
    ll res = 0;

    while (ut.size(0) < N)
    {
        auto p = min_que.top();
        min_que.pop();
        int cost = p.first;
        pii indices = p.second;

        if (!ut.is_same(indices.first, indices.second))
        {
            ut.unite(indices.first, indices.second);
            res += cost;
        }
    }
    cout << res << endl;
    return 0;
}
