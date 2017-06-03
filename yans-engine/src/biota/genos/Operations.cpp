#include "Operations.h"

#include "biota/genos/Allele.h"
#include "biota/genos/Gene.h"
#include "biota/genos/Genotype.h"

#include <cassert>
#include <limits>

YANS_NS_B2( biota, genos )

Operations::Operations()
    : m_Device(),
      m_Generator( m_Device() ),
      m_DistribMutation( 0.0, 1.0 ),
      m_DistribGeneValue( std::numeric_limits< decltype( m_DistribGeneValue )::result_type >::min(),
                          std::numeric_limits< decltype( m_DistribGeneValue )::result_type >::max() )
{
}

Allele&& Operations::makeNew( const Allele& a, const Allele& b ) noexcept
{
    Allele result( crossover( a, b ) );
    mutation( result.m_GeneOne );
    mutation( result.m_GeneTwo );
    return std::move( result );
}

Genotype&& Operations::makeNew( const Genotype& a, const Genotype& b ) noexcept
{
    // TODO: support genotypes with different number of alleles
    assert( a.m_Alleles.size() == b.m_Alleles.size() );

    decltype( a.m_Alleles ) result;
    result.reserve( a.m_Alleles.size() );
    for( decltype( result.size() ) idx = 0; idx < result.size(); ++idx )
    {
        Allele allele = makeNew( a.m_Alleles[idx], b.m_Alleles[idx] );
        result.push_back( allele );
    }

    return std::move( Genotype( result ) );
}

Gene& Operations::mutation( Gene& a ) noexcept
{
    static constexpr double chance = 0.01;

    if( Q_UNLIKELY( m_DistribMutation( m_Generator ) < chance ) )
    {
        a.m_Power = ( a.m_Power == Gene::Power::Dominant ) ? Gene::Power::Recessive : Gene::Power::Dominant;
    }

    if( Q_UNLIKELY( m_DistribMutation( m_Generator ) < chance ) )
    {
        a.m_Information = m_DistribGeneValue( m_Generator );
    }

    return a;
}

Allele&& Operations::crossover( const Allele& a, const Allele& b ) noexcept
{
    static constexpr double chance = 0.01;

    Allele result( a );
    if( Q_UNLIKELY( m_DistribMutation( m_Generator ) < chance ) )
    {
        result.m_GeneOne = b.m_GeneOne;
    }

    if( Q_UNLIKELY( m_DistribMutation( m_Generator ) < chance ) )
    {
        result.m_GeneTwo = b.m_GeneTwo;
    }

    return std::move( result );
}

YANS_NS_E2( biota, genos )
