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
const double EPS = 1e-9;
const ll MOD = 1000000007;

const int dx[] = {1, 0, -1, 0}, dy[] = {0, -1, 0, 1};
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

int main()
{
  cin >> N >> M;
  UnionFind ut(N);
  ll result = 0;
  for (int i = 0; i < M; i++)
  {
    int a, b;
    
    cin >> a >> b;
    a--, b--;

    if (ut.is_same(a, b))
    {

      result--;
    }
    ut.unite(a, b);
  }
  vector<ll> values;
  for (int i = 0; i < N; i++)
  {
    if (ut.is_parent(i))
    {
      if (ut.is_same(0, i) or ut.is_same(1, i))
      {
        continue;
      }
      values.push_back(ut.size(i));
    }
  }

  ll res = 0;
  for (const auto &val : values)
  {
    res += val;
    result -= val - 1;
  }
  
  ll a = max(ut.size(0), ut.size(1));
  ll b = min(ut.size(0), ut.size(1));
  res += a;

  result += res * (res - 1) / 2;
  result -= a - 1;

  result += b * (b - 1) / 2;
  result -= b - 1;

  cout << result << endl;

  return 0;
}
