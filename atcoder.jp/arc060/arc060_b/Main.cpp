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
ll N, S;
ll f(ll b, ll n)
{
    if (n < b)
    {
        return n;
    }
    return f(b, n / b) + n % b;
}
int main()
{
    cin >> N;
    cin >> S;
    if (S == N)
    {
        cout << N + 1 << endl;
        return 0;
    }
    bool ok = false;
    ll b = 2;
    ll result = LL_INF;
    while (true)
    {

        if (f(b, N) == S)
        {
            ok = true;
            result = min(result, b);
            break;
        }
        b++;
        if (b * b > N)
        {
            break;
        }
    }

    ll sn = sqrt(N) + 10;
    while (true)
    {
        if (sn == 0)
        {
            break;
        }
        ll b = (N - S) / sn + 1;
        if (b <= 1)
        {
            sn--;
            continue;
        }
        if (f(b, N) == S)
        {
            ok = true;
            result = min(result, b);
            break;
        }
        sn--;
        if (sn == 0)
        {
            break;
        }
    }

    if (not ok)
    {
        cout << -1 << endl;
        return 0;
    }
    cout << result << endl;

    return 0;
}
