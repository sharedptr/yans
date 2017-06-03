#pragma once
#ifndef YANS_ENGINE_BIOTA_GENOS_TYPEGENE_H_
#define YANS_ENGINE_BIOTA_GENOS_TYPEGENE_H_

#include "yans-engine.h"

#include <cstdint>

YANS_NS_B2( biota, genos )

/**
 * @brief Type of genetic information about phenotype
 */
enum class TypeGene : std::uint8_t
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

YANS_NS_E2( biota, genos )

#endif // YANS_ENGINE_BIOTA_GENOS_TYPEGENE_H_
