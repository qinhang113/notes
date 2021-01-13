import QtQuick 2.4

Text {
    id: define
    font.pointSize: 10
    property double m_BaseSize: (define.font.pixelSize * 1000) / define.font.pointSize / 1000 / 3

    property double location_Btn: 140*m_BaseSize
    property string color_Shadow: "#999999"
    property string color_Current_green:"#09bb06"
    property double height_BotomTitle: 150 * m_BaseSize

    function backMenu(){
        if(pageList.depth>1)
            pageList.pop()
        else
            Qt.quit()

    }
}
