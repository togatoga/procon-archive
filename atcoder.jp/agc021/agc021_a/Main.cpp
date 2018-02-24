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
string N;
const int MAX_D = 20;
int dp[MAX_D][2]; //(pos, small)
int M;
void init()
{
    for (int i = 0; i < MAX_D; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            dp[i][j] = -INF;
        }
    }
}
int main()
{
    init();
    cin >> N;
    M = N.size();
    dp[0][0] = 0;
    int result = 0;

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (dp[i][j] <= -INF)
            {
                continue;
            }
            int max_val = 9;
            if (j == 0)
            {
                max_val = N[i] - '0';
            }
            for (int k = 0; k < max_val; k++)
            {
                dp[i + 1][1] = max(dp[i + 1][1], dp[i][j] + k);
            }
            dp[i + 1][j] = max(dp[i + 1][j], dp[i][j] + max_val);
            // cerr << i << " " << j << " " << dp[i][j] << " " << max_val << endl;
        }
    }
    for (int j = 0; j < 2; j++)
    {
        result = max(result, dp[M][j]);
    }
    cout << result << endl;
    return 0;
}
