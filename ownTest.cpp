#include "PlayersManager.h"
#include "library2.h"

int main()
{
    PlayersManager *pm = new PlayersManager(4, 6);
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
    double players = 0;
    pm->GetPercentOfPlayersWithScoreInBounds(0, 3, 1, 5, &players);
    pm->MergeGroups(1, 2);
    pm->RemovePlayer(20);
    double avgLevel = 0;
    pm->AverageHighestPlayerLevelByGroup(2, 3, &avgLevel);
    pm->Quit(pm);
    return 0;
}