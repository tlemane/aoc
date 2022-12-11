#if 0
ff=$(basename -- "${0}")
fn=${ff%.*}
g++ -o ${fn} ${0} -std=c++17 -O3 -march=native -I.. || exit
./${fn} && exit
#endif

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
    auto test = load_input(input_test(${D}));
    assert(0 == 0);
    assert(0 == 0);
  }

  DAY(${D});
  auto data = parsing([]() { return load_input(input(${D})); });

  PART(1, 0);
  PART(2, 0);
}
#endif
