#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <memory>

class PrimeTable {
public:

    enum class CtorAlgorithm { NAIVE = 0, RESTRICTED_MEMORY_ERATOSTHENES = 1};

    PrimeTable(uint32_t max_factor, CtorAlgorithm alg = CtorAlgorithm::NAIVE);

    uint32_t operator[](uint32_t i) const { return m_primes[i]; }
    size_t size() const { return m_primes.size(); }
    bool contains(uint32_t val) const;

    friend std::ostream& operator<<(std::ostream& os, const PrimeTable& pt);

    static void init(uint32_t max_factor);
    static PrimeTable* instance();

private:
    // TODO Lookup when these are actually needed. I recall being scolded for this
    // but damn it my intent is to not use these so here I am enforcing that, sue me.
    PrimeTable() = delete;
    PrimeTable(const PrimeTable&) = delete;
    PrimeTable(PrimeTable&&) = delete;
    PrimeTable& operator=(const PrimeTable&) = delete;
    PrimeTable& operator=(PrimeTable&&) = delete;

    std::vector<uint32_t> m_primes;

    static std::shared_ptr<PrimeTable> mp_instance;
};