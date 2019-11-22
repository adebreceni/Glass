BUILD_DIR=./build

ALL: test

build_dir:
	mkdir -p ./build

build_test: build_dir
	g++ -std=c++17 test.cpp -isystem $(GTEST)/include -L$(GTEST_LIB) -lgtest -lgtest_main -lpthread -o $(BUILD_DIR)/test

test: build_test
	$(BUILD_DIR)/test > $(BUILD_DIR)/result.txt

