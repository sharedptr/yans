#pragma once
#ifndef YANS_ENGINE_BIOTA_GENOS_OPRATIONS_H_
#define YANS_ENGINE_BIOTA_GENOS_OPRATIONS_H_

#include "yans-engine.h"

#include <random>

YANS_ENS_B2( biota, genos )

class Gene;
class Allele;
class Genotype;

class YANS_ENGINE_EXPORT Operations
{
public:
    explicit Operations();

    Allele&& makeNew( const Allele& a, const Allele& b ) noexcept;
    Genotype&& makeNew( const Genotype& a, const Genotype& b ) noexcept;

private:
    std::random_device m_Device;
    std::mt19937 m_Generator;
    std::uniform_real_distribution< double > m_DistribMutation;
    std::uniform_int_distribution< quint8 > m_DistribGeneValue;

    Gene& mutation( Gene& a ) noexcept;
    Allele&& crossover( const Allele& a, const Allele& b ) noexcept;
};

YANS_ENS_E2( biota, genos )

#endif // YANS_ENGINE_BIOTA_GENOS_OPRATIONS_H_
