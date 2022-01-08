#ifndef GROUP_H
#define GROUP_H

#include <memory>

#include "AVLTree.h"
#include "HashTable.h"
#include "Player.h"
#include "library2.h"
using std::shared_ptr;

class Player;

class Group
{
    int group_id;
    int group_size;

    //* players[0] is all the players in the group,
    //* players[i] is all the players in the group with score i (0<i<201).
    AVLTree<shared_ptr<HashTable<shared_ptr<Player>>>> **players;

public:
    Group(int g_id);
    // Group(int g_id, int g_size, AVLTree<shared_ptr<HashTable<shared_ptr<Player>>>> &players);
    Group() = delete;
    Group(const Group &) = default;
    ~Group() = default;

    int GetId();
    int GetSize();
    StatusType AddPlayerToGroup(shared_ptr<Player> p);
    StatusType RemovePlayerFromGroup(int p_id, int p_level);
    StatusType RemovePlayerFromGroupWithoutDelete(Player *p);
    friend std::ostream &operator<<(std::ostream &os, const Group &g);

    //AVLTree<HashTable<shared_ptr<Player>>> *GetPlayerByLevel();
    //void SetTree(AVLTree<HashTable<shared_ptr<Player>>> &players, int new_size);
};

#endif