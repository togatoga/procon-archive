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
#include <vector>

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
int N, M;
vector<pii> XY;
vector<int> P;
int main()
{
    cin >> N >> M;
    P.resize(N);
    for (auto &val : P)
    {
        cin >> val;
        val--;
    }
    XY.resize(M);
    UnionFind ut(N);
    for (auto &val : XY)
    {
        cin >> val.first >> val.second;
        val.first--;
        val.second--;
        ut.unite(val.first, val.second);
    }
    int res = 0;
    for (int i = 0; i < N; i++)
    {
        int a = P[i];
        int b = i;
        if (ut.is_same(a, b))
        {
            res++;
        }
    }
    cout << res << endl;
    return 0;
}
