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
const int MAX_N = 100010;
int N;
vector<int> heights;
ll dp[MAX_N];
void init()
{
    for (int i = 0; i < MAX_N; i++)
    {
        dp[i] = LL_INF;
    }
}

int main()
{
    init();
    cin >> N;
    heights.resize(N);
    for (auto &val : heights)
    {
        cin >> val;
    }
    dp[0] = 0;
    for (int i = 1; i < N; i++)
    {
        if (i - 1 >= 0)
        {
            dp[i] = min(dp[i], dp[i - 1] + abs(heights[i] - heights[i - 1]));
        }
        if (i - 2 >= 0)
        {
            dp[i] = min(dp[i], dp[i - 2] + abs(heights[i] - heights[i - 2]));
        }
        // cout << dp[i] << endl;
    }
    cout << dp[N - 1] << endl;
    return 0;
}
