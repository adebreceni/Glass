BUILD_DIR=./build

ALL: raw_benchmark sanitize
	
build_dir:
	mkdir -p ./build

build_benchmark: build_dir
	g++ -std=c++17 benchmark.cpp -isystem $(GBENCH)/include -L$(GBENCH_LIB) -lbenchmark -lpthread -o $(BUILD_DIR)/benchmark

raw_benchmark: build_benchmark
	$(BUILD_DIR)/benchmark --benchmark_out=$(BUILD_DIR)/raw_result.json --benchmark_out_format=json

sanitize: $(BUILD_DIR)/raw_result.json
	cat $(BUILD_DIR)/raw_result.json | node ./sanitize.js > ./result.json
	
