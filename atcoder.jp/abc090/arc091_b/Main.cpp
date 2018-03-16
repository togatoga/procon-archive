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
ll N, K;
int f(int a, int b)
{
    return a - a / b;
}

int main()
{
    cin >> N >> K;
    if (K == 0)
    {
        cout << N * N << endl;
        return 0;
    }
    ll result = 0;
    for (int b = K + 1; b <= N; b++)
    {
        ll x = N / b;
        ll y = b - K;
        ll z = max(0LL, N % b - K + 1);
        result += x * y + z;

    }
    cout << result << endl;
    return 0;
}
