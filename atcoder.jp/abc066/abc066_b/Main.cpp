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
string S;
int N;

bool check(){
    int M = S.size();
    if (M % 2 != 0){
        return false;
    }
    if (S.substr(0, M / 2) == S.substr(M / 2)){
        return true;
    }

    return false;
}
int main() {
    cin >> S;
    N = S.size();
    S.pop_back();
    for (int i = N - 2; i >= 0; i--){
        if (check()){
            cout << S.size() << endl;
            return 0;
        }
        S.pop_back();
    }
   return 0;
 }
