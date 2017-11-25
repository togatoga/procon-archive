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
string S;
map<char, int> cnt;
int N;
bool check(map<char, int> &tmp) {
  for (char i = 'a'; i <= 'c'; i++) {
    if (tmp[i] < 0) {
      return false;
    }
  }
  return true;
}
int main() {
  cin >> S;
  N = S.size();
  for (auto &val : S) {
    cnt[val]++;
  }
  // if (N == 1) {
  //   cout << "YES" << endl;
  //   return 0;
  // }
  // if (N == 2) {
  //   if (cnt[0] != cnt[1]) {
  //     cout << "YES" << endl;
  //   } else {
  //     cout << "NO" << endl;
  //   }
  //   return 0;
  // }
  vector<int> tmp;
  for (char i ='a'; i <= 'c'; i++){
      tmp.push_back(cnt[i]);
  }
  sort(tmp.begin(), tmp.end());
  if (abs(tmp[0] - tmp[2]) <= 1){
    cout << "YES" << endl;
    return 0;
  }
  cout << "NO" << endl;
  return 0;
  for (char i = 'a'; i <= 'c'; i++) {
    for (char j = 'a'; j <= 'c'; j++) {
      for (char k = 'a'; k <= 'c'; k++) {
        if (i == j or j == k or i == k) {
          continue;
        }
        map<char, int> tmp = cnt;
        int head = 0;
        bool ok = true;
        while (head < N) {
          if (head % 3 == 0) {
            tmp[i]--;
          } else if (head % 3 == 1) {
            tmp[j]--;
          } else {
            tmp[k]--;
          }
          if (not check(tmp)) {
            ok = false;
            break;
          }
          head++;
        }
        if (ok and check(tmp)) {
          cout << "YES" << endl;
          return 0;
        }
      }
    }
  }
  cout << "NO" << endl;
  return 0;
}
