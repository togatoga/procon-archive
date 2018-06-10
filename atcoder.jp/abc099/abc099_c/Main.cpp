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
int dp[MAX_N];
int memo(int rest)
{
    if (rest == 0)
    {
        return 0;
    }
    int &res = dp[rest];
    if (res >= 0)
    {
        return res;
    }
    res = INF;
    res = min(res, memo(rest - 1) + 1);
    int six = 6;
    while (rest - six >= 0)
    {
        res = min(res, memo(rest - six) + 1);
        six *= 6;
    }
    int nine = 9;
    while (rest - nine >= 0)
    {
        res = min(res, memo(rest - nine) + 1);
        nine *= 9;
    }
    return res;
}
int main()
{
    int N;
    cin >> N;
    memset(dp, -1, sizeof(dp));
    cout << memo(N) << endl;
    return 0;
}
