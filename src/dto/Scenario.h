#ifndef SCENARIO_H
#define SCENARIO_H

#include <QString>

struct Scenario {
    int id_scenario = 0;
    QString name;
    bool is_favorite = false; // si le scenraio a été mis en favoris par l'utilisateur (faux par défaut)
    int score = 0;
    long long created_at = 0; // date sous forme de timestamp
};

#endif // SCENARIO_H
