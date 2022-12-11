#include <utils.hpp>

using type = std::pair<char, int>;
using data_type = std::vector<type>;

auto load_input(const std::string& in_path)
{
  std::ifstream fin(in_path, std::ios::in);
  data_type d;

  for (std::string line; std::getline(fin, line);)
  {
    if (line[0] == 'a')
      d.emplace_back(line[0], std::stoi(line.substr(5)));
    else
      d.emplace_back(line[0], 0);

  }
  return d;
}

int signal(const data_type& d)
{
  unsigned c = 0;
  unsigned s = 0;
  int X = 1;

  int next = 20;
  int step = 40;
  for (auto& [o, i] : d)
  {
    switch (o)
    {
      case 'a':
        if (c + 2 < next)
        {
          X += i;
        }
        else
        {
          s += (next * X);
          next += step;
          X += i;
        }
        c += 2;
        break;
      case 'n':
        c += 1;
        break;

    }
  }
  return s;
}

std::string draw(const data_type& d, char cc = '.')
{
  std::stringstream ss;

  int X = 1;
  int p = 0;

  for (auto& [o, i] : d)
  {
    for (int j = 0; j <= (o == 'a') ? 1 : 0; ++j)
    {
      if (std::abs(p - X) <= 1)
        ss << '#';
      else
        ss << cc;

      ++p;

      if (p == 40)
      {
        ss << '\n';
        p = 0;
      }
    }

    if (o == 'a')
      X += i;
  }
  return ss.str();
}

const std::string part2 =
  "##..##..##..##..##..##..##..##..##..##..\n"
  "###...###...###...###...###...###...###.\n"
  "####....####....####....####....####....\n"
  "#####.....#####.....#####.....#####.....\n"
  "######......######......######......####\n"
  "#######.......#######.......#######.....\n";


#ifndef BENCH
int main(int argc, char* argv[])
{
  {
    auto test = load_input(input_test(10));
    assert(signal(test) == 13140);
    assert(draw(test) == part2);
  }

  DAY(10);
  auto data = parsing([]() { return load_input(input(10)); });

  PART(1, signal(data));
  PART(2, "\n" + draw(data, ' '));
}
#endif
