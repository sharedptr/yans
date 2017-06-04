#include "Genotype.h"

YANS_ENS_B2( biota, genos )

Genotype::Genotype( const AllelesList& alleles ) : m_Alleles( alleles )
{
}

const AllelesList& Genotype::alleles() const noexcept
{
    return m_Alleles;
}

YANS_ENS_E2( biota, genos )
