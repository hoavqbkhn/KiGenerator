import QtQuick 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import "."
import "../"
ColumnLayout{
    property string noUse: ""
    property string noUseData: "0"
    property string fieldName: noUse
    property string fieldData: noUseData
    property string fieldType: noUse
    property alias currentText: tfFieldData.text
    property bool enableThis: true
    property bool visibleThis: true
    property int fontSize: fontDefaultSize + 1
    property string placeHolderText: ""
    readonly property real spacePadding: 7
    property alias echoMode: tfFieldData.echoMode
    signal returnPress
    readonly property color backGroundColor: "#1c3f4e"

    property var fieldValidator: RegExpValidator {}
    function setFieldData(value){
        tfFieldData.text = value
    }
    readonly property color textColor : "#FFFFFF"
    property bool visibleAll: true

    spacing: 0
    visible: visibleAll
    Rectangle {
        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.preferredWidth: 1
        Layout.preferredHeight: 1
        color: "transparent"
        Label {
            id: lbName
            anchors.fill: parent
            verticalAlignment: Qt.AlignBottom
            horizontalAlignment: Qt.AlignLeft
            text: fieldName.toLocaleUpperCase()
            wrapMode: Text.WordWrap
            font.pointSize: fontDefaultSize
            visible: visibleThis
            color: "black"
        }
        visible: visibleThis
    }

    Rectangle{
        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.preferredWidth: 1
        Layout.preferredHeight: 1.25
        radius: 5
        color: backGroundColor

        TextField {
            id:tfFieldData
            anchors.fill: parent
            anchors.rightMargin: parent.width * 15 / 100
            selectByMouse: true
            text: fieldData
            font.pointSize: fontSize
            horizontalAlignment: TextInput.AlignLeft
            verticalAlignment: TextInput.AlignVCenter
            placeholderText: placeHolderText

            background: Rectangle {
                color: "transparent"
                enabled: enableThis
            }
            enabled: enableThis
            color: textColor
            validator: fieldValidator

            Keys.onPressed: {
                if (event.key === Qt.Key_Return) {
                    returnPress()
                }
            }
        }

        Label{
            id: lbType
            anchors.fill: parent
            anchors.leftMargin: parent.width * 85 / 100
            horizontalAlignment: TextInput.AlignRight
            verticalAlignment: TextInput.AlignVCenter
            rightPadding: spacePadding
            text: fieldType
            font.pointSize: fontDefaultSize
            background: Rectangle {
                color: "transparent"
                enabled: enableThis
            }
            enabled: enableThis
        }
    }
}
