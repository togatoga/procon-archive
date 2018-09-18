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
const int MAX_N = 500100;
#include <map>
#include <string>
class Trie
{
public:
  Trie()
  {
    this->cnt = 0;
    this->bad = false;
  }

  void insert(const std::string &S, int idx = 0, bool bad = false)
  {
    this->bad |= bad;
    if (!bad)
    {
      this->cnt++;
    }
    if (idx >= S.size())
    {
      //terminate node
      return;
    }
    if (this->nodes.count(S[idx]) == 0)
    {
      this->nodes[S[idx]] = new Trie();
    }
    this->nodes[S[idx]]->insert(S, idx + 1, bad);
  }

  bool find_all_match(const std::string &S, int idx = 0)
  {
    if (idx >= S.size())
    {
      return this->cnt > 0;
    }
    if (this->nodes.count(S[idx]) == 0)
    {
      return false;
    }
    return this->nodes[S[idx]]->find_all_match(S, idx + 1);
  }

  bool find_prefix_match(const std::string &S, int idx = 0)
  {
    if (idx >= S.size())
    {
      return true;
    }
    if (this->nodes.count(S[idx]) == 0)
    {
      return false;
    }
    return this->nodes[S[idx]]->find_prefix_match(S, idx + 1);
  }

  int count(const std::string &S, int idx = 0)
  {
    if (idx >= S.size())
    {
      return this->cnt;
    }
    if (this->nodes.count(S[idx]) == 0)
    {
      return 0;
    }
    return this->nodes[S[idx]]->count(S, idx + 1);
  }
  std::map<char, Trie*> nodes;
  int cnt;
  bool bad;
};

int N, K;
vector<int> A;
vector<string> S;
set<int> wanted;
Trie trie;
int main()
{
  cin >> N >> K;
  if (N == K)
  {
    cout << endl;
    return 0;
  }

  A.resize(K);
  for (int i = 0; i < K; i++)
  {
    cin >> A[i];
    A[i]--;
    wanted.insert(A[i]);
  }

  S.resize(N);
  for (int i = 0; i < N; i++)
  {
    cin >> S[i];
  }

  for (int i = 0; i < N; i++)
  {
    if (wanted.count(i))
    {
      trie.insert(S[i], 0, false);
    }
    else
    {
      trie.insert(S[i], 0, true);
    }
  }
  Trie *pos = &trie;
  string result = "";
  while (true)
  {
    bool ok = false;
    // cerr << " result = " << result << endl;
    for (char c = 'a'; c <= 'z'; c++)
    {
      
      if (pos->nodes.count(c) == 0)
      {
        continue;
      }
      auto p = pos->nodes[c];
      // cerr << c << " " << pos->nodes.count(c) << " " << p->cnt << " " << p->bad << endl;
      if (p->cnt == K)
      {
        ok = true;
        result += c;
        if (!p->bad)
        {
          cout << result << endl;
          return 0;
        }
        pos = p;
        break;
      }

    }

    if (!ok)
    {
      break;
    }
  }
  cout << -1 << endl;
  return 0;
}
