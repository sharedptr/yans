#include "YansUIPlugin.h"

#include "quick/GameItem.h"

#include <QtQml/qqml.h>

YANS_UNS_B

namespace
{
template < typename T >
int registerType( const char* uri, const char* qmlName )
{
    return qmlRegisterType< T >( uri, YANS_UI_VERSION_MAJOR, YANS_UI_VERSION_MINOR, qmlName );
}
} // namespace

void YansUIPlugin::registerTypes( const char* uri )
{
    //    static constexpr

    Q_ASSERT( uri == QLatin1String( "yans.ui" ) );
    registerType< quick::GameItem >( uri, "GameItem" );
}

YANS_UNS_E
