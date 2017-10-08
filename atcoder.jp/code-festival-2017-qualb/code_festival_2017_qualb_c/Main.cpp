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
const int MAX_N = 100100;
ll N,M;
vector<int> edges[MAX_N];
int visited[MAX_N];
int colors[MAX_N];
bool is_cycle(int pos, int pre, int color){
    visited[pos] = 2;
    colors[pos] = color;
    for (auto &nxt : edges[pos]){
        if (nxt != pre){
            if (visited[nxt] == 2 and colors[nxt] == color){
                return true;
            }
            if (visited[nxt] == -1){
                if (is_cycle(nxt, pos, 1 - color)){
                    return true;
                }
            }
        }
    }
    visited[pos] = 1;
    return false;
}
int main() {
    cin >> N >> M;
    for (int i = 0; i < M; i++){
        int a,b;
        cin >> a >> b;
        a--,b--;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    memset(visited, -1, sizeof(visited));
    bool cycle = is_cycle(0, -1, 0);
    if (cycle){
        ll res = (ll)N * (N - 1) / 2;
        cout << res - M << endl;
    }else{
        int X,Y;
        X = Y = 0;
        for (int i = 0; i < N; i++){
            if (colors[i]){
                X++;
            }else{
                Y++;
            }
        }
        cout << (ll)X*Y - M << endl;
    }
   return 0;
 }
