#include "AllocationDao.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

AllocationDao::AllocationDao() {

}

bool AllocationDao::insertAllocation(const Allocation& allocation) {
    QSqlQuery query;

    query.prepare(
        "INSERT INTO allocation (student_id, classroom_id) "
        "VALUES (?, ?)"
    );

    query.addBindValue(allocation.student_id);
    query.addBindValue(allocation.classroom_id);

    if (!query.exec()) {
        qWarning() << "ERROR AllocationDao.cpp : error while inserting allocation - " << query.lastError().text();
        return false;
    }
    return true;
}

bool AllocationDao::deleteAllocation(int studentId, int classroomId) {
    QSqlQuery query;

    query.prepare(
        "DELETE FROM allocation "
        "WHERE student_id = ? AND classroom_id = ?"
    );

    query.addBindValue(studentId);
    query.addBindValue(classroomId);

    if (!query.exec()) {
        qWarning() << "ERROR AllocationDao.cpp : error while deleting allocation - " << query.lastError().text();
        return false;
    }
    return true;
}

QList<Student> AllocationDao::getStudentsByClassroom(int classroomId) const {
    QList<Student> studentList;
    QSqlQuery query;

    // jointure sql (INNER JOIN) :
    // cherche les infos dans 'student' (s) seulement si l'id correspond
    // à une ligne dans 'allocation' (a) pour la classe demandée.
    query.prepare(
        "SELECT s.id_student, s.first_name, s.last_name, s.gender, "
        "s.grade_level, s.skill_level, s.behavior_level, s.autonomy_level "
        "FROM student s "
        "INNER JOIN allocation a ON s.id_student = a.student_id "
        "WHERE a.classroom_id = ?"
    );

    query.addBindValue(classroomId);

    if (!query.exec()) {
        qWarning() << "ERROR AllocationDao.cpp : error while fetching students for classroom - " << query.lastError().text();
        return studentList;
    }

    while (query.next()) {
        Student s;
        s.id_student = query.value(0).toInt();
        s.first_name = query.value(1).toString();
        s.last_name = query.value(2).toString();
        s.gender = query.value(3).toString();
        s.grade_level = query.value(4).toString();
        s.skill_level = query.value(5).toInt();
        s.behavior_level = query.value(6).toInt();
        s.autonomy_level = query.value(7).toInt();

        studentList.append(s);
    }

    return studentList;
}
