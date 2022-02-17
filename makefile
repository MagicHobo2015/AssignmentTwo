build: time.cpp
	clang++ -std=c++17 time.cpp -o time

clean: time
	rm ./time
