# use g++ with C++11 support
CXX=g++
CXXFLAGS?=-Wall -pedantic -g -O0 -std=c++11 -fsanitize=address,undefined
OUTFILES=compress uncompress

all: $(OUTFILES)

compress: compress.cpp Helper.cpp HCTree.cpp Helper.hpp HCTree.hpp
	$(CXX) $(CXXFLAGS) -o compress compress.cpp Helper.cpp HCTree.cpp

uncompress: uncompress.cpp Helper.cpp HCTree.cpp Helper.hpp HCTree.hpp
	$(CXX) $(CXXFLAGS) -o uncompress uncompress.cpp Helper.cpp HCTree.cpp

gprof: compress.cpp uncompress.cpp Helper.cpp HCTree.cpp Helper.hpp HCTree.hpp
	make clean
	$(CXX) $(CXXFLAGS) -pg -o compress compress.cpp Helper.cpp HCTree.cpp
	$(CXX) $(CXXFLAGS) -pg -o uncompress uncompress.cpp Helper.cpp HCTree.cpp

clean:
	rm -f $(OUTFILES) *.o
