#ifndef ALLOCATIONDAO_H
#define ALLOCATIONDAO_H

#include <QList>
#include "../dto/Allocation.h"
#include "../dto/Student.h"

class AllocationDao {
public:

    // Pour chaque association élève <--> classe une créer un objet Allocation
    AllocationDao();

    // relier un élève à une classe
    bool insertAllocation(const Allocation& allocation);

    // retirer un élève d'une classe
    bool deleteAllocation(int studentId, int classroomId);

    // récupère tous les élèves d'une classe
    QList<Student> getStudentsByClassroom(int classroomId) const;
};

#endif // ALLOCATIONDAO_H
