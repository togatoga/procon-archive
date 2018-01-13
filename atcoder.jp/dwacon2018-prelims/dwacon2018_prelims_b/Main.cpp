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
string S;
int N;
map<int, int> values;
int main()
{
    cin >> S;
    N = S.size();
    for (int i = 0; i < N; i++)
    {
        int v = S[i] - '0';
        if (v == 2)
        {
            if (values[5] > 0)
            {
                values[5]--;
                values[2]++;
            }
            else
            {
                values[2]++;
            }
        }
        else
        {
            if (values[2] > 0)
            {
                values[2]--;
                values[5]++;
            }
            else
            {
                cout << -1 << endl;
                return 0;
            }
        }
    }
    if (values[2] > 0){
        cout << -1 << endl;
        return 0;
    }
    int res = values[5];
    cout << res << endl;
    return 0;
}
