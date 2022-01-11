#include "PlayersManager.h"
#include "library2.h"

int main()
{
    PlayersManager *pm = new PlayersManager(4, 6);
<<<<<<< HEAD
    pm->AddPlayer(10, 1, 2);
    pm->AddPlayer(11, 2, 3);
    pm->AddPlayer(9, 0, 2);
    cout << "HI" << endl;
    pm->AddPlayer(7, 1, 5);
    pm->AddPlayer(12, 1, 4);
    
    pm->AddPlayer(20, 1, 5);
    pm->IncreasePlayerIDLevel(10, 2);
    pm->IncreasePlayerIDLevel(12, 3);
    pm->ChangePlayerIDScore(10, 3);
=======
    if(pm->AddPlayer(10, 1, 2) != SUCCESS)
        return 0;
    pm->printgroup1();
    if (pm->AddPlayer(11, 2, 3) != SUCCESS)
        return 0;
    pm->printgroup1();
    if (pm->AddPlayer(9, 0, 2) != INVALID_INPUT)
        return 0;
    pm->printgroup1();
    if (pm->AddPlayer(7, 1, 5) != SUCCESS)
        return 0;
    pm->printgroup1();
    if (pm->AddPlayer(12, 1, 4) != SUCCESS)
        return 0;
    if(pm->AddPlayer(20, 1, 5) != SUCCESS)
        return 0;
    if(pm->IncreasePlayerIDLevel(10, 2) != SUCCESS)
        return 0;
    if(pm->IncreasePlayerIDLevel(12, 3) != SUCCESS)
        return 0;
    if(pm->ChangePlayerIDScore(10, 3) != SUCCESS)
        return 0;
>>>>>>> 307a314a6cca6d38f5b99463672102cf07bc0466
    double players = 0;
    pm->GetPercentOfPlayersWithScoreInBounds(0, 3, 1, 5, &players);
    if(players != 50.00)
        return 0;
    if(pm->MergeGroups(1, 2) != SUCCESS)
        return 0;
    if(pm->RemovePlayer(20) != SUCCESS)
        return 0;
    double avgLevel = 0;
    pm->AverageHighestPlayerLevelByGroup(2, 3, &avgLevel);
    if(avgLevel != 1.67)
        return 0;
    pm->Quit(pm);
    if(pm != nullptr)
        return 0;
    return 0;
}