#include <utils.hpp>

using data_type = std::vector<std::vector<unsigned>>;

auto load_input(const std::string& in_path)
{
  data_type d;

  std::ifstream fin(in_path, std::ios::in);

  for (std::string line; std::getline(fin, line);)
  {
    d.push_back({});
    for(auto& c : line)
      d.back().push_back(c - '0');
  }
  return d;
}

unsigned check(const data_type& d, unsigned i, unsigned j)
{

  auto v = d[i][j];
  bool vi0 = true, vi1 = true, vi2 = true, vi3 = true;

  for (int ii = i + 1; ii < d.size(); ++ii)
  {
    if (v <= d[ii][j])
    {
      vi0 = false;
      break;
    }
  }

  for (int ii = i - 1; ii >= 0; --ii)
  {
    if (v <= d[ii][j])
    {
      vi1 = false;
      break;
    }
  }

  for (int jj = j + 1; jj < d[0].size(); ++jj)
  {
    if (v <= d[i][jj])
    {
      vi2 = false;
      break;
    }
  }

  for (int jj = j - 1; jj >= 0; --jj)
  {
    if (v <= d[i][jj])
    {
      vi3 = false;
      break;
    }
  }
  return vi0 || vi1 || vi2 || vi3;
}

unsigned check2(const data_type& d, unsigned i, unsigned j)
{

  auto v = d[i][j];
  int vi0 = 0, vi1 = 0, vi2 = 0, vi3 = 0;

  for (int ii = i + 1; ii < d.size(); ++ii)
  {
    if (v > d[ii][j])
      ++vi0;
    else
    {
      ++vi0;
      break;
    }
  }

  for (int ii = i - 1; ii >= 0; --ii)
  {
    if (v > d[ii][j])
      ++vi1;
    else
    {
      ++vi1;
      break;
    }
  }

  for (int jj = j + 1; jj < d[0].size(); ++jj)
  {
    if (v > d[i][jj])
      ++vi2;
    else
    {
      ++vi2;
      break;
    }
  }

  for (int jj = j - 1; jj >= 0; --jj)
  {
    if (v > d[i][jj])
      ++vi3;
    else
    {
      ++vi3;
      break;
    }
  }
  return vi0 * vi1 * vi2 * vi3;
}

unsigned count_visible(const data_type& d)
{
  unsigned c = 0;

  for (std::size_t i = 1; i < d.size() - 1; ++i)
  {
    for (std::size_t j = 1; j < d[0].size() - 1; ++j)
    {
      c += check(d, i, j);
    }
  }

  return c + (d.size() * 2) + (d[0].size() * 2) - 4;
}

unsigned count_distance(const data_type& d)
{
  unsigned c = 0;

  for (std::size_t i = 1; i < d.size() - 1; ++i)
  {
    for (std::size_t j = 1; j < d[0].size() - 1; ++j)
    {
      c = std::max(c, check2(d, i, j));
    }
  }
  return c;
}

#ifndef BENCH
int main(int argc, char* argv[])
{
  {
    auto test = load_input(input_test(8));
    assert(count_visible(test) == 21);
    assert(count_distance(test) == 8);
  }

  DAY(8);
  auto data = parsing([]() { return load_input(input(8)); });

  PART(1, count_visible(data));
  PART(2, count_distance(data));
}
#endif
