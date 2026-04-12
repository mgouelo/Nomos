import QtQuick
import QtQuick.Controls

// base
Item {
    id: root

    // propriété du bouton modifiable de l'exterieur
    property string text: "Bouton"
    property string bgColor: "#2563EB" // bleu
    property string hoverColor: "#1D4ED8" // bleu plus foncé au survol

    // signal envoyé au clique
    signal clicked()

    // taille du bouton
    width: 200
    height: 50

    // fond du bouton
    Rectangle {
        id: bgRect
        anchors.fill: parent // rempli d'une couleur unie
        radius: 8 // bords arrondis

        // changement de couleur selon la position de la souris
        color: mouseArea.containsMouse ? root.hoverColor : root.bgColor

        // animation pour le changement de couleur
        Behavior on color {
            ColorAnimation { duration: 150 }
        }

        // texte du bouton
        Text {
            anchors.centerIn: parent
            text: root.text
            color: "white"
            font.pixelSize: 16
            font.bold: true
        }
    }

    // zone interractive pour détecter la souris et les cliques
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true // active pour détecter le survol
        cursorShape: Qt.PointingHandCursor // changement de l'apparence du curseur pour montrer que c'est cliquable

        // au clique, lance le signal clicked()
        onClicked: root.clicked()
    }
}
