#ifndef AFFINITY_H
#define AFFINITY_H

#include <QString>

struct Affinity {
    int id_affinity = 0;
    int student_a_id = 0;
    int student_b_id = 0;
    QString type; // TOGETHER si c'est un voeu d'élève | SEPARATED si c'est un voeu d'enseignant
    int weight = 0; // Poid du voeu. S'il n'est pas respecté ça fait gonfler le score de la configuration générée
};

#endif // AFFINITY_H
