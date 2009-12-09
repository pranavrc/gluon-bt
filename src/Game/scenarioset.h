#ifndef SCENARIOSET_H
#define SCENARIOSET_H

#include <QObject>
#include "scenario.h"

class ScenarioSet : public QObject
{
public:
    ScenarioSet();
    void save();
    void load();
    float calculateInterest();
    float calculateSpatialDiversity();
    float calculateBehavioralDiversity();
    float calculateChallengeLevel();

    float calcAverageKillTime();
    int findMaxKillTime();
    int findMinKillTime();
    float calcMaximumDeviation();
    float calcStandardDeviation();
    //void visit(int x,int y);

private:
    QList<Scenario*> scenarios;
    float average_kill_time;
    int max_kill_time;

    // weights
    float p1;
    float p2;
    float p3;

    // interest weights
    float wt;
    float ws;
    float we;
};

#endif // SCENARIOSET_H
