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
using pii = pair<ll, ll>;

const int INF = 1 << 29;
const ll LL_INF = 1LL << 60;
const double EPS = 1e-9;
const ll MOD = 1000000007;

const int dx[] = {1, 0, -1, 0}, dy[] = {0, -1, 0, 1};
int N, K;
priority_queue<pii, vector<pii>, greater<pii>> pq;
int main()
{
    cin >> N >> K;
    for (int i = 0; i < N; i++){
        int a,b;
        cin >> a >> b;
        pq.emplace(mp(a, b));
    }
    ll res = 0;
    for (int i = 0; i < K; i++){
        auto p = pq.top();
        pq.pop();
        res += p.first;
        p.first += p.second;
        pq.emplace(p);
    }
    cout << res << endl;
    return 0;
}
