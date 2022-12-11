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
  std::vector<int> data;

  for (std::string line; std::getline(fin, line);)
  {
    data.push_back(0);
    while (!line.empty())
    {
      data.back() += std::stoll(line);
      std::getline(fin, line);
    }
  }
  return data;
}

int find_max(const std::vector<int>& data)
{
  return *std::max_element(std::begin(data), std::end(data));
}

int find_max3(const std::vector<int>& data)
{
  int s1 = 0, s2 = 0, s3 = 0;

  for (auto& s : data)
  {
    if (s > s3)
    {
      s3 = s;

      if (s > s2)
      {
        std::swap(s3, s2);
        s2 = s;

        if (s > s1)
        {
          std::swap(s2, s1);
          s1 = s;
        }
      }
    }
  }

  return s1 + s2 + s3;
}

#ifndef BENCH
int main(int argc, char* argv[])
{
  {
    auto test = load_input(input_test(1));
    assert(find_max(test) == 24000);
    assert(find_max3(test) == 45000);
  }

  DAY(1);
  auto data = parsing([]() { return load_input(input(1)); });

  PART(1, find_max(data));
  PART(2, find_max3(data));
}
#endif
