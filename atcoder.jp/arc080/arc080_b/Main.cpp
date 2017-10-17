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
const int MAX_HW = 110;
int H, W;
int N;
vector<int> A;
int board[MAX_HW][MAX_HW];
int main() {
  cin >> H >> W;
  cin >> N;
  A.resize(N);
  for (auto &val : A) {
    cin >> val;
  }
  int y = 0;
  int x = 0;
  int dir = 1;
  for (int i = 0; i < N; i++) {
    int deg = A[i];
    int node = i + 1;
    while (deg > 0) {
      board[y][x] = node;
      x += dir;
      if (x < 0) {
        x = 0;
        y++;
        dir = 1;
      } else if (x >= W) {
          x = W - 1;
          y++;
          dir = -1;
      }
      deg--;
    }
  }
  for (int i = 0; i < H; i++){
      for (int j = 0; j < W; j++){
          cout << board[i][j] << " ";
      }
      cout << endl;
  }
  return 0;
}
