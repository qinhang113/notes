import QtQuick 2.4
import QtQuick.Controls 1.4
import ".."
Rectangle{
    Define{id:define}
    color: "#ebe5e5"
    property string str_Dia: ""
    Item{
        id:topArea
        anchors.top: parent.top
        width: parent.width
        height:define.m_BaseSize*60
    }
    Rectangle{
        id:dia
        z:10
        width: 600*define.m_BaseSize
        height: 300*define.m_BaseSize
        radius: 10*define.m_BaseSize
        color: "black"
        opacity: 0
        visible: opacity>0
        anchors.centerIn: parent
        Text {
            text: str_Dia
            anchors.centerIn: parent
            font.pixelSize: 45*define.m_BaseSize
            color: "white"
        }
        PropertyAnimation {
            id: heigAnimation
            target: dia
            properties: "opacity"
            duration: 1500
        }
    }

    Rectangle{
        width: parent.width
        height: 140*define.m_BaseSize
        anchors.top: topArea.bottom
        Image {
            id: ico
            source: "qrc:/png/recycle.png"
            height: 80*define.m_BaseSize
            width: height
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 36*define.m_BaseSize
        }
        Text {
            text: "清空记录"
            anchors.left: ico.right
            anchors.leftMargin: 36*define.m_BaseSize
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 45*define.m_BaseSize
            color: "#4e4e4e"
        }
        MouseArea{
            anchors.fill: parent
            onPressed: {
                if(mySql.delTable()){
                    str_Dia="已清空"
                    dia.opacity=0.6
                    heigAnimation.to=0
                    heigAnimation.start()
                }else{
                    str_Dia="清空失败"
                    dia.opacity=0.6
                    heigAnimation.to=0
                    heigAnimation.start()
                }

            }
        }
    }
}
