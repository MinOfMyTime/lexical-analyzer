#include "Scanner.h"
#include <iostream>
using namespace std;

int main() {
    
    char filename[] = "test.txt";
    FileDescriptor file(filename);
    Scanner scanner(file);
    scanner.scan();
    return 0;
}