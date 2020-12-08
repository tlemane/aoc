#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <unordered_map>

using namespace std;
using data_t = vector<pair<string, int>>;

void execute(data_t& data, set<int>& visited, int& accumulator, bool& infinite, int id)
{
  if (id == data.size()) return;
  if (visited.count(id))
  {
    infinite = true;
    return;
  }
  else visited.insert(id);

  pair<string, int> inst = data[id];
  if (inst.first == "acc") 
    execute(data, visited, accumulator+=inst.second, infinite, ++id);
  else if (inst.first == "jmp")
    execute(data, visited, accumulator, infinite, id+=inst.second);
  else if (inst.first == "nop")
    execute(data, visited, accumulator, infinite, ++id);
  return;
}

int solve1(data_t& data)
{
  int accumulator = 0;
  bool infinite = false;
  set<int> visited;
  execute(data, visited, accumulator, infinite, 0);
  return accumulator;
}

int solve2(data_t& data)
{
  std::unordered_map<string, string> flip = { {"nop", "jmp"}, {"jmp", "nop"} };
  int accumulator = 0;
  bool infinite = false;
  set<int> visited;
  
  for (auto& [inst, value] : data)
  {
    if (inst == "nop" || inst == "jmp")
      inst = flip[inst];
    else continue;
    
    accumulator = 0; 
    visited.clear(); 
    infinite = false; 
    
    execute(data, visited, accumulator, infinite, 0);
    if (!infinite) 
      return accumulator;
    inst = flip[inst];
  }
  return 0;
}

int main(int argc, char* argv[])
{
  data_t data;
  string path = argv[1];
  ifstream in(path, ios::in);

  for (string line; getline(in, line);)
  {
    string inst = line.substr(0, 3); 
    if (line[4] == '+') data.push_back({inst, stoi(line.substr(5, string::npos))});
    else data.push_back({inst, -stoi(line.substr(5, string::npos))});
  }

  cout << "DAYXX - " << "1: " << solve1(data) << endl;
  cout << "DAYXX - " << "2: " << solve2(data) << endl;
  return 0;
}