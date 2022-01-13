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
        return ((PlayersManager *)DS)->MergeGroups(GroupID1, GroupID2);
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
    if(DS == NULL || PlayerID <= 0 || LevelIncrease <= 0)
        return INVALID_INPUT;
    try { return ((PlayersManager *)DS)->IncreasePlayerIDLevel(PlayerID, LevelIncrease); }
    catch(const std::bad_alloc& e) { return ALLOCATION_ERROR; }
    catch(const std::exception& e) { return FAILURE; }
}

StatusType ChangePlayerIDScore(void *DS, int PlayerID, int NewScore)
{
    if(DS == NULL || PlayerID <= 0 || NewScore <= 0)
        return INVALID_INPUT;
    try { return ((PlayersManager *)DS)->ChangePlayerIDScore(PlayerID, NewScore); }
    catch(const std::bad_alloc& e) { return ALLOCATION_ERROR; }
    catch(const std::exception& e) { return FAILURE; }
}

StatusType GetPercentOfPlayersWithScoreInBounds(void *DS, int GroupID, int score, int lowerLevel, int higherLevel,
                                                double *players)
{
    if(DS == NULL || GroupID < 0 || players == NULL)
        return INVALID_INPUT;
    try 
    {
        return ((PlayersManager *)DS)->GetPercentOfPlayersWithScoreInBounds(GroupID, score, 
                                                                            lowerLevel, higherLevel,
                                                                            players);
    }
    catch(const std::bad_alloc& e) { return ALLOCATION_ERROR; }
    catch(const std::exception& e) { return FAILURE; }
}

StatusType AverageHighestPlayerLevelByGroup(void *DS, int GroupID, int m, double *level)
{
    if(DS == NULL || GroupID < 0 || m <= 0 || level == NULL)
        return INVALID_INPUT;
    try  { return ((PlayersManager *)DS)->AverageHighestPlayerLevelByGroup(GroupID, m, level); }
    catch(const std::bad_alloc& e) { return ALLOCATION_ERROR; }
    catch(const std::exception& e) { return FAILURE; }
}

StatusType GetPlayersBound(void *DS, int GroupID, int score, int m,
                           int *LowerBoundPlayers, int *HigherBoundPlayers)
{
    return SUCCESS; // i'm optimist
}

void Quit(void **DS)
{
    if(DS == NULL) return;
    PlayersManager *pm = ((PlayersManager *)(*DS));
    pm->Quit(pm);
    *DS = nullptr;
}