#include "AffinityDao.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

AffinityDao::AffinityDao() {

}

bool AffinityDao::insertAffinity(const Affinity& affinity) {
    QSqlQuery query;

    query.prepare(
        "INSERT INTO affinity (student_a_id, student_b_id, type, weight) "
        "VALUES (?, ?, ?, ?)"
    );

    query.addBindValue(affinity.student_a_id);
    query.addBindValue(affinity.student_b_id);
    query.addBindValue(affinity.type);
    query.addBindValue(affinity.weight);

    if (!query.exec()) {
        qWarning() << "ERROR AffinityDao.cpp : error while inserting affinity - " << query.lastError().text();
        return false;
    }
    return true;
}

bool AffinityDao::deleteAffinity(int affinityId) {
    QSqlQuery query;

    query.prepare("DELETE FROM affinity WHERE id_affinity = ?");
    query.addBindValue(affinityId);

    if (!query.exec()) {
        qWarning() << "ERROR AffinityDao.cpp : error while deleting affinity - " << query.lastError().text();
        return false;
    }
    return true;
}

QList<Affinity> AffinityDao::getAffinitiesForStudent(int studentId) const {
    QList<Affinity> affinityList;
    QSqlQuery query;

    // cherche toutes les lignes où l'élève est soit "A" soit "B"
    query.prepare(
        "SELECT id_affinity, student_a_id, student_b_id, type, weight "
        "FROM affinity WHERE student_a_id = ? OR student_b_id = ?"
    );

    query.addBindValue(studentId);
    query.addBindValue(studentId);

    if (!query.exec()) {
        qWarning() << "ERROR AffinityDao.cpp : error while fetching affinities for student - " << query.lastError().text();
        return affinityList;
    }

    while (query.next()) {
        Affinity a;
        a.id_affinity = query.value(0).toInt();
        a.student_a_id = query.value(1).toInt();
        a.student_b_id = query.value(2).toInt();
        a.type = query.value(3).toString();
        a.weight = query.value(4).toInt();

        affinityList.append(a);
    }

    return affinityList;
}

QList<Affinity> AffinityDao::getAllAffinities() const {
    QList<Affinity> affinityList;
    QSqlQuery query(
        "SELECT id_affinity, student_a_id, student_b_id, type, weight "
        "FROM affinity"
    );

    while (query.next()) {
        Affinity a;
        a.id_affinity = query.value(0).toInt();
        a.student_a_id = query.value(1).toInt();
        a.student_b_id = query.value(2).toInt();
        a.type = query.value(3).toString();
        a.weight = query.value(4).toInt();

        affinityList.append(a);
    }

    return affinityList;
}
