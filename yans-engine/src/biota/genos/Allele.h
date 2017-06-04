#pragma once
#ifndef YANS_ENGINE_BIOTA_GENOS_ALLELE_H_
#define YANS_ENGINE_BIOTA_GENOS_ALLELE_H_

#include "yans-engine.h"

#include "biota/genos/Gene.h"
#include "biota/genos/TypeGene.h"

YANS_ENS_B2( biota, genos )

class YANS_ENGINE_EXPORT Allele
{
public:
    friend class Operations;

    Allele( const Gene& one, const Gene& two );
    Allele( const Allele& other );

    const Gene& geneOne() const noexcept;
    const Gene& geneTwo() const noexcept;
    TypeGene type() const noexcept;

private:
    Gene m_GeneOne;
    Gene m_GeneTwo;
    TypeGene m_Type;
};

YANS_ENS_E2( biota, genos )

#endif // YANS_ENGINE_BIOTA_GENOS_ALLELE_H_
