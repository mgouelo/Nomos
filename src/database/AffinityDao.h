#ifndef AFFINITYDAO_H
#define AFFINITYDAO_H

#include <QList>
#include "../dto/Affinity.h"

class AffinityDao {
public:
    AffinityDao();

    // inséré un voeu
    bool insertAffinity(const Affinity& affinity);

    // supprimer un voeu
    bool deleteAffinity(int affinityId);

    // récupérer toutes les affinités impliquant un élève précis
    QList<Affinity> getAffinitiesForStudent(int studentId) const;

    // récupérer toutes les voeux
    QList<Affinity> getAllAffinities() const;
};

#endif // AFFINITYDAO_H
