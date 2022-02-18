# this will compile time.cpp to a file named timeShm
build: time_shm.cpp
	clang++ -std=c++17 time_shm.cpp -o timeShm.exe



clean: timeShm.exe
	rm ./time_shm time
