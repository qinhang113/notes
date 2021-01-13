import QtQuick 2.4
import QtQuick.Controls 1.4
ListView{
    id:myFirstView
    property int curPage: choosePage
    currentIndex:curPage
    orientation : ListView.Horizontal
    boundsBehavior: Flickable.StopAtBounds
    clip: true
    interactive : false
    onCurrentIndexChanged: {
        myFirstView.positionViewAtIndex(currentIndex,
                                     ListView.Beginning)
    }
    model: ListModel{
        id:pageModel
        Component.onCompleted: {
            pageModel.append({qmlPath:"qrc:/page/location.qml"})
            pageModel.append({qmlPath:"qrc:/user/userMain.qml"})
        }
    }
    delegate: StackView {
        id: stack
        width: myFirstView.width
        height: myFirstView.height
        initialItem: qmlPath
    }
}
