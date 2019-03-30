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
int N, X;
const int MAX_N = 210;
const int MAX_SX = 100010;
ll dp[MAX_N][MAX_SX];
ll factor[MAX_N];
vector<int> S;
ll result;

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(false);
    cin >> N >> X;
    S.resize(N);
    for (auto &val : S)
    {
        cin >> val;
    }
    sort(S.rbegin(), S.rend());
    factor[0] = 1;
    for (int i = 1; i < MAX_N; i++)
    {
        factor[i] = factor[i - 1] * i;
        factor[i] %= MOD;
    }
    dp[0][X] = 1;
    for (int i = 0; i < N; i++)
    {
        const int y = S[i];
        for (int j = 0; j <= X; j++)
        {
            if (dp[i][j] == 0)
            {
                continue;
            }
            dp[i + 1][j % y] += dp[i][j];
            dp[i + 1][j % y] %= MOD;
            if (i != N - 1)
            {
                dp[i + 1][j] += dp[i][j] * (N - i - 1);
                dp[i + 1][j] %= MOD;
            }
        }
    }
    for (int i = 0; i < MAX_SX; i++)
    {
        result += (ll)i * dp[N][i];
        result %= MOD;
    }
    cout << result << endl;
    return 0;
}
