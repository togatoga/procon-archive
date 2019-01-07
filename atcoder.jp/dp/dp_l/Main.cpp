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
vector<int> A;
const int MAX_N = 3010;
ll dp[MAX_N][MAX_N][2];

ll memo(int head, int tail, int turn)
{
    if (head > tail)
    {
        return 0;
    }
    ll &res = dp[head][tail][turn];
    if (res != -LL_INF)
    {
        return res;
    }

    if (turn == 0)
    {
        res = -LL_INF;
        res = max(res, memo(head + 1, tail, !turn) + A[head]);
        res = max(res, memo(head, tail - 1, !turn) + A[tail]);
    }
    else
    {
        res = LL_INF;
        res = min(res, memo(head + 1, tail, !turn) - A[head]);
        res = min(res, memo(head, tail - 1, !turn) - A[tail]);
    }

    return res;
}

void init() 
{
    for (int i = 0; i < MAX_N; i++)
    {
        for (int j = 0; j < MAX_N; j++)
        {
            dp[i][j][0] = -LL_INF;
            dp[i][j][1] = -LL_INF;
        }
    }
}
int main()
{
    init();
    cin >> N;
    A.resize(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    cout << memo(0, N - 1, 0) << endl;

    return 0;
}
