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
const int MAX_K = 100010;
int dp[MAX_K][2];

int memo(int k, int turn)
{
    if (k == 0)
    {
        return !turn;
    }
    if (dp[k][turn] != -1)
    {
        return dp[k][turn];
    }
    int &res = dp[k][turn];
    res = !turn;
    for (int i = 0; i < N; i++)
    {
        if (k - A[i] >= 0)
        {
            int tmp = memo(k - A[i], !turn);
            if (tmp == turn)
            {
                res = turn;
                return res;
            }
        }
    }
    return res;
}
int main()
{
    cin >> N >> K;
    A.resize(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    sort(A.begin(), A.end());
    memset(dp, -1, sizeof(dp));
    int res = memo(K, 0);
    if (res == 0)
    {
        cout << "First" << endl;
    }
    else
    {
        cout << "Second" << endl;
    }

    return 0;
}
