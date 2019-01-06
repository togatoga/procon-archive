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
int N;
const int MAX_N = 100010;
vector<tuple<int, int, int>> abc;
ll dp[MAX_N][3];
int main()
{
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        abc.emplace_back(mt(a, b, c));
    }
    dp[0][0] = get<0>(abc[0]);
    dp[0][1] = get<1>(abc[0]);
    dp[0][2] = get<2>(abc[0]);

    for (int i = 1; i < N; i++)
    {
        int a, b, c;
        tie(a, b, c) = abc[i];
        dp[i][0] = max(dp[i - 1][1] + a, dp[i - 1][2] + a);
        dp[i][1] = max(dp[i - 1][0] + b, dp[i - 1][2] + b);
        dp[i][2] = max(dp[i - 1][0] + c, dp[i - 1][1] + c);
    }
    ll result = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            result = max(result, dp[i][j]);
        }
    }
    cout << result << endl;
    return 0;
}
