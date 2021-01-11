import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "./"
import "../"
import "."
import "../common"
import Flux 1.0

Item {
    id: loadingScreen
    focus: true
    width: 1366
    height: 768
    anchors.fill: parent
    readonly property real fontSize: fontDefaultSize
    readonly property real fontSizeHeader: fontDefaultSize
    readonly property real spacePadding: 5
    signal gotoSettingScreen()
    signal gotoAdjustScreen()
    Rectangle {
        id: rectModel
        anchors.fill: parent
        anchors.topMargin: parent.height * 5/100
        anchors.bottomMargin: parent.height * 20 /100
        anchors.leftMargin: parent.width * 5 / 100
        anchors.rightMargin: parent.width * 5 / 100
        color: noColor
        border.color: noColor
        ColumnLayout {
            anchors.fill: parent
            spacing: 20

            Rectangle {
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.preferredWidth: 1
                Layout.preferredHeight: 1
                color: noColor
                Label{
                    id: lbList
                    anchors.left: parent.left
                    wrapMode: Text.WordWrap
                    text: "Danh sách nhân viên:"
                    font.pixelSize: fontSize + 4
                    font.bold: true
                    color: textColor
                }
            }

            Rectangle {
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.preferredWidth: 1
                Layout.preferredHeight: 40
                // Header Table
                Rectangle {
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.topMargin: 0
                    anchors.bottomMargin: parent.height * (95/100)
                    anchors.leftMargin: 0
                    anchors.rightMargin: 0
                    color: noColor
                    RowLayout {
                        anchors.fill: parent
                        spacing: 0
                        Label {
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            Layout.preferredHeight: implicitHeight
                            Layout.preferredWidth: listView.columnWidths.tgStt
                            background: Rectangle {border.color: tableBorderColor; color: tableHeaderColor}
                            text: "STT"
                            wrapMode: Text.WordWrap
                            color: tableHeaderTextColor
                            horizontalAlignment: Text.AlignHCenter
                            //                    verticalAlignment: Text.AlignVCenter
                            font.pointSize: fontSizeHeader
                            font.bold: true
                            padding: spacePadding
                        }
                        Label {
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            Layout.preferredHeight: implicitHeight
                            Layout.preferredWidth: listView.columnWidths.tgId
                            background: Rectangle {border.color: tableBorderColor; color: tableHeaderColor}
                            text: "MSNV"
                            wrapMode: Text.WordWrap
                            color: tableHeaderTextColor
                            horizontalAlignment: Text.AlignHCenter
                            //                    verticalAlignment: Text.AlignVCenter
                            font.pointSize: fontSizeHeader
                            font.bold: true
                            padding: spacePadding
                        }
                        Label {
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            Layout.preferredHeight: implicitHeight
                            Layout.preferredWidth: listView.columnWidths.tgName
                            background: Rectangle {border.color: tableBorderColor; color: tableHeaderColor}
                            text: "Tên"
                            wrapMode: Text.WordWrap
                            color: tableHeaderTextColor
                            horizontalAlignment: Text.AlignHCenter
                            //                    verticalAlignment: Text.AlignVCenter
                            font.pointSize: fontSizeHeader
                            font.bold: true
                            padding: spacePadding
                        }
                        Label {
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            Layout.preferredHeight: implicitHeight
                            Layout.preferredWidth: listView.columnWidths.tgKiStatus
                            background: Rectangle {border.color: tableBorderColor; color: tableHeaderColor}
                            text: "KIA Status"
                            wrapMode: Text.WordWrap
                            color: tableHeaderTextColor
                            horizontalAlignment: Text.AlignHCenter
                            //                    verticalAlignment: Text.AlignVCenter
                            font.pointSize: fontSizeHeader
                            font.bold: true
                            padding: spacePadding
                        }
                        Label {
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            Layout.preferredHeight: implicitHeight
                            Layout.preferredWidth: listView.columnWidths.tgKiStatus
                            background: Rectangle {border.color: tableBorderColor; color: tableHeaderColor}
                            text: "KIB Status"
                            wrapMode: Text.WordWrap
                            color: tableHeaderTextColor
                            horizontalAlignment: Text.AlignHCenter
                            //                    verticalAlignment: Text.AlignVCenter
                            font.pointSize: fontSizeHeader
                            font.bold: true
                            padding: spacePadding
                        }
                        Label {
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            Layout.preferredHeight: implicitHeight
                            Layout.preferredWidth: listView.columnWidths.tgKiStatus
                            background: Rectangle {border.color: tableBorderColor; color: tableHeaderColor}
                            text: "KIC Status"
                            wrapMode: Text.WordWrap
                            color: tableHeaderTextColor
                            horizontalAlignment: Text.AlignHCenter
                            //                    verticalAlignment: Text.AlignVCenter
                            font.pointSize: fontSizeHeader
                            font.bold: true
                            padding: spacePadding
                        }
                        Label {
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            Layout.preferredHeight: implicitHeight
                            Layout.preferredWidth: listView.columnWidths.tgKiStatus
                            background: Rectangle {border.color: tableBorderColor; color: tableHeaderColor}
                            text: "KID Status"
                            wrapMode: Text.WordWrap
                            color: tableHeaderTextColor
                            horizontalAlignment: Text.AlignHCenter
                            //                    verticalAlignment: Text.AlignVCenter
                            font.pointSize: fontSizeHeader
                            font.bold: true
                            padding: spacePadding
                        }
                    }
                }

                // Content Table
                Rectangle {
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.topMargin: parent.height * (5/100)
                    anchors.bottomMargin: 0
                    anchors.leftMargin: 0
                    anchors.rightMargin: 0
                    color: noColor

                    ListView {
                        id: listView
                        anchors.fill: parent
                        clip: true // This attribute force listView not overscrolling of border
                        ScrollBar.vertical: ScrollBar {
                            active: hovered || pressed
                            policy: ScrollBar.AsNeeded
                        }

                        // Fixed sizes or minimum sizes
                        property var columnWidths: ({"tgName": 3,
                                                      "tgKI": 1,
                                                      "tgId":2,
                                                        "tgStt":1,
                                                    "tgKiStatus":1.5})


                        orientation: Qt.Vertical
                        model: KiAppStore.mListOfficerModel

                        highlight: highLight

                        // Display table content
                        delegate: ItemDelegate {
                            id: itemDelegate
                            width: parent.width
                            height: 30 * scaleRatio

                            onClicked: {
                                listView.forceActiveFocus()
                                listView.currentIndex = index
                            }

                            onDoubleClicked: {
                                listView.forceActiveFocus()
                                listView.currentIndex = index
                            }


                            function changeCurrentLineOfListView(_color, cNum) {
                                for (var i = 0; i < rowLayoutTb.children.length; i++) {
                                    if (i === cNum)
                                        rowLayoutTb.children[i].background.color = _color
                                    //                        rowLayoutFromAp.children[i].background.color = _color
                                }
                            }

                            function changeCurrentLineOfListViewToTransparent() {
                                for (var i = 0; i < rowLayoutTb.children.length; i++) {
                                    rowLayoutTb.children[i].background.color = "transparent"
                                }
                            }

                            RowLayout {
                                id: rowLayoutTb
                                spacing: 0
                                anchors.fill: parent
                                Label {
                                    id: tgStt
                                    Layout.fillHeight: true
                                    Layout.fillWidth: true
                                    Layout.preferredHeight: implicitHeight
                                    Layout.preferredWidth: listView.columnWidths.tgStt
                                    background: Rectangle {border.color: tableBorderColor; color: tableContentColor}
                                    text: OfficerStt
                                    wrapMode: Text.WordWrap
                                    horizontalAlignment: Text.AlignHCenter
                                    verticalAlignment: Text.AlignVCenter
                                    color: "black"
                                    font.pointSize: fontSize
                                }
                                Label {
                                    id: tgMsnv
                                    Layout.fillHeight: true
                                    Layout.fillWidth: true
                                    Layout.preferredHeight: implicitHeight
                                    Layout.preferredWidth: listView.columnWidths.tgId
                                    background: Rectangle {border.color: tableBorderColor; color: tableContentColor}
                                    text: OfficerMsnv
                                    wrapMode: Text.WordWrap
                                    horizontalAlignment: Text.AlignHCenter
                                    verticalAlignment: Text.AlignVCenter
                                    color: "black"
                                    font.pointSize: fontSize
                                }
                                Label {
                                    id: tgName
                                    Layout.fillHeight: true
                                    Layout.fillWidth: true
                                    Layout.preferredHeight: implicitHeight
                                    Layout.preferredWidth: listView.columnWidths.tgName
                                    background: Rectangle {border.color: tableBorderColor; color: tableContentColor}
                                    text: OfficerName
                                    wrapMode: Text.WordWrap
                                    horizontalAlignment: Text.AlignHCenter
                                    verticalAlignment: Text.AlignVCenter
                                    color: "black"
                                    font.pointSize: fontSize
                                }
                                Label {
                                    id: tgKiAStatus
                                    Layout.fillHeight: true
                                    Layout.fillWidth: true
                                    Layout.preferredHeight: implicitHeight
                                    Layout.preferredWidth: listView.columnWidths.tgKiStatus
                                    background: Rectangle {border.color: tableBorderColor; color: tableContentColor}
                                    text: OfficerKiAStatus
                                    wrapMode: Text.WordWrap
                                    horizontalAlignment: Text.AlignHCenter
                                    verticalAlignment: Text.AlignVCenter
                                    color: "black"
                                    font.pointSize: fontSize
                                }
                                Label {
                                    id: tgKiBStatus
                                    Layout.fillHeight: true
                                    Layout.fillWidth: true
                                    Layout.preferredHeight: implicitHeight
                                    Layout.preferredWidth: listView.columnWidths.tgKiStatus
                                    background: Rectangle {border.color: tableBorderColor; color: tableContentColor}
                                    text: OfficerKiBStatus
                                    wrapMode: Text.WordWrap
                                    horizontalAlignment: Text.AlignHCenter
                                    verticalAlignment: Text.AlignVCenter
                                    color: "black"
                                    font.pointSize: fontSize
                                }
                                Label {
                                    id: tgKiCStatus
                                    Layout.fillHeight: true
                                    Layout.fillWidth: true
                                    Layout.preferredHeight: implicitHeight
                                    Layout.preferredWidth: listView.columnWidths.tgKiStatus
                                    background: Rectangle {border.color: tableBorderColor; color: tableContentColor}
                                    text: OfficerKiCStatus
                                    wrapMode: Text.WordWrap
                                    horizontalAlignment: Text.AlignHCenter
                                    verticalAlignment: Text.AlignVCenter
                                    color: "black"
                                    font.pointSize: fontSize
                                }
                                Label {
                                    id: tgKiDStatus
                                    Layout.fillHeight: true
                                    Layout.fillWidth: true
                                    Layout.preferredHeight: implicitHeight
                                    Layout.preferredWidth: listView.columnWidths.tgKiStatus
                                    background: Rectangle {border.color: tableBorderColor; color: tableContentColor}
                                    text: OfficerKiDStatus
                                    wrapMode: Text.WordWrap
                                    horizontalAlignment: Text.AlignHCenter
                                    verticalAlignment: Text.AlignVCenter
                                    color: "black"
                                    font.pointSize: fontSize
                                }


                            }
                        }


                        Keys.onPressed: {
                            if (event.key === Qt.Key_Down) {
                                listView.currentIndex++
                                if(listView.currentIndex === listView.count)
                                    listView.currentIndex = 0
                                event.accepted = true
                            } else if (event.key === Qt.Key_Up) {
                                listView.currentIndex--
                                if(listView.currentIndex === -1)
                                    listView.currentIndex = listView.count - 1
                                event.accepted = true
                            } else if (event.key === Qt.Key_Return) {
                                //customDialog.visible = true
                            }
                        }

                        onFocusChanged:  {
                            if(!focus)
                                listView.highlight = nonHighLight
                            else
                            {
                                listView.highlight = highLight
                            }
                        }
                    }
                }

                Component {
                    id: highLight
                    Rectangle {
                        width: listView.width
                        color: highLightColor
                    }
                }

                Component {
                    id: nonHighLight
                    Rectangle {
                        color: noColor
                    }
                }

            }

        }
    }
    ConfigDialog{
        id: configDialog
        x: (parent.width - configDialog.width)/2
        y: (parent.height - configDialog.height)/2
        visible: false
        onAccepted: {

        }
        onClosed: {
        }
    }


    Rectangle {
        id: rectNext
        anchors.fill: parent
        anchors.topMargin: parent.height * 85/100
        anchors.bottomMargin: parent.height * 5 /100
        anchors.leftMargin: parent.width * 15 / 100
        anchors.rightMargin: parent.width * 15 / 100
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
                buttonName: "Tải file dữ liệu KI"
                onClicked: {
                    console.log("loading...")
                    ActionProvider.openFileKiData()
                }
            }
            MyButton{
                id: btnConfig
                Layout.alignment: Qt.AlignCenter
                Layout.fillWidth: true
                Layout.fillHeight: true
                buttonName: "Cấu hình"
                enabled: KiAppStore.isLoadedFile
                onClicked: {
                    console.log("config...")
                    configDialog.open()
                }
            }
            MyButton {
                id: btnEdit
                Layout.alignment: Qt.AlignCenter
                Layout.fillWidth: true
                Layout.fillHeight: true
                enabled: KiAppStore.isLoadedFile
                buttonName: "Điều chỉnh KI"
                onClicked: {
                    console.log("adjust...")
                    ActionProvider.accessAdjustMode()
                    gotoAdjustScreen()
                }
            }
            MyButton {
                id: btnGen
                Layout.alignment: Qt.AlignCenter
                Layout.fillWidth: true
                Layout.fillHeight: true
                buttonName: "Tạo KI"
                enabled: KiAppStore.isLoadedFile
                onClicked: {
                    console.log("create new...")
                    ActionProvider.accessCreateMode()
                    gotoSettingScreen()
                }
            }


        }
    }
}
