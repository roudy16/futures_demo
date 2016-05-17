#include "prime_table.h"
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <cassert>
#include <memory>

using std::ceil; using std::sqrt;
using std::ostream; using std::cout;
using std::to_string;
using std::binary_search;
using std::make_shared; using std::shared_ptr;

shared_ptr<PrimeTable> PrimeTable::mp_instance = nullptr;

void PrimeTable::init(uint32_t max_factor) {
    assert(mp_instance == nullptr && "Can only init PrimeTable once");
    mp_instance = make_shared<PrimeTable>(max_factor);
}

PrimeTable* PrimeTable::instance() {
    assert(mp_instance && "Init the PrimeTable first");
    return mp_instance.get();
}

PrimeTable::PrimeTable(uint32_t max_factor) : m_primes{ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31 } {
    assert(max_factor > 0);

    const uint32_t limit = max_factor;

    for (uint32_t i = 37; i <= limit; i++) {
        const uint32_t i_limit = static_cast<uint32_t>(ceil(sqrt(i)));
        bool isPrime = true;

        for (uint32_t j = 0; j < m_primes.size(); j++) {
            // Don't check beyond sqrt
            if (m_primes[j] > i_limit) {
                break;
            }

            // Is number evenly divisable by something
            if (i % m_primes[j] == 0) {
                isPrime = false;
                break;
            }
        }

        if (isPrime) {
            m_primes.push_back(i);
        }
    }
}

bool PrimeTable::contains(uint32_t val) const {
    return binary_search(m_primes.begin(), m_primes.end(), val,
        [](uint32_t lhs, uint32_t rhs) { return lhs < rhs; });
}

ostream& operator<<(ostream& os, const PrimeTable& pt) {
    uint32_t i = 5;
    for (auto val : pt.m_primes) {
        os << to_string(val) + "   ";

        if (i-- == 0) {
            os << '\n';
            i = 5;
        }
    }

    return os;
}
