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
ll N, D;
vector<int> X;
const int MAX_N = 100100;
ll Right[MAX_N];
ll Left[MAX_N];
ll result;
int main()
{
    cin >> N >> D;
    X.resize(N);
    for (auto &val : X)
    {
        cin >> val;
    }
    result = N * (N - 1) * (N - 2) / 6;
    int l = 0;
    for (int r = 0; r < N; r++)
    {
        while (l < r && D < X[r] - X[l])
        {
            l++;
        }
        Left[r] = r - l;
    }
    int r = N - 1;
    for (int l = N - 1; l >= 0; l--)
    {
        while (l < r && D < X[r] - X[l])
        {
            r--;
        }
        Right[l] = r - l;
    }
    ll tmp = 0;
    // cerr << "result = " << result << endl;
    for (int j = 0; j < N; j++)
    {
        // cerr << Left[j] << endl;
        //1
        tmp += (Left[j]) * (Left[j] - 1) / 2;
        ll rest1 = j - Left[j];
        ll rest2 = (N - 1 - j) - Right[j];
        
        //2.1
        tmp += rest1 * Right[j];
        //2.2
        tmp += Left[j] * rest2;
        //2.3
        tmp += rest1 * rest2;
    }
    cout << result - tmp << endl;

    return 0;
}
