#ifndef CLASSROOM_H
#define CLASSROOM_H

#include <QString>

struct Classroom {
    int id_classroom = 0;
    QString name; // nom de la classe
    QString grade_level; // ex: "CP", "CE1" etc...
    int scenario_id = 0; // id du scenario auquel cette classe générée est rattachée
};

#endif // CLASSROOM_H
