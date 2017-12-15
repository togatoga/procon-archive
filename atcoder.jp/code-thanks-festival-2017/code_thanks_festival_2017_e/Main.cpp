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
int N;
int get_weight(vector<int> query)
{
    cout << "? ";
    for (auto &val : query)
    {
        cout << val << " ";
    }
    cout << endl;
    int sum;
    cin >> sum;
    return sum;
}
void init(vector<int> &query)
{
    for (auto &val : query)
    {
        val = 0;
    }
}

bool dfs(int sum, int cnt, int limit, vector<int> &res)
{
  if (sum <= 0 or cnt > limit){
    if (sum == 0 and cnt == limit * 10){
      return true;
    }
    return false;
  }
  
  res.push_back(0);
  if (dfs(sum - 12 * cnt, cnt * 10, limit, res)){
    return true;
  }
  res.pop_back();

  res.push_back(0);
  if (dfs(sum - 10 * cnt, cnt * 10, limit, res)){
    return true;
  }
  res.pop_back();
  
  res.push_back(0);
  if (dfs(sum - 8 * cnt, cnt * 10, limit, res)){
    return true;
  }
  res.pop_back();
  
  res.push_back(1);
  if (dfs(sum - 11 * cnt, cnt * 10, limit, res)){
    return true;
  }
  res.pop_back();
  
  res.push_back(1);
  if (dfs(sum - 9 * cnt, cnt * 10, limit, res)){
    return true;
  }
  res.pop_back();
  
  return false; 
}
void set_answer(int sum, vector<int> &answer, int head, int tail)
{
  int cnt = head - tail;
  int limit = 1;
  for (int i = 0; i < cnt - 1; i++){
    limit *= 10;
  }
  vector<int> result;
  dfs(sum,  1, limit, result);
  for (int i = 0; i < cnt; i++){
    answer[i + tail] = result[i];
  }
}

int main()
{
    cin >> N;
    vector<int> query(N);
    vector<int> answer(N);
    int head, tail;
    head = tail = 0;

    int cnt = 1;
    while (head < N)
    {
        query[head] = cnt;
        cnt *= 10;
        head++;
        if (cnt > 10000 || head >= N)
        {
            int sum = get_weight(query);
            set_answer(sum, answer, head, tail);
            init(query);
            cnt = 1;
            tail = head;
        }
    }
    cout << "! ";
    for (auto &val : answer)
    {
        cout << val << " ";
    }
    cout << endl;
    return 0;
}
