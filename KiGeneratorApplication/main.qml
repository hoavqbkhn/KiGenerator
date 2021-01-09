import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Controls.Universal 2.2
import QtQuick.Layouts 1.3
import "./"
import "./common"
import Flux 1.0
Window {
    id: startedWindow
    visible: true

    property string currentDateString

    readonly property int resolution: 1
    readonly property real appWidthResolution: resolution == 1 ? 1024 : 1920
    readonly property real appHeightResolution: resolution == 1 ? 728 : 1080
    width: appWidthResolution
    height: appHeightResolution
    title: qsTr("KIAPP")

    property bool isVisibleFooter: false
    property bool isNormalMode: true
    readonly property real defaultWidth: appWidthResolution
    readonly property real defaultHeight: appHeightResolution
    property real scaleWidthRatio: startedWindow.width/defaultWidth
    property real scaleHeightRatio: startedWindow.height/defaultHeight
    property real scaleRatio: scaleHeightRatio < scaleWidthRatio ? scaleHeightRatio : scaleWidthRatio

    property real fontDefaultSize : 10 * scaleRatio

    readonly property color backgroundColor: "#E8E8E8"
    readonly property color textColor: "#444444"
    readonly property color noColor: "transparent"
    readonly property color rectBorderColor:  "#5F5F5F"
    readonly property color rectBackGroundColor: "#E8E8E8"

    readonly property color tableBorderColor: "#E8E8E8"
    readonly property color tableHeaderColor: "#444444"
    readonly property color tableHeaderTextColor: "#D9D9D9"
    readonly property color tableContentColor: "#52A353"
    readonly property color highLightColor: "#6AF6FF"

    readonly property color tfBackgroundColor: "#E8E8E8"
    readonly property color tfBackgroundColorDisable: "#C9CDC5"
    readonly property color tfBorderColor: "#5F5F5F"
    readonly property color tfBoderOnFocusColor: "#000000"
    readonly property color textColorDisable: "#9F9999"

    readonly property color kiAColor: "#2DD232"
    readonly property color kiBColor: "#2DD2C2"
    readonly property color kiCColor: "#F5D549"
    readonly property color kiDColor: "#EE3611"
    readonly property color noteColor: "brown"

    function getColorFromKi(ki){
        if(ki === "A"){
            return kiAColor
        }else if(ki === "B"){
            return kiBColor
        }else if(ki === "C"){
            return kiCColor
        }else if(ki === "D"){
            return kiDColor
        }else{
            return "white"
        }
    }

    Universal.theme: Universal.Dark
    Universal.accent: Universal.Cyan

    Rectangle {
        anchors.fill: parent
        color: backgroundColor
    }
    Loader {
        id: mainLoader
        focus: true
        anchors.fill: parent

        source: "qrc:/functionalscreen/StartScreen.qml"
        property bool valid: item !== null
    }
    CustomDialog {
        id: issueDialog
        width: startedWindow.width * 4 / 10
        height: startedWindow.height * 3 / 10
        x: Math.round((startedWindow.width - width) / 2)
        y: Math.round((startedWindow.height - height) / 2)
        closePolicy: Popup.CloseOnEscape
        modal: true
        focus: true
        title: "Thông báo"
        visible: false
        buttons: dialogs.OK
        contentItem: Rectangle {
            color: "transparent"
            Label {
                anchors.centerIn: parent
                anchors.fill: parent
                wrapMode: Text.WordWrap
                text: KiAppStore.issue
            }
        }
        onAccepted: {
            issueDialog.visible = false
        }
    }
    Connections {
        target: KiAppStore
        onIssueChanged:{
            issueDialog.visible= true
        }
    }
    Connections {
        ignoreUnknownSignals: true
        target: mainLoader.valid ? mainLoader.item : null
        onGotoLoadingScreen: {
            mainLoader.setSource("qrc:/functionalscreen/LoadingScreen.qml")
        }
        onGotoSettingScreen: {
            mainLoader.setSource("qrc:/functionalscreen/SettingScreen.qml")
        }
        onGotoAdjustScreen:{
            mainLoader.setSource("qrc:/functionalscreen/AdjustKiScreen.qml")
        }

    }

    CustomDialog {
        id: confirmExit
        width: startedWindow.width * 4 / 10
        height: startedWindow.height * 3 / 10
        x: Math.round((startedWindow.width - width) / 2)
        y: Math.round((startedWindow.height - height) / 2)
        closePolicy: Popup.CloseOnEscape
        modal: true
        focus: true
        title: "Thông báo"
        visible: false
        buttons: dialogs.OK
        contentItem: Rectangle {
            color: "transparent"
            Label {
                anchors.centerIn: parent
                anchors.fill: parent
                wrapMode: Text.WordWrap
                text: "Bạn có muốn thoát chương trình?"
            }
        }

        onAccepted: {
            confirmExit.visible = false
            ActionProvider.exitApplication()
        }

        onRejected: {
            confirmExit.visible = false
        }
    }

    Component.onCompleted: {
        //declare healthStatusWindow
        console.log("onCompleted")
    }

}
