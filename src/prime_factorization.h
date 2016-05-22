#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <cassert>

#include "prime_table.h"

class PrimeFactorization {
public:
    PrimeFactorization(uint32_t num);
    PrimeFactorization() : m_factors{ Factor(0, 0) }, m_num(0) {}
    PrimeFactorization(PrimeFactorization&& o) = default;
    PrimeFactorization& operator=(PrimeFactorization&&) = default;

    void add_factor(uint32_t base);
    bool contains_factor(uint32_t f) const;


    friend std::ostream& operator<<(std::ostream& os, const PrimeFactorization& pf);

    struct Factor {
        Factor(uint32_t b, uint32_t m) : m_base_mult(b, m) {}
        Factor(const Factor& f) : m_base_mult(f.m_base_mult) {}
        Factor() : m_base_mult(0, 0) {}
        Factor(Factor&&) = default;

        uint32_t get_base() const { return m_base_mult.first; }
        uint32_t get_mult() const { return m_base_mult.second; }

        std::pair<uint32_t, uint32_t> m_base_mult;
    };

    static bool element_compare(const Factor& lhs, const Factor& rhs) ;

private:
    std::vector<Factor> m_factors;
    uint32_t m_num;
};

