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
int N;
vector<int> A;
int main() {
  cin >> N;
  A.resize(N);
  for (auto &val : A) {
    cin >> val;
  }
  vector<int> B(A);
  sort(B.begin(), B.end());
  int m1 = N / 2;
  int m2 = m1 - 1;
  int v1 = B[m1];
  int v2 = B[m2];
  for (int i = 0; i < N; i++) {
    if (A[i] <= v2) {
      cout << v1 << endl;
      continue;
    } else {
      cout << v2 << endl;
      continue;
    }
  }

  return 0;
}
