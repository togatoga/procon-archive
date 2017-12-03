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
const int MAX_C = 31;
int N,C;
vector<tuple<int, int, int>> cs;
priority_queue<int, vector<int>, greater<int>> last[100];
int main() {

  cin >> N >> C;
  for (int i = 0; i < N; i++){
    int s,t,c;
    cin >> s >> t >> c;
    c--;
    cs.emplace_back(mt(s, t, c));
  }
  sort(cs.begin(), cs.end());
  int result = 0;
  for (int i = 0; i < cs.size(); i++){
    int s,t,c;
    tie(s, t, c) = cs[i];
    while (not last[c].empty()){
      int l = last[c].top();
      if (l <= s){
        last[c].pop();
      }
    }
    // cerr << last[c].size() << endl;
    last[c].push(t);
    int tmp = 0;
    for (int j = 0; j < C; j++){
      while (not last[j].empty()){
        if (last[j].top() < s){
          last[j].pop();
        }else{
          break;
        }
      }
      tmp += last[j].size();
    }
    result = max(result, tmp);
  }
  cout << result << endl;
  return 0;
}
