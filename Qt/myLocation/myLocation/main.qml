import QtQuick 2.4
import QtQuick.Controls 1.4
import "web.js" as Web

Rectangle{
    anchors.fill: parent
    property int deep: 1
    property int choosePage: btnList.currentIndex
    Define{id:define}
    focus: true
    Keys.onPressed: {
        if(event.key === Qt.Key_Back||event.key === Qt.Key_Backspace){
            define.backMenu();
            event.accepted = true;
        }
    }
    Rectangle {
        id: btn
        z: 5
        visible : pageList.depth ===deep?true:false
        width: parent.width
        height:pageList.depth ===deep?define.height_BotomTitle:0
        anchors.bottom: parent.bottom
        Rectangle {
            id: shadow
            width: parent.width
            height: 1
            color: define.color_Shadow
            anchors.top: parent.top
        }

        ListView {
            id: btnList
            anchors.top: shadow.bottom
            width: parent.width
            height: parent.height - 1
            model:mainData
            currentIndex:0
            orientation : ListView.Horizontal

            delegate: Rectangle {
                color: "WhiteSmoke"
                id: rect
                visible: true
                width: btn.width / mainData.count
                height: parent.height
                Item{
                    width: parent.width
                    height: parent.height*0.9
                    anchors.centerIn: parent
                    Image {
                        anchors.top: parent.top
                        height: parent.height*0.8
                        width: height
                        source: sourceImg
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Text {
                        anchors.bottom: parent.bottom
                        text: index?"设置":"打卡"
                        font.pixelSize: parent.height/5
                        color:index==btnList.currentIndex?"green":"gray"
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            btnList.currentIndex=index

                        }
                    }
                }

            }
        }
    }
    StackView {
        id: pageList
        anchors.bottom: btn.top
        width: parent.width
        height: (parent.height - btn.height)
        initialItem:"qrc:/initFile.qml"
        delegate: StackViewDelegate {
            function transitionFinished(properties)
            {
                properties.exitItem.opacity = 1
            }

            pushTransition: StackViewTransition {
                PropertyAnimation {
                    target: enterItem
                    property: "opacity"
                    from: 0
                    to: 1
                }
                PropertyAnimation {
                    target: exitItem
                    property: "opacity"
                    from: 1
                    to: 0
                }
            }

        }

    }
    ListModel{
        id:mainData
        Component.onCompleted: {
            mainData.append({sid:1001,sourceImg:"qrc:/png/fingerprint.png",sourceImg2:"qrc:/png/fingerprint.png"})
            mainData.append({sid:1002,sourceImg:"qrc:/png/set.png",sourceImg2:"qrc:/png/set.png"})
        }
    }
}
