#pragma once
#ifndef YANS_ENGINE_BIOTA_GENOS_GENE_H_
#define YANS_ENGINE_BIOTA_GENOS_GENE_H_

#include "yans-engine.h"

#include "biota/genos/TypeGene.h"

#include <cstdint>

YANS_NS_B2( biota, genos )

class YANS_ENGINE_EXPORT Gene
{
public:
    friend class Operations;

    enum class Power : std::uint8_t
    {
        Dominant = 0,
        Recessive = 1
    };

public:
    Gene( TypeGene type, Power power, std::uint8_t info = 0 );

    TypeGene type() const noexcept;
    Power power() const noexcept;
    std::uint8_t information() const noexcept;

private:
    TypeGene m_Type;
    Power m_Power;
    std::uint8_t m_Information;
};

YANS_NS_E2( biota, genos )

#endif // YANS_ENGINE_BIOTA_GENOS_GENE_H_
