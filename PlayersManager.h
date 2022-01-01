#ifndef PLAYERS_MANAGER_H
#define PLAYERS_MANAGER_H

#include "AVLTree.h"
#include "UnionFind.h"
#include "HashTable.h"
#include "Group.h"
#include "Player.h"

template<typename T>
class UnionFind;
template <typename T>
class AVLTree;
template <typename T>
class HashTable;
class Group;
class Player;


class PlayersManager
{
    UnionFind<Group> groups;
    HashTable<shared_ptr<Player>> playersbyid;
    AVLTree<shared_ptr<HashTable<shared_ptr<Player>>>> playersbylevel;
    AVLTree<shared_ptr<HashTable<shared_ptr<Player>>>> * playersbyscore;

    public:
        PlayersManager() = delete;
        PlayersManager(int k, int scale)
        {
            groups = UnionFind<Group>(k);
            playersbyid = HashTable<shared_ptr<Player>>();
            playersbylevel = AVLTree<shared_ptr<HashTable<shared_ptr<Player>>>>();
            playersbyscore = new AVLTree<shared_ptr<HashTable<shared_ptr<Player>>>>[scale];
        }

};

#endif