import QtQuick 2.4
import QtQuick.Controls 1.4
import QtGraphicalEffects 1.0
import ".."

Rectangle {
    id: mark
    Define{id:define}
    property string loName: ""
    property bool isEdit: false
    property string strHint: ""
    property ListModel markList: markModel
    property QtObject parentPage:null
    ListModel{
        id:markModel
    }
    ListView{
        id:markView
        width: parent.width
        height: parent.height-title.height-bottomBtn.height
        model:markList
        anchors.top: title.bottom
        delegate: Item {
            id: listItem
            width: markView.width
            height: 140* define.m_BaseSize
            MouseArea{
                anchors.fill: parent
                onPressAndHold:{
                    menDelAni.to=500* define.m_BaseSize
                    menDelAni.start()
                }
                onPressed: {
                    menDelAni.to=0
                    menDelAni.start()
                }
            }
            Item{
                id:markMenu
                width: 0
                height: parent.height
                visible: width
                anchors.right: parent.right
                PropertyAnimation {
                    id: menDelAni
                    target: markMenu
                    properties: "width"
                    duration: 200
                }
                Rectangle{
                    id:menDel
                    width: parent.width/2
                    height: parent.height
                    color: "red"
                    anchors.right: parent.right
                    Text {
                        text: "删除"
                        anchors.centerIn: parent
                        font.pixelSize: 40* define.m_BaseSize
                        color:"#ffffff"
                    }
                    MouseArea{
                        anchors.fill: parent
                        onPressed: {
                            markMenu.width=0
                            mySql.delMark(markName)
                            markList.remove(index)
                        }
                    }
                }
                Rectangle{
                    id:menSet
                    width: parent.width/2
                    height: parent.height
                    color: "#c0b728"
                    visible: width
                    anchors.left: parent.left
                    Text {
                        text: "设置"
                        anchors.centerIn: parent
                        font.pixelSize: 40* define.m_BaseSize
                        color:"#ffffff"
                    }
                    MouseArea{
                        anchors.fill: parent
                        onPressed: {
                            markMenu.width=0
                            parentPage.getback(markName)
                            mySql.addNewLo(loName,markName)
                        }
                    }
                }

            }


            Rectangle{
                width: parent.width
                height: 1
                anchors.bottom: parent.bottom
                color: define.color_Shadow
            }

            Image {
                id: clockPng
                width: 60* define.m_BaseSize
                height: 60* define.m_BaseSize
                source: "qrc:/png/clock.png"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 36* define.m_BaseSize
            }
            Item{
                width: parent.width-markMenu.width
                height: parent.height
                anchors.right: markMenu.left
                Text {
                    text: markName
                    anchors.centerIn: parent
                    font.pixelSize: 40* define.m_BaseSize
                    color:"#4e4e4e"
                }
            }


        }
    }

    Rectangle{
        id:title
        width: parent.width
        height: 90 * define.m_BaseSize + (loText.lineCount - 1) * 40 * define.m_BaseSize

        color:"#ebebeb"
        Text {
            id:loText
            text: loName
            lineHeight: 45 * define.m_BaseSize
            font.pixelSize: 40*define.m_BaseSize
            color: "#4e4e4e"
            width:parent.width-72*define.m_BaseSize
            wrapMode: Text.WrapAnywhere
            horizontalAlignment: Text.AlignHCenter
            anchors.centerIn: parent
            lineHeightMode: Text.FixedHeight
        }
    }
    Item{
        id:bottomBtn
        width: height
        height: 300*define.m_BaseSize
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        MouseArea{
            anchors.fill: parent
            onPressed: {
                isEdit=true
            }
        }

        Image {
            id: add
            source: "qrc:/png/plus.png"
            width: 200*define.m_BaseSize
            height: width
            anchors.centerIn: parent
            visible: false
        }
        DropShadow {
            id: shadow
            visible: true
            anchors.fill: add
            horizontalOffset: 3
            verticalOffset: 3
            radius: 8.0
            samples: 16
            color: "#80000000"
            transparentBorder: true
            smooth:true
            source: add
        }
    }
    Rectangle{
        id:shadowArea
        anchors.fill: parent
        color: "#b0b0b0"
        opacity: 0.7
        z:100
        visible: isEdit
    }


    Item{
        id:addDialog
        anchors.fill: parent
        z:shadowArea.z+1
        visible: isEdit
        Rectangle{
            id:editArea
            anchors.centerIn: parent
            color: "white"
            width: 860*define.m_BaseSize
            height:432*define.m_BaseSize
            radius: 10*define.m_BaseSize
            Rectangle{
                id:save
                color: define.color_Current_green
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 26*define.m_BaseSize
                radius: 10*define.m_BaseSize
                height: 106*define.m_BaseSize
                width: 600*define.m_BaseSize
                anchors.horizontalCenter: parent.horizontalCenter
                Text{
                    color: "white"
                    text:"保存"
                    anchors.centerIn: parent
                    font.pixelSize: 40*define.m_BaseSize
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        console.log("groupInput.text"+groupInput.text)
                        var isadd=mySql.addMark(groupInput.text)
                        if(isadd){
                            isEdit=false
                            markList.append({markName:groupInput.text})
                            groupInput.text=""
                        }
                        else{
                           groupInput.text=""
                           strHint="已存在!保存失败"
                        }
                    }
                }
            }
            Rectangle{
                id:str_Line
                width: 708*define.m_BaseSize
                height: 2
                color: define.color_Current_green
                anchors.bottom: save.top
                anchors.bottomMargin:112*define.m_BaseSize
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Item{
                anchors.bottom: str_Line.top
                height: 75*define.m_BaseSize
                width: 708*define.m_BaseSize
                anchors.horizontalCenter: parent.horizontalCenter
                Text{
                    id:str_GroupName
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    color: "#4e4e4e"
                    text: "分组名:"
                    font.pixelSize: 40*define.m_BaseSize

                }
                TextInput{
                    id:groupInput
                    width: parent.width-str_GroupName.contentWidth-40*define.m_BaseSize
                    height: contentHeight
                    anchors.left: str_GroupName.right
                    anchors.leftMargin: 40*define.m_BaseSize
                    anchors.verticalCenter: parent.verticalCenter
                    color: "#4e4e4e"
                    enabled: isEdit
                    maximumLength: 10
                    font.pixelSize:40*define.m_BaseSize
                    wrapMode: Text.NoWrap
                    Text {
                        id: placeholderText
                        anchors.fill: parent
                        visible: !(parent.text.length || parent.inputMethodComposing)
                        font.pixelSize:  40*define.m_BaseSize
                        text:strHint
                        color: "#4e4e4e"
                    }
                }
            }


        }

        Image{
            width: 70*define.m_BaseSize
            height: width
            anchors.left: editArea.right
            anchors.leftMargin: -(width/2)
            anchors.bottom: editArea.top
            anchors.bottomMargin: -(width/2)
            source: "qrc:/png/close.png"
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    groupInput.text=""
                    isEdit=false
                }
            }

        }
    }
}
