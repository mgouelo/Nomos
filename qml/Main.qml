import QtQuick
import QtQuick.Controls
import QtQuick.Window
import "views" // importe les vues

Window {
    width: 1024
    height: 768
    visible: true
    title: qsTr("Nomos - Répartition Scolaire")

    // StackView : gère la navigation
    StackView {
        id: stackView
        anchors.fill: parent

        // écran initial --> HomeView
        initialItem: HomeView {
            // écoute les signaux envoyés par HomeView
            onGoToDashboard: {
                console.log("Navigate to Dashboard")
                // stackView.push("DashboardView.qml")
            }
            onGoToTutorial: {
                console.log("Navigate to Tutorial !")
                // stackView.push("TutorialView.qml")
            }
        }
    }
}
