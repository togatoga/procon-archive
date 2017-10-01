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
int N,S,T;
int main() {
  cin >> N >> S >> T;
  if (S > T){
    cout << -1 << endl;
    return 0;
  }
  int left = S;
  int right = S;
  int cnt = 0;
  while (cnt < 30){
    if (left <= T and T <= right){
      cout << cnt << endl;
      return 0;
    }
    int n_left = 2 * left;
    int n_right = 2 * right + 1;
    left = n_left;
    right = n_right;
    cnt++;
  }
  cout << -1 << endl;
  return 0;
}
