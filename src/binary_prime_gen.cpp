#include "prime_table.h"

int main(int argc, char** argv) {
    PrimeTable::init(UINT32_MAX / 2);

    PrimeTable::instance()->saveToFile();

    kPRIMETABLEBLOBNAME;

    return 0;
}
