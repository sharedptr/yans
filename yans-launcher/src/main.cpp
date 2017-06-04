#include <QGuiApplication>
#include <QQuickView>
#include <QUrl>

int main( int argc, char* argv[] )
{
    QGuiApplication app( argc, argv );

    QQuickView view;

    // Rendering in a thread introduces a slightly more complicated cleanup
    // so we ensure that no cleanup of graphics resources happen until the
    // application is shutting down.
    view.setPersistentOpenGLContext( true );
    view.setPersistentSceneGraph( true );

    view.setResizeMode( QQuickView::SizeRootObjectToView );
    view.setSource( QUrl( "qrc:///yans/launcher/qml/main.qml" ) );
    view.show();

    return app.exec();
}
