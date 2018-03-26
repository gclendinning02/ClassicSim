import QtQuick 2.0

Rectangle {
    color: root.darkGray
    height: width / 3 * 1.77 + 50
    width: parent.width

    Connections {
        target: talents
        onTalentsUpdated: {
            leftTotalPoints.text = talents.getTreePoints("LEFT")
            midTotalPoints.text = talents.getTreePoints("MID")
            rightTotalPoints.text = talents.getTreePoints("RIGHT")
        }
    }

    Row {
        height: width / 3 * 1.77
        width: parent.width - 1
        x: 1

        spacing: 1

        TalentTree {
            talentTreeImage: "Assets/warrior/warrior_arms.jpg"
            treePosition: "LEFT"
            y: 1
            z: 2
            height: parent.height - 2
            width: parent.width / 3 - 1
        }
        TalentTree {
            talentTreeImage: "Assets/warrior/warrior_fury.jpg"
            treePosition: "MID"
            y: 1
            z: 1
            height: parent.height - 2
            width: parent.width / 3 - 1
        }
        TalentTree {
            talentTreeImage: "Assets/warrior/warrior_protection.jpg"
            treePosition: "RIGHT"
            y: 1
            z: 0
            height: parent.height - 2
            width: parent.width / 3 - 1
        }
    }

    Rectangle {
        anchors {
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }
        height: 50
        color: "transparent"

        Row {
            anchors.fill: parent

            Rectangle {
                height: parent.height
                width: parent.width / 3

                color: "transparent"

                Text {
                    id: leftTotalPoints

                    anchors.centerIn: parent

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter

                    color: root.gold

                    font {
                        family: root.fontNumbers
                        pointSize: 28
                    }

                    text:  talents.getTreePoints("LEFT")
                }

                ClickableImage {
                    onImageClicked: talents.clearTree("LEFT")
                }
            }

            Rectangle {
                height: parent.height
                width: parent.width / 3

                color: "transparent"

                Text {
                    id: midTotalPoints

                    anchors.centerIn: parent

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter

                    color: root.gold

                    font {
                        family: root.fontNumbers
                        pointSize: 28
                    }

                    text:  talents.getTreePoints("MID")
                }

                ClickableImage {
                    onImageClicked: talents.clearTree("MID")
                }
            }

            Rectangle {
                height: parent.height
                width: parent.width / 3

                color: "transparent"
                Text {
                    id: rightTotalPoints

                    anchors.centerIn: parent

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter

                    color: root.gold

                    font {
                        family: root.fontNumbers
                        pointSize: 28
                    }

                    text: talents.getTreePoints("RIGHT")
                }

                ClickableImage {
                    onImageClicked: talents.clearTree("RIGHT")
                }
            }
        }
    }
}