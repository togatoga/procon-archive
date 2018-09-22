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
vector<int> A;
const int MAX_N = 60;
ll dp[MAX_N][4000][2];
int main()
{
    cin >> N >> K;
    int sum = 0;
    for (int i = 0; i < N; i++)
    {
        ll a;
        cin >> a;
        int cnt = 0;
        while (a > 0)
        {
            a /= 2;
            cnt++;
        }
        A.push_back(cnt);
        sum += cnt;
    }
    sort(A.begin(), A.end());
    dp[0][0][0] = 1;
    // cerr << "sum = " << sum << endl;
    for (int pos = 0; pos < N; pos++)
    {
        for (int val = 0; val < 3600; val++)
        {
            for (int flg = 0; flg < 2; flg++)
            {
                if (dp[pos][val][flg] == 0)
                {
                    continue;
                }
                for (int nxt = 0; nxt <= A[pos]; nxt++)
                {
                    bool is_zero = nxt == A[pos] ? true : false;
                    is_zero |= flg;
                    dp[pos + 1][val + nxt][is_zero] += dp[pos][val][flg];
                    dp[pos + 1][val + nxt][is_zero] %= MOD;
                }
            }
        }
    }
    ll result = 0;
    if (K <= sum)
    {

        for (int i = 0; i <= K; i++)
        {
            result += dp[N][i][1];
            result %= MOD;
        }
        result += dp[N][K][0];
        result %= MOD;
    }
    else
    {
        for (int i = 0; i <= sum; i++)
        {
            result += dp[N][i][1];
            result %= MOD;
        }
        result += dp[N][sum][0];
        result %= MOD;
    }
    cout << result << endl;

    return 0;
}
