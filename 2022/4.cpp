#include <utils.hpp>
#include <charconv>

struct section {
  int b1 {0};
  int e1 {0};
  int b2 {0};
  int e2 {0};
};

using data_type = std::vector<struct section>;

auto load_input(const std::string& in_path)
{
  data_type d;
  std::ifstream fin(in_path, std::ios::in);

  for (std::string line; std::getline(fin, line);)
  {
    struct section s;

    auto i = std::find(std::begin(line), std::end(line), '-');
    auto i2 = std::find(i, std::end(line), ',');
    auto i3 = std::find(i2, std::end(line), '-');

    std::from_chars(line.data(), &(*i), s.b1);
    std::from_chars(&(*i)+1, &(*i2), s.e1);
    std::from_chars(&(*i2)+1, &(*i3), s.b2);
    std::from_chars(&(*i3)+1, line.data() + line.size(), s.e2);

    d.push_back(std::move(s));
  }

  return d;
}

int contain(const section& s)
{
  return ((s.b1 - s.b2) * (s.e1 - s.e2)) <= 0;
}

int overlap(const section& s)
{
  return std::max(s.b1, s.b2) <= std::min(s.e1, s.e2);
}

template<typename F>
int count(const data_type& d, const F&& f)
{
  return std::accumulate(std::begin(d), std::end(d), 0, [&](const auto& a, const auto& b){
    return a + f(b);
  });
}

#ifndef BENCH
int main(int argc, char* argv[])
{
  {
    auto test = load_input(input_test(4));
    assert(count(test, contain) == 2);
    assert(count(test, overlap) == 4);
  }

  DAY(4);
  auto data = parsing([]() { return load_input(input(4)); });

  PART(1, count(data, contain));
  PART(2, count(data, overlap));
}
#endif
