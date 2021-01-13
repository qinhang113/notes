import QtQuick 2.4
import QtQuick.Controls 1.4
import "../web.js" as Web
import ".."

Rectangle {
    id: root
    Define {
        id: define
    }
    property bool isClick: false
    property int errorInfo: 0
    property string str_Info: "点击获取位置信息"
    property string str_Url: "http://api.map.baidu.com/geocoder/v2/?coordtype=wgs84ll&location=posinfo&output=json&pois=1&ak=YVUMbX0tO7smbZYewBK2dGW4"
    property int chooseIndex: -1
    property bool isRefresh:false
    function getLocation() {
        //        location.startGet()addr+"-"+name
        posiModel.clear()
        posiModel.append({
                             addr: "地址13htehtrh",
                             name: "地址13htehtrh"
                         })
        posiModel.append({                             
                             addr: "地址23htehtrh",
                             name: "地址23htehtrh"
                         })
        posiModel.append({                             
                             addr: "地址33htehtrh",
                             name: "地址33htehtrh"
                         })
        posiModel.append({                             
                             addr: "地址43htehtrh",
                             name: "地址43htehtrh"
                         })
        posiModel.append({                             
                             addr: "地址53htehtrh",
                             name: "地址53htehtrh"
                         })
        var p=posiModel.count
        for(var i=0;i<p;i++){
            var strMark=mySql.searchLoMark(posiModel.get(i).location1)
            posiModel.set(i,{"markName":strMark})
        }
    }
    AnimatedImage {
        id: waitting
        source: "qrc:/png/waitting.gif"
        playing : false
        visible: playing
        width: 200 * define.m_BaseSize
        height: width
        anchors.centerIn: parent
    }
    Rectangle {
        id: tip
        visible: isClick
        width: parent.width
        height: isClick ? 120 * define.m_BaseSize : 0
        color: "#ebebeb"
        opacity: 0
        z:10
        Text {
            text: qsTr("请选择距您最近位置。若位置信息不准确,请在空旷处【点击刷新】")
            font.pixelSize: 40 * define.m_BaseSize
            color: "#4e4e4e"
            anchors.centerIn: parent
        }
        PropertyAnimation {
            id: myAnimation
            target: tip
            properties: "opacity"
            duration: 1500
        }
        MouseArea{
            anchors.fill: parent
            onPressed: {
                locaList.height=0
                posiModel.clear()
                if(!isRefresh)
                    loca.startGet()
                errorInfo=0
                isRefresh=true
                waitting.playing=true
            }
        }
    }
    Image {
        visible: !isClick
        width: 200 * define.m_BaseSize
        height: width
        source: "qrc:/png/map.png"
        anchors.centerIn: parent
        MouseArea {
            anchors.fill: parent
            onClicked: {
                isClick = true
                errorInfo=0
                waitting.playing=true
                isRefresh=true
                loca.startGet()                
            }
        }
    }
    Item {
        id:contItem
        width: parent.width
        visible: isClick
        height: parent.height - 120 * define.m_BaseSize
        anchors.bottom: parent.bottom
        ListView {
            id: locaList
            width: parent.width
            visible: isClick
            height: 0
            anchors.centerIn: parent
            model: posiModel
            spacing: 2
            clip: false
            PropertyAnimation {
                id: heigAnimation
                target: locaList
                properties: "height"
                duration: 1500
            }

            delegate: Rectangle {
                id: entry
                width: locaList.width
                height:errorInfo?locaList.height: 150 * define.m_BaseSize + (locaTxt.lineCount - 1) * 50 * define.m_BaseSize
                color: define.color_Current_green
                Item {
                    id: menue
                    visible: width
                    width: {
                        if(locaList.currentIndex==index)
                            return 0
                        else
                            return 0
                    }

                    height: parent.height
                    anchors.right: parent.right
//                    color:"#c0b728"
                    Rectangle{
                        anchors.right: parent.right
                        width: parent.width/2
                        height: parent.height
                        color:"red"
                        Text {
                            visible:menue.width
                            text: "备注"
                            anchors.centerIn: parent
                            font.pixelSize: 40*define.m_BaseSize
                            color:"white"
                        }
                        MouseArea {
                            anchors.fill: parent
                            onPressed: {
                                chooseIndex=index
                                var re=mySql.serchAllMark();
                                var re_Arr=re.split("***")
                                markTemp.clear()
                                for(var i=0;i<re_Arr.length-1;i++){
                                    markTemp.append({markName:re_Arr[i]})
                                }

                                pageList.push({item:"qrc:/page/mark.qml",properties:{loName:addr+"-"+name,markList:markTemp,parentPage:root}})
                                menue.width=0
                            }
                        }
                    }
                    Rectangle{
                        anchors.left: parent.left
                        width: parent.width/2
                        height: parent.height
                        color:"#c0b728"
                        Text {
                            visible:menue.width
                            text: "打卡"
                            anchors.centerIn: parent
                            font.pixelSize: 40*define.m_BaseSize
                            color:"white"
                        }
                        MouseArea {
                            anchors.fill: parent
                            onPressed: {
                                console.log("开始打卡")
                                mySql.addRecord(addr+"-"+name)
                                menAni.to = 0
                                menAni.start()
                            }
                        }
                    }

                    PropertyAnimation {
                        id: menAni
                        target: menue
                        properties: "width"
                        duration: 200
                    }
                }

                Item {
                    id: txtcontainer
                    width: entry.width - menue.width
                    height: parent.height
                    anchors.right: menue.left
                    Image {
                        id:lopng
                        width: 60 * define.m_BaseSize
                        height: width
                        anchors.left: parent.left
                        anchors.leftMargin: 36* define.m_BaseSize
                        source: "qrc:/png/map.png"
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    Text {
                        id: locaTxt
                        textFormat: Text.StyledText
                        lineHeight: 50 * define.m_BaseSize
                        anchors.left:lopng.right
                        anchors.leftMargin: 36* define.m_BaseSize
                        width: parent.width - 144 * define.m_BaseSize
//                        text: location1+'</p>'+'<font color="gray">'+markName+'</font>'
                        text:{
                            if(markName.length){
                                return addr+"-"+name+'</p>'+'<font color="gray">'+markName+'</font>'
                            }else{
                                return addr+"-"+name
                            }
                        }

                        font.pixelSize: 40 * define.m_BaseSize
                        wrapMode: Text.WrapAnywhere
                        horizontalAlignment: Text.AlignHCenter
                        color: "#ffffff"
                        anchors.centerIn: parent
                        lineHeightMode: Text.FixedHeight
                    }
                    MouseArea {
                        anchors.fill: parent
                        onPressAndHold: {
                            locaList.currentIndex=index
                            menAni.to = 500 * define.m_BaseSize
                            menAni.start()
                        }
                    }
                }
            }
        }
    }

    onErrorInfoChanged: {
        switch (errorInfo) {
        case 1000:
            str_Info = "权限错误!"
            break
        case 1001:
            str_Info = "GPS服务关闭!"
            break
        case 1002:
            str_Info = "未知错误!"
            break
        case 1004:
            str_Info = "超时!"
            break
        case 1005:
            str_Info = "无效地址信息!"
            break
        }
        if(errorInfo){
            posiModel.clear()
            posiModel.append({addr:errorInfo.toString(),name:str_Info,markName:""})
        }

    }

        Connections{
            target: loca
            onErInChanged:{
                myAnimation.to = "1"
                myAnimation.start()
                isRefresh=false
                waitting.playing=false
                errorInfo=loca.getErrorInfo()
                locaList.height = root.height
            }
            onReLocationChanged:{
                isRefresh=false
                waitting.playing=false
                var strPos=loca.getLo()
                console.log(str_Url.replace("posinfo",strPos))
                Web.get(str_Url.replace("posinfo",strPos),function(result){
                    var jsonData = JSON.parse(result);
                    if(jsonData.status==0){
                        /////定位成功
                        console.log(jsonData.result)
    //                    var pois=JSON.parse(jsonData.result).pois
    //                    var poisObj=JSON.parse(jsonData.result)
                        posiModel.clear()
                        posiModel.append(jsonData.result.pois)
                        var p=posiModel.count
                        for(var i=0;i<p;i++){
                            var strMark=mySql.searchLoMark(posiModel.get(i).addr+"-"+posiModel.get(i).name)
                            posiModel.set(i,{"markName":strMark})
                        }
                        myAnimation.to = "1"
                        myAnimation.start()
                        heigAnimation.to = root.height-120*define.m_BaseSize
                        heigAnimation.start()
                    }else{
                        myAnimation.to = "1"
                        myAnimation.start()
                        locaList.height = root.height-120*define.m_BaseSize
                        errorInfo=jsonData.status
                    }
                })
            }
        }

    ListModel {
        id: posiModel
    }
    ListModel{
        id:markTemp
    }
    function getback(strmark){
        pageList.pop()
        posiModel.setProperty(chooseIndex,"markName",strmark)
    }
}
