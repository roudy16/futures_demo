#include "prime_factorization.h"
#include <string>
#include <algorithm>
#include <cassert>
#include <cmath>

using std::vector; using std::pair;
using std::cout; using std::ostream;
using std::string; using std::to_string;
using std::binary_search; using std::is_sorted; using std::lower_bound;
using std::sqrt; using std::ceil;

// compiler should optimize this to one division operation, let's hope
inline pair<uint32_t, uint32_t> divmod(uint32_t x, uint32_t y) {
    return { x / y, x % y };
}

PrimeFactorization::PrimeFactorization(uint32_t num) : m_num(num) {
    // case where num is prime
    if (num <= 1 || PrimeTable::instance()->contains(num)) {
        add_factor(num);
        return;
    }

    for (uint32_t i = 0; i < PrimeTable::instance()->size(); i++) {
        auto dm = divmod(num, (*PrimeTable::instance())[i]);

        while (dm.second == 0) {
            num = dm.first;
            add_factor((*PrimeTable::instance())[i]);
            dm = divmod(num, (*PrimeTable::instance())[i]);
        }

        if (num == 1) {
            break;
        }
    }

}

bool PrimeFactorization::element_compare(const Factor& lhs, const Factor& rhs) {
    return lhs.get_base() < rhs.get_base();
}

bool PrimeFactorization::contains_factor(uint32_t f) const {
    assert(is_sorted(m_factors.begin(), m_factors.end(), &PrimeFactorization::element_compare));

    Factor factor(f, 0);
    return binary_search(m_factors.begin(), m_factors.end(), factor,
                         &PrimeFactorization::element_compare);
}

void PrimeFactorization::add_factor(uint32_t base) {
    assert(is_sorted(m_factors.begin(), m_factors.end(), &PrimeFactorization::element_compare));
    assert(m_factors.empty() || base >= m_factors.back().get_base());

    auto it = m_factors.rbegin();

    if (m_factors.empty() || base > it->get_base()) {
        m_factors.emplace_back(Factor(base, 1));
    }
    else {
        it->m_base_mult.second++;
    }
}

ostream& operator<<(ostream& os, const PrimeFactorization& pf) {
    assert(!pf.m_factors.empty());
    os << to_string(pf.m_num) + ": ";

    for (uint32_t i = 0; i < pf.m_factors.size() - 1; i++) {
        os << to_string(pf.m_factors[i].get_base()) + '^' + to_string(pf.m_factors[i].get_mult()) + " * ";
    }

    os << to_string(pf.m_factors.rbegin()->get_base()) + '^' + to_string(pf.m_factors.rbegin()->get_mult()) + '\n';

    return os;
}
