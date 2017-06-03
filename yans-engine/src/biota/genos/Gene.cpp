#include "Gene.h"

YANS_NS_B2( biota, genos )

Gene::Gene( TypeGene type, Gene::Power power, std::uint8_t info )
    : m_Type( type ), m_Power( power ), m_Information( info )
{
}

TypeGene Gene::type() const noexcept
{
    return m_Type;
}

Gene::Power Gene::power() const noexcept
{
    return m_Power;
}

std::uint8_t Gene::information() const noexcept
{
    return m_Information;
}

YANS_NS_E2( biota, genos )
