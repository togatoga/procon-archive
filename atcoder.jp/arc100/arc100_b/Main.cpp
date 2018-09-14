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
const int MAX_N = 200010;
int N;
vector<ll> A;
ll sum[MAX_N];
ll query(int l, int r)
{
  return sum[r] - sum[l - 1];
}

int calc(const int left, const int right)
{
  int l = left;
  int r = right;

  while (r - l > 1)
  {
    int med = (r + l) / 2;
    // cerr << "l = " << l << " r = " << r << " med = " << med << endl;
    ll sum_left = query(left, med);
    ll sum_right = query(med + 1, right);
    if (med < left)
    {
      l = med;
      continue;
    }
    if (med + 1 > right)
    {
      r = med;
      continue;
    }
    if (sum_left >= sum_right)
    {
      r = med;
    }
    else
    {
      l = med;
    }
  }
  ll res1 = abs(query(left, r) - query(r + 1, right));

  ll med = (l + r) / 2;
  ll res2 = abs(query(left, med) - query(med + 1, right));
  if (res1 > res2)
  {
    return med;
  }
  return r;
}

ll solve()
{
  ll result = LL_INF;
  for (int med_id = 2; med_id <= N - 2; med_id++)
  {
    int a = calc(1, med_id);
    int b = calc(med_id + 1, N);
    ll min_val = LL_INF;
    ll max_val = -LL_INF;

    ll P = query(1, a);
    min_val = min(min_val, P);
    max_val = max(max_val, P);

    ll Q = query(a + 1, med_id);
    min_val = min(min_val, Q);
    max_val = max(max_val, Q);

    ll R = query(med_id + 1, b);
    min_val = min(min_val, R);
    max_val = max(max_val, R);

    ll S = query(b + 1, N);
    min_val = min(min_val, S);
    max_val = max(max_val, S);

    result = min(result, abs(max_val - min_val));
    // cerr << med_id << " " << a << " " << b << endl;
    // cerr << P << " " << Q << " " << R << " " << S << " " << abs(max_val - min_val) << endl;
    // cerr << endl;
  }
  return result;
}
int main()
{
  cin >> N;
  A.resize(N);
  for (auto &val : A)
  {
    cin >> val;
  }
  for (int i = 1; i <= N; i++)
  {
    sum[i] = A[i - 1];
  }
  for (int i = 1; i < MAX_N - 1; i++)
  {
    sum[i] += sum[i - 1];
  }
  cout << solve() << endl;
  return 0;
}
