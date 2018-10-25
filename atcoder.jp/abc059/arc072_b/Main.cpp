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
ll X, Y;
const int MAX_N = 100;
int dp[2 * MAX_N][2 * MAX_N][2];
int memo(int x, int y, bool turn)
{

    if (x <= 1 && y <= 1)
    {
        return !turn;
    }
    int &res = dp[x][y][turn];
    if (res >= 0)
    {
        return res;
    }
    res = !turn;
    int i = 1;

    while (2 * i <= x)
    {
        if (memo(x - 2 * i, y + i, !turn) == turn)
        {
            res = turn;
            return res;
        }
        i++;
    }
    i = 1;
    while (2 * i <= y)
    {
        if (memo(x + i, y - 2 * i, !turn) == turn)
        {
            res = turn;
            return res;
        }
        i++;
    }

    return res;
}
int main()
{
    cin >> X >> Y;
    if (abs(X - Y) <= 1)
    {
        cout << "Brown" << endl;
        return 0;
    }
    cout << "Alice" << endl;
    // memset(dp, -1, sizeof(dp));
    // for (int x = 0; x <= MAX_N; x++)
    // {
    //     for (int y = 0; y <= MAX_N; y++)
    //     {
    //         string res = (memo(x, y, 0) == 0 ? "Alice" : "Brown");
    //         if (res == "Brown")
    //         {
    //             cout << x << " " << y << " " << res << endl;
    //         }
    //     }
    // }

    return 0;
}
