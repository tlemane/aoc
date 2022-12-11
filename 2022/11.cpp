#include <utils.hpp>

class monkey
{
  public:
    monkey(std::istream& is)
    {
      std::string monkey; std::getline(is, monkey);
      m_id = monkey[7] - '0';

      std::string items; std::getline(is, items);
      std::string operation; std::getline(is, operation);
      std::string test; std::getline(is, test);
      std::string ttrue; std::getline(is, ttrue);
      std::string tfalse; std::getline(is, tfalse);

      parse(items, operation, test, ttrue, tfalse);
      std::getline(is, monkey);
    }

    auto& op() { return m_op; }
    auto& test() { return m_test; }
    auto& items() { return m_items; }
    auto& div() { return m_n; }
  private:

    void parse(std::string& items,
               std::string& operation,
               std::string& test,
               std::string& ttrue,
               std::string& tfalse)
    {
      { // parse items
        items = items.substr(items.find(": ") + 1);
        int i;
        char c;
        std::stringstream ss(items);

        while (ss)
        {
          ss >> i >> c;
          m_items.push(i);
        }
      }

      { // parse operation
        char op;
        char s[32];

        std::sscanf(operation.c_str(), "  Operation: new = old %c %s", &op, s);

        int n = 0;
        if (s[0] == 'o')
          n = -1;
        else
          n = std::atoi(s);
        m_op = get_op(op, n);
      }

      { // parse test
        int n, x, y;
        std::sscanf(test.c_str(), "  Test: divisible by %d", &n);
        std::sscanf(ttrue.c_str(), "    If true: throw to monkey %d", &x);
        std::sscanf(tfalse.c_str(), "    If false: throw to monkey %d", &y);
        m_test = get_test(n, x, y);
        m_n = n;
      }
    }

    std::function<std::int64_t(std::int64_t)> get_test(int n, std::int64_t x, std::int64_t y)
    {
      return [n, x, y](int v) -> int{ return v % n == 0 ? x : y; };
    }

    std::function<std::int64_t(std::int64_t)> get_op(char op, std::int64_t n)
    {
      if (op == '*')
      {
        if (n == - 1)
          return [](std::int64_t v) -> std::int64_t { return v * v; };
        else
          return [n](std::int64_t v) -> std::int64_t { return v * n; };
      }
      else
      {
        if (n == - 1)
          return [](std::int64_t v) -> std::int64_t { return v + v; };
        else
          return [n](std::int64_t v) -> std::int64_t { return v + n; };
      }
    }

  private:
    int m_id;
    std::queue<std::int64_t> m_items;
    std::function<std::int64_t(std::int64_t)> m_op;
    std::function<std::int64_t(std::int64_t)> m_test;
    int m_n;
};

using data_type = std::vector<monkey>;

auto load_input(const std::string& in_path)
{
  data_type d;
  std::ifstream fin(in_path, std::ios::in);

  while (fin)
    d.emplace_back(fin);

  auto w = std::accumulate(std::begin(d), std::end(d), 1, [](const auto& a, auto& b){
    return a * b.div();
  });

  for (auto& m : d)
    m.div() = w;

  return d;
}

unsigned long rounds(data_type& dd, int nr, int p)
{
  auto d = dd;
  std::vector<std::int64_t> count(d.size(), 0);

  for (int nn = 0; nn < nr; ++nn)
  {
    int mi = 0;
    for (auto& m : d)
    {
      while (m.items().size() > 0)
      {
        auto i = m.items().front();
        auto l = p == 1 ? m.op()(i) / 3 : m.op()(i) % m.div();
        auto nm = m.test()(l);
        d[nm].items().push(l);
        m.items().pop();
        ++count[mi];
      }
      mi++;
    }
  }

  std::sort(count.begin(), count.end(), std::greater<std::int64_t>{});
  return count[0] * count[1];
}

#ifndef BENCH
int main(int argc, char* argv[])
{
  {
    auto test = load_input(input_test(11));
    assert(rounds(test, 20, 1) == 10605);
    assert(rounds(test, 10000, 2) == 2713310158);
  }

  DAY(11);
  auto data = parsing([]() { return load_input(input(11)); });
  PART(1, rounds(data, 20, 1));
  PART(2, rounds(data, 10000, 2));
}
#endif
