#include "StudentController.h"
#include "../dto/Student.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QUrl>

StudentController::StudentController(QObject *parent) : QObject(parent) {}

bool StudentController::addStudent(const QString& firstName, const QString& lastName, const QString& gender, const QString& gradeLevel, int skill, int behavior, int autonomy) {
    Student s;
    s.first_name = firstName;
    s.last_name = lastName;
    s.gender = gender;
    s.grade_level = gradeLevel;
    s.skill_level = skill;
    s.behavior_level = behavior;
    s.autonomy_level = autonomy;

    return m_studentDao.insertStudent(s);
}


bool StudentController::importFromCSV(const QString& fileUrl) {
    // we convert file url to local path
    QString localPath = QUrl(fileUrl).toLocalFile();

    QFile file(localPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "ERROR : unable to open CSV file " << localPath;
        return false;
    }

    QTextStream in(&file);
    bool isFirstLine = true; // to ignore column headers

    while (!in.atEnd()) {
        QString line = in.readLine();
        if (isFirstLine) {
            isFirstLine = false;
            continue;
        }

        QStringList parts = line.split(';');
        if (parts.size() >= 7) {
                addStudent(parts[0], parts[1], parts[2], parts[3], parts[4].toInt(), parts[5].toInt(), parts[6].toInt());
        }
    }

    file.close();
    qDebug() << "SUCESS : csv import finished";
    return true;
}
