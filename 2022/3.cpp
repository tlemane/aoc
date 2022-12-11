#include <utils.hpp>
#include <bitset>

using data_type = std::vector<std::pair<std::uint64_t, std::uint64_t>>;

auto pack(const std::string_view sv)
{
  return std::accumulate(std::begin(sv), std::end(sv), 0ULL, [](const auto& a, const auto& b){
    return a | (1ULL << (b - (b > 90 ? 97 : 39)));
  });
}

unsigned priority(const std::pair<std::uint64_t, std::uint64_t>& pb)
{
  return 64 - __builtin_clzll(pb.first & pb.second);
}

unsigned sum(const data_type& data)
{
  return std::accumulate(std::begin(data), std::end(data), 0, [](const auto& a, const auto& b){
    return a + priority(b);
  });
}

unsigned sumg(const data_type& data)
{
  unsigned s = 0;
  for (std::size_t i = 0; i < data.size(); i += 3)
  {
    s += 64 - __builtin_clzll((data[i].first | data[i].second) &
                              (data[i+1].first | data[i+1].second) &
                              (data[i+2].first | data[i+2].second));
  }
  return s;
}

auto load_input(const std::string& in_path)
{
  data_type d;
  std::ifstream fin(in_path, std::ios::in);
  for (std::string line; std::getline(fin, line);)
  {
    auto s = line.size()/2;
    d.emplace_back(pack(std::string_view(line.data(), s)),
                   pack(std::string_view(line.data()+s, s)));
  }
  return d;
}

#ifndef BENCH
int main(int argc, char* argv[])
{
  {
    auto test = load_input(input_test(3));
    assert(sum(test) == 157);
    assert(sumg(test) == 70);
  }

  DAY(3);
  auto data = parsing([]() { return load_input(input(3)); });

  PART(1, sum(data));
  PART(2, sumg(data));
}
#endif
