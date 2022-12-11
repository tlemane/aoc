#include <utils.hpp>

using data_type = std::vector<std::pair<std::uint8_t, std::uint8_t>>;

auto load_input(const std::string& in_path)
{
  data_type d;
  std::ifstream fin(in_path, std::ios::in);

  for (std::string line; std::getline(fin, line);)
    d.emplace_back(line[0] - 'A', line[2] - 'X');

  return d;
}

int score1(char o, char p)
{
  return (o + 1) + ((p - o + 4) % 3) * 3;
}

int score2(char o, char p)
{
  char p2 = (o + p + 2) % 3;
  return (p2 + 1) + p * 3;
}

template<typename T>
int score(const data_type& data, const T&& f)
{
  return std::accumulate(std::begin(data), std::end(data), 0, [&](const auto& a, const auto& b){
    return a + f(b.first, b.second);
  });
}

#ifndef BENCH
int main(int argc, char* argv[])
{
  {
    auto test = load_input(input_test(2));
    assert(score(test, score1) == 15);
    assert(score(test, score2) == 12);
  }

  DAY(2);
  auto data = parsing([]() { return load_input(input(2)); });

  PART(1, score(data, score1));
  PART(2, score(data, score2));
}
#endif
