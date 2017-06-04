#pragma once
#ifndef YANS_ENGINE_BIOTA_GENOS_GENOTYPE_H_
#define YANS_ENGINE_BIOTA_GENOS_GENOTYPE_H_

#include "yans-engine.h"

#include "biota/genos/Allele.h"

#include <vector>

YANS_ENS_B2( biota, genos )

using AllelesList = std::vector< Allele >;

class YANS_ENGINE_EXPORT Genotype
{
public:
    friend class Operations;

    Genotype( const AllelesList& alleles );

    const AllelesList& alleles() const noexcept;

private:
    AllelesList m_Alleles;
    bool m_IsLifable;

    // Genotype* m_Species;
};

YANS_ENS_E2( biota, genos )

#endif // YANS_ENGINE_BIOTA_GENOS_GENOTYPE_H_
