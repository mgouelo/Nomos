#include "StudentDao.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

// constructeur
StudentDao::StudentDao() {

}

bool StudentDao::insertStudent(const Student& student) {
    QSqlQuery query;

    query.prepare(
        "INSERT INTO student (first_name, last_name, gender, grade_level, skill_level, behavior_level, autonomy_level) "
        "VALUES (?, ?, ?, ?, ?, ?, ?)"
    );

    // bindings
    query.addBindValue(student.first_name);
    query.addBindValue(student.last_name);
    query.addBindValue(student.gender);
    query.addBindValue(student.grade_level);
    query.addBindValue(student.skill_level);
    query.addBindValue(student.behavior_level);
    query.addBindValue(student.autonomy_level);

    // exécution et vérification d'erreur
    if (!query.exec()) {
        qWarning() << "ERROR StudentDAO.cpp : error while adding a new student - " << query.lastError().text();
        return false;
    }
    return true;
}


QList<Student> StudentDao::getAllStudents() const {
    QList<Student> studentList;
    QSqlQuery query(
        "SELECT id_student, first_name, last_name, gender, grade_level, skill_level, behavior_level, autonomy_level "
        "FROM student"
    );

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

        studentList.append(s); // ajoute l'élève à la liste
    }

    return studentList;
}

bool StudentDao::deleteAllStudents() {
    QSqlQuery query;

    if (!query.exec("DELETE FROM student")) {
        qWarning() << "ERROR StudentDAO.cpp : error while deleting all students - " << query.lastError().text();
        return false;
    }
    return true;
}
