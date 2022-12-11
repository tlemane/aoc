#include <benchmark/benchmark.h>
#define BENCH
#include "11.cpp"

static void INPUT(benchmark::State& state)
{
  for (auto _ : state)
  {
    auto d = load_input(input(11));
    benchmark::DoNotOptimize(d);
  }
}
BENCHMARK(INPUT)->Unit(benchmark::kMicrosecond);

static void PART_1(benchmark::State& state)
{
  auto d = load_input(input(11));
  for (auto _ : state)
  {
    auto x = rounds(d, 20, 1);
    benchmark::DoNotOptimize(x);
  }
}
BENCHMARK(PART_1)->Unit(benchmark::kMicrosecond);

static void PART_2(benchmark::State& state)
{
  auto d = load_input(input(11));
  for (auto _ : state)
  {
    auto x = rounds(d, 10000, 2);
    benchmark::DoNotOptimize(x);
  }
}
BENCHMARK(PART_2)->Unit(benchmark::kMicrosecond);

BENCHMARK_MAIN();
