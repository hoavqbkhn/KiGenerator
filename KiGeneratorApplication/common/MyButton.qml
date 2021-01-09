import QtQuick 2.11
import QtQuick.Controls 2.2
import QtQml.StateMachine 1.11 as DSM
import "../"
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
    property int btnRadius: 0

    // Color for state of button: button color, border color, text color
    // disable
    property color disableButtonColor: noColor
    property color disableBorderColor: "#DDDDDD"
    property color disableTextColor: "#D9D9D9"

    // enter
    readonly property color enteredButtonColor: "#949494"
    readonly property color enteredBorderColor: "#949494"
    readonly property color enteredTextColor: "#000000"

    // idle
    property color idleButtonColor: "#444444"
    property color idleBorderColor: "#444444"
    property color idleTextColor: "#FFFFFF"

    // press
    readonly property color pressButtonColor: "#444444"
    readonly property color pressBorderColor: "#444444"
    readonly property color pressTextColor: "#FFFFFF"

    visible: isVisible

    activeFocusOnTab : true
    background: Rectangle {
        id: btn
        anchors.fill: parent
        radius: btnRadius
        color: idleButtonColor
        border.color: idleBorderColor



        MouseArea {
            id: mouseArea
            anchors.fill: parent
            hoverEnabled: true

            onEntered: {
                stateMachine.processEvent("evEntered")
            }
            onExited: {
                stateMachine.processEvent("evExited")
            }
            onClicked: {
                //console.log("onClicked")
            }

            onPressed: {
                stateMachine.processEvent("evPressed")
            }
            onReleased: {
                stateMachine.processEvent("evReleased")
            }

            onHoveredChanged: {
                //if(hovered)
                //console.log("onHovered")
            }
        }
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


    DSM.StateMachine {
        id: stateMachine
        initialState: button.enabled ? idleState : disableState
        running: true
        signal evEntered()
        signal evExited()
        signal evReleased()
        signal evPressed()
        signal evStartFocus()
        signal evStopFocus()
        signal evDisable()
        signal evEnable()

        function processEvent(event) {
            switch(event) {
            case "evEntered":
                evEntered()
                break
            case "evExited":
                evExited()
                break
            case "evReleased":
                evReleased()
                button.clicked()
                break
            case "evPressed":
                evPressed()
                break
            case "evStartFocus":
                evStartFocus()
                break
            case "evStopFocus":
                evStopFocus()
                break
            case "evDisable":
                evDisable()
                break
            case "evEnable":
                evEnable()
                break
            }
        }


        DSM.State {
            id: idleState

            DSM.SignalTransition{
                targetState: enteredState
                signal: stateMachine.evEntered
                onTriggered: {
//                    console.log("idle->entered")
                }
            }

            DSM.SignalTransition{
                targetState: enteredState
                signal: stateMachine.evStartFocus
                onTriggered: {
//                    console.log("idle->entered")
                }
            }

            DSM.SignalTransition {
                targetState: disableState
                signal: stateMachine.evDisable
                onTriggered: {
//                    console.log("enable->disable")
                }
            }

            onEntered: {
                btn.color = idleButtonColor
                btn.border.color = idleBorderColor
                text.color = idleTextColor
            }
        }

        DSM.State {
            id: enteredState
            DSM.SignalTransition{
                targetState: idleState
                signal: stateMachine.evExited
                onTriggered: {
//                    console.log("onTriggered[stateMachine.evPressed]: entered->idle")
                }
            }

            DSM.SignalTransition {
                targetState: disableState
                signal: stateMachine.evDisable
                onTriggered: {
//                    console.log("onTriggered[stateMachine.evDisable]: enable->disable")
                }
            }

            DSM.SignalTransition{
                targetState: idleState
                signal: stateMachine.evStopFocus
                onTriggered: {
//                    console.log("onTriggered[stateMachine.evStopFocus]: entered->idle")
                }
            }

            DSM.SignalTransition{
                targetState: pressedState
                signal: stateMachine.evPressed
                onTriggered: {
//                    console.log("onTriggered[stateMachine.evPressed]: entered->pressed")
                }
            }

            onEntered: {
                btn.color = enteredButtonColor
                btn.border.color = enteredBorderColor
                text.color = enteredTextColor
            }
        }

        DSM.State {
            id: pressedState
            DSM.SignalTransition{
                targetState: enteredState
                signal: stateMachine.evReleased
                onTriggered: {
//                    console.log("onTriggered[stateMachine.evReleased]: pressed->entered")
                }
            }

            onEntered: {
                btn.color = pressButtonColor
                btn.color = pressBorderColor
                text.color = pressTextColor
            }
        }

        DSM.State {
            id: disableState
            DSM.SignalTransition{
                targetState: idleState
                signal: stateMachine.evEnable
                onTriggered: {
//                    console.log("onTriggered[stateMachine.evEnable]: disable->enable")
                }
            }

            onEntered: {
                btn.color = disableButtonColor
                btn.border.color = disableBorderColor
                text.color = disableTextColor
            }
        }
    }

    onVisualFocusChanged: {
        if (button.visualFocus) {
            stateMachine.processEvent("evStartFocus")
        } else {
            stateMachine.processEvent("evStopFocus")
        }
    }

    onEnabledChanged: {
        if(!enabled) {
            stateMachine.processEvent("evDisable")
        }else {
            stateMachine.processEvent("evEnable")
        }
    }

    Keys.onReturnPressed:  {
        //console.log("return press")
        stateMachine.processEvent("evPressed")
        keyTimer.start()
    }

    Keys.onSpacePressed:  {
        //        console.log("space press")
        stateMachine.processEvent("evPressed")
        keyTimer.start()
    }

    Timer {
        id: keyTimer
        interval: 50
        repeat: false
        onTriggered: {
            stateMachine.processEvent("evReleased")
            keyTimer.stop()
        }
    }
}
