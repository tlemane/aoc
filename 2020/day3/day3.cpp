#include <vector>
#include <iostream>
#include <tuple>
#include <fstream>

using namespace std;
using data_t = vector<string>;

int walk(data_t& data, int i, int j, int c, int& r, int& d, int& jmax, int& imax)
{
  if (i > imax-1) 
    return 0;
  c = data[i][j] == '#' ? 1 : 0;
  return c + walk(data, i+d, (j+r)%jmax, c, r, d, jmax, imax);
}

int solve1(data_t& data)
{
  int r = 3, d = 1, imax = data.size(), jmax = data[0].size();
  return walk(data, 0, 0, 0, r, d, jmax, imax);
}

int solve2(data_t& data)
{
  int res = 1, imax = data.size(), jmax = data[0].size();
  vector<tuple<int, int>> slopes { {1,1}, {2,1}, {5,1}, {7,1}, {1,2} };
  for (auto [r, d]: slopes)
  {
    res *= walk(data, 0, 0, 0, r, d, jmax, imax);
  }
  return res;
}

int main(int argc, char* argv[])
{
  data_t data;

  string path = argv[1];
  ifstream in(path, ios::in);
  for (string line; getline(in, line);) {
    data.push_back(line);
  }
  
  cout << "DAY03 - " << "1: " << solve1(data) << endl;
  cout << "DAY03 - " << "2: " << solve2(data) << endl;
}