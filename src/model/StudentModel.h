#ifndef STUDENTMODEL_H
#define STUDENTMODEL_H

#include "../database/StudentDao.h"

#include <QAbstractListModel>

class StudentModel : public QAbstractListModel {
    Q_OBJECT

public:
    enum StudentRoles {
        IdRole = Qt::UserRole + 1,
        FirstNameRole,
        LastNameRole,
        GenderRole,
        GradeRole,
        SkillRole,
        BehaviorRole,
        AutonomyRole
    };

    explicit StudentModel(QObject *parent = nullptr);

    // refresh student list from DB
    Q_INVOKABLE void loadStudents();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    StudentDao m_studentDao;
    QList<Student> m_students;
};

#endif // STUDENTMODEL_H
