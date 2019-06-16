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
const int MAX_N = 2010;
int N, M;
vector<int> S;
vector<int> T;
int dp[MAX_N][MAX_N];

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(false);
    cin >> N >> M;
    S.resize(N);
    T.resize(M);
    for (auto &val : S)
    {
        cin >> val;
    }
    for (auto &val : T)
    {
        cin >> val;
    }
    dp[0][0] = 1;
    for (int i = 0; i <= S.size(); i++)
    {
        dp[i][0] = 1;
    }
    for (int i = 0; i <= T.size(); i++)
    {
        dp[0][i] = 1;
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (S[i] == T[j])
            {
                dp[i + 1][j + 1] += dp[i][j];
            }
            dp[i + 1][j + 1] += dp[i][j + 1];
            dp[i + 1][j + 1] %= MOD;
            dp[i + 1][j + 1] += dp[i + 1][j];
            dp[i + 1][j + 1] %= MOD;
            dp[i + 1][j + 1] += MOD - dp[i][j];
            dp[i + 1][j + 1] %= MOD;
        }
    }
    cout << dp[N][M] << endl;
    return 0;
}
