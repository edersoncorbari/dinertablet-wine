
import QtQuick 2.0
import QtQuick.XmlListModel 2.0
import "content"

Rectangle {
    id: window
    width: 800; height: 480
    color: "transparent"

    //property string currentFeed: "rss.news.yahoo.com/rss/topstories"

    property string currentFeed: "g1.globo.com/dynamo/rss2.xml"
    property bool loading: feedModel.status == XmlListModel.Loading

    RssFeeds { id: rssFeeds }

    XmlListModel {
        id: feedModel
        source: "http://" + window.currentFeed
        query: "/rss/channel/item"

        XmlRole { name: "title"; query: "title/string()" }
        XmlRole { name: "link"; query: "link/string()" }
        XmlRole { name: "description"; query: "description/string()" }
    }

    Row {
        Rectangle {
            width: 220; height: window.height
            color: "#efefef"
            //color: "red"
            //ColorAnimation { from: "white"; to: "black"; duration: 200 }

            ListView {
                focus: true
                id: categories
                anchors.fill: parent
                model: rssFeeds
                footer: quitButtonDelegate
                delegate: CategoryDelegate {}
                highlight: Rectangle { color: "steelblue" }
                highlightMoveVelocity: 9999999
            }
            ScrollBar {
                scrollArea: categories; height: categories.height; width: 8
                anchors.right: categories.right
            }
        }
        ListView {
            id: list
            width: window.width - 220; height: window.height
            model: feedModel
            delegate: NewsDelegate {}
        }
    }
    Component {
        id: quitButtonDelegate
        Item {
            width: categories.width; height: 60
            Text {
                text: "Voltar"
                font { family: "Helvetica"; pixelSize: 16; bold: true }
                anchors {
                    left: parent.left; leftMargin: 15
                    verticalCenter: parent.verticalCenter
                }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: window.visible = false 
                //Qt.close()
            }
        }
    }
    ScrollBar { scrollArea: list; height: list.height; width: 8; anchors.right: window.right }
    //Rectangle { x: 220; height: window.height; width: 1; color: "#cccccic" }
    Rectangle { x: 220; height: window.height; width: 1; color: "black" }
}
