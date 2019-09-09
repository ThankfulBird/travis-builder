make clean
make
./test/travis.test.out
gcov ./lib/travis.h
