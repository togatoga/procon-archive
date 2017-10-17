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
int N;
vector<int> A;
int odd,even1,even2;
int main() {
    cin >> N;
    A.resize(N);
    for (auto &val : A){
        cin >> val;
    }
    sort(A.begin(), A.end());
    for (int i = 0; i < A.size(); i++){
        if (A[i] % 2 != 0){
            odd++;
        }else if(A[i] % 4 == 0){
            even2++;
        }else if(A[i] % 2 == 0){
            even1++;
        }
    }
    if (odd == 0){
        cout << "Yes"<< endl;
        return 0;
    }
    if (odd - even2 > 1){
        cout << "No" << endl;
        return 0;
    }
    even2 -= (odd - 1);
    if (even2 > 0){
        cout << "Yes" << endl;
        return 0;
    }
    if (even1 == 0){
        cout << "Yes" << endl;
        return 0;
    }

    cout << "No" << endl;
   return 0;
 }
