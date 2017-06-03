#pragma once
#ifndef YANS_ENGINE_DATA_ISERIALIZABLE_H_
#define YANS_ENGINE_DATA_ISERIALIZABLE_H_

#include "yans-engine.h"

class QJsonObject;

YANS_NS_B1( data )

class YANS_ENGINE_EXPORT ISerializable
{
public:
    virtual void read( const QJsonObject& json ) = 0;
    virtual void write( QJsonObject& json ) const noexcept = 0;

protected:
    virtual ~ISerializable();
};

YANS_NS_E1( data )

#endif // YANS_ENGINE_DATA_ISERIALIZABLE_H_
