import QtQuick 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import Flux 1.0

RowLayout {
    property string lbName: ""
    readonly property real textSize: fontDefaultSize - 1
    property bool enableThis: true
    property string tfText: "0"
    property string placeHolderText: "0"
    property var fieldValidator: DoubleValidator {
        bottom: 0
        top: 1000
    }
    Label {
        Layout.fillWidth: true
        Layout.preferredWidth: 1.25
        text: lbName
        color: "black"
        wrapMode: Text.WordWrap
        font.pointSize: textSize
        enabled: enableThis
    }

    TextField {
        id: tf
        Layout.fillWidth: true
        Layout.preferredWidth: 1.5
        validator: fieldValidator
        text: tfText
        selectByMouse: true
        horizontalAlignment: TextInput.AlignHCenter
        background: Rectangle {
            color: enabled ? tfBackgroundColor : tfBackgroundColorDisable
            border.color: tf.focus ? tfBoderOnFocusColor : tfBorderColor
        }
        color: enabled ? textColor : textColorDisable
        enabled: enableThis
        placeholderText: placeHolderText
        onTextChanged: {
            tfText = tf.text
        }
    }

    Item{
        Layout.fillWidth: true
        Layout.preferredWidth: 0.25
    }
}
