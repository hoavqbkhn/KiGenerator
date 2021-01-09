import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Controls.Universal 2.2
import QtQuick.Layouts 1.3

GroupBox {
    id: control
    title: "Groupbox"

    property string myTitle: "GroupBox"
    property int myTitleSize: 12 * scaleRatio
    property string borderColor: rectBorderColor

    background: Rectangle {
        y: control.topPadding - control.padding
        width: parent.width
        height: parent.height - control.topPadding + control.padding
        color: "transparent"
        border.color: borderColor
        radius: 2
    }

    label: Rectangle {
        x: control.leftPadding
        color: backgroundColor
        anchors.bottom: parent.top
        anchors.bottomMargin: -height / 5
        width: myTitle.length * myTitleSize / 1.75
        height: title.font.pixelSize

        Label {
            anchors.fill: parent
            color: textColor
            id: title
            horizontalAlignment: Text.AlignHCenter
            text: myTitle
            elide: Text.ElideRight
            font.pixelSize: myTitleSize
        }
    }
}
