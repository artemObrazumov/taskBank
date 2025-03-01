import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    visible: true
    width: 1200
    height: 700
    title: "Редактор контрольных работ"
    color: "#111827"

    property int tab: 0
    property int selectedTaskId: -1
    property int selectedVariantId: -1

    FontLoader {
        id: montserratRegular
        source: "qrc:/font/Montserrat-Regular.ttf"
    }

    FontLoader {
        id: montserratMedium
        source: "qrc:/font/Montserrat-Medium.ttf"
    }

    ListModel {
        id: tasksModel
        ListElement {
            title: "Задание 1"
            show: false
            taskVariants: [
                ListElement {
                    taskId: 1
                    title: "Вариант 1"
                },
                ListElement {
                    taskId: 2
                    title: "Вариант 2"
                },
                ListElement {
                    taskId: 3
                    title: "Вариант 2"
                }

            ]
        }
        ListElement {
            title: "Задание 2"
            show: false
            taskVariants: [
                ListElement {
                    taskId: 4
                    title: "Вариант 1"
                },
                ListElement {
                    taskId: 5
                    title: "Вариант 2"
                }
            ]
        }
    }

    ListModel {
        id: variantsModel
        ListElement {
            varId: 1
            title: "Вариант 1"
        }
        ListElement {
            varId: 2
            title: "Вариант 2"
        }
    }

    Rectangle {
        id: navigationSection
        width: parent.width * 0.3
        height: parent.height
        color: "#1F2937"

        Rectangle {
            id: header
            width: parent.width
            height: workTitle.height + 32
            color: "transparent"
            Text {
                id: workTitle
                width: parent.width
                color: "#fff"
                font.family: montserratMedium.name
                font.pointSize: 18
                font.weight: 700
                text: "Название работы работы работы работы работы работы"
                elide: Text.ElideRight
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.margins: 16
            }
        }

        Row {
            anchors.top: header.bottom
            width: parent.width - 32
            anchors.left: parent.left
            anchors.leftMargin: 16
            spacing: 16

            Rectangle {
                id: tasksTab
                width: parent.width / 2 - 8
                height: tasksText.height + 24
                color: bgColor
                radius: 10
                Text {
                    id: tasksText
                    text: "Задания"
                    font.family: montserratRegular.name
                    font.weight: 500
                    font.pointSize: 16
                    anchors.margins: 12
                    anchors.centerIn: parent
                    color: if (tab == 0) { "#fff" } else { "#9CA3AF" }
                }

                readonly property color unselectedColor: "transparent"
                readonly property color selectedColor: "#2B384A"
                property color bgColor: selectedColor

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor

                    onEntered: {
                        parent.bgColor = parent.selectedColor;
                    }

                    onExited: {
                        if (tab == 0) return;
                        parent.bgColor = parent.unselectedColor;
                    }

                    onClicked: {
                        tab = 0;
                        varinatsTab.bgColor = varinatsTab.unselectedColor;
                        variantsContainer.visible = false;
                        tasksListContainer.visible = true;
                    }
                }
            }

            Rectangle {
                id: varinatsTab
                width: parent.width / 2 - 8
                height: variantsText.height + 24
                color: bgColor
                radius: 10
                Text {
                    id: variantsText
                    text: "Варианты"
                    font.family: montserratRegular.name
                    font.weight: 500
                    font.pointSize: 16
                    anchors.centerIn: parent
                    anchors.margins: 12
                    color: if (tab == 1) { "#fff" } else { "#9CA3AF" }
                }

                readonly property color unselectedColor: "transparent"
                readonly property color selectedColor: "#2B384A"
                property color bgColor: unselectedColor

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor

                    onEntered: {
                        parent.bgColor = parent.selectedColor;
                    }

                    onExited: {
                        if (tab == 1) return;
                        parent.bgColor = parent.unselectedColor;
                    }

                    onClicked: {
                        tab = 1;
                        tasksTab.bgColor = tasksTab.unselectedColor;
                        tasksListContainer.visible = false;
                        variantsContainer.visible = true;
                    }
                }
            }
        }

        Rectangle {
            id: tasksListContainer
            y: header.height + varinatsTab.height + 16
            width: parent.width
            height: 400
            color: "transparent"

            ListView {
                anchors.fill: parent
                model: tasksModel
                clip: true
                delegate: Item {
                    width: parent.width
                    height: column.height + 8

                    Column {
                        id: column
                        width: parent.width
                        Rectangle {
                            id: taskContainer
                            width: parent.width - 16
                            height: taskTitle.height + 16
                            x: 8
                            radius: 4
                            color: "transparent"

                            Row {
                                height: taskTitle.height + 16
                                anchors.left: parent.left
                                anchors.leftMargin: 8
                                spacing: 10

                                Image {
                                    source: "qrc:/image/openIndicator.svg"
                                    rotation: if (show) { 0 } else { -90 }
                                    anchors.verticalCenter: parent.verticalCenter
                                }

                                Text {
                                    id: taskTitle
                                    text: title
                                    font.family: montserratRegular.name
                                    font.weight: 500
                                    font.pointSize: 16
                                    color: if (show) { "#fff" } else { "#6B7280" }
                                    anchors.verticalCenter: parent.verticalCenter
                                }

                            }
                            MouseArea {
                                width: parent.width
                                height: parent.height
                                hoverEnabled: true
                                cursorShape: Qt.PointingHandCursor
                                z: 1

                                onEntered: {
                                    parent.color = "#2B384A";
                                }

                                onExited: {
                                    if (show) return;
                                    parent.color = "transparent";
                                }

                                onClicked: {
                                    model.show = !model.show;
                                }
                            }
                        }

                        Item {
                            width: parent.width
                            height: 8
                            visible: show
                        }

                        Repeater {
                            id: taskVariantsList
                            model: taskVariants
                            Layout.topMargin: 8
                            delegate: Rectangle {
                                width: parent.width + 16
                                height: taskVariantTitle.height + 16
                                visible: show
                                radius: 4
                                anchors.left: parent.left
                                anchors.right: parent.right
                                anchors.leftMargin: 8 + 24
                                anchors.rightMargin: 8
                                color: "transparent"

                                Text {
                                    id: taskVariantTitle
                                    text: title
                                    anchors.left: parent.left
                                    anchors.right: parent.right
                                    anchors.margins: 8
                                    anchors.top: parent.top
                                    font.family: montserratRegular.name
                                    font.weight: 500
                                    font.pointSize: 16
                                    color: if (selectedTaskId == taskId) { "#fff" } else { "#6B7280" }
                                }

                                MouseArea {
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    cursorShape: Qt.PointingHandCursor
                                    z: 2

                                    onEntered: {
                                        parent.color = "#2B384A";
                                    }

                                    onExited: {
                                        parent.color = "transparent";
                                    }

                                    onClicked: {
                                        selectedTaskId = taskId;
                                    }
                                }
                            }
                        }

                        Item {
                            width: parent.width
                            height: 8
                            visible: show
                        }
                    }
                }
            }
        }

        Rectangle {
            visible: false
            id: variantsContainer
            y: header.height + varinatsTab.height + 16
            width: parent.width
            height: 400
            color: "transparent"
            clip: true

            ListView {
                anchors.fill: parent
                model: variantsModel
                delegate: Item {
                    width: parent.width
                    height: variantsColumn.height + 8

                    Column {
                        id: variantsColumn
                        width: parent.width
                        Rectangle {
                            id: variantItemContainer
                            width: parent.width - 16
                            height: variantTitle.height + 16
                            x: 8
                            radius: 4
                            color: "transparent"

                            Text {
                                id: variantTitle
                                text: title
                                font.family: montserratRegular.name
                                font.weight: 500
                                font.pointSize: 16
                                anchors.left: parent.left
                                anchors.right: parent.right
                                anchors.margins: 8
                                color: if (selectedVariantId == varId) { "#fff" } else { "#6B7280" }
                                anchors.verticalCenter: parent.verticalCenter
                            }

                            MouseArea {
                                width: parent.width
                                height: parent.height
                                hoverEnabled: true
                                cursorShape: Qt.PointingHandCursor
                                z: 1

                                onEntered: {
                                    parent.color = "#2B384A";
                                }

                                onExited: {
                                    parent.color = "transparent";
                                }

                                onClicked: {
                                    selectedVariantId = varId;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    Rectangle {
        width: 1
        height: parent.height
        color: "#374151"
        anchors.left: navigationSection.right
    }
}
