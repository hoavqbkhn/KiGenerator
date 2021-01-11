import QtQuick 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import Flux 1.0

RowLayout {
    property int fontSize: fontDefaultSize
    property string kiType: ""
    property string amount: ""
    property bool check: false
    Label {
        text: kiType
        color: textColor
        font.pointSize: fontSize
        Layout.fillWidth: true
        Layout.preferredWidth: 1
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
    Label {
        text: amount
        color: textColor
        font.pointSize: fontSize
        Layout.fillWidth: true
        Layout.preferredWidth: 1
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
    }

}
