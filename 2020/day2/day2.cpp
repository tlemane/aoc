#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <regex>
#include <string>
#include <tuple>

using namespace std;

using data_t = vector<tuple<int, int, string, string>>;

const static vector<regex> rules {
  regex{string(R"([0-9]{1,}(?=-))")},
  regex{string(R"([0-9]{1,}(?=\s))")},
  regex{string(R"([a-z](?=:))")},
  regex{string(R"([a-z]{2,}(?=\n|\b))")}
};

int solve1(data_t& data)
{
  int res = 0;
  for (auto [mi, ma, l, p]: data)
  {
    int c = count(p.begin(), p.end(), l[0]);
    if (c >= mi && c <= ma)
      res++;
  }
  return res;
}

int solve2(data_t& data)
{  
  int res = 0;
  vector<bool> v(2);
  for (auto [mi, ma, l, p]: data)
  {
    v[0] = l[0] == p[mi-1] ? true : false;
    v[1] = l[0] == p[ma-1] ? true : false;
    if (count(v.begin(), v.end(), true) == 1)
      res++;
  }
  return res;
}

int main(int argc, char* argv[])
{
  int mi, ma;
  string l, p;
  smatch match;

  string path = argv[1];
  ifstream in(path, ios::in);
  data_t data;
  
  for (string line; getline(in, line);) 
  {
    regex_search(line, match, rules[0]); mi = stoi(match.str());
    regex_search(line, match, rules[1]); ma = stoi(match.str());
    regex_search(line, match, rules[2]); l = match.str();
    regex_search(line, match, rules[3]); p = match.str();
    data.push_back(make_tuple(mi, ma, l, p));
  }
 
  cout << "DAY02 - " << "1: " << solve1(data) << endl;
  cout << "DAY02 - " << "2: " << solve2(data) << endl;
}
