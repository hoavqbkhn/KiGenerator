import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "./"
import "../"
import "."
import "../common"
import Flux 1.0

Item {
    id: adjustScreen
    focus: true
    width: 1366
    height: 768
    anchors.fill: parent
    readonly property real fontSize: fontDefaultSize
    readonly property real fontSizeHeader: fontDefaultSize
    readonly property real spacePadding: 5
    signal gotoLoadingScreen()

    Keys.onPressed: {
        if(event.key === Qt.Key_Backspace) {
            console.log("Key_Backspace")
            gotoLoadingScreen()
            event.accepted = true
        }
    }
    Rectangle {
        anchors.fill: parent
        anchors.topMargin: parent.height * 5/100
        anchors.bottomMargin: parent.height * 60 /100
        anchors.leftMargin: parent.width * 5 / 100
        anchors.rightMargin: parent.width * 70 / 100
        color: noColor
        border.color: noColor
        MyGroupBox {
            anchors.fill: parent
            myTitle: "Thiết lập tỷ lệ KI mới"
            Switch{
                id: swMode
                anchors.fill: parent
                anchors.bottomMargin: parent.height * 80 / 100
                enabled: true
                checked: KiAppStore.isPercentMode
                text: "Theo (%)"
                onCheckedChanged: {
                    var preData = {
                        factorA : tfKiA.tfText,
                        factorB : tfKiB.tfText,
                        factorD : tfKiD.tfText,
                        isPercentMode: swMode.checked
                    }
                    ActionProvider.updatePercentMode(preData)
                }
            }
            ColumnLayout{
                anchors.fill: parent
                anchors.topMargin: parent.height * 20 / 100
                spacing: 10
                ExtrasTextField {
                    id: tfKiA
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.preferredWidth: 1
                    Layout.preferredHeight: 5
                    lbName: KiAppStore.isPercentMode ? "KI A (%)" : "KI A (người)"
                    tfText: "10"
                }
                ExtrasTextField {
                    id: tfKiB
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.preferredWidth: 1
                    Layout.preferredHeight: 5
                    lbName: KiAppStore.isPercentMode ? "KI B (%)" : "KI B (người)"
                    tfText: "30"
                }
                ExtrasTextField {
                    id: tfKiD
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.preferredWidth: 1
                    Layout.preferredHeight: 5
                    lbName: KiAppStore.isPercentMode ? "KI D (%)" : "KI D (người)"
                    tfText: "10"
                }
            }
        }
    }


    Rectangle{
        anchors.fill: parent
        anchors.topMargin: parent.height * 45/100
        anchors.bottomMargin: parent.height * 5 /100
        anchors.leftMargin: parent.width * 5 / 100
        anchors.rightMargin: parent.width * 70 / 100
        color: noColor
        border.color: noColor
        MyGroupBox{
            anchors.fill: parent
            myTitle: "Chức năng"
            ColumnLayout {
                anchors.fill: parent
                anchors.topMargin: parent.height * 15/100
                anchors.bottomMargin: parent.height * 15 /100
                anchors.leftMargin: parent.width * 5 / 100
                anchors.rightMargin: parent.width * 5 / 100
                spacing: 50
                MyButton{
                    id: btnGen
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    buttonName: "Điều chỉnh"
                    onClicked: {
                        console.log("Generate")
                        var adjustData = {
                            factorA : tfKiA.tfText,
                            factorB : tfKiB.tfText,
                            factorD : tfKiD.tfText,
                            isPercentMode: swMode.checked
                        }
                        ActionProvider.adjustKi(adjustData)
                    }
                }


                MyButton{
                    id: btnExport
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    buttonName: "Xuất file"
                    onClicked: {
                        ActionProvider.exportData()
                    }
                }
            }
        }
    }

    Rectangle{
        anchors.fill: parent
        anchors.topMargin: parent.height * 96/100
        anchors.bottomMargin: 0
        anchors.leftMargin: parent.width * 80 / 100
        anchors.rightMargin: parent.width * 5 / 100
        color: noColor
        border.color: noColor
        RowLayout{
            anchors.fill: parent
            spacing: 15
            Label{
                Layout.preferredWidth: 1
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: "Mode: Điều chỉnh  "
                color: noteColor
                horizontalAlignment: Text.AlignLeft
                font.pointSize: fontSizeHeader
                font.kerning: true
            }
            Label{
                Layout.preferredWidth: 1
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: "Quý: " + KiAppStore.thisQuarter
                color: noteColor
                horizontalAlignment: Text.AlignRight
                font.pointSize: fontSizeHeader
                font.kerning: true
            }
        }
    }


    MyGroupBox{
        anchors.fill: parent
        anchors.topMargin: parent.height * 5/100
        anchors.bottomMargin: parent.height * 5 /100
        anchors.leftMargin: parent.width * 35 / 100
        anchors.rightMargin: parent.width * 5 / 100
        myTitle: "Kết quả sau khi điều chỉnh"
        // Header Table
        Rectangle {
            anchors.fill: parent
            anchors.topMargin: 0
            anchors.bottomMargin: parent.height * (95/100)
            anchors.leftMargin: 0
            anchors.rightMargin: 0
            color: noColor
            border.color: noColor
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
                    text: "KI T1"
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
                    text: "KI T2"
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
                    text: "KI T3"
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

        // Content Table
        Rectangle {
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.topMargin: parent.height * (5/100)
            anchors.bottomMargin: parent.height * (5/100)
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
                property var columnWidths: ({"tgName": 5,
                                                "tgKI": 2,
                                                "tgId":5,
                                                "tgStt":1})


                orientation: Qt.Vertical
                model: KiAppStore.mResultModelKiGroupStyle

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

                    RowLayout {
                        id: rowLayoutTb
                        spacing: 0
                        anchors.fill: parent
                        Label {
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            Layout.preferredHeight: implicitHeight
                            Layout.preferredWidth: listView.columnWidths.tgStt
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
                            Layout.preferredWidth: listView.columnWidths.tgId
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
                            Layout.preferredWidth: listView.columnWidths.tgName
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
                            Layout.preferredWidth: listView.columnWidths.tgKI
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
                            Layout.preferredWidth: listView.columnWidths.tgKI
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
                            Layout.preferredWidth: listView.columnWidths.tgKI
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
                            Layout.preferredWidth: listView.columnWidths.tgKI
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

        // info
        Rectangle {
            anchors.fill: parent
            anchors.topMargin: parent.height * (95/100)
            anchors.bottomMargin: parent.height * (1/100)
            anchors.leftMargin: 0
            anchors.rightMargin: 0
            color: noColor
            RowLayout{
                anchors.fill: parent
                spacing: 0
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
