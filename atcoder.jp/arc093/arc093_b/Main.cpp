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
int H, W;
int A, B;
const int MAX_HW = 110;
char board[MAX_HW][MAX_HW];
int main()
{
    cin >> A >> B;
    H = W = 100;
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            if (i < H / 2)
            {
                board[i][j] = '.';
            }
            else
            {
                board[i][j] = '#';
            }
        }
    }
    int y, x;
    y = 1;
    x = 1;
    for (int i = 0; i < B - 1; i++)
    {
        board[y][x] = '#';
        x += 2;
        if (x >= W)
        {
            y += 2;
            x = 1;
        }
    }
    y = H - 2;
    x = W - 2;
    for (int i = 0; i < A - 1; i++)
    {
        board[y][x] = '.';
        x -= 2;
        if (x < 0)
        {
            y -= 2;
            x = W - 2;
        }
    }
    cout << H << " " << W << endl;
    rep(i, H)
    {
        rep(j, W)
        {
            cout << board[i][j];
        }
        cout << endl;
    }
    return 0;
}
