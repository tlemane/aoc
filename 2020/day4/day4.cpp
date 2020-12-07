#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <fstream>

using namespace std;
using data_t = vector<string>;

const static vector<string> rules {
  string(R"(byr:19[2-9][0-9]|200[0-2])"),
  string(R"(iyr:(201[0-9]|2020))"),
  string(R"(eyr:(202[0-9]|2030))"),
  string(R"(hgt:(1[5-8][0-9]|19[0-3])cm|(59|6[0-9]|7[0-6])in)"),
  string(R"(hcl:#([0-9]|[a-f]){6})"),
  string(R"(ecl:(amb|blu|brn|gry|grn|hzl|oth))"),
  string(R"(pid:\d{9}(?!\S))")
};

int solve1(data_t& data)
{
  int res = 0;
  for (auto& s: data)
  {
    if (all_of(rules.begin(), rules.end(), [&s](string r) -> bool {
      return regex_search(s, regex(r.substr(0,4)));
      })) res++;
  }
  return res;
}

int solve2(data_t& data)
{
  int res = 0;
  for (auto& s: data)
  {
    if (all_of(rules.begin(), rules.end(), [&s](string r) -> bool {
      return regex_search(s, regex(r));
      })) res++;
  }
  return res;
}

int main(int argc, char* argv[])
{
  data_t data;
  
  string path = argv[1];
  ifstream in(path, ios::in);

  string s;
  
  for (string line; getline(in, line);)
  {
    if (line.size() > 0)
      s += line + " ";
    else
    {
      data.push_back(s);
      s = "";
    }
  }
  data.push_back(s);

  cout << "DAY04 - " << "1: " << solve1(data) << endl;
  cout << "DAY04 - " << "2: " << solve2(data) << endl;
  return 0;
}