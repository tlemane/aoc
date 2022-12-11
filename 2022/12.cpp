#include <utils.hpp>

auto load_input(const std::string& in_path)
{
  std::ifstream fin(in_path, std::ios::in);
  return 0;
}

#ifndef BENCH
int main(int argc, char* argv[])
{
  {
    auto test = load_input(input_test(12));
    assert(0 == 0);
    assert(0 == 0);
  }

  DAY(12);
  auto data = parsing([]() { return load_input(input(12)); });

  PART(1, 0);
  PART(2, 0);
}
#endif
