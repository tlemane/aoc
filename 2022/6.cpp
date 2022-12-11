#include <utils.hpp>

auto load_input(const std::string& in_path)
{
  std::ifstream fin(in_path, std::ios::in);
  std::string line; std::getline(fin, line);
  return line;
}

int find_marker(const std::string& s, std::size_t w)
{
  for (int i=0; i < s.size() - w + 1; i++)
  {
    std::uint32_t m = 0;
    for (int j = 0; j < w; ++j)
      m |= (1 << (s[i+j] - 'a'));

    if (__builtin_popcount(m) == w)
      return i + w;
  }
  return 0;
}

#ifndef BENCH
int main(int argc, char* argv[])
{
  {
    auto test = load_input(input_test(6));
    assert(find_marker(test, 4) == 7);
    assert(find_marker(test, 14) == 19);
  }

  DAY(6);
  auto data = parsing([]() { return load_input(input(6)); });

  PART(1, find_marker(data, 4));
  PART(2, find_marker(data, 14));
}
#endif
