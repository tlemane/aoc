#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;
using data_t = vector<string>;

int search(string& seq)
{
  int rlower = 0, rupper = 127, rmid = 0;
  int clower = 0, cupper = 7, cmid = 0;
  for (auto& c: seq)
  {
    rmid = rlower + (rupper - rlower) / 2;
    cmid = clower + (cupper - clower) / 2;
    if (c == 'F') rupper = rmid;
    else if (c == 'B') rlower = rmid + 1;
    else if (c == 'L') cupper = cmid;
    else if (c == 'R') clower = cmid + 1; 
  }
  return rlower*8+clower;
}

int solve1(data_t& data)
{
  int max = 0;
  int temp = 0;
  for (auto& s: data)
  {
    temp = search(s);
    if (temp > max) max = temp;
  }
  return max;
}

int solve2(data_t& data)
{
  int max = numeric_limits<int>::min();
  int min = numeric_limits<int>::max();
  int sum = 0;
  
  for (auto& s: data)
  {
    int i = search(s);
    if (max < i) max = i;
    if (min > i) min = i;
    sum += i;
  }
  return ((max-min+1) * (min+max) / 2) - sum;
}

int main(int argc, char* argv[])
{
  data_t data;
  string path = argv[1];
  ifstream in(path, ios::in);
  for (string line; getline(in, line);)
    data.push_back(line);
  
  cout << "DAY05 - " << "1: " << solve1(data) << endl;
  cout << "DAY05 - " << "2: " << solve2(data) << endl;
  return 0;
}