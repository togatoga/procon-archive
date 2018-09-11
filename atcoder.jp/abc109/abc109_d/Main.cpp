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
int H, W;
const int MAX_HW = 510;
int board[MAX_HW][MAX_HW];
int main()
{
  cin >> H >> W;
  for (int i = 1; i <= H; i++)
  {
    for (int j = 1; j <= W; j++)
    {
      cin >> board[i][j];
    }
  }
  int y = 1;
  int x = 1;
  vector<pii> yx;
  vector<tuple<pii, pii>> paths;
  vector<pii> path;
  while (true)
  {
    if (y > H)
    {
      break;
    }
    // cerr << y << " " << x << endl;
    if (board[y][x] % 2 == 1)
    {
      if (yx.empty())
      {
        yx.push_back(mp(y, x));
      }
      else
      {
        //path
        int py = y;
        int px = x;
        
        for (int i = path.size() - 1; i >= 0; i--)
        {
          paths.push_back(mt(mp(py, px), mp(path[i].first, path[i].second)));
          
          py = path[i].first;
          px = path[i].second;
        }
        //clear
        yx.clear();
        path.clear();
      }
    }

    if (not yx.empty())
    {
      path.push_back(mp(y, x));
    }
    int dir = 1;
    if (y % 2 == 0)
    {
      dir *= -1;
    }
    x += dir;
    if (x < 1 || x > W)
    {
      x -= dir;
      y++;
    }
  }

  cout << paths.size() << endl;
  for (int i = 0; i < paths.size(); i++)
  {
    pii p, q;
    tie(p, q) = paths[i];
    cout << p.first << " " << p.second << " " << q.first << " " << q.second << endl;
  }
  return 0;
}
