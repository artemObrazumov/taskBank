import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import components.controlWorks
import utils.checkboxModel

Window {
    id: generateVariantsWindow
    visible: true
    width: 650
    height: 650
    title: "Генерация вариантов"
    modality: Qt.ApplicationModal
    flags: Qt.FramelessWindowHint
    color: "transparent"

    property int dragX: 0
    property int dragY: 0

    property CheckBoxModel taskGroupsModel: CheckBoxModel {}
    property CheckBoxModel taskTagsModel: CheckBoxModel {}

    signal cancelled()
    signal checkedGroup(int groupId)
    signal checkedTag(int tagId)
    signal createVariants(int count)

    MouseArea {
        id: dragArea
        anchors.fill: parent

        onPressed: {
            dragX = mouse.x;
            dragY = mouse.y;
        }

        onPositionChanged: {
            generateVariantsWindow.x += mouse.x - dragX;
            generateVariantsWindow.y += mouse.y - dragY;
        }
    }

    ControlWorksComponent {
        id: repository
    }

    FontLoader {
        id: montserratRegular
        source: "qrc:/font/Montserrat-Regular.ttf"
    }

    FontLoader {
        id: montserratMedium
        source: "qrc:/font/Montserrat-Medium.ttf"
    }

    Rectangle {
        width: parent.width
        height: parent.height
        color: "#1F2937"
        radius: 8

        anchors.fill: parent

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 20

            Text {
                id: titleText
                text: "Сгенерировать варианты"
                font.pointSize: 20
                font.family: montserratMedium.name
                font.weight: 700
                Layout.alignment: Qt.AlignTop
                width: parent.width
                color: "#fff"
            }

            Item {
                height: 20
            }

            Row {
                id: optionsRow
                Layout.fillWidth: true
                height: 400
                spacing: 12

                Column {
                    width: parent.width / 2
                    height: parent.height

                    Text {
                        id: tasksText
                        text: "Задания"
                        font.pointSize: 16
                        font.family: montserratMedium.name
                        font.weight: 500
                        width: parent.width
                        color: "#fff"
                    }

                    CheckboxList {
                        model: taskGroupsModel
                        width: parent.width
                        height: parent.height

                        onChecked: function(id) {
                            generateVariantsWindow.onCheckedGroup(id)
                        }
                    }
                }

                Column {
                    width: parent.width / 2
                    height: parent.height

                    Text {
                        id: tagsText
                        text: "Категории"
                        font.pointSize: 16
                        font.family: montserratMedium.name
                        font.weight: 500
                        width: parent.width
                        color: "#fff"
                    }

                    CheckboxList {
                        model: taskTagsModel
                        width: parent.width
                        height: parent.height

                        onChecked: function(id) {
                            generateVariantsWindow.onCheckedTag(id)
                        }
                    }
                }
            }

            Item {
                height: 12
            }

            Row {
                id: numberVariantsRow
                Layout.fillWidth: true
                height: borderRect.height
                Layout.alignment: Qt.AlignVCenter
                spacing: 12

                Text {
                    id: numberVariantsTitle
                    text: "Кол-во вариантов"
                    font.family: montserratMedium.name
                    font.pointSize: 14
                    font.weight: 500
                    color: "#D1D5DB"
                    anchors.verticalCenter: parent.verticalCenter
                }

                Rectangle {
                    id: numberVariantsRect
                    width: parent.width - numberVariantsTitle.width
                    height: numberVariantsTitleField.height + 12
                    radius: 6
                    color: "#374151"
                    border.color: "#4B5563"
                    border.width: 2

                    TextField {
                        id: numberVariantsTitleField
                        anchors.fill: parent
                        font.family: montserratMedium.name
                        font.weight: 500
                        font.pointSize: 16
                        background: null
                        anchors.topMargin: 8
                        anchors.leftMargin: 8

                        onActiveFocusChanged: {
                            numberVariantsRect.border.color = activeFocus ? "#4680FF" : "#4B5563";
                        }

                        validator: IntValidator {
                            bottom: 1
                            top: 100
                        }
                    }
                }
            }

            Item {
                height: 12
            }

            Row {
                id: buttonsRow
                Layout.alignment: Qt.AlignBottom | Qt.AlignRight
                width: parent.width
                spacing: 12

                Rectangle {
                    color: bgColor
                    radius: 8
                    Layout.leftMargin: 16
                    Layout.rightMargin: 16
                    Layout.topMargin: 8
                    Layout.bottomMargin: 8

                    readonly property color unselectedColor: "#4B5563"
                    readonly property color selectedColor: "#606873"
                    property color bgColor: unselectedColor

                    width: cancelButtonText.width + 32
                    height: cancelButtonText.height + 16

                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor

                        onEntered: {
                            parent.bgColor = parent.selectedColor;
                        }

                        onExited: {
                            parent.bgColor = parent.unselectedColor;
                        }

                        onClicked: {
                            generateVariantsWindow.close()
                            cancelled()
                        }
                    }

                    Text {
                        id: cancelButtonText
                        text: "Отмена"
                        font.family: montserratRegular.name
                        font.pointSize: 16
                        font.weight: 400
                        color: "#fff"
                        anchors.centerIn: parent
                    }
                }

                Rectangle {
                    color: bgColor
                    radius: 8
                    Layout.leftMargin: 16
                    Layout.rightMargin: 16
                    Layout.topMargin: 8
                    Layout.bottomMargin: 8

                    readonly property color unselectedColor: "#2563EB"
                    readonly property color selectedColor: "#4680FF"
                    property color bgColor: unselectedColor

                    width: applyButtonText.width + 32
                    height: applyButtonText.height + 16

                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor

                        onEntered: {
                            parent.bgColor = parent.selectedColor;
                        }

                        onExited: {
                            parent.bgColor = parent.unselectedColor;
                        }

                        onClicked: {
                            //generateVariantsWindow.close()
                            var numberValue = parseInt(numberVariantsTitleField.text)
                            if (isNaN(numberValue) === false) {
                                generateVariantsWindow.createVariants(numberValue)
                            }
                        }
                    }

                    Text {
                        id: applyButtonText
                        font.family: montserratRegular.name
                        font.pointSize: 16
                        font.weight: 400
                        text: "Создать"
                        color: "#fff"
                        anchors.centerIn: parent
                    }
                }
            }
        }
    }
}
