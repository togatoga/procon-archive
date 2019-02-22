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
int N, K;
const int MAX_N = 110;
const int MAX_K = 100010;
vector<int> A;
ll dp[MAX_N][MAX_K];

int main()
{
    cin >> N >> K;
    A.resize(N);
    for (auto &val : A)
    {
        cin >> val;
    }
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for (int n = 0; n < N; n++)
    {
        for (int k = 0; k <= K; k++)
        {

            dp[n + 1][k] += dp[n][k];
            dp[n + 1][min(k + A[n], K) + 1] -= dp[n][k];
            dp[n + 1][min(k + A[n], K) + 1] += MOD;
            dp[n + 1][min(k + A[n], K) + 1] %= MOD;

            // for (int i = 0; i <= A[n]; i++)
            // {
            //     if (i + k > K)
            //     {
            //         break;
            //     }
            //     dp[n + 1][i + k] = max(0, dp[n + 1][i + k]);
            //     dp[n + 1][i + k] += dp[n][k];
            //     dp[n + 1][i + k] %= MOD;
            // }
        }
        for (int i = 0; i < MAX_K; i++)
        {
            dp[n + 1][i + 1] += dp[n + 1][i];
            dp[n + 1][i + 1] %= MOD;
        }
    }
    cout << dp[N][K] << endl;
    return 0;
}
