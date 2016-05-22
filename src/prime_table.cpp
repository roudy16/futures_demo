#include "prime_table.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <cassert>
#include <memory>
#include <utility>
#include <fstream>
#include <exception>
#include <iostream>

using std::vector;
using std::ceil; using std::sqrt;
using std::ostream; using std::cout;
using std::to_string; using std::string;
using std::binary_search;
using std::make_shared; using std::shared_ptr;
using std::ofstream;
using std::runtime_error;
using std::cout;
using std::move;

shared_ptr<PrimeTable> PrimeTable::mp_instance = nullptr;

void PrimeTable::init(Element_t max_factor) {
    assert(mp_instance == nullptr && "Can only init PrimeTable once");
    mp_instance = make_shared<PrimeTable>(max_factor);
}

void PrimeTable::init(string filename) {
    assert(mp_instance == nullptr && "Can only init PrimeTable once");
    mp_instance = make_shared<PrimeTable>(filename);
}

PrimeTable* PrimeTable::instance() {
    assert(mp_instance && "Init the PrimeTable first");
    return mp_instance.get();
}

PrimeTable::PrimeTable(string filename) {


}

PrimeTable::PrimeTable(Element_t max_factor, CtorAlgorithm alg)
    : m_primes{ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31 }
{
    assert(max_factor > 0);

    const Element_t limit = max_factor;

    switch (alg) {
    case CtorAlgorithm::NAIVE:
        for (Element_t i = 37; i <= limit; i++) {
            const Element_t i_limit = static_cast<Element_t>(ceil(sqrt(i)));
            bool isPrime = true;

            for (Element_t j = 0; j < m_primes.size(); j++) {
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
        break;

    case CtorAlgorithm::RESTRICTED_MEMORY_ERATOSTHENES:
        break;

    default:
        throw runtime_error("Something horked up with PrimeTable Ctor, default case hit");
    }
}

bool PrimeTable::contains(Element_t val) const {
    return binary_search(m_primes.begin(), m_primes.end(), val,
        [](Element_t lhs, Element_t rhs) { return lhs < rhs; });
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

/* Loads a prime number table from a binary file. The format of the binary file is as follows:
    size_t number_of_elements
    size_t size_of_each_element
    element_t[] elements
*/
bool PrimeTable::saveToFile(std::string filename) const {
    bool success = false;
    ofstream fs;
    const size_t pt_size = m_primes.size();
    constexpr size_t element_size = sizeof(PrimeTable::Element_t);

    try {
        fs.open(filename, std::ios_base::out | std::ios_base::binary);
        if (!fs.is_open()) {
            throw runtime_error(filename + " was not found.");
        }

        fs.write(reinterpret_cast<const char*>(&pt_size), sizeof(size_t));
        fs.write(reinterpret_cast<const char*>(&element_size), sizeof(size_t));
        fs.write(reinterpret_cast<const char*>(m_primes.data()), pt_size * element_size);
        success = true;
    }
    catch (runtime_error &e) {
        cout << e.what() << '\n';
    }
    catch (...) {
        // TODO do something here if needed
    }

    fs.close();
    return success;
}

