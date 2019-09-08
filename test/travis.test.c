#include "../lib/travis.h"

int main(int argc, char *argv[])
{ 
    configure_travis_project(argv[1]);
    return 0;
}