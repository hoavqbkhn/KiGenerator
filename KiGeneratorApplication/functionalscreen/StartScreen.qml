import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "./"
import "../"
import "."
import "../common"
import Flux 1.0

Item {
    id: startScreen
    focus: true
    width: 1366
    height: 768
    anchors.fill: parent
    signal gotoLoadingScreen()
    Rectangle{
        anchors.fill: parent
        anchors.topMargin: parent.height * 15/100
        anchors.bottomMargin: parent.height * 45 /100
        anchors.leftMargin: parent.width * 10 / 100
        anchors.rightMargin: parent.width * 10 / 100
        color: rectBackGroundColor
        border.color: rectBorderColor
        Label {
            id: lbAppName
            anchors.centerIn: parent
            text: "Phần mềm tính KI"
            font.pixelSize: 40
            font.bold: true
            color: textColor
        }
    }

    Rectangle{
        anchors.fill: parent
        anchors.topMargin: parent.height * 80/100
        anchors.bottomMargin: parent.height * 10 /100
        anchors.leftMargin: parent.width * 40 / 100
        anchors.rightMargin: parent.width * 40 / 100
        color: noColor
        border.color: noColor
        RowLayout {
            spacing: 10
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            MyButton {
                id: btnStart
                Layout.alignment: Qt.AlignCenter
                Layout.fillWidth: true
                Layout.fillHeight: true
                buttonName: "Bắt đầu"
                onClicked: {
                    console.log("onClick")
                    gotoLoadingScreen()
                }
            }
        }
    }
}
