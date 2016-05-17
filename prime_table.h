#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <memory>

class PrimeTable {
public:
    PrimeTable(uint32_t max_factor);

    uint32_t operator[](uint32_t i) const { return m_primes[i]; }
    size_t size() const { return m_primes.size(); }
    bool contains(uint32_t val) const;

    friend std::ostream& operator<<(std::ostream& os, const PrimeTable& pt);

    static void init(uint32_t max_factor);
    static PrimeTable* instance();

private:

    std::vector<uint32_t> m_primes;

    static std::shared_ptr<PrimeTable> mp_instance;
};