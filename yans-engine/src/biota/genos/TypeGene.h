#pragma once
#ifndef YANS_ENGINE_BIOTA_GENOS_TYPEGENE_H_
#define YANS_ENGINE_BIOTA_GENOS_TYPEGENE_H_

#include "yans-engine.h"

YANS_ENS_B2( biota, genos )

/**
 * @brief Type of genetic information about phenotype
 */
enum class TypeGene : quint8
{
    Aggressiveness = 0,
    BodySize,
    BreedingPeriod,
    BreedingType,
    BreedSize,
    Force,
    GrowthRate,
    MetabolicRate,
    MovementSpeed,
    Resistance,
    Stamina,
    TotalEnergy,
    TypeOfReproduction,
    TypeOfTroph, ///< Autotroph, HeteroTroph
    //
    TypeGeneTotalSize
};

YANS_ENS_E2( biota, genos )

#endif // YANS_ENGINE_BIOTA_GENOS_TYPEGENE_H_
