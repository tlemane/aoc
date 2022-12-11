#include <benchmark/benchmark.h>
#define BENCH
#include "6.cpp"

static void INPUT(benchmark::State& state)
{
  for (auto _ : state)
  {
    auto d = load_input(input(6));
    benchmark::DoNotOptimize(d);
  }
}
BENCHMARK(INPUT)->Unit(benchmark::kMicrosecond);

static void PART_1(benchmark::State& state)
{
  auto d = load_input(input(6));
  for (auto _ : state)
  {
    auto x = find_marker(d, 4);
    benchmark::DoNotOptimize(x);
  }
}
BENCHMARK(PART_1)->Unit(benchmark::kMicrosecond);

static void PART_2(benchmark::State& state)
{
  auto d = load_input(input(6));
  for (auto _ : state)
  {
    auto x = find_marker(d, 14);
    benchmark::DoNotOptimize(x);
  }
}
BENCHMARK(PART_2)->Unit(benchmark::kMicrosecond);

BENCHMARK_MAIN();
