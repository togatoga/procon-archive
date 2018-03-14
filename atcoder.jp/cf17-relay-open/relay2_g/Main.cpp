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
#include <assert.h>

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
ll L;
string S, T;
ll N, M;
string get_result(const string &a, const string &b)
{
    string result = "";
    int cnt1 = 0;
    int cnt2 = 0;
    for (int i = 0; i <= L; i++)
    {
        ll res = L - i * a.size();
        if (res < 0)
        {
            break;
        }
        if (res % b.size() == 0)
        {
            cnt1 = i;
            cnt2 = res / b.size();
        }
    }
    // cerr << a << " " << b << " " << cnt1 << " " << cnt2 << endl;
    for (int i = 0; i < cnt1; i++)
    {
        result += a;
    }
    for (int i = 0; i < cnt2; i++)
    {
        result += b;
    }

    return result;
}
int main()
{
    cin >> L;
    cin >> S;
    cin >> T;
    if (S >= T)
    {
        swap(S, T);
    }
    N = S.size();
    M = T.size();
    bool ok = true;
    for (int i = 0; i < min(N, M); i++)
    {
        if (S[i] != T[i])
        {
            ok = false;
            break;
        }
    }
    if (ok)
    {
        if (S[0] > T[M - 1])
        {
            swap(S, T);
        }
    }
    string result1 = get_result(S, T);
    string result2 = get_result(T, S);
    cout << min(result1, result2) << endl;
    return 0;
}
