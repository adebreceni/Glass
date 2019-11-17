BUILD_DIR=./build

ALL: test benchmark
	
build_dir:
	mkdir -p ./build

build_test: build_dir
	g++ -std=c++17 test.cpp -isystem $(GTEST)/include -L$(GTEST_LIB) -lgtest -lgtest_main -lpthread -o $(BUILD_DIR)/test

test: build_test
	$(BUILD_DIR)/test

build_benchmark:
	g++ -std=c++17 benchmark.cpp -isystem $(GBENCH)/include -L$(GBENCH_LIB) -lbenchmark -lpthread -o $(BUILD_DIR)/benchmark

benchmark: build_benchmark
	$(BUILD_DIR)/benchmark --benchmark_out=$(BUILD_DIR)/benchmark_result.csv --benchmark_out_format=csv

	
