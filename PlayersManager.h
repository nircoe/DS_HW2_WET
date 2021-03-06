#ifndef PLAYERS_MANAGER_H
#define PLAYERS_MANAGER_H

#include "library2.h"
#include "AVLTree.h"
#include "UnionFind.h"
#include "HashTable.h"
#include "Group.h"
#include "Player.h"

class UnionFind;
template <typename T>
class AVLTree;
template <typename T>
class HashTable;
class Group;
class Player;


class PlayersManager
{
    UnionFind *groups;
    HashTable<shared_ptr<Player>> *playersbyid;
    int numOfGroups;
    int maxScore;
    ~PlayersManager();

public:
    PlayersManager() = delete;
    PlayersManager(int k, int scale);
    StatusType MergeGroups(int GroupID1, int GroupID2);
    StatusType AddPlayer(int PlayerID, int GroupID, int score);
    StatusType RemovePlayer(int PlayerID);
    StatusType IncreasePlayerIDLevel(int PlayerID, int LevelIncrease);
    StatusType ChangePlayerIDScore(int PlayerID, int NewScore);
    StatusType GetPercentOfPlayersWithScoreInBounds(int GroupID, int score, int lowerLevel, int higherLevel, double *players);
    StatusType AverageHighestPlayerLevelByGroup(int GroupID, int m, double *avgLevel);
    void Quit(PlayersManager *pm);
    void PrintGroup(int id);
    friend std::ostream &operator<<(std::ostream &os, const PlayersManager &pm);
};

#endif