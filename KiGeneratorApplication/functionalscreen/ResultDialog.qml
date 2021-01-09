import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "./"
import "../"
import "."
import "../common"
import Flux 1.0

CustomDialog {
    id: detailResultDialog
    width: settingScreen.width * 9 / 10
    height: settingScreen.height * 9 / 10
    property real xPos: 0
    property real yPos: 0
    x: xPos
    y: yPos
    closePolicy: Popup.CloseOnEscape
    modal: true
    focus: true
    title: "Kết quả"
    visible: false
    buttons:dialogs.Cancel
    contentItem: Rectangle {

        color: noColor
        Rectangle {
            anchors.fill: parent
            anchors.topMargin: 0
            anchors.bottomMargin: parent.height * (97/100)
            anchors.leftMargin: parent.width * 15 /100
            anchors.rightMargin: parent.width * 10 /100
            color: noColor

            RadioButton{
                id: rbOrderStyle
                text: "Theo thứ tự"
                checked: true
                anchors.fill: parent
                anchors.rightMargin: parent.width * 80 /100
            }
            RadioButton{
                id: rbKiGroupStyle
                text: "Theo KI"
                anchors.fill: parent
                anchors.leftMargin: parent.width * 80 /100
                checked: false
            }
        }

        //Header
        Rectangle {
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.topMargin: parent.height * (5/100)
            anchors.bottomMargin: parent.height * (90/100)
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
                    font.pointSize: fontSizeHeader
                    font.bold: true
                    padding: spacePadding
                }

                Label {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.preferredHeight: implicitHeight
                    Layout.preferredWidth: listView.columnWidths.tgKI
                    background: Rectangle {border.color: tableBorderColor; color: tableHeaderColor}
                    text: "KI TT 1"
                    wrapMode: Text.WordWrap
                    color: tableHeaderTextColor
                    horizontalAlignment: Text.AlignHCenter
                    font.pointSize: fontSizeHeader
                    font.bold: true
                    padding: spacePadding
                }

                Label {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.preferredHeight: implicitHeight
                    Layout.preferredWidth: listView.columnWidths.tgKI
                    background: Rectangle {border.color: tableBorderColor; color: tableHeaderColor}
                    text: "KI TT 2"
                    wrapMode: Text.WordWrap
                    color: tableHeaderTextColor
                    horizontalAlignment: Text.AlignHCenter
                    font.pointSize: fontSizeHeader
                    font.bold: true
                    padding: spacePadding
                }

                Label {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.preferredHeight: implicitHeight
                    Layout.preferredWidth: listView.columnWidths.tgKI
                    background: Rectangle {border.color: tableBorderColor; color: tableHeaderColor}
                    text: "KI TT 3"
                    wrapMode: Text.WordWrap
                    color: tableHeaderTextColor
                    horizontalAlignment: Text.AlignHCenter
                    font.pointSize: fontSizeHeader
                    font.bold: true
                    padding: spacePadding
                }

                Label {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.preferredHeight: implicitHeight
                    Layout.preferredWidth: listView.columnWidths.tgKI
                    background: Rectangle {border.color: tableBorderColor; color: tableHeaderColor}
                    text: "KI Quý"
                    wrapMode: Text.WordWrap
                    color: tableHeaderTextColor
                    horizontalAlignment: Text.AlignHCenter
                    font.pointSize: fontSizeHeader
                    font.bold: true
                    padding: spacePadding
                }
            }
        }

        //Content
        Rectangle {
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.topMargin: parent.height * (10/100)
            anchors.bottomMargin: parent.height * (5/100)
            anchors.leftMargin: 0
            anchors.rightMargin: 0
            color: noColor

            ListView {
                id: listViewInDetailDialog
                anchors.fill: parent
                clip: true // This attribute force listView not overscrolling of border
                ScrollBar.vertical: ScrollBar {
                    active: hovered || pressed
                    policy: ScrollBar.AsNeeded
                }

                // Fixed sizes or minimum sizes
                property var columnWidths: ({"tgName": 5,
                                                "tgKI": 2,
                                                "tgId":5,
                                                "tgStt":1})

                orientation: Qt.Vertical
                model: rbOrderStyle.checked ? KiAppStore.mResultModelOrderStyle : KiAppStore.mResultModelKiGroupStyle

                highlight: highLight

                // Display table content
                delegate: ItemDelegate {
                    id: itemDelegateInDetailDialog
                    width: parent.width
                    height: 30 * scaleRatio

                    onClicked: {
                        listViewInDetailDialog.forceActiveFocus()
                        listViewInDetailDialog.currentIndex = index
                    }

                    onDoubleClicked: {
                        //nothing
                    }

                    RowLayout {
                        spacing: 0
                        anchors.fill: parent
                        Label {
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            Layout.preferredHeight: implicitHeight
                            Layout.preferredWidth: listViewInDetailDialog.columnWidths.tgStt
                            background: Rectangle {border.color: tableBorderColor; color: getColorFromKi(OfficerQuarterKI)}
                            text: OfficerStt
                            wrapMode: Text.WordWrap
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            color: "black"
                            font.pointSize: fontSize
                        }
                        Label {
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            Layout.preferredHeight: implicitHeight
                            Layout.preferredWidth: listViewInDetailDialog.columnWidths.tgId
                            background: Rectangle {border.color: tableBorderColor; color: getColorFromKi(OfficerQuarterKI)}
                            text: OfficerMsnv
                            wrapMode: Text.WordWrap
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            color: "black"
                            font.pointSize: fontSize
                        }
                        Label {
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            Layout.preferredHeight: implicitHeight
                            Layout.preferredWidth: listViewInDetailDialog.columnWidths.tgName
                            background: Rectangle {border.color: tableBorderColor; color: getColorFromKi(OfficerQuarterKI)}
                            text: OfficerName
                            wrapMode: Text.WordWrap
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            color: "black"
                            font.pointSize: fontSize
                        }

                        Label {
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            Layout.preferredHeight: implicitHeight
                            Layout.preferredWidth: listViewInDetailDialog.columnWidths.tgKI
                            background: Rectangle {border.color: tableBorderColor; color: getColorFromKi(OfficerQuarterKI)}
                            text: OfficerMonth1KI
                            wrapMode: Text.WordWrap
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            color: "black"
                            font.pointSize: fontSize
                        }

                        Label {
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            Layout.preferredHeight: implicitHeight
                            Layout.preferredWidth: listViewInDetailDialog.columnWidths.tgKI
                            background: Rectangle {border.color: tableBorderColor; color: getColorFromKi(OfficerQuarterKI)}
                            text: OfficerMonth2KI
                            wrapMode: Text.WordWrap
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            color: "black"
                            font.pointSize: fontSize
                        }

                        Label {
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            Layout.preferredHeight: implicitHeight
                            Layout.preferredWidth: listViewInDetailDialog.columnWidths.tgKI
                            background: Rectangle {border.color: tableBorderColor; color: getColorFromKi(OfficerQuarterKI)}
                            text: OfficerMonth3KI
                            wrapMode: Text.WordWrap
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            color: "black"
                            font.pointSize: fontSize
                        }

                        Label {
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            Layout.preferredHeight: implicitHeight
                            Layout.preferredWidth: listViewInDetailDialog.columnWidths.tgKI
                            background: Rectangle {border.color: tableBorderColor; color: getColorFromKi(OfficerQuarterKI)}
                            text: OfficerQuarterKI
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
                        listViewInDetailDialog.currentIndex++
                        if(listViewInDetailDialog.currentIndex === listViewInDetailDialog.count)
                            listViewInDetailDialog.currentIndex = 0
                        event.accepted = true
                    } else if (event.key === Qt.Key_Up) {
                        listViewInDetailDialog.currentIndex--
                        if(listViewInDetailDialog.currentIndex === -1)
                            listViewInDetailDialog.currentIndex = listViewInDetailDialog.count - 1
                        event.accepted = true
                    } else if (event.key === Qt.Key_Return) {
                        //customDialog.visible = true
                    }
                }

                onFocusChanged:  {
                    if(!focus)
                        listViewInDetailDialog.highlight = nonHighLight
                    else
                    {
                        listViewInDetailDialog.highlight = highLight
                    }
                }
            }
        }

        // info
        Rectangle {
            anchors.fill: parent
            anchors.topMargin: parent.height * (95/100)
            anchors.bottomMargin: parent.height * (1/100)
            anchors.leftMargin: parent.width * (5/100)
            anchors.rightMargin: parent.width * (5/100)
            color: noColor
            RowLayout{
                anchors.fill: parent
                spacing: 20
                KiXInfo{
                    Layout.fillWidth: true
                    Layout.preferredWidth: 1
                    kiType: "KiA:"
                    amount: KiAppStore.kiAPeople
                }
                KiXInfo{
                    Layout.fillWidth: true
                    Layout.preferredWidth: 1
                    kiType: "KiB:"
                    amount: KiAppStore.kiBPeople
                }
                KiXInfo{
                    Layout.fillWidth: true
                    Layout.preferredWidth: 1
                    kiType: "KiC:"
                    amount: KiAppStore.kiCPeople
                }
                KiXInfo{
                    Layout.fillWidth: true
                    Layout.preferredWidth: 1
                    kiType: "KiD:"
                    amount: KiAppStore.kiDPeople
                }
                KiXInfo{
                    Layout.fillWidth: true
                    Layout.preferredWidth: 1
                    kiType: "Tổng số:"
                    amount: (KiAppStore.kiAPeople + KiAppStore.kiBPeople + KiAppStore.kiCPeople + KiAppStore.kiDPeople)
                }
            }
        }


    }

    onAccepted: {
        detailResultDialog.visible = false
    }

    onRejected: {
        detailResultDialog.visible = false
    }
}


