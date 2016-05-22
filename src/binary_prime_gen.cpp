#include "prime_table.h"
#include <fstream>
#include <string>
#include <vector>


using std::ofstream; using std::string;


int main(int argc, char** argv) {
    PrimeTable::init(UINT32_MAX / 2);

    PrimeTable::instance()->saveToFile();

    return 0;
}
