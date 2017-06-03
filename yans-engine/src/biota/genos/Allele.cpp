#include "Allele.h"

#include <cassert>

YANS_NS_B2( biota, genos )

Allele::Allele( const Gene& one, const Gene& two ) : m_GeneOne( one ), m_GeneTwo( two ), m_Type( one.type() )
{
    assert( one.type() == two.type() );
}

Allele::Allele( const Allele& other ) : Allele( other.m_GeneOne, other.m_GeneTwo )
{
}

const Gene& Allele::geneOne() const noexcept
{
    return m_GeneOne;
}

const Gene& Allele::geneTwo() const noexcept
{
    return m_GeneTwo;
}

TypeGene Allele::type() const noexcept
{
    return m_Type;
}

YANS_NS_E2( biota, genos )
