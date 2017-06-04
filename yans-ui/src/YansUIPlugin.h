#pragma once
#ifndef YANS_UI_YANSUIPLUGIN_H_
#define YANS_UI_YANSUIPLUGIN_H_

#include "yans-ui.h"

#include <QtQml/QQmlExtensionPlugin>

YANS_UNS_B

class YANS_UI_EXPORT YansUIPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA( IID QQmlExtensionInterface_iid )

    // QQmlTypesExtensionInterface interface
public:
    virtual void registerTypes( const char* uri ) final;
};

YANS_UNS_E

#endif // YANS_UI_YANSUIPLUGIN_H_
