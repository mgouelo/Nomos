#ifndef STUDENTCONTROLLER_H
#define STUDENTCONTROLLER_H

#include <QObject>
#include <QString>
#include "../database/StudentDao.h"

class StudentController : public QObject {
    Q_OBJECT // communication with QML

public:
    explicit StudentController(QObject *parent = nullptr);

    // allow this method to be called from QML
    Q_INVOKABLE bool addStudent(const QString& firstName, const QString& lastName, const QString& gender, const QString& gradeLevel, int skill, int behavior, int autonomy);
    Q_INVOKABLE bool importFromCSV(const QString& filePath);

private:
    StudentDao m_studentDao;
};

#endif // STUDENTCONTROLLER_H
