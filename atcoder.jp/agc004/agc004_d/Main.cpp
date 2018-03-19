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
int N, K;
const int MAX_N = 100010;
int root;
vector<int> edges[MAX_N];
int ans;

int dfs(int cur, int par)
{
  int m = 0;
  for (auto &val : edges[cur])
  {
    if (val != par)
    {
      m = max(m, dfs(val, cur));
    }
  }
  m++;
  if (cur == 1 or par == 1)
  {
    return 0;
  }
  if (m < K)
  {
    return m;
  }
  ans++;
  return 0;
}
int main()
{
  cin >> N >> K;
  cin >> root;
  for (int i = 1; i < N; i++)
  {
    int a;
    cin >> a;
    edges[a].push_back(i + 1);
    edges[i + 1].push_back(a);
  }
  dfs(1, 0);
  if (root != 1)
  {
    ans++;
  }
  cout << ans << endl;
  return 0;
}
