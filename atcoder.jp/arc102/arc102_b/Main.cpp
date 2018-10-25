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
ll L;
const int MAX_N = 20;
vector<pii> edges[MAX_N];
int pow2[MAX_N + 10];
int get_pow2_idx(int L)
{
  if (L == 1)
  {
    return 0;
  }
  int idx = 0;
  int p = 1;
  while (p <= L)
  {
    idx++;
    p *= 2;
  }
  return idx - 1;
}
void init()
{
  pow2[0] = 1;
  for (int i = 1; i < MAX_N + 5; i++)
  {
    pow2[i] = 2 * pow2[i - 1];
  }
}

int main()
{
  init();
  cin >> L;
  for (int i = 0; i < MAX_N - 1; i++)
  {
    edges[i].push_back(mp(i + 1, 0));
  }
  int p = 1;
  ll tmp_L = L - 1;
  int base = 0;
  for (int i = MAX_N - 1; i >= 1; i--)
  {
    if (tmp_L - p < 0)
    {
      break;
    }
    tmp_L -= p;
    edges[i - 1].push_back(mp(i, p));
    base += p;
    p *= 2;
  }
  while (tmp_L > 0)
  {

    int sum = 1;
    int idx = 0;
    for (int i = 1; i < MAX_N; i++)
    {
      if (2 * sum > tmp_L)
      {
        break;
      }
      sum *= 2;
      idx = i;
    }
    cerr << "tmp_L = " << tmp_L << " base = " << base << " idx = " << idx << " sum = " << sum << endl;
    edges[0].push_back(mp(MAX_N - 1 - idx, base + 1));
    tmp_L -= sum;
    base += sum;
  }
  int M = 0;
  for (int i = 0; i < MAX_N; i++)
  {
    M += edges[i].size();
  }
  cout << MAX_N << " " << M << endl;
  for (int i = 0; i < MAX_N; i++)
  {
    for (int j = 0; j < edges[i].size(); j++)
    {
      cout << i + 1 << " " << edges[i][j].first + 1 << " " << edges[i][j].second << endl;
    }
  }
  return 0;
}
