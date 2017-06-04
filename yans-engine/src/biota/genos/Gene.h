#pragma once
#ifndef YANS_ENGINE_BIOTA_GENOS_GENE_H_
#define YANS_ENGINE_BIOTA_GENOS_GENE_H_

#include "yans-engine.h"

#include "biota/genos/TypeGene.h"

YANS_NS_B2( biota, genos )

class YANS_ENGINE_EXPORT Gene
{
public:
    friend class Operations;

    enum class Power : quint8
    {
        Dominant = 0,
        Recessive = 1
    };

public:
    Gene( TypeGene type, Power power, quint8 info = 0 );

    TypeGene type() const noexcept;
    Power power() const noexcept;
    quint8 information() const noexcept;

private:
    TypeGene m_Type;
    Power m_Power;
    quint8 m_Information;
};

YANS_NS_E2( biota, genos )

#endif // YANS_ENGINE_BIOTA_GENOS_GENE_H_
