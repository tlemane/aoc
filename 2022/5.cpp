#include <utils.hpp>

class cargo
{
  public:

  struct move_t {
    int m {0};
    int f {0};
    int t {0};
    move_t(int m, int f, int t) : m(m), f(f), t(t) {}
  };

  cargo(std::istream& is) { parse(is); }

  void parse(std::istream& is)
  {
    parse_stacks(is);
    parse_procedure(is);
  }

  void parse_stacks(std::istream& is)
  {
    std::vector<std::string> lines;
    for (std::string line; std::getline(is, line);)
    {
      lines.push_back(line);
      if (!line.size()) break;
    }

    lines.pop_back();
    std::vector<int> index;
    for (int i = 0; i < lines.back().size(); ++i)
    {
      if (lines.back()[i] != ' ')
        index.push_back(i);
    }
    lines.pop_back();

    m_stacks.resize(index.size());
    int ii = 0;
    for (auto& i : index)
    {
      for (int j = lines.size()-1; j >= 0; --j)
      {
        if (lines[j].size() > i)
        {
          if (lines[j][i] != ' ')
            m_stacks[ii].push_back(lines[j][i]);
        }
      }
      ++ii;
    }
  }

  void parse_procedure(std::istream& is)
  {
    static std::regex proc_regex("move (\\d+) from (\\d+) to (\\d+)");
    for (std::string line; std::getline(is, line);)
    {
      std::smatch match;
      if (std::regex_match(line, match, proc_regex))
      {
        m_procedure.emplace_back(std::stoll(match[1]), std::stoll(match[2])-1, std::stoll(match[3])-1);
      }
    }
  }

  std::string solve1()
  {
    auto stacks = m_stacks;
    for (auto& p : m_procedure)
    {
      for (int i = 0; i < p.m; ++i)
      {
         if (stacks[p.f].size())
         {
          char c = stacks[p.f].back();
          stacks[p.f].pop_back();
          stacks[p.t].push_back(c);
         }
      }
    }

    std::stringstream ss;
    for (auto& s : stacks)
      ss << s.back();

    return ss.str();
  }

  std::string solve2()
  {
    auto stacks = m_stacks;
    for (auto& p : m_procedure)
    {
      auto s = stacks[p.f].size();
      stacks[p.t].insert(stacks[p.t].end(),  stacks[p.f].begin() + (s - p.m), stacks[p.f].begin() + s);
      stacks[p.f].erase(stacks[p.f].begin() + (s - p.m), stacks[p.f].end());
    }

    std::stringstream ss;
    for (auto& s : stacks)
      ss << s.back();

    return ss.str();
  }

  private:
    std::vector<std::vector<char>> m_stacks;
    std::vector<move_t> m_procedure;
};

auto load_input(const std::string& in_path)
{
  std::ifstream fin(in_path, std::ios::in);
  return cargo(fin);
}

#ifndef BENCH
int main(int argc, char* argv[])
{
  {
    auto test = load_input(input_test(5));
    assert(test.solve1() == "CMZ");
    assert(test.solve2() == "MCD");
  }

  DAY(5);
  auto data = parsing([]() { return load_input(input(5)); });

  PART(1, data.solve1());
  PART(2, data.solve2());
}
#endif
