#ifndef STUDENT_H
#define STUDENT_H

#include <QString>

struct Student {
    int id_student = 0; // 0 by default, id will be generate by SQLite
    QString first_name;
    QString last_name;
    QString gender;
    QString grade_level;
    int skill_level;
    int behavior_level;
    int autonomy_level;
};

#endif //  STUDENT_H
