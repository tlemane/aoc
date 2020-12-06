#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>

using namespace std;
using data_t = vector<vector<string>>;

int solve1(data_t& data)
{
  set<char> v;
  int sum = 0;
  for (auto& vs : data)
  {
    v.clear();
    for (auto&s : vs)
      for (char& c: s)
        v.insert(c);
    sum += v.size();
  }
  return sum;
}

int solve2(data_t& data)
{
  int sum;
  vector<int> v(26);
  for (auto& vs: data)
  {
    int p = vs.size();
    fill(v.begin(), v.end(), 0);
    for (auto& s: vs)
      for(char& c: s)
        v[c-97] += 1;
    sum += count(v.begin(), v.end(), p);
  }
  return sum;
}


int main(int argc, char* argv[])
{
  data_t data;
  string path = argv[1];
  ifstream in(path, ios::in);
  
  vector<string> s;
  for (string line; getline(in, line);)
  {
    if (!line.empty())
    {
      s.push_back(line);
      continue;
    }
    else
    {
      data.push_back(s);
      s.clear();
    }
  }
  data.push_back(s);

  cout << "DAY06 - " << "1: " << solve1(data) << endl;
  cout << "DAY06 - " << "2: " << solve2(data) << endl;
}