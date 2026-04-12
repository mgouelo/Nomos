#include "ClassroomDao.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

ClassroomDao::ClassroomDao() {

}

int ClassroomDao::insertClassroom(const Classroom& classroom) {
    QSqlQuery query;

    query.prepare(
        "INSERT INTO classroom (name, grade_level, scenario_id) "
        "VALUES (?, ?, ?)"
    );

    query.addBindValue(classroom.name);
    query.addBindValue(classroom.grade_level);
    query.addBindValue(classroom.scenario_id);

    if (!query.exec()) {
        qWarning() << "ERROR ClassroomDao.cpp : error while inserting classroom - " << query.lastError().text();
        return -1;
    }

    // retourne l'ID de la classe qui vient d'être crée
    return query.lastInsertId().toInt();
}

QList<Classroom> ClassroomDao::getClassroomsByScenario(int scenarioId) const {
    QList<Classroom> classroomList;
    QSqlQuery query;

    query.prepare(
        "SELECT id_classroom, name, grade_level, scenario_id "
        "FROM classroom WHERE scenario_id = ?"
    );
    query.addBindValue(scenarioId);

    if (!query.exec()) {
        qWarning() << "ERROR ClassroomDao.cpp : error while fetching classrooms - " << query.lastError().text();
        return classroomList;
    }

    while (query.next()) {
        Classroom c;
        c.id_classroom = query.value(0).toInt();
        c.name = query.value(1).toString();
        c.grade_level = query.value(2).toString();
        c.scenario_id = query.value(3).toInt();

        classroomList.append(c);
    }

    return classroomList;
}

bool ClassroomDao::deleteClassroom(int classroomId) {
    QSqlQuery query;

    query.prepare("DELETE FROM classroom WHERE id_classroom = ?");
    query.addBindValue(classroomId);

    if (!query.exec()) {
        qWarning() << "ERROR ClassroomDao.cpp : error while deleting classroom - " << query.lastError().text();
        return false;
    }
    return true;
}
