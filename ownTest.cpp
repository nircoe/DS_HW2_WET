#include "PlayersManager.h"
#include "library2.h"

int main()
{
    PlayersManager *pm = new PlayersManager(4, 6);
    if(pm->AddPlayer(10, 1, 2) != SUCCESS)
        return 0;
    //pm->printgroup1();
    if (pm->AddPlayer(11, 2, 3) != SUCCESS)
        return 0;
    //pm->printgroup1();
    if (pm->AddPlayer(9, 0, 2) != INVALID_INPUT)
        return 0;
    //pm->printgroup1();
    if (pm->AddPlayer(7, 1, 5) != SUCCESS)
        return 0;
    //pm->printgroup1();
    if (pm->AddPlayer(12, 1, 4) != SUCCESS)
        return 0;
    if (pm->AddPlayer(20, 1, 5) != SUCCESS)
        return 0;
    pm->printgroup1();
    if(pm->IncreasePlayerIDLevel(10, 2) != SUCCESS)
        return 0;
    pm->printgroup1();
    if(pm->IncreasePlayerIDLevel(12, 3) != SUCCESS)
        return 0;
    pm->printgroup1();
    if(pm->ChangePlayerIDScore(10, 3) != SUCCESS)
        return 0;
    pm->printgroup1();
    double players = 0;
    pm->GetPercentOfPlayersWithScoreInBounds(0, 3, 1, 5, &players);
    pm->printgroup1();
    //if(players != 50.00)
    //    return 0;
    if(pm->MergeGroups(1, 2) != SUCCESS)
        return 0;
    pm->printgroup1();
    if(pm->RemovePlayer(20) != SUCCESS)
        return 0;
    pm->printgroup1();
    double avgLevel = 0;
    pm->AverageHighestPlayerLevelByGroup(2, 3, &avgLevel);
    if (avgLevel != 1.67)
        return 0;
    pm->Quit(pm);
    if (pm != nullptr)
        return 0;
    cout << "FINISH" << endl;
    return 0;
}