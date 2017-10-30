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
int H,W;
map<char, int> deg;
int main() {
    cin >> H >> W;
    for (int i = 0; i < H; i++){
        for (int j = 0; j < W; j++){
            char c;
            cin >> c;
            deg[c]++;
        }
    }
    priority_queue<int> que;
    for (const auto &val : deg){
        que.push(val.second);
    }

    for (int i = 0; i < H / 2; i++){
        for (int j = 0; j < W / 2; j++){
            int val = que.top();
            que.pop();
            if (val < 4){
                cout << "No" << endl;
                return 0;
            }
            val -= 4;
            que.push(val);
        }
    }
    if (H % 2 != 0){
        for (int j = 0; j < W / 2; j++){
            int val = que.top();
            que.pop();
            if (val < 2){
                cout << "No" << endl;
                return 0;
            }
            val -= 2;
            que.push(val);
        }
    }
    if (W % 2 != 0 ){
        for (int j = 0; j < H / 2; j++){
            int val = que.top();
            que.pop();
            if (val < 2){
                cout << "No" << endl;
                return 0;
            }
            val -= 2;
            que.push(val);
        }
    }
    cout << "Yes" << endl;
   return 0;
 }
