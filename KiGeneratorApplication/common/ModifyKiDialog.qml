import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Flux 1.0

CustomDialog {
    id: dialog
    height: 360
    width: 540

    property real xPos: 0
    property real yPos: 0

    x: xPos
    y: yPos

    title: "Thay đổi giá trị KI"

    buttons: dialogs.OK | dialogs.Cancel


    focus: true
    closePolicy: Popup.CloseOnEscape
    modal: true
    contentItem: Rectangle {
        color: "transparent"
        GridLayout {
            anchors.fill: parent
            columns: 4
            columnSpacing: 10

            Item {
                Layout.fillWidth: true
                Layout.preferredWidth: 0.25
            }

            Label {
                text: "Name:"
                Layout.fillWidth: true
                Layout.preferredWidth: 0.75
            }

            Label {
                id: lbName
                Layout.fillWidth: true
                Layout.preferredWidth: 1.5
            }

            Item {
                Layout.fillWidth: true
                Layout.preferredWidth: 0.25
            }

            Item {
                Layout.fillWidth: true
                Layout.preferredWidth: 0.25
            }

            Label {
                text: "Id:"
                Layout.fillWidth: true
                Layout.preferredWidth: 0.75
            }

            Label {
                id: lbId
                Layout.fillWidth: true
                Layout.preferredWidth: 1.5
            }

            Item {
                Layout.fillWidth: true
                Layout.preferredWidth: 0.25
            }

            Item {
                Layout.fillWidth: true
                Layout.preferredWidth: 0.25
            }

            Label {
                text: "KI"
                Layout.fillWidth: true
                Layout.preferredWidth: 0.75
            }

            Rectangle {
                Layout.fillWidth: true
                Layout.preferredWidth: 1.3

                TextField {
                    id: inputKi
                    anchors.centerIn: parent
                    implicitWidth: parent.width
                    selectByMouse: true
                    placeholderText: "A | B | C | D"
                    validator: RegExpValidator {
                        regExp: /[a-dA-D]{1}$/
                    }
                }
            }

            Item {
                Layout.fillWidth: true
                Layout.preferredWidth: 0.25
            }
        }
    }

    onAccepted: {
        if (isValidInput()) {
            var info = {
                id: lbId.text,
                ki: inputKi.text
            }
            ActionProvider.updateFixingKiList(info)
        } else {
            visible = true
        }
    }

    onRejected: {
    }

    function setEditValue(_msnv, _name) {
        lbName.text = _name
        lbId.text = _msnv
    }

    function getEditedValue() {

    }

    function isValidInput() {
        if(inputKi.text.length === 0) {
            return false
        }
        return true
    }
}
