#ifndef GROUP_H
#define GROUP_H

#include "AVLTree.h"
#include "HashTable.h"
#include "Player.h"
#include "library2.h"
#include <memory>

const int MAX_SCALE = 200;
class Player;

class Group
{
    int group_id;
    int group_size;
    AVLTree<HashTable<shared_ptr<Player>>> players_by_level;
    AVLTree<HashTable<shared_ptr<Player>>> players_by_score[MAX_SCALE + 1];

public:
    Group(int g_id);
    Group(int g_id, int g_size, AVLTree<HashTable<shared_ptr<Player>>> &players);
    Group() = delete;
    Group(const Group &) = default;
    ~Group() = default;

    int GetId();
    int GetSize();
    StatusType AddPlayerToGroup(shared_ptr<Player> p);
    StatusType RemovePlayerFromGroup(int p_id, int p_level);
    StatusType RemovePlayerFromGroupWithoutDelete(Player *p);
    //AVLTree<HashTable<shared_ptr<Player>>> *GetPlayerByLevel();
    //void SetTree(AVLTree<HashTable<shared_ptr<Player>>> &players, int new_size);
};

#endif