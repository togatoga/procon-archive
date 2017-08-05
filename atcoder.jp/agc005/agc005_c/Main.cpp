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
const int MAX_N = 110;
int N;
int deg[MAX_N];
vector<int> A;
bool ok;

bool check() {
  for (int i = 0; i < MAX_N; i++) {
    if (deg[i] > 0) {
      return false;
    }
  }
  return true;
}
int main() {
  ok = true;
  cin >> N;
  A.resize(N);
  for (auto &val : A) {
    cin >> val;
    deg[val]++;
  }
  sort(A.rbegin(), A.rend());
  int max_val = A[0];
  int min_val = A[N - 1];
  if (max_val % 2) {
    int res = max_val;
    for (int i = 0; i <= max_val / 2; i++) {
      deg[res] -= 2;
      if (deg[res] < 0) {
        ok = false;
        goto END;
      }
      res--;
    }
    int left = max_val - ((max_val / 2) - 1);
    int right = max_val;
    for (int i = 0; i < MAX_N; i++){
      if (deg[i] > 0){
        if (not (left <= i and i <= right)){
          ok = false;
          goto END;
        }
        deg[i] = 0;
      }
    }
  } else {
    int res = max_val;
    for (int i = 0; i < max_val / 2; i++) {
      deg[res] -= 2;
      if (deg[res] < 0) {
        ok = false;
        goto END;
      }
      res--;
    }
    deg[res]--;

    int left = max_val - ((max_val / 2) - 1);
    int right = max_val;
    for (int i = 0; i < MAX_N; i++){
      if (deg[i] > 0){
        if (not (left <= i and i <= right)){
          ok = false;
          goto END;
        }
        deg[i] = 0;
      }
    }
  }
END:;
  ok &= check();
  if (ok){
    cout << "Possible" << endl;
  }else{
    cout << "Impossible" << endl;
  }
  return 0;
}
