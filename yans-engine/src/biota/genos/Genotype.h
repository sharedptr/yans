#pragma once
#ifndef YANS_ENGINE_BIOTA_GENOS_GENOTYPE_H_
#define YANS_ENGINE_BIOTA_GENOS_GENOTYPE_H_

#include "yans-engine.h"

#include "biota/genos/Allele.h"

#include <vector>

YANS_NS_B2( biota, genos )

class YANS_ENGINE_EXPORT Genotype
{
public:
    friend class Operations;

    Genotype( const std::vector< Allele >& alleles );

private:
    std::vector< Allele > m_Alleles;

    Genotype* m_Species;
};

YANS_NS_E2( biota, genos )

#endif // YANS_ENGINE_BIOTA_GENOS_GENOTYPE_H_
