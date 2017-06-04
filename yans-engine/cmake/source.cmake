cmake_minimum_required( VERSION 3.7 )

set( YANS_ENGINE_SOURCES )
set( YANS_ENGINE_HEADERS )
mark_as_advanced(
    YANS_ENGINE_SOURCES
    YANS_ENGINE_HEADERS
)

list( APPEND YANS_ENGINE_SOURCES
    src/biota/Biota.cpp
    src/biota/genos/Allele.cpp
    src/biota/genos/Gene.cpp
    src/biota/genos/Genotype.cpp
    src/biota/genos/Operations.cpp
    src/biota/genos/TypeGene.cpp
    src/biota/Organism.cpp
    src/biota/Phenotype.cpp
    src/data/ISerializable.cpp
)

list( APPEND YANS_ENGINE_HEADERS
    src/biota/Biota.h
    src/biota/genos/Allele.h
    src/biota/genos/Gene.h
    src/biota/genos/Genotype.h
    src/biota/genos/Operations.h
    src/biota/genos/TypeGene.h
    src/biota/Organism.h
    src/biota/Phenotype.h
    src/data/ISerializable.h
)
