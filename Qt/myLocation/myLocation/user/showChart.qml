import QtQuick 2.5
import QtQuick.Controls 1.4
import "../chart"
import ".."
import "../chart/QChart.js"        as Charts
import "../chart/QChartGallery.js" as ChartsData
Rectangle{
    Define{id:define}
    ListModel{
        id:charModle
        Component.onCompleted: {
            charModle.append({
                                 value: 60,
                                 color1: "#FF8080",
                                 strname:"codding"
                             })
            charModle.append({
                                 value: 30,
                                 color1: "#ffff80",
                                 strname:"eat"
                             })
            charModle.append({
                                 value: 80,
                                 color1: "#8080ff",
                                 strname:"sleep"
                             })
            charModle.append({
                                 value: 10,
                                 color1: "#80ffff",
                                 strname:"game"
                             })
            charModle.append({
                                 value: 60,
                                 color1: "#0080ff",
                                 strname:"other"
                             })
        }
    }
    Text {
        text: qsTr("时间统计")
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 40*define.m_BaseSize
        color: "#4e4e4e"
        anchors.top: parent.top
        anchors.topMargin: 36*define.m_BaseSize
    }
    QChart {
        id: chart;
        anchors.centerIn: parent
        width: parent.width*0.8;
        height: width;
        chartAnimated: true;
        chartAnimationEasing: Easing.InOutElastic;
        chartAnimationDuration: 2000;
        chartData: ChartsData.ChartPieData;
//        chartData:pieData
        chartType: Charts.ChartType.PIE;
    }
    Item{
        width: chart.width
        height: (parent.height-chart.height)/2
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        GridView{
            id:myGrid
            width: parent.width
            height: parent.height
            model: charModle
            cellHeight: height/2
            cellWidth: width/3
            delegate:Item {
                width: myGrid.cellWidth
                height: myGrid.cellHeight
                Rectangle{
                    id:fram
                    width: 100*define.m_BaseSize
                    height: 60*define.m_BaseSize
                    color: color1
                    anchors.verticalCenter: parent.verticalCenter
                }
                Text {
                    text: strname
                    font.pixelSize: 35*define.m_BaseSize
                    color: "#4e4e4e"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: fram.right
                    anchors.leftMargin: 36*define.m_BaseSize
                }
            }
        }

    }
}
