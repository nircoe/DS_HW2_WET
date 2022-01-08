#include "library2.h"
#include "PlayersManager.h"

void *Init(int k, int scale)
{
    if(k <= 0 || scale <= 0 || 200 < scale)
        return NULL;
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
    if(DS == NULL || GroupID1 <= 0 || GroupID2 <= 0)
        return INVALID_INPUT;
    try
    {
        /* code */
    }
    catch(const std::exception& e)
    {
        return ALLOCATION_ERROR;
    }
    
}

StatusType AddPlayer(void *DS, int PlayerID, int GroupID, int score)
{
    if(DS == NULL || PlayerID <= 0 || GroupID <= 0 || score <= 0)
        return INVALID_INPUT;
    try { return ((PlayersManager *)DS)->AddPlayer(PlayerID, GroupID, score); }
    catch(const std::bad_alloc& e) { return ALLOCATION_ERROR; }
    catch(const std::exception& e) { return FAILURE; }
    
}

StatusType RemovePlayer(void *DS, int PlayerID)
{
    if(DS == NULL || PlayerID <= 0)
        return INVALID_INPUT;
    try { return ((PlayersManager *)DS)->RemovePlayer(PlayerID); }
    catch(const std::exception& e) { return FAILURE; }
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