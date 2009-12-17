#include "scenarioset.h"
#include "math.h"
#include <QFile>
#include <QDebug>

ScenarioSet::ScenarioSet()
{
    wt = 0.333;
    ws = 0.333;
    we = 0.333;
}

// Load the game scenarios from a file
void ScenarioSet::save(QString filename)
{

}

// Save the game scenarios to a file
void ScenarioSet::load(QString filename)
{

}

// Add a scenario to the set
void ScenarioSet::addScenario(Scenario* scenario)
{
    scenarios.append(scenario);
}

// Calculate the overall performance of the behavior.
// Uses entertainment metrics.
float ScenarioSet::calculateInterest()
{
    float challengeLevel = calculateChallengeLevel();
    float behavioralDiversity = calculateBehavioralDiversity();
    float spatialDiversity = calculateSpatialDiversity();
    qDebug() << "Challenge Level: " << challengeLevel;
    qDebug() << "Behavioral Diversity: " << behavioralDiversity;
    qDebug() << "Spatial Diversity: " << spatialDiversity;
    return ((wt * challengeLevel) +
            (ws * behavioralDiversity) +
            (we * spatialDiversity)) / (wt + ws + we);
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
        return diversity / static_cast<float>(scenarios.count());
    }else{
        return 0.0;
    }
}

// called S in the litterature
// Calculate how diverse the behavior is
float ScenarioSet::calculateBehavioralDiversity()
{
    float maximumDeviation = calcMaximumDeviation();
    float standardDeviation = calcStandardDeviation();
    qDebug() << "Behavior Standard Deviation: " << standardDeviation;
    qDebug() << "Behavior Max Deviation: " << maximumDeviation;
    if(maximumDeviation > 0){
        return standardDeviation / maximumDeviation;
    }else{
        return 0.0;
    }
}

// called T in the litterature
// Calculate the level of challenge
float ScenarioSet::calculateChallengeLevel()
{
    int maxkilltime = findMaxKillTime();
    if(maxkilltime != 0){
        return 1 - (calcAverageKillTime() / static_cast<float>(maxkilltime));
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
        return static_cast<float>(steps) / static_cast<float>(scenarios.count());
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
    if(scenarios.count() > 1){
        return 0.5 * sqrt(static_cast<float>(scenarios.count())/(static_cast<float>(scenarios.count()) - 1.0)) * (findMaxKillTime() - findMinKillTime());
    }else{
        return 0.0;
    }
//    return 0.5 * sqrt(static_cast<float>(scenarios.count())/(static_cast<float>(scenarios.count()) - 1.0)) * (findMaxKillTime() - findMinKillTime());
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
        return sqrt( sum / static_cast<float>(scenarios.count()) );
    }else{
        return 1.0;
    }
}

#include "scenarioset.moc"



