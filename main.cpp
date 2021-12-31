#define CATCH_CONFIG_RUNNER
#include <iostream>
#include "Stack.h"
#include "catch.hpp"
#include "readInput.h"
void testCases(){
    Catch::Session().run();

}

int main(int argc, char **argv) {
    std::ifstream fin(argv[1]);
    std::ofstream out(argv[2]);
    std::ofstream out1(argv[3]);
    testCases();
    readInput test;
    test.readData(fin);
    test.createAdjList();
    test.findPaths();
    test.findMin(out);
    test.findMax(out1);

}
