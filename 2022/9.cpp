#include <utils.hpp>
#include <cmath>
#include <list>

using type = std::pair<int, int>;
using data_type = std::vector<type>;

auto load_input(const std::string& in_path)
{
  data_type d;
  std::ifstream fin(in_path, std::ios::in);

  for (std::string line; std::getline(fin, line);)
    d.emplace_back(line[0], std::stoull(line.substr(2)));

  return d;
}

//std::ostream& operator<<(std::ostream& os, type p)
//{
//  os << '(' << p.first << ',' << p.second << ')';
//  return os;
//}
//
//void show(type h, type t)
//{
//  std::vector<std::string> v;
//
//  for (std::size_t i = 0; i < 20; ++i)
//  {
//    std::stringstream ss;
//    for (std::size_t j = 0; j < 20; ++j)
//    {
//      if (i == 0 && j == 0)
//      {
//        ss << 's';
//        continue;
//      }
//
//      if (h.first == i && h.second == j)
//      {
//        ss << 'H';
//      }
//      else if (t.first == i && t.second == j)
//      {
//        ss << 'T';
//      }
//      else
//      {
//        ss << '.';
//      }
//    }
//    v.push_back(ss.str());
//  }
//
//  //for (auto& sss : v)
//  //  std::cout << sss << std::endl;
//  for (int i = v.size() - 1; i >= 0; --i)
//    std::cout << v[i] << std::endl;
//  std::cout << std::endl;
//}
//
//
//void show_one(char n, const type& t)
//{
//  std::cout << n << '=' << t << std::endl;
//}

void move_head(char m, type& head)
{
  switch (m)
  {
    case 'R':
      ++head.second;
      break;
    case 'L':
      --head.second;
      break;
    case 'U':
      ++head.first;
      break;
    case 'D':
      --head.first;
      break;
  }
}

bool is_adj(const type& head, const type& tail)
{
  if (std::abs(head.first - tail.first) > 1 || std::abs(head.second - tail.second) > 1)
    return false;
  return true;
}

void move_tail(char m, const type& head, type& tail)
{
  if (!is_adj(head, tail))
  {
    if (head.first != tail.first)
      tail.first += head.first > tail.first ? 1 : -1;

    if (head.second != tail.second)
      tail.second += head.second > tail.second ? 1 : -1;
  }
}

namespace std {
template<>
struct hash<type>
{
  inline std::size_t operator()(const type& p) const
  {
    return p.first * 31 ^ p.second * 17;
  }
};
}

unsigned count(const data_type& d)
{
  std::unordered_set<type> ps;

  type h = {0, 0};
  type t = {0, 0};

  for (auto& [s, n] : d)
  {
    for (std::size_t i = 0; i < n; ++i)
    {
      move_head(s, h);
      move_tail(s, h, t);
      ps.insert(t);
    }
  }
  return ps.size();
}

unsigned count2(const data_type& d)
{
  std::unordered_set<type> ps;

  std::vector<type> knots(10);

  for (auto& [s, n] : d)
  {
    for (std::size_t i = 0; i < n; ++i)
    {
      auto& head = knots[0];
      move_head(s, head);

      for (int j = 1; j < knots.size(); ++j)
      {
        auto& head2 = knots[j - 1];
        auto& tail = knots[j];
        move_tail(s, head2, tail);
      }

      ps.insert(knots.back());
    }
  }

  return ps.size();
}

#ifndef BENCH
int main(int argc, char* argv[])
{
  {
    auto test = load_input(input_test(9));
    assert(count(test) == 13);
    assert(count2(test) == 1);
  }

  DAY(9);
  auto data = parsing([]() { return load_input(input(9)); });

  PART(1, count(data));
  PART(2, count2(data));
}
#endif
