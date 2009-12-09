#include "scenarioset.h"
#include "math.h"

ScenarioSet::ScenarioSet()
{
    wt = 1 / 3;
    ws = 1 / 3;
    we = 1 / 3;
}

// Load the game scenarios from a file
void ScenarioSet::save()
{

}

// Save the game scenarios to a file
void ScenarioSet::load()
{

}

// Calculate the overall performance of the behavior.
// Uses entertainment metrics.
float ScenarioSet::calculateInterest()
{
    return ((wt * calculateChallengeLevel()) +
            (ws * calculateBehavioralDiversity()) +
            (we * calculateSpatialDiversity())) / (wt + ws + we);
}

// called H in the litterature
// Calculate the average spatial diversity
float ScenarioSet::calculateSpatialDiversity()
{
    if(scenarios.count() > 0){
        float diversity = 0.0;
        foreach(Scenario* s, scenarios){
            diversity += s->calculateSpatialDiversity();
        }
        return diversity / scenarios.count();
    }else{
        return 0.0;
    }
}

// called S in the litterature
// Calculate how diverse the behavior is
float ScenarioSet::calculateBehavioralDiversity()
{
    return calcStandardDeviation() / calcMaximumDeviation();
}

// called T in the litterature
// Calculate the level of challenge
float ScenarioSet::calculateChallengeLevel()
{
    int maxkilltime = 0;
    if((maxkilltime = findMaxKillTime()) != 0){
        return 1 - (calcAverageKillTime() / maxkilltime);
    }else{
        return 0.0;
    }
}

// called E{t_k} in the litterature
// Calculate the average number of steps to kill the player.
float ScenarioSet::calcAverageKillTime()
{
    if(scenarios.count() > 0){
        int steps = 0;
        foreach(Scenario* s, scenarios){
            steps += s->getKillTime();
        }
        return steps / scenarios.count();
    }else{
        return 0.0;
    }
}

// called max{t_k} in the litterature
// Find the maximum number of steps to kill the player.
int ScenarioSet::findMaxKillTime()
{
    int maxkilltime = 0;
    foreach(Scenario* s, scenarios){
        if(s->getKillTime() > maxkilltime){
            maxkilltime = s->getKillTime();
        }
    }
    return maxkilltime;
}

// Find the minimum number of steps to kill the player.
int ScenarioSet::findMinKillTime()
{
    int minkilltime = scenarios.first()->getKillTime();
    foreach(Scenario* s, scenarios){
        if(s->getKillTime() < minkilltime){
            minkilltime = s->getKillTime();
        }
    }
    return minkilltime;
}

// Calculate the maximum standard deviation in killtime
float ScenarioSet::calcMaximumDeviation()
{
    return 0.5 * sqrt(scenarios.count()/(scenarios.count() - 1)) * (findMaxKillTime() - findMinKillTime());
}

// Calculate the standard deviation in killtime
// Found the formula on Wiki so approach with caution
float ScenarioSet::calcStandardDeviation()
{
    if(scenarios.count() > 0){
        float u = calcAverageKillTime();
        float sum = 0.0;

        foreach(Scenario* s, scenarios){
            sum += pow(s->getKillTime() - u,2);
        }
        return sqrt( sum / scenarios.count() );
    }else{
        return 1.0;
    }
}






