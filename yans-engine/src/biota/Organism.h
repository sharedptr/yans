#pragma once
#ifndef YANS_ENGINE_BIOTA_ORGANISM_H_
#define YANS_ENGINE_BIOTA_ORGANISM_H_

#include "yans-engine.h"

#include "biota/Phenotype.h"
#include "biota/genos/Genotype.h"

YANS_ENS_B1( biota )

class IPhenotypeActions;

class YANS_ENGINE_EXPORT Organism
{
public:
    explicit Organism( const genos::Genotype& genotype );

private:
    genos::Genotype m_Genotype;

    quint8 life;
};

YANS_ENS_E1( biota )

#endif // YANS_ENGINE_BIOTA_ORGANISM_H_
