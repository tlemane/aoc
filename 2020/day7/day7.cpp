#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <regex>
#include <set>
#include <list>
#include <tuple>
#include <deque>

using namespace std;

using data_t = map<string, unordered_map<string, int>>;

static const regex r1(R"([a-z\s]{1,}(?=\sbags\scontain))");
static const regex r2(R"([0-9]{1}[a-z\s]{1,}(?=,|\.))");
static const regex r3(R"([0-9]{1})");
static const regex r4(R"((\s){0}[a-z]{1,}[a-z\s]{1,}(?=\sbag|\sbags))");

void search(bool& found, data_t& data, vector<string> d)
{
  if (found) return;
  for (auto s: d)
  {
    if (s == "shiny gold")
    {
      found = true;
      return;
    }
    vector<string> vs;
    for (auto& [b, i]: data[s]) vs.push_back(b);
    search(found, data, vs);
  }
  return;
}

int solve1(data_t& data)
{
  int sum = 0;
  bool found = false;
  for (auto [s, d]: data)
  {
    if (s == "shiny gold") continue;
    found = false;
    vector<string> c = {s};
    search(found, data, c);
    if (found) sum++;
  }
  return sum;
}

void count(int& sum, data_t& data, vector<tuple<string, int>> d)
{
  for (auto& [s, i]: d)
  {
    sum += i;
    vector<tuple<string, int>> vt;
    for (auto& [b, ii] : data[s])
      vt.push_back(make_tuple(b, i*ii));
    count(sum, data, vt);
  }
  return;
}

int solve2(data_t& data)
{
  int sum = 0;
  vector<tuple<string, int>> v;
  v.push_back(make_tuple("shiny gold", 1));
  count(sum, data, v);
  return --sum;
}

int main(int argc, char* argv[])
{
  data_t data;
  string path = argv[1];
  ifstream in(path, ios::in);

  smatch match, match2, match3, match4;
  int nb;
  string s;
  string f;
  for (string line; getline(in, line);)
  {
    regex_search(line, match, r1);
    f = match.str();
    while(regex_search(line, match2, r2))
    {
      string tmp = match2.str();
      regex_search(tmp, match3, r3);
      regex_search(tmp, match4, r4);
      data[f][match4.str()] = stoi(match3.str());
      line = match2.suffix().str();
    }
  }

  cout << "DAY07 - " << "1: " << solve1(data) << endl;
  cout << "DAY07 - " << "2: " << solve2(data) << endl;
  return 0;
}