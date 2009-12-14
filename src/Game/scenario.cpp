#include "scenario.h"
#include "scenarioset.h"
#include "math.h"
#include <QDebug>

Scenario::Scenario()
{
     for(int x = 0; x < 15; ++x){
        for(int y = 0;y < 15; ++y){
            board[x][y] = 0;
        }
    }
     kill_time  = 0;
     visits     = 0;

}

void Scenario::killed()
{
    //handle when the player is killed
}

void Scenario::visit(int x,int y)
{
    kill_time   += 1;
    board[x][y] += 1;
    visits       += 1;
}

float Scenario::calculateInterest()
{
    return 0.0;
}

// called H_n in the litterature
float Scenario::calculateSpatialDiversity()
{
    // something might be wrong here, check with paper
    int v_n = visits;
    if(v_n <= 1){   // log(1) = 0, no diversity
        return 0.0;
    }
    float sum = 0.0;
    // summation
    for(int x = 0; x < 15; ++x){
        for(int y = 0;y < 15; ++y){
            if(board[x][y] > 0){
                sum += (static_cast<float>(board[x][y]) / static_cast<float>(v_n)) * log(static_cast<float>(board[x][y]) / static_cast<float>(v_n));
            }
        }
    }

    return -((1.0/log(v_n)) * sum);
}

// called T in the litterature
float Scenario::calculateChallengeLevel()
{
    return 0.0;
}

int Scenario::getKillTime()
{
    return kill_time;
}

int Scenario::getVisits()
{
    return visits;
}

#include "scenario.moc"
