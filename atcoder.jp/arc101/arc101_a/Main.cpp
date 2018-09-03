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
int N, K;
vector<int> X;
int main()
{
  cin >> N >> K;
  X.resize(N);
  for (auto &val : X)
  {
    cin >> val;
  }
  vector<int> X1, X2;
  for (int i = 0; i < N; i++)
  {
    if (X[i] < 0)
    {
      X1.push_back(X[i]);
    }
    else
    {
      X2.push_back(X[i]);
    }
  }
  reverse(X1.begin(), X1.end());
  ll result = LL_INF;

  for (int i = 0; i < X1.size(); i++)
  {
    int cnt = i + 1;
    ll dist = 2LL * abs(X1[i]);
    if (cnt < K)
    {
      ll rest = K - cnt;
      if (rest > X2.size())
      {
        continue;
      }
      dist += X2[rest - 1];
      result = min(result, dist);
    }
    else
    {
      result = min(result, dist / 2);
    }
  }

  for (int i = 0; i < X2.size(); i++)
  {
    int cnt = i + 1;
    ll dist = 2LL * abs(X2[i]);
    if (cnt < K)
    {
      ll rest = K - cnt;
      if (rest > X1.size())
      {
        continue;
      }
      dist += abs(X1[rest - 1]);
      result = min(result, dist);
    }
    else
    {
      result = min(result, dist / 2);
    }
  }
  cout << result << endl;
  return 0;
}
