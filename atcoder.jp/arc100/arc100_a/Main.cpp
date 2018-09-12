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

const ll INF = 1LL << 40;
const ll LL_INF = 1LL << 60;
const double EPS = 1e-9;
const ll MOD = 1000000007;

const int dx[] = {1, 0, -1, 0}, dy[] = {0, -1, 0, 1};
int N, K;
vector<ll> A;

ll calc(ll b)
{
  ll res = 0;
  for (int i = 0; i < N; i++)
  {
    res += abs(A[i] - (b + i + 1));
  }
  return res;
}

template <class Function>
double ternarySearch(ll l, ll r, Function f)
{
  for (int i = 0; i < 200; i++)
  {
    // cerr << "l = " << l << " r = " << r << endl;
    ll a = (l + l + r) / 3;
    ll b = (l + r + r) / 3;
    if (f(a) > f(b))
      l = a;
    else
      r = b;
  }
  return l;
}
int main()
{
  cin >> N;
  A.resize(N);
  for (auto &val : A)
  {
    cin >> val;
  }
  ll left = -INF;
  ll right = INF;
  ll b = ternarySearch(left, right, calc);
  // cerr << "b = " << b << endl;
  cout << calc(b + 1) << endl;
  return 0;
}
