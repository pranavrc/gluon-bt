#ifndef SCENARIO_H
#define SCENARIO_H

#include <QObject>

class Scenario : public QObject
{
    Q_OBJECT
public:
    Scenario();

    float calculateInterest();
    float calculateSpatialDiversity();
    float calculateChallengeLevel();
    int getKillTime();
    int getVisits();
    int board[15][15];

public Q_SLOTS:
    void visit(int x,int y);
    void killed();

private:
    int kill_time;
    int visits;
};

#endif // SCENARIO_H
