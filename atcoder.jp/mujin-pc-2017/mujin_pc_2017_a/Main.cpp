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
int N;
vector<ll> X;
ll result;
int main()
{
    cin >> N;
    X.resize(N);
    for (auto &val : X)
    {
        cin >> val;
    }
    stack<ll> positions;
    result = 1;
    for (int i = 0; i < N; i++)
    {
        positions.emplace(X[i]);
        while (not positions.empty())
        {
            ll p = positions.top();
            int size = positions.size();
            if (2 * size - 1 <= p)
            {
                break;
            }
            else
            {
                positions.pop();
                result *= size;
                result %= MOD;
            }
        }
    }
    int size = positions.size();
    for (int i = 1; i <= size; i++)
    {
        result *= i;
        result %= MOD;
    }

    cout << result << endl;
    return 0;
}
