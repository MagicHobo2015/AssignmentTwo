# this will compile time_shm.cpp to a file named timeShm.exe
build: time_shm.cpp
	clang++ -std=c++17 time_shm.cpp -o timeShm.exe -lrt

# gonna change the commands when there are two seperate files to build in here.
# just starting with the shared mem version..

# this just cleans up the binaries
clean: timeShm.exe
	rm ./*.exe
