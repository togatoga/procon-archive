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
int Q;
const int MAX_LR = 100100;
bool prime[MAX_LR];
void sieve() {

  for (int i = 2; i < MAX_LR; i++) {
    prime[i] = true;
  }
  for (int i = 2; i < MAX_LR; i++) {
    if (prime[i]) {
      for (int j = 2 * i; j < MAX_LR; j += i) {

        prime[j] = false;
      }
    }
  }
}
int res[MAX_LR];
int main() {
  sieve();
  // cerr << "hoge" << endl;
  cin >> Q;
  for (int i = 2; i < MAX_LR; i++) {
    res[i] += res[i-1];
    if (not prime[i] or i % 2 == 0) {
      continue;
    }
    if (prime[i] and prime[(i + 1) / 2]) {
      res[i]++;
    }

  }
  for (int i = 0; i < Q; i++) {
    int l, r;
    cin >> l >> r;
    cout << res[r] - res[l - 1] << endl;
  }
  return 0;
}
