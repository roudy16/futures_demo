#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <memory>
#include <string>

constexpr char* kPRIMETABLEBLOBNAME("primeTable.pt");

// A Singleton that contains an ordered container of prime numbers.
class PrimeTable {
public:
    using Element_t = uint32_t;
    using PrimeContainer_t = std::vector<Element_t>;

    enum class CtorAlgorithm { NAIVE = 0, RESTRICTED_MEMORY_ERATOSTHENES = 1};

    // Load PrimeTable From File, way way faster, should use this
    PrimeTable(std::string filename = kPRIMETABLEBLOBNAME);

    // Actually calculate the primes at runtime up to max_factor using the specified algorithm
    // pretty slow to very very slow depending on the algorithm.
    PrimeTable(Element_t max_factor, CtorAlgorithm alg = CtorAlgorithm::NAIVE);

    Element_t operator[](size_t i) const { return m_primes[i]; }
    size_t size() const { return m_primes.size(); }
    bool contains(Element_t val) const;

    bool saveToFile(std::string filename = kPRIMETABLEBLOBNAME) const;

    friend std::ostream& operator<<(std::ostream& os, const PrimeTable& pt);

    // PrimeTable can be initialized from a file or computed at runtime.
    static void init(Element_t max_factor);
    static void init(std::string filename = kPRIMETABLEBLOBNAME);
    static PrimeTable* instance();

private:
    // TODO Lookup when these are actually needed. I recall being scolded for this
    // but damn it my intent is to not use these so here I am enforcing that, sue me.
    PrimeTable() = delete;
    PrimeTable(const PrimeTable&) = delete;
    PrimeTable(PrimeTable&&) = delete;
    PrimeTable& operator=(const PrimeTable&) = delete;
    PrimeTable& operator=(PrimeTable&&) = delete;

    PrimeContainer_t m_primes;
    static std::shared_ptr<PrimeTable> mp_instance;
}; // PrimeTable Class