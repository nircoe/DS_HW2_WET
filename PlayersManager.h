#ifndef PLAYERS_MANAGER_H
#define PLAYERS_MANAGER_H

#include "library2.h"
#include "AVLTree.h"
#include "UnionFind.h"
#include "HashTable.h"
#include "Group.h"
#include "Player.h"

class UnionFind;
class AVLTree;
template <typename T>
class HashTable;
class Group;
class Player;

class PlayersManager
{
    UnionFind *groups;
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
    //void printallgroups();
};

#endif