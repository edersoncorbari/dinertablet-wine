import QtQuick 2.2
import QtQuick.Window 2.1

Rectangle {

    id: rectangle
    color: "transparent"
    Component.onCompleted: animation.start()

    width: 300; height: 300

    Component {
        id: delegate
        Column {
            id: wrapper
            Image {
                anchors.horizontalCenter: nameText.horizontalCenter
                width: 64; height: 64
                source: icon
            }
            Text {
                id: nameText
                text: name
                font.pointSize: 16
                color: wrapper.PathView.isCurrentItem ? "red" : "black"
            }
        }
    }

    PathView {
        anchors.fill: parent
        model: ContactModel {}
        delegate: delegate
        //focus: true
        //Keys.onLeftPressed: decrementCurrentIndex()
        //Keys.onRightPressed: incrementCurrentIndex()
        path: Path {
            startX: 120; startY: 100
            PathQuad { x: 120; y: 25; controlX: 260; controlY: 75 }
            PathQuad { x: 120; y: 100; controlX: -20; controlY: 75 }
        }
    }
}



// Integrar C++ and QML http://qt-project.org/doc/qt-5/qtqml-cppintegration-interactqmlfromcpp.html
/*
Rectangle {
    width: 400; height: 240
    //color: "white"
    color:  "transparent"

    ListModel {
        id: appModel
        ListElement { name: "Menu"; icon: "../images/menu1.jpg" }
        ListElement { name: "Movies"; icon: "../images/menu2.jpg" }
        //ListElement { name: "Camera"; icon: "pics/Camera_48.png" }
        //ListElement { name: "Calendar"; icon: "pics/DateBook_48.png" }
        //ListElement { name: "Messaging"; icon: "pics/EMail_48.png" }
        //ListElement { name: "Todo List"; icon: "pics/TodoList_48.png" }
        //ListElement { name: "Contacts"; icon: "pics/AddressBook_48.png" }
    }

    Component {
        id: appDelegate
        Item {
            width: 100; height: 100
            scale: PathView.iconScale

            Image {
                id: myIcon
                y: 20; anchors.horizontalCenter: parent.horizontalCenter
                source: icon
                smooth: true
            }
            Text {
                anchors { top: myIcon.bottom; horizontalCenter: parent.horizontalCenter }
                text: name
                smooth: true
            }

            MouseArea {
                anchors.fill: parent
                onClicked: view.currentIndex = index
            }
        }
    }

    Component {
        id: appHighlight
        Rectangle { width: 80; height: 80; color: "lightsteelblue" }
    }

    PathView {
        Keys.onRightPressed: if (!moving) { incrementCurrentIndex(); console.log(moving) }
        Keys.onLeftPressed: if (!moving) decrementCurrentIndex()
        id: view
        anchors.fill: parent
        highlight: appHighlight
        preferredHighlightBegin: 0.5
        preferredHighlightEnd: 0.5
        focus: true
        model: appModel
        delegate: appDelegate
        path: Path {
            startX: 10
            startY: 50
            PathAttribute { name: "iconScale"; value: 0.5 }
            PathQuad { x: 200; y: 150; controlX: 50; controlY: 200 }
            PathAttribute { name: "iconScale"; value: 1.0 }
            PathQuad { x: 390; y: 50; controlX: 350; controlY: 200 }
            PathAttribute { name: "iconScale"; value: 0.5 }
        }
    }
}
*/

// Original
/*
Rectangle {
    id: rectangle
    color: "transparent"
    width: 300
    height: 300
    Component.onCompleted: animation.start()

    PathView {
        id: pathView1
        x: 25
        y: 85
        width: 250
        height: 130
        delegate: Component {
            Column {
                Rectangle {
                    width: 40
                    height: 40
                    color: colorCode
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Text {
                    x: 5
                    text: name
                    font.bold: true
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                spacing: 5
            }
        }
        model: ListModel {
            ListElement {
                name: "Grey"
                colorCode: "grey"
            }

            ListElement {
                name: "Red"
                colorCode: "red"
            }

            ListElement {
                name: "Blue"
                colorCode: "blue"
            }

            ListElement {
                name: "Green"
                colorCode: "green"
            }
        }
        path: Path {
            PathQuad {
                x: 120
                y: 25
                controlX: 260
                controlY: 75
            }

            PathQuad {
                x: 120
                y: 100
                controlX: -20
                controlY: 75
            }
            startY: 100
            startX: 120
        }
    }
}
*/
