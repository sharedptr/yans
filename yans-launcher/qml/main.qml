import QtQuick 2.0

import yans.ui 1.0

Item {
    width: 1280
    height: 720

    GameItem {
        id: renderer
        anchors.fill: parent
        opacity: 0
        Component.onCompleted: renderer.opacity = 1;
    }

    Rectangle {
        anchors.margins: -10
        radius: 5
        color: "white"
        border.color: "black"
        opacity: 0.8
        anchors.fill: bottomPanel
    }

    Text {
        id: bottomPanel
        anchors{
            bottom: renderer.bottom
            left: renderer.left
            right: renderer.right
            margins: 20
        }
        wrapMode: Text.WordWrap
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        text: "Bottom panel"
    }
}
