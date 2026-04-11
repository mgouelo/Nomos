#ifndef SCENARIODAO_H
#define SCENARIODAO_H

#include <QList>
#include "../dto/Scenario.h"

class ScenarioDao {
public:
    ScenarioDao();

    // insère le scenario et retourne l'id généré par SQLite
    int insertScenario(const Scenario& scenario);

    // récupéré tous les scénarios
    QList<Scenario> getAllScenarios() const;

    // met à jour le statut de favoris d'un scenario
    bool updateFavoriteStatus(int scenarioId, bool isFavorite);

    // supprime un scénario (et ses classes associées)
    bool deleteScenario(int scenarioId);
};

#endif // SCENARIODAO_H
