#ifndef GROUP_H
#define GROUP_H

#include <memory>

#include "AVLTree.h"
#include "HashTable.h"
#include "Player.h"
#include "library2.h"
using std::shared_ptr;

class AVLNode;
class AVLTree;
class Player;
const int MAX_SCALE = 200;
class Group
{
    int group_id;
    int group_size;
    int scale;
    //* players[0] is all the players in the group,
    //* players[i] is all the players in the group with score i (0<i<201).
    //AVLTree<shared_ptr<HashTable<shared_ptr<Player>>>> *players;
    HashTable<shared_ptr<Player>> *playersbyid;
    AVLTree *levelsinscorei;

public:
    Group(int g_id, int scale);
    // Group(int g_id, int g_size, AVLTree<shared_ptr<HashTable<shared_ptr<Player>>>> &players);
    Group() = delete;
    Group(const Group &) = default;
    ~Group();

    int GetId();
    int GetSize();
    HashTable<shared_ptr<Player>> *GetPlayersByID();
    void SetSize(int new_size);
    StatusType AddPlayerToGroup(shared_ptr<Player> p);
    StatusType RemovePlayerFromGroup(int p_id, int p_level);
    StatusType RemovePlayerFromGroupWithoutDelete(Player *p);
    friend std::ostream &operator<<(std::ostream &os, const Group &g);
    StatusType GetPercentOfPlayersWithScoreInBounds(int score, int lowerLevel, int higherLevel, double *players);
    StatusType AverageHighestPlayerLevel(int m, double *avgLevel);
    shared_ptr<Player> *GetAllPlayersInArray();
    void MergeWith(Group *subgroup);
};

#endif