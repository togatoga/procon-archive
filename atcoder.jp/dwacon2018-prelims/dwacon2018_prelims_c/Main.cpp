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
int N, M;
vector<int> killA, killB;
const int MAX_NM = 110;
const int MAX_SUM = 1010;
ll dp[MAX_NM][MAX_SUM];
int calc(int n, vector<int> kill, int sum)
{
    vector<int> same(n);
    same[0] = 1;
    for (int i = 1; i < n; i++)
    {
        if (kill[i] == kill[i - 1])
        {
            same[i] += same[i - 1] + 1;
        }
        else
        {
            same[i] = 1;
        }
    }
    memset(dp, 0, sizeof(dp));
    dp[0][sum] = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= sum; j++)
        {
            for (int x = 0; x <= j; x += same[i])
            {
                dp[i + 1][j - x] += dp[i][j];
                dp[i + 1][j - x] %= MOD;
            }
        }
    }
    return dp[n][0];
}
int main()
{
    cin >> N >> M;
    killA.resize(N);
    int sumA, sumB;
    sumA = sumB = 0;
    for (auto &val : killA)
    {
        cin >> val;
        sumA += val;
    }
    killB.resize(M);
    for (auto &val : killB)
    {
        cin >> val;
        sumB += val;
    }

    ll resA = calc(N, killA, sumB);
    ll resB = calc(M, killB, sumA);

    cout << (ll)resA % MOD * resB % MOD << endl;
    return 0;
}
