import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Dialog {
    id: dialog

    property int buttons: 0  // Using OR operator when chosing button, example buttons: dialogs.OK | dialogs.Cancel
    property int numOfButton: getBit(bits.OK, buttons) + getBit(bits.Cancel, buttons)
    property int currentIndex: 0

    readonly property var dialogs: ({"OK": 1, "Cancel" : 2})

    readonly property var bits: ({"OK": 0, "Cancel": 1})

    onVisibleChanged: {
        if(visible) {
            // Default, set focus to OK button
            // When not using OK button, set focus to Cancel button
            // Note: When add more than 2 buttons, this function needs to refactor
            if (!getBit(bits.OK, buttons)) {
                cancelBtn.forceActiveFocus()
            } else {
                okBtn.forceActiveFocus()
            }
            currentIndex = 0
        }
    }

    footer: RowLayout {
        focus: true
        spacing: 10

        ButtonGroup {
            id: tabViewButton

            onClicked:  {
            }
        }

        Item {
            Layout.fillWidth: true
            Layout.preferredWidth: (okBtn.visible && cancelBtn.visible) ? 0.1 : 5
        }

        Button {
            id: okBtn
            Layout.fillWidth: true
            Layout.preferredWidth: 2
            Layout.topMargin: 5
            Layout.bottomMargin: 15
            text: "OK"
            ButtonGroup.group: tabViewButton
            onClicked: {
                dialog.accept()
            }
            onFocusChanged: {
                if(focus) {
                    okBtn.highlighted = true
                    // set currentIndex in situation using tab, not left, right key
                    currentIndex = bits.OK
                }else {
                    okBtn.highlighted = false
                }
            }
            visible: getBit(bits.OK, buttons)
        }

        Button {
            id: cancelBtn
            Layout.fillWidth: true
            Layout.preferredWidth: 2
            Layout.topMargin: 5
            Layout.bottomMargin: 15
            text: "Close"
            ButtonGroup.group: tabViewButton
            onClicked: {
                dialog.reject()
            }
            onFocusChanged: {
                if(focus) {
                    cancelBtn.highlighted = true
                    currentIndex = bits.Cancel
                }else {
                    cancelBtn.highlighted = false
                }
            }
            visible: getBit(bits.Cancel, buttons)
        }

        Item {
            Layout.fillWidth: true
            Layout.preferredWidth: 0.1
        }

        Keys.onReturnPressed: {
            if(okBtn.focus) {
                okBtn.clicked()
            } else if(cancelBtn.focus) {
                cancelBtn.clicked()
            }
        }

        Keys.onLeftPressed: {
            currentIndex--
            if(currentIndex < 0)
                currentIndex = numOfButton - 1

            // active focus for current button
            // Because ButtonGroup index count from right to left,
            // so need to use numOfButton - currentIndex - 1
            tabViewButton.buttons[numOfButton - currentIndex - 1].forceActiveFocus()
        }

        Keys.onRightPressed: {
            currentIndex++
            if(currentIndex == numOfButton)
                currentIndex = 0
            tabViewButton.buttons[numOfButton - currentIndex - 1].forceActiveFocus()
        }

    }

    Component.onCompleted: {
        if(!getBit(bits.Cancel, buttons))
            tabViewButton.removeButton(cancelBtn)
        if(!getBit(bits.OK, buttons))
            tabViewButton.removeButton(okBtn)
    }

    function getBit(bit, number) {
        return (number >> bit) & 0x1
    }

}
