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
vector<string> board;
const int MAX_HW = 1010;
ll dp[MAX_HW][MAX_HW];
int main()
{
    cin >> H >> W;
    board.resize(H);
    for (int i = 0; i < H; i++)
    {
        cin >> board[i];
    }
    dp[0][0] = 1;
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            if (dp[i][j] == 0)
            {
                continue;
            }
            //right
            if (j + 1 < W && board[i][j + 1] == '.')
            {
                dp[i][j + 1] += dp[i][j] % MOD;
            }
            //down
            if (i + 1 < H && board[i + 1][j] == '.')
            {
                dp[i + 1][j] += dp[i][j] % MOD;
            }
        }
    }
    cout << dp[H - 1][W - 1] % MOD << endl;
    return 0;
}
