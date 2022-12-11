#include <utils.hpp>

class fs
{
  enum class out_type {
    cd, ls, dir, f
  };

  enum out_type get_type(const std::string& s)
  {
    if (s[0] == '$')
      return s[2] == 'c' ? out_type::cd : out_type::ls;

    return s[0] == 'd' ? out_type::dir : out_type::f;
  }

  struct directory
  {
    directory(const std::string& name, directory* p = nullptr) : name(name), parent(p) {}

    std::string name;
    directory* parent {nullptr};
    std::unordered_map<std::string, directory*> sub;
    std::size_t size {0};

    unsigned sum(int m = std::numeric_limits<unsigned>::max())
    {
      return size + std::accumulate(std::begin(sub), std::end(sub), 0, [&](const auto& a, const auto& b){
        return a + b.second->sum(m);
      });
    }
  };

  void op_dir(const std::string& line)
  {
    auto name = line.substr(4);
    m_current->sub[name] = new directory(name, m_current);
    m_dir.push_back(m_current->sub[name]);
  }

  void op_cd(const std::string& line)
  {
    if (line[5] == '/')
      return;
    if (line[5] == '.')
      m_current = m_current->parent;
    else
      m_current = m_current->sub[line.substr(5)];
  }

  void op_f(const std::string& line)
  {
    std::stringstream ss(line);
    unsigned i;
    ss >> i;
    m_current->size += i;
  }

  public:
    fs()
    {
      m_root = new directory("/");
      m_current = m_root;
      m_dir.push_back(m_root);
    }

    ~fs()
    {
      for (auto& d : m_dir)
        delete d;
    }

    unsigned sum(unsigned m = 100000)
    {
      return std::accumulate(std::begin(m_dir), std::end(m_dir), 0, [&](const auto& a, const auto& b){
        auto s = b->sum(m);
        return s <= m ? a + s : a;
      });
    }

    unsigned del(unsigned space = 70000000, unsigned required = 30000000)
    {
      auto root_size = m_root->sum();
      auto need = required - (space - root_size);
      auto f = [&need](const auto& a, const auto& b){
        auto s = b->sum();
        return s >= need ? std::min(s, a) : a;
      };
      return std::accumulate(std::begin(m_dir), std::end(m_dir), std::numeric_limits<unsigned>::max(), f);
    }

    void parse(std::istream& is)
    {
      m_current = m_root;
      for (std::string line; std::getline(is, line);)
      {
        auto t = get_type(line);
        switch (t)
        {
          case out_type::cd:
            op_cd(line);
            break;
          case out_type::ls:
            break;
          case out_type::dir:
            op_dir(line);
            break;
          case out_type::f:
            op_f(line);
            break;
        }
      }
    }

  private:
    directory* m_root {nullptr};
    directory* m_current {nullptr};
    std::vector<directory*> m_dir;

};

auto load_input(const std::string& in_path)
{
  std::ifstream fin(in_path, std::ios::in);
  fs f;
  f.parse(fin);
  return f;
}

#ifndef BENCH
int main(int argc, char* argv[])
{
  {
    auto test = load_input(input_test(7));
    assert(test.sum(100000) == 95437);
    assert(test.del() == 24933642);
  }

  DAY(7);
  auto data = parsing([]() { return load_input(input(7)); });

  PART(1, data.sum(100000));
  PART(2, data.del());
}
#endif
