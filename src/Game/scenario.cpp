#include "scenario.h"
#include "scenarioset.h"
#include "math.h"

Scenario::Scenario()
{
     for(int x = 0; x < 15; ++x){
        for(int y = 0;y < 15; ++y){
            board[x][y] = 0;
        }
    }
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

float Scenario::calculateGoodness()
{
    return 0.0;
}

// called H_n in the litterature
float Scenario::calculateSpatialDiversity()
{
    int v_n = visits;
    float sum = 0.0;
    // summation
    for(int x = 0; x < 15; ++x){
        for(int y = 0;y < 15; ++y){
            sum += (board[x][y] / v_n) * log(board[x][y] / v_n);
        }
    }
    return -(1/log(v_n)) * sum;
}

// called T in the litterature
float Scenario::calculateChallengeLevel()
{

}

int Scenario::getKillTime()
{
    return kill_time;
}

int Scenario::getVisits()
{
    return visits;
}
