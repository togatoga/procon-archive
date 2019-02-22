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
ll N;
int dfs(int pos, int turn)
{
    if (pos == 0)
    {
        return !turn;
    }
    int num = 1;
    while (true)
    {
        if (pos - num < 0)
        {
            break;
        }
        int res = dfs(pos - num, !turn);
        if (res == turn)
        {
            return turn;
        }
        num *= 8;
    }
    return !turn;
}

bool ok(ll N)
{
    if (N >= 7)
    {
        ll a = N - 7;
        if (a % 9 == 0)
        {
            return true;
        }
        ll cnt = a / 9;
        cnt %= 2;
        if (N % 2 == cnt)
        {
            return true;
        }
        return false;
    }
    else
    {
        if (N % 2 == 0)
        {
            return false;
        }
        return true;
    }
}
int main()
{
    cin >> N;
    // for (int i = 1; i <= 1000; i++){
    //     cout << i << " " << !dfs(i, 0) << " " << ok(i) << endl;
    // }
    if (ok(N))
    {
        cout << "Win" << endl;
    }
    else
    {
        cout << "Lose" << endl;
    }

    return 0;
}
