#include "library2.h"
#include "PlayersManager.h"

void *Init(int k, int scale)
{
    try
    {
        PlayersManager *DS = new PlayersManager(k, scale);
        return (void *)(DS);
    }
    catch (const std::exception &e)
    {
        return NULL;
    }
}

StatusType MergeGroups(void *DS, int GroupID1, int GroupID2)
{

}

StatusType AddPlayer(void *DS, int PlayerID, int GroupID, int score)
{

}

StatusType RemovePlayer(void *DS, int PlayerID)
{

}

StatusType IncreasePlayerIDLevel(void *DS, int PlayerID, int LevelIncrease)
{

}

StatusType ChangePlayerIDScore(void *DS, int PlayerID, int NewScore)
{

}

StatusType GetPercentOfPlayersWithScoreInBounds(void *DS, int GroupID, int score, int lowerLevel, int higherLevel,
                                                double *players)
{

}

StatusType AverageHighestPlayerLevelByGroup(void *DS, int GroupID, int m, double *level)
{

}

StatusType GetPlayersBound(void *DS, int GroupID, int score, int m,
                           int *LowerBoundPlayers, int *HigherBoundPlayers)
{

}

void Quit(void **DS)
{

}