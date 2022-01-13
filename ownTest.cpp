#include "PlayersManager.h"
#include "library2.h"

int main()
{
    PlayersManager *pm = new PlayersManager(4, 6);
    if (pm->AddPlayer(10, 1, 2) != SUCCESS)
        return 0;
    if (pm->AddPlayer(11, 2, 3) != SUCCESS)
        return 0;
    if (pm->AddPlayer(9, 0, 2) != INVALID_INPUT)
        return 0;
    if (pm->AddPlayer(7, 1, 5) != SUCCESS)
        return 0;
    if (pm->AddPlayer(12, 1, 4) != SUCCESS)
        return 0;
    if (pm->AddPlayer(20, 1, 5) != SUCCESS)
        return 0;
    cout << "---------ADDED ALL PLAYERS---------" << endl;
    cout << "---------INCREASING 10 LEVEL BY 2---------" << endl;
    if (pm->IncreasePlayerIDLevel(10, 2) != SUCCESS)
        return 0;
    cout << "---------INCREASING 12 LEVEL BY 3---------" << endl;
    if (pm->IncreasePlayerIDLevel(12, 3) != SUCCESS)
        return 0;
    cout << "---------CHANGING 10 SCORE TO 3---------" << endl;
    if (pm->ChangePlayerIDScore(10, 3) != SUCCESS)
        return 0;
    cout << "---------CHECKING PLAYERS IN BOUND [1,5] WITH SCORE 3---------" << endl;
    double players = 0;
    pm->GetPercentOfPlayersWithScoreInBounds(0, 3, 1, 5, &players);
    cout << "Inbound: " << players << endl;

    if (players != 50.00)
        return 0;
    if (pm->MergeGroups(1, 2) != SUCCESS)
        return 0;
    if (pm->RemovePlayer(20) != SUCCESS)
        return 0;
    double avgLevel = 0;
    pm->AverageHighestPlayerLevelByGroup(2, 3, &avgLevel);
    cout << "Average: " << avgLevel << endl;
    // if (avgLevel != 1.67)
    //     return 0;
    pm->Quit(pm);
    if (pm != nullptr)
        return 0;
    cout << "--------------FINISH----------------" << endl;
    return 0;
}