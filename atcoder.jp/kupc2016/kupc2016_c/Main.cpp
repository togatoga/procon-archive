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
const double EPS = 1e-9;
const ll MOD = 1000000007;

const int dx[] = {1, 0, -1, 0}, dy[] = {0, -1, 0, 1};
int T;
int N,D;
int check(int val1, int val2){
    for (int i = 6; i >= 0; i--){
        int b1 = (val1 >> i) & 1;
        int b2 = (val2 >> i) & 1;
        if (b1 < b2){
            return true;
        }
        if (b1 > b2){
            return false;
        }
    }
    return true;
}
void solve(){
    cin >> N >> D;
    int sum = D;

    priority_queue<int, vector<int>, greater<int>> cookies;
    cookies.emplace(D);
    int res = D;
    while (N--){
        if (N <= 0)break;
        int tmp = 0;
        // cout << "res = " << res << endl;
        for (int i = 0; i < 7; i++){
            if ((res & (1 << i))){//bit 1
            //pass
            }else{
                tmp |= 1 << i;
            }
        }
        sum -= res;
        sum += tmp + (tmp ^ res);
        res = min(tmp, tmp ^ res);
    }

    cout << sum << endl;
}
int main() {
    cin >> T;
    for (int i = 0; i < T; i++){
        solve();
    }

   return 0;
 }
