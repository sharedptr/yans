#pragma once
#ifndef YANS_UI_QUICK_GAMEITEM_H_
#define YANS_UI_QUICK_GAMEITEM_H_

#include "yans-ui.h"

#include <QQuickItem>

YANS_UNS_B2( render, detail )
class RenderThread;
YANS_UNS_E2( render, detail )

YANS_UNS_B1( quick )

class YANS_UI_EXPORT GameItem : public QQuickItem
{
    Q_OBJECT

public:
    GameItem();
    virtual ~GameItem();

public Q_SLOTS:
    void ready();

signals:
    void shutdown();

protected:
    QSGNode* updatePaintNode( QSGNode*, UpdatePaintNodeData* );

private:
    render::detail::RenderThread* m_renderThread;
};

YANS_UNS_E1( quick )

#endif // YANS_UI_QUICK_GAMEITEM_H_
