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
string S;
int N;
map<char, int> cnts;
int main()
{
    cin >> S;
    N = S.size();
    int cnt = 0;
    for (int i = 0; i < N; i++)
    {
        cnts[S[i]]++;
        cnt++;
    }

    ll len = 0;
    ll remain = 0;
    for (auto &val : cnts)
    {
        len += val.second - val.second % 2;
        remain += val.second % 2;
    }
    ll result = 0;
    if (remain > 0)
    {
        result += (len + 1) * (len + 1);
        result += remain - 1;
    }
    else
    {
        result += len * len;
    }
    cout << result << endl;
    return 0;
}
