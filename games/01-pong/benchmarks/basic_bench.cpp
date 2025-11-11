// Basic benchmark to validate benchmarking system
#include <benchmark/benchmark.h>

// Benchmark example: simple addition
static void BM_SimpleAddition(benchmark::State &state) {
    int sum = 0;
    for (auto _ : state) {
        sum += 1;
        benchmark::DoNotOptimize(sum);
    }
}
BENCHMARK(BM_SimpleAddition);

// Benchmark example: vector operations (will be useful for Pong)
static void BM_VectorAddition(benchmark::State &state) {
    struct Vec2 {
        float x, y;
    };
    Vec2 a{1.0f, 2.0f};
    Vec2 b{3.0f, 4.0f};
    Vec2 result{0.0f, 0.0f};

    for (auto _ : state) {
        result.x = a.x + b.x;
        result.y = a.y + b.y;
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(BM_VectorAddition);

BENCHMARK_MAIN();
