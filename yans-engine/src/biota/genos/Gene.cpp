#include "Gene.h"

YANS_ENS_B2( biota, genos )

Gene::Gene( TypeGene type, Gene::Power power, quint8 info ) : m_Type( type ), m_Power( power ), m_Information( info )
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

quint8 Gene::information() const noexcept
{
    return m_Information;
}

YANS_ENS_E2( biota, genos )
