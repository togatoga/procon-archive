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
    int N,C;
    multiset<int> L;

    int main() {
        cin >> N >> C;
        int result = 0;
        for (int i = 0; i < N; i++){
            int l;
            cin >> l;
            if (l >= C){
                result++;
                continue;
            }
            L.insert(l);
        }
        N = L.size();
        while (not L.empty()){
            result++;
            int l1 = *L.rbegin();
            auto p = L.find(l1);
            L.erase(p);
            if (L.empty())break;
            int l2 = *L.rbegin();
            auto q = L.find(l2);
            if (l1 + l2 + 1 <= C){
                L.erase(q);
                continue;
            }
            int tmp = C - l1 - 1;
            auto t1 = L.upper_bound(tmp);
            if (t1 != L.begin()){
                t1--;
                L.erase(t1);
            }
        }
        cout << result << endl;
       return 0;
     }
