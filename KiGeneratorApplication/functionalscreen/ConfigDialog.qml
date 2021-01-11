import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Flux 1.0
import "../common/"
import "../"
import Flux 1.0
CustomDialog {
    id: confdialog
    width: 800
    height: 500
    readonly property color textColor : "black"
    readonly property color tfBackgroundColor: "white"
    readonly property color tfBorderColor: "#353431"
    readonly property color tfBoderOnFocusColor: "#1A1A19"
    readonly property real textSize: fontDefaultSize
    readonly property int margin: 20
    property int orderType : 0
    title: "Cấu hình phần mềm"

    focus: true
    closePolicy: Popup.CloseOnEscape
    modal: true
    buttons: dialogs.OK | dialogs.Cancel
    onAccepted: {
        console.log("ActionProvider.config(config)")
        var config = {
            disQuaterD : tfDisQuaterD.currentText,
            disMonthD : tfDisMonthD.currentText,
            disQuaterA: tfDisQuaterA.currentText,
            thisYear: tfThisYear.currentText,
        }
        ActionProvider.config(config)
    }

    GridLayout{
        anchors.fill: parent
        anchors.leftMargin: parent.width * 10 / 100
        anchors.rightMargin: parent.width * 10 / 100
        anchors.topMargin: parent.height * 10 / 100
        anchors.bottomMargin: parent.height * 10 / 100
        columns: 2
        rowSpacing: 20
        CustomTextField{
            id: tfDisQuaterD
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredHeight: 1
            Layout.preferredWidth: 1
            fieldName: "Khoảng cách năm KID theo quý cần lọc:"
            fieldData: "2"
        }

        CustomTextField{
            id: tfDisMonthD
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredHeight: 1
            Layout.preferredWidth: 1
            fieldName: "Khoảng cách năm KID theo tháng cần lọc:"
            fieldData: "1"
        }
        CustomTextField{
            id: tfDisQuaterA
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredHeight: 1
            Layout.preferredWidth: 1
            fieldName: "Khoảng cách năm KIA theo quý cần lọc:"
            fieldData: "1"
        }
        CustomTextField{
            id: tfThisYear
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredHeight: 1
            Layout.preferredWidth: 1
            fieldName: "Năm hiện tại:"
            fieldData: "2020"
        }
    }
}
