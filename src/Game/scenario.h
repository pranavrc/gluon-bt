#ifndef SCENARIO_H
#define SCENARIO_H

#include <QObject>

class Scenario : public QObject
{
public:
    Scenario();
    void visit(int x,int y);
    void killed();

    float calculateGoodness();
    float calculateSpatialDiversity();
    float calculateChallengeLevel();
    int getKillTime();
    int getVisits();

private:
    int board[15][15];
    int kill_time;
    int visits;
};

#endif // SCENARIO_H
