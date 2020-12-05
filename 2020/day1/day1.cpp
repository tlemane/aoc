#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

const static int V = 2020;
using data_t = vector<int>;

int solve1(data_t& data)
{
  for (int i=0; i<data.size(); i++)
    for (int j=i+1; j<data.size(); j++)
      if (data[i]+data[j] == V)
        return data[i]*data[j];
  return 0;
}

int solve2(data_t& data)
{
  for (int i=0; i<data.size(); i++)
    for (int j=i+1; j<data.size(); j++)
      for (int k=j+1; k<data.size(); k++)
        if (data[i]+data[j]+data[k] == V)
          return data[i]*data[j]*data[k];
  return 0;
}

int main(int argc, char *argv[])
{
  data_t data;
  string      path = argv[1];
  ifstream    in(path, ios::in);

  for (string line; getline(in, line);) 
    data.push_back(stoi(line));
  sort(data.begin(), data.end());

  cout << "DAY01 - " << "1: " << solve1(data) << endl;
  cout << "DAY01 - " << "2: " << solve2(data) << endl;
  return 0;
}