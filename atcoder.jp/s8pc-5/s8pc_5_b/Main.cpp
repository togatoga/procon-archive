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
int N,M;
vector<tuple<int, int, int>> A;//y,x,r;
vector<pii> B;

bool is_contain(int y1, int x1, double r1, int y2, int x2, double r2){
  double dist = sqrt((y1 - y2) * (y1 - y2) + (x2 - x1) * (x2 - x1));
  if (dist < r1){
    return true;
  }
  if (dist < r2){
    return true;
  }
  return false;
}

bool is_cross(int y1, int x1, double r1, int y2, int x2, double r2){
  double dist = sqrt((y1 - y2) * (y1 - y2) + (x2 - x1) * (x2 - x1));
  if (dist >= r1 + r2){
    return false;
  }
  return true;
}

bool ok(const double r){
  for (int i = 0; i < B.size(); i++){
    int y1,x1;
    double r1;
    y1 = B[i].first;
    x1 = B[i].second;
    r1 = r;
    for (int j = i + 1; j < B.size(); j++){
      int y2,x2;
      double r2;
      y2 = B[j].first;
      x2 = B[j].second;
      r2 = r;
      if (is_cross(y1, x1, r1, y2, x2, r2) || is_contain(y1, x1, r1, y2, x2, r2)){
	return false;
      }
    }
    for (int j = 0; j < A.size(); j++){
      int y2,x2;
      double r2;
      tie(y2, x2, r2) = A[j];
      if (is_cross(y1, x1, r1, y2, x2, r2) || is_contain(y1, x1, r1, y2, x2, r2)){
	return false;
      }
    }
  }
  return true;

}
int main() {
  cin >> N >> M;
  for (int i = 0; i < N; i++){
    int x,y,r;
    cin >> x >> y >> r;
    A.emplace_back(mt(y, x, r));
  }
  for (int i = 0; i < M; i++){
    int x,y;
    cin >> x >> y;
    B.emplace_back(mp(y, x));
  }
  double left,right;
  left = 0;
  right = 1LL << 50;
  for (int i = 0; i < 100; i++){
    double med = (left + right) / 2;
    if (ok(med)){
      left = med;
    }else{
      right = med;
    }
  }
  for (int i = 0; i < A.size(); i++){
    double r = get<2>(A[i]);
    left = min(left, r);
  }
  
  printf("%.20lf\n", left);
  return 0;
}
