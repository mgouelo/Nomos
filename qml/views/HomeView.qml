import QtQuick
import QtQuick.Controls
import "../components" // import des composents

Item {
    id: root

    // signaux envoyés au main pour changer de page
    signal goToDashboard()
    signal goToTutorial()

    // background de la page
    Rectangle {
        anchors.fill: parent
        color: "#F8FAFC"
    }

    // élément dans un layout colonne
    Column {
        anchors.centerIn: parent
        spacing: 30 // Espace entre chaque élément de la colonne

        // titre
        Text {
            text: "Nomos"
            font.pixelSize: 48
            font.bold: true
            color: "#0F172A"
            anchors.horizontalCenter: parent.horizontalCenter
        }

        // description
        Text {
            text: "L'outil intelligent pour équilibrer vos classes.\nCréez des répartitions parfaites en respectant les vœux et l'équité."
            font.pixelSize: 18
            color: "#475569"
            horizontalAlignment: Text.AlignHCenter // Centre le texte multi-lignes
            anchors.horizontalCenter: parent.horizontalCenter
        }

        // boutons dans un layout horizontal
        Row {
            spacing: 20
            anchors.horizontalCenter: parent.horizontalCenter

            // Bouton 1 : Tableau de bord
            NomosButton {
                text: "Tableau de Bord"
                bgColor: "#2563EB"
                hoverColor: "#1D4ED8"
                onClicked: root.goToDashboard() // déclenche le signal de changement d'écran
            }

            // Bouton 2 : Mode d'emploi
            NomosButton {
                text: "Mode d'emploi"
                bgColor: "#64748B" // Gris pour le bouton secondaire
                hoverColor: "#475569"
                onClicked: root.goToTutorial()
            }
        }
    }
}
