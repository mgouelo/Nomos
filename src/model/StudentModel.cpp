#include "StudentModel.h"

StudentModel::StudentModel(QObject *parent)
    : QAbstractListModel(parent)
{
    loadStudents(); // load student at start
}

void StudentModel::loadStudents() {
    beginResetModel();
    m_students = m_studentDao.getAllStudents();
    endResetModel();
}

int StudentModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) return 0;
    return m_students.count();
}

QVariant StudentModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= m_students.count())
        return QVariant();

    const Student &student = m_students[index.row()];

    switch (role) {
    case IdRole: return student.id_student;
    case FirstNameRole: return student.first_name;
    case LastNameRole: return student.last_name;
    case GenderRole: return student.gender;
    case GradeRole: return student.grade_level;
    case SkillRole: return student.skill_level;
    case BehaviorRole: return student.behavior_level;
    case AutonomyRole: return student.autonomy_level;
    default: return QVariant();
    }
}

QHash<int, QByteArray> StudentModel::roleNames() const {
    QHash<int, QByteArray> roles;

    roles[IdRole] = "idStudent";
    roles[FirstNameRole] = "firstName";
    roles[LastNameRole] = "lastName";
    roles[GenderRole] = "gender";
    roles[GradeRole] = "gradeLevel";
    roles[SkillRole] = "skillLevel";
    roles[BehaviorRole] = "behaviorLevel";
    roles[AutonomyRole] = "autonomyLevel";
    return roles;
}
