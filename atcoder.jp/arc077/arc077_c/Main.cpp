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
const int MAX_N = 100100;
int N, M;
vector<int> A;
ll total;
ll imos[3 * MAX_N];
ll imos1[3 * MAX_N];
int main() {
  cin >> N >> M;
  A.resize(N);
  for (auto &val : A) {
    cin >> val;
    val--;
  }
  for (int i = 0; i < N - 1; i++) {
    int s = A[i];
    int t = A[i + 1];
    if (s > t) {
      t += M;
    }
    total += t - s;
    if (t - s > 1) {
      imos[s + 2] += 1;
      imos[t + 1] -= 1;

      imos1[t + 1] -= (t - s - 1);
    }
  }

  for (int i = 1; i < 2 * M; i++) {
    imos[i] += imos[i - 1];
    imos1[i] += imos1[i - 1] + imos[i];
  }
  vector<ll> profits(M);
  for (int i = 0; i < M; i++) {
    profits[i] = imos1[i] + imos1[i + M];
  }
  ll res = *max_element(profits.begin(), profits.end());
  cout << total - res << endl;
  return 0;
}
