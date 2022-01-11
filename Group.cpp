#include "Group.h"
#include "AVLTree.h"
#include <memory>
using std::make_shared;
using std::shared_ptr;
/*
    StatusType AddPlayerToGroup(shared_ptr<Player> p);
    StatusType RemovePlayerFromGroup(int p_id, int p_level);
    StatusType RemovePlayerFromGroupWithoutDelete(Player *p);
*/
Group::Group(int g_id, int scale) : group_id(g_id), group_size(0), scale(scale)
{
    if (scale > MAX_SCALE)
        throw FAILURE;
    players = new AVLTree<shared_ptr<HashTable<shared_ptr<Player>>>>[scale + 1];
    for (int i = 0; i <= scale; i++)
    {
        players[i] = AVLTree<shared_ptr<HashTable<shared_ptr<Player>>>>();
    }
}
// Group::Group(int g_id, int g_size, AVLTree<HashTable<shared_ptr<Player>>> &g_players)
// {
//     group_id = g_id;
//     group_size = g_size;
//     players = g_players;
// }
int Group::GetId()
{
    return (this != 0) ? this->group_id : -1;
}
int Group::GetSize()
{
    return (this != 0) ? this->group_size : -1;
}
StatusType Group::AddPlayerToGroup(shared_ptr<Player> p)
{
    int p_level = p.get()->GetLevel();
    int p_score = p.get()->GetScore();
    shared_ptr<HashTable<shared_ptr<Player>>> ht_ptr;
    //* do the same insert twice: once for players[0] and once for players[p_score]
    for (int i = 0; i < p_score + 1; i += p_score)
    {
        if (players[i].Exists(p_level)) //* this level exist in the tree
            ht_ptr = players[i].Find(p_level);
        else //* create new node in the tree
        {
            ht_ptr = make_shared<HashTable<shared_ptr<Player>>>();
            if (!players[i].Insert(p_level, ht_ptr)) //* if Insert return false => allocation error
            {
                //? ht_ptr.reset();
                return ALLOCATION_ERROR;
            }
        }
        if (!ht_ptr.get()->Insert(p.get()->GetId(), p)) //* if Insert return false => allocation error
            return ALLOCATION_ERROR;
    }
    this->group_size++;
    return SUCCESS;
}
StatusType Group::RemovePlayerFromGroup(int p_id, int p_level)
{
    shared_ptr<Player> sp_p = players[0].Find(p_level).get()->Search(p_id);
    if (sp_p != NULL)
    {
        int score = sp_p.get()->GetScore();
        if (players[0].Find(p_level).get()->Delete(p_id) &&
            players[score].Find(p_level).get()->Delete(p_id))
        {
            this->group_size--;
            return SUCCESS;
        }
    }
    return FAILURE;
}
std::ostream &operator<<(std::ostream &os, const Group &g)
{
    os << "GROUP " << g.group_id << std::endl;
    shared_ptr<HashTable<shared_ptr<Player>>> *ps = g.players[0].GetDataArray();
    for (int i = 0; i < g.group_size; i++)
    {
        os << ps->get() << std::endl;
    }
    return os;
}
StatusType Group::GetPercentOfPlayersWithScoreInBounds(int score, int lowerLevel, int higherLevel, double *players)
{
    double total_players_in_bound, total_players_with_score_in_bound;
    total_players_in_bound = GetNumOfPlayersInBound<shared_ptr<HashTable<shared_ptr<Player>>>>(this->players[0], lowerLevel, higherLevel);
    if (total_players_in_bound == 0)
        return FAILURE;
    if (score < 1 || scale < score)
        total_players_with_score_in_bound = 0;
    else
        total_players_with_score_in_bound = GetNumOfPlayersInBound<shared_ptr<HashTable<shared_ptr<Player>>>>(this->players[score], lowerLevel, higherLevel);
    *players = ((total_players_with_score_in_bound / total_players_in_bound) * 100);
    return SUCCESS;
}

StatusType Group::AverageHighestPlayerLevel(int m, double *avgLevel)
{
    return AverageHighest<shared_ptr<HashTable<shared_ptr<Player>>>>(this->players[0], m, avgLevel);
}
// AVLTree<shared_ptr<HashTable<shared_ptr<Player>>>> *Group::GetPlayers()
// {
//     return this->players.;
// }
// void Group::SetTree(AVLTree<shared_ptr<AVLTree<shared_ptr<Player>>>> &new_players, int new_size)
// {
//     this->group_size = new_size;
//     this->players = new_players;
// }
shared_ptr<Player> *Group::GetAllPlayersInArray()
{
    shared_ptr<Player> *players_in_ht;
    shared_ptr<Player> *all_players = new shared_ptr<Player>[group_size];
    int index = 0;
    HashTable<std::shared_ptr<Player>> *hts = this->players[0].GetDataArray()->get();
    int n = this->players[0].GetTreeSize();
    for (int i = 0; i < n; i++)
    {
        players_in_ht = hts[i].GetDataArray();
        for (int j = 0; j < hts[i].GetSize(); j++)
        {
            all_players[index] = players_in_ht[j];
            index++;
        }
    }
    return all_players;
}

void Group::MergeWith(Group *sub)
{
    for (int i = 0; i <= scale; i++)
    {
        int n1 = this->players[i].GetTreeSize(),
            n2 = sub->players[i].GetTreeSize(),
            i1 = 0, i2 = 0, j = 0;
        int *keys1 = this->players[i].GetKeysArray(),
            *keys2 = sub->players[i].GetKeysArray(),
            *merged_keys = new int[n1 + n2];
        shared_ptr<HashTable<shared_ptr<Player>>> *data1 = this->players[i].GetDataArray(),
                                                  *data2 = sub->players[i].GetDataArray(),
                                                  *merged_data = new shared_ptr<HashTable<shared_ptr<Player>>>[n1 + n2];
        //* merging hashtables by each level:
        while (i1 < n1 && i2 < n2)
        {
            if (keys1[i1] < keys2[i2])
            {
                merged_data[j] = data1[i1];
                merged_keys[j] = keys1[i1];
                i1++;
            }
            else if (keys1[i1] > keys2[i2])
            {
                merged_data[j] = data2[i2];
                merged_keys[j] = keys2[i2];
                i2++;
            }
            else
            {
                data1[i1].get()->MergeWith(data2[i2].get());
                merged_data[j] = data1[i1];
                merged_keys[j] = keys1[i1];
                i1++;
                i2++;
            }
            j++;
        }
        while (i1 < n1)
        {
            merged_data[j] = data1[i1];
            merged_keys[j] = keys1[i1];
            i1++;
            j++;
        }
        while (i2 < n2)
        {
            merged_data[j] = data2[i2];
            merged_keys[j] = keys2[i2];
            i2++;
            j++;
        }
        AVLTree<shared_ptr<HashTable<shared_ptr<Player>>>> *merged_tree =
            new AVLTree<shared_ptr<HashTable<shared_ptr<Player>>>>(merged_keys, merged_data, n1 + n2);
        delete[] keys1;
        delete[] keys2;
        delete[] data1;
        delete[] data2;
        delete[] merged_data;
        delete[] merged_keys;
        merged_tree->UpdateAllRankes(merged_tree->root);
        //! I hope this won`t cause problems:
        this->players[i] = *merged_tree;
    }
    delete sub;
}

Group::~Group()
{
    //* Should work, players is an array.
    delete[] players;
}
