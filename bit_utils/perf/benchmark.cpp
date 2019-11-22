#include <benchmark/benchmark.h>
#include "../bit_utils.h"

static void Arguments(benchmark::internal::Benchmark* bm){
	unsigned k_list[9] = {1, 2, 4, 7, 16, 21, 32, 47, 64};
	for(auto k: k_list){
		bm->Args({0x0f0f'0f0fU, 0x8000'0000U, k});
		bm->Args({0x0f1f'0f0fU, 0x8000'0000U, k});
		bm->Args({0x0f0f'0f0eU, 0x8000'0000U, k});
		bm->Args({0x0000'ffffU, 0xffff'0000U, k});
		bm->Args({0xffff'ffffU, 0xffff'ffffU, k});
	}
}

static void BM_Index(benchmark::State& state, int(*fn)(const u32&, const u32&, unsigned)) {
  for (auto _ : state){
    int result = fn(state.range(0), state.range(1), state.range(2));
    benchmark::DoNotOptimize(result);
  }
}
// Register the function as a benchmark
BENCHMARK_CAPTURE(BM_Index, index_1, index_1)->Apply(Arguments);
BENCHMARK_CAPTURE(BM_Index, index_2, index_2)->Apply(Arguments);

BENCHMARK_MAIN();
