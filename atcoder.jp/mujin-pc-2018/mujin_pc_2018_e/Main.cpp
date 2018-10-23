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
int N, M, K;
string D;
const int MAX_NM = 1010;
char board[MAX_NM][MAX_NM];
ll dist_costs[MAX_NM][MAX_NM];
pii src, dst;
// map<int, pii> costs[4]; //(idx, (idx, cost))
pair<int, ll> costs[4][100010];
void init()
{
  cin >> N >> M >> K;
  cin >> D;
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < M; j++)
    {
      cin >> board[i][j];
      if (board[i][j] == 'S')
      {
        src = mp(i, j);
      }
      if (board[i][j] == 'G')
      {
        dst = mp(i, j);
      }
    }
  }
  for (int i = 0; i < MAX_NM; i++)
  {
    for (int j = 0; j < MAX_NM; j++)
    {
      dist_costs[i][j] = LL_INF;
    }
  }
}
const int LIMIT = INF - 3 * 100010;
int main()
{
  init();
  string D2 = D + D;
  ll r, u, l, d;
  r = u = l = d = LL_INF;

  for (int i = D2.size() - 1; i >= 0; i--)
  {
    if (D2[i] == 'R')
    {

      r = i;
    }
    else if (D2[i] == 'U')
    {

      u = i;
    }
    else if (D2[i] == 'L')
    {

      l = i;
    }
    else if (D2[i] == 'D')
    {
      d = i;
    }
    costs[0][i % K] = mp(r % K, (r - i));
    costs[1][i % K] = mp(u % K, (u - i));
    costs[2][i % K] = mp(l % K, (l - i));
    costs[3][i % K] = mp(d % K, (d - i));
  }
  min_priority_queue<tuple<ll, ll, pii>> que;
  que.emplace(mt(0, 0, mp(src.first, src.second)));
  while (not que.empty())
  {
    auto p = que.top();
    que.pop();
    ll cost;
    ll idx;
    pii pos;
    tie(cost, idx, pos) = p;
    if (pos == dst)
    {
      cout << cost << endl;
      return 0;
    }
    const int py = pos.first;
    const int px = pos.second;
    if (dist_costs[py][px] <= cost)
    {
      continue;
    }
    dist_costs[py][px] = cost;
    for (int i = 0; i < 4; i++)
    {
      const int ny = py + dy[i];
      const int nx = px + dx[i];
      if (ny < 0 || ny >= N || nx < 0 || nx >= M)
      {
        continue;
      }
      if (board[ny][nx] == '#')
      {
        continue;
      }
      if (costs[i][idx].second >= LIMIT)
      {
        continue;
      }
      const int nxt_idx = (costs[i][idx].first + 1) % K;
      const ll nxt_cost = cost + costs[i][idx].second + 1;
      if (dist_costs[ny][nx] <= nxt_cost)
      {
        continue;
      }
      que.emplace(mt(nxt_cost, nxt_idx, mp(ny, nx)));
    }
  }
  cout << -1 << endl;
  return 0;
}
