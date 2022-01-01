#ifndef GROUP_H
#define GROUP_H

#include "AVLTree.h"
#include "Player.h"
#include "library2.h"

class Player;

class Group
{
    int group_id;
    int group_size;
    AVLTree<shared_ptr<HashTable<shared_ptr<Player>>>> players;

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
    AVLTree<shared_ptr<HashTable<shared_ptr<Player>>>> *GetPlayerByLevel();
    void SetTree(AVLTree<shared_ptr<HashTable<shared_ptr<Player>>>> &players, int new_size);
};

#endif