#include "ScenarioDao.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <QDateTime>

ScenarioDao::ScenarioDao() {

}

int ScenarioDao::insertScenario(const Scenario& scenario) {
    QSqlQuery query;

    query.prepare(
        "INSERT INTO scenario (name, is_favorite, score, created_at) "
        "VALUES (?, ?, ?, ?)"
    );

    query.addBindValue(scenario.name);
    query.addBindValue(scenario.is_favorite ? 1 : 0); // conversion bool -> int
    query.addBindValue(scenario.score);

    long long timestamp = scenario.created_at != 0 ? scenario.created_at : QDateTime::currentSecsSinceEpoch();
    query.addBindValue(timestamp);

    if (!query.exec()) {
        qWarning() << "ERROR ScenarioDao.cpp : error while inserting scenario - " << query.lastError().text();
        return -1;
    }

    // on récupère le dernier ID inséré
    return query.lastInsertId().toInt();
}

QList<Scenario> ScenarioDao::getAllScenarios() const {
    QList<Scenario> scenarioList;

    // trie par date de création décroissante
    QSqlQuery query(
        "select id_scenario, name, is_favorite, score, created_at "
        "FROM scenario ORDER BY created_at DESC"
    );

    while(query.next()) {
        Scenario s;
        s.id_scenario = query.value(0).toInt();
        s.name = query.value(1).toString();
        s.is_favorite = query.value(2).toInt();
        s.score = query.value(3).toInt();
        s.created_at = query.value(4).toLongLong();

        scenarioList.append(s);
    }

    return scenarioList;
}

bool ScenarioDao::updateFavoriteStatus(int scenarioId, bool isFavorite) {
    QSqlQuery query;

    query.prepare(
        "UPDATE scenario SET is_favorite = ? "
        "WHERE id_scenario = ?"
    );
    query.addBindValue(isFavorite ? 1 : 0);
    query.addBindValue(scenarioId);

    if (!query.exec()) {
        qWarning() << "ERROR ScenarioDao.cpp : error while updating favorite status - " << query.lastError().text();
        return false;
    }

    return true;
}

bool ScenarioDao::deleteScenario(int scenarioId) {
    QSqlQuery query;

    query.prepare(
        "DELETE FROM scenario WHERE id_scenario = ?"
    );
    query.addBindValue(scenarioId);

    if (!query.exec()) {
        qWarning() << "ERROR ScenarioDao.cpp : errror while deleting scenario - " << query.lastError().text();
        return false;
    }

    return true;
}
