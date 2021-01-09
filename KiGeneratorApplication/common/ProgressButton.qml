import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQml.StateMachine 1.11 as DSM

MyButton {
    id: button

    property alias start: startState
    property alias process: processingState
    property alias finish: finishedState
    property alias initState: stateMachine.initialState
    DSM.StateMachine {
        id: stateMachine
        initialState: startState
        running: true
        signal evStart()
        signal evFinish()
        signal evReset()

        function processEvent(event) {
            switch(event) {
            case "evStart":
                evStart()
                break
            case "evFinish":
                evFinish()
                break
            case "evReset":
                evReset()
                break
            }
        }


        DSM.State {
            id: startState

            DSM.SignalTransition{
                targetState: processingState
                signal: stateMachine.evStart
                onTriggered: {
                    console.log("start->processing")
                }
            }

            onEntered: {
                disableButtonColor = gray_75
                disableBorderColor = gray_75
                disableTextColor = gray_65
                enabled = true
                enabled = false
            }
        }

        DSM.State {
            id: processingState
            DSM.SignalTransition{
                targetState: finishedState
                signal: stateMachine.evFinish
                onTriggered: {
                    //console.log("onTriggered[stateMachine.evPressed]: entered->idle")
                }
            }

            DSM.SignalTransition {
                targetState: startState
                signal: stateMachine.evReset
                onTriggered: {
                    //console.log("onTriggered[stateMachine.evDisable]: enable->disable")
                }
            }

            onEntered: {
                idleBorderColor = greenColor
                enabled = true
            }
        }

        DSM.State {
            id: finishedState
            DSM.SignalTransition{
                targetState: startState
                signal: stateMachine.evReset
                onTriggered: {
                    //console.log("onTriggered[stateMachine.evReleased]: pressed->entered")
                }
            }

            onEntered: {
                disableButtonColor = greenColor
                disableBorderColor = greenColor
                disableTextColor = gray_85
                enabled = true
                enabled = false
            }
        }
    }

    function startProcess() {
        console.log("process evStart")
        stateMachine.processEvent("evStart")
    }

    function resetProcess() {
        console.log("process evReset")
        stateMachine.processEvent("evReset")
    }

    function finishProcess() {
        console.log("process evFinish")
        stateMachine.processEvent("evFinish")
    }
}
