#ifndef CLASSROOMDAO_H
#define CLASSROOMDAO_H

#include <QList>
#include "../dto/Classroom.h"

class ClassroomDao {
public:
    ClassroomDao();

    // insérer une classe
    int insertClassroom(const Classroom& classroom);

    // récupéré les classes d'un scénario spécifique
    QList<Classroom> getClassroomsByScenario(int scenarioId) const;

    // supprimer une classe
    bool deleteClassroom(int classroomId);
};

#endif
