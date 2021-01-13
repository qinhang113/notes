import QtQuick 2.4
import QtQuick.Controls 1.4
import ".."
Rectangle{
    Define{id:define}
    color: "#ebe5e5"
    Item{
        id:topArea
        anchors.top: parent.top
        width: parent.width
        height:define.m_BaseSize*60
    }
    Rectangle{
        id:userInfo
        width: parent.width
        height: 150*define.m_BaseSize
        anchors.top: topArea.bottom
        Image{
            id:userImg
            source: "qrc:/png/portrait.png"
            width: 148*define.m_BaseSize
            height: width
            anchors.left: parent.left
            anchors.leftMargin: 36*define.m_BaseSize
            anchors.verticalCenter: parent.verticalCenter
        }
        Item{
            width: parent.width-userInfo.width-81*define.m_BaseSize
            height: parent.height
            anchors.left: userImg.right
            anchors.leftMargin: 45*define.m_BaseSize
            Text{
                id:userName
                anchors.left: parent.left
                font.pixelSize: 45*define.m_BaseSize
                text:"用户名"
                color: "#4e4e4e"
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }

    Item{
        id:cutArea
        anchors.top: userInfo.bottom
        width: parent.width
        height:define.m_BaseSize*60
    }
    ListView{
        id:funList
        anchors.top: cutArea.bottom
        clip: false
        width: parent.width
        height: parent.height-cutArea.height-topArea.height-userInfo.height
        model: userModel
        interactive : false
        delegate: Rectangle{
            width:funList.width
            height: 140*define.m_BaseSize
            Rectangle{
                anchors.bottom: parent.bottom
                width: parent.width
                height:2
                color: "#ebe5e5"
                visible: index!==userModel.count-1
            }

            Image {
                id: ico
                source: pngPath
                height: 80*define.m_BaseSize
                width: height
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 36*define.m_BaseSize
            }
            Text {
                text: funName
                anchors.left: ico.right
                anchors.leftMargin: 36*define.m_BaseSize
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 45*define.m_BaseSize
                color: "#4e4e4e"
            }
            MouseArea{
                anchors.fill: parent
                onPressed: {
                    pageList.push(qmlPath)
                }
            }
        }
    }
    ListModel{
        id:userModel
        Component.onCompleted: {
            userModel.append({funName:"设置",pngPath:"qrc:/png/set.png",qmlPath:"qrc:/user/setting.qml"})
            userModel.append({funName:"统计图",pngPath:"qrc:/png/chart.png",qmlPath:"qrc:/user/showChart.qml"})
            userModel.append({funName:"关于软件",pngPath:"qrc:/png/information.png",qmlPath:"qrc:/user/setting.qml"})
        }
    }
}
