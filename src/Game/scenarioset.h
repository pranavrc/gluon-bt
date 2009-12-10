#ifndef SCENARIOSET_H
#define SCENARIOSET_H

#include <QObject>
#include "scenario.h"

class ScenarioSet : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float wchallenge READ wchallenge WRITE setWChallenge)
    Q_PROPERTY(float wbehavior READ wbehavior WRITE setWBehavior)
    Q_PROPERTY(float wspatial READ wspatial WRITE setWSpatial)
public:
    ScenarioSet();
    void save(QString filename);
    void load(QString filename);
    float calculateInterest();
    float calculateSpatialDiversity();
    float calculateBehavioralDiversity();
    float calculateChallengeLevel();

    int findMaxKillTime();
    int findMinKillTime();
    float calcAverageKillTime();
    float calcMaximumDeviation();
    float calcStandardDeviation();

    void addScenario(Scenario* scenario);

    float wchallenge() const {return wt;}
    void setWChallenge(float wchallenge) {wt = wchallenge;}

    float wbehavior() const {return ws;}
    void setWBehavior(float wbehavior) {ws = wbehavior;}

    float wspatial() const {return we;}
    void setWSpatial(float wspatial) {we = wspatial;}

private:
    QList<Scenario*> scenarios;
    float average_kill_time;
    int max_kill_time;

    // weights
    float p1;
    float p2;
    float p3;

    // interest weights
    float wt;   // challenge
    float ws;   // behavior
    float we;   // spatial
};

#endif // SCENARIOSET_H
