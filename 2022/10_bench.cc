#include <benchmark/benchmark.h>
#define BENCH
#include "10.cpp"

static void INPUT(benchmark::State& state)
{
  for (auto _ : state)
  {
    auto d = load_input(input(10));
    benchmark::DoNotOptimize(d);
  }
}
BENCHMARK(INPUT)->Unit(benchmark::kMicrosecond);

static void PART_1(benchmark::State& state)
{
  auto d = load_input(input(10));
  for (auto _ : state)
  {
    auto x = signal(d);
    benchmark::DoNotOptimize(x);
  }
}
BENCHMARK(PART_1)->Unit(benchmark::kMicrosecond);

static void PART_2(benchmark::State& state)
{
  auto d = load_input(input(10));
  for (auto _ : state)
  {
    auto x = draw(d);
    benchmark::DoNotOptimize(x);
  }
}
BENCHMARK(PART_2)->Unit(benchmark::kMicrosecond);

BENCHMARK_MAIN();
