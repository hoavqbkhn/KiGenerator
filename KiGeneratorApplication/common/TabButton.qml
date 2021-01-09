import QtQuick 2.11
import QtQuick.Controls 2.2
import QtQml.StateMachine 1.11 as DSM

Button {
    id: button
    implicitHeight: 70
    implicitWidth: 70

    property var definedPosition : ({
                                        "Top":0,
                                        "Bottom":1,
                                        "Left":2,
                                        "Right":3
                                    })
    property int imagePosition: definedPosition.Right
    property string imageSource: ""
    property string buttonName: ""
    property int textSize: 10 * scaleRatio
    property bool isVisible: true
    property bool isFinished: false
    property int btnRadius: 5

    // Color for state of button: button color, border color, text color
    // disable
    property color disableButtonColor: gray_75
    property color disableBorderColor: gray_75
    property color disableTextColor: gray_65

    // enter
    readonly property color enteredButtonColor: gray_55
    readonly property color enteredBorderColor: gray_55
    readonly property color enteredTextColor: gray_90

    // idle
    property color idleButtonColor: gray_825
    property color idleBorderColor: gray_20
    property color idleTextColor: gray_15

    // press
    readonly property color pressButtonColor: gray_60
    readonly property color pressBorderColor: gray_60
    readonly property color pressTextColor: gray_10

    visible: isVisible

    activeFocusOnTab : true
    background: Rectangle {
        id: btn
        anchors.fill: parent
        color: idleButtonColor
        border.color: idleBorderColor

    }

    Text {
        id: text
        text: buttonName
        anchors.fill: parent
        font.pointSize: textSize
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        //        anchors.left: imagePosition === definedPosition.Right ? parent.left : undefined
        //        anchors.leftMargin: image.width
        //        anchors.right: imagePosition === definedPosition.Left ? parent.right : undefined
        //        anchors.rightMargin: image.width
        color: idleTextColor
        wrapMode: Text.WordWrap
        padding: 5
    }

    function setToFocusColor() {
        text.color = whiteColor
        btn.color = gray_40

    }

    function setToMainColor() {
        btn.color = idleButtonColor
        text.color = gray_20
    }

}
