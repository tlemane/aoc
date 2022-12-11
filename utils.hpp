#ifndef UTILS_HPP_JFUHAIYW
#define UTILS_HPP_JFUHAIYW

#include <regex>
#include <variant>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <utility>
#include <numeric>
#include <algorithm>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <map>
#include <stack>
#include <queue>
#include <chrono>
#include <cassert>
#include <sstream>
#include <locale>
#include <tuple>
#include <fstream>
#include <array>
#include <bitset>
#include <functional>
#include <cmath>

#define DAY(x) std::cout << "- DAY " << (x) << " -" << std::endl;

#define GREEN "\033[1;32m"
#define RED "\033[1;32m"
//#define RED "\033[1;31m"
#define END "\033[0m"

#define TIME1(p) \
  auto start##p = std::chrono::steady_clock::now() \

#define TIME2(p) \
  auto elapsed##p = std::chrono::steady_clock::now() - start##p; \
  std::cout << (std::chrono::duration_cast<std::chrono::microseconds>(elapsed##p).count() > 500 ? RED : GREEN); \
  std::cout << " [" << std::chrono::duration_cast<std::chrono::microseconds>(elapsed##p).count() << "μs]"; \
  std::cout << END \

#define PART(p,exp) \
  auto rrr##p = exp; \
  std::cout << p << " -> "; \
  std::cout << rrr##p; \
  std::cout << (p == 2 ? "\n\n" : "\n");

#define PARSING1 TIME1(0)
#define PARSING2 TIME2(0)
std::string input_test(unsigned day)
{
  std::ostringstream ss;
  ss << "data/input" << day << ".test";
  return ss.str();
}

std::string input(unsigned day)
{
  std::ostringstream ss;
  ss << "data/input" << day;
  return ss.str();
}

template<typename T>
auto parsing(T&& f)
{
  // TIME1(0);
  auto d = f();
  // std::cout << "Parsing ->";
  // TIME2(0);
  // std::cout << '\n';
  return d;
}

template<char C>
struct stream_sep : std::ctype<char>
{
  stream_sep(): std::ctype<char>(get_table()) {}
  static const std::ctype_base::mask* get_table()
  {
    static std::vector<std::ctype_base::mask> rc(table_size, std::ctype_base::mask());
    rc[C] = std::ctype_base::space;
    return &rc[0];
  }
};

template<typename T>
void print_vec(const std::vector<T>& v)
{
  std::cout << "[";
  for (auto&& e : v)
  {
    if constexpr(std::is_same_v<T, std::uint8_t>)
      std::cout << std::to_string(e) << ",";
    else
      std::cout << e << ",";
  }
  std::cout << "]" << std::endl;
}

template<typename T, std::size_t S>
void print_arr(const std::array<T, S>& v)
{
  std::cout << "[";
  for (auto&& e : v)
  {
    if constexpr(std::is_same_v<T, std::uint8_t>)
      std::cout << std::to_string(e) << ",";
    else
      std::cout << e << ",";
  }
  std::cout << "]" << std::endl;
}

template<typename T, typename I, typename P>
unsigned aoc_count_if(I first, I last, T n, P p)
{
  unsigned count = 0;
  for (std::size_t i=0; first != last; i++, first++)
    if (p(i) && *first == n)
      count++;
  return count;
}

template<typename... Args>
void cprint(Args&&... args)
{
  ((std::cout << args << ' '), ...) << "\n";
}

namespace std {
  template<typename T>
  T max(const std::pair<T, T>& p)
  {
    return std::max(p.first, p.second);
  }

  template<typename T>
  struct hash<std::tuple<T, T, T, T>>
  {
    std::size_t operator()(const std::tuple<T, T, T, T>& t) const
    {
      return std::get<0>(t) ^ std::get<1>(t) ^ std::get<2>(t) ^ std::get<3>(t);
    }
  };
}

#endif /* end of include guard: UTILS_HPP_JFUHAIYW */
