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
void Group::SetSize(int new_size)
{
    this->group_size = new_size;
}
StatusType Group::AddPlayerToGroup(shared_ptr<Player> p)
{
    //TODO: remove print
    std::cout << "adding " << p.get()->GetId() << " to group " << this->GetId() << std::endl;
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
                //TODO: remove
                cout << "FAILED TO ADD NEW HASHTABLE!!!!!" << endl;
                return ALLOCATION_ERROR;
            }
        }
        if (ht_ptr.get()->Insert(p.get()->GetId(), p) == -1) //* if Insert return false => allocation error
        {
            //TODO: remove
            cout << "FAILED TO ADD NEW PLAYER!!!!!" << endl;
            return ALLOCATION_ERROR;
        }
        players[i].addPlayerTo(p_level, 1);
    }
    this->group_size++;
    //TODO: remove
    cout << *this << endl;
    //cout << "Group " << this->GetId() << std::endl
    //    << *(players[0].Find(p_level).get());

    return SUCCESS;
}
StatusType Group::RemovePlayerFromGroup(int p_id, int p_level)
{
    //TODO: remove
    cout << "group " << this->GetId() << " removing " << p_id << " from level " << p_level;
    //cout << "Group " << this->group_id << " level " << p_level << " before delete"<< std::endl << *(players[0].Find(p_level).get());
    shared_ptr<Player> sp_p = players[0].Find(p_level).get()->Search(p_id);
    if (sp_p != NULL)
    {
        int score = sp_p.get()->GetScore();
        if (players[0].Find(p_level).get()->Delete(p_id) &&
            players[score].Find(p_level).get()->Delete(p_id))
        {
            players[0].addPlayerTo(p_level, -1);
            players[score].addPlayerTo(p_level, -1);
            this->group_size--;
            //cout << "Group " << this->group_id << " level " << p_level << " after delete"<< std::endl << *(players[0].Find(p_level).get());
            cout << " DONE" << endl;
            return SUCCESS;
        }
    }
    cout << " FAILED" << endl;
    return FAILURE;
}
std::ostream &operator<<(std::ostream &os, const Group &g)
{
    os << "Group " << g.group_id << ":" << std::endl;
    for (int i = 0; i <= g.scale; i++)
    {
        if (g.players[i].GetTreeSize())
        {
            os << "PLayers with score: " << i << ":" << endl;
            g.players[i].Print();
        }
    }

    return os;
}
StatusType Group::GetPercentOfPlayersWithScoreInBounds(int score, int lowerLevel, int higherLevel, double *players)
{
    int total_players_in_bound, total_players_with_score_in_bound;
    total_players_in_bound = this->players[0].GetNumOfPlayersInBound(lowerLevel, higherLevel);
    //TODO: Remove this print.
    std::cout << "total_in_bound: " << total_players_in_bound << std::endl;
    if (total_players_in_bound == 0)
        return FAILURE;
    if (score < 1 || scale < score)
        total_players_with_score_in_bound = 0;
    else
    {
        total_players_with_score_in_bound = this->players[score].GetNumOfPlayersInBound(lowerLevel, higherLevel);
        cout << "printing group " << this->GetId() << " in score " << score << endl;
        this->players[score].Print();
    }
    std::cout << "score_in_bound: " << total_players_with_score_in_bound << std::endl;
    *players = ((double)total_players_with_score_in_bound / (double)total_players_in_bound) * 100;
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
        if (n1 + n2 == 0)
            continue;
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
            new AVLTree<shared_ptr<HashTable<shared_ptr<Player>>>>(merged_keys, merged_data, j);
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
    //delete sub;
}

Group::~Group()
{
    //* Should work, players is an array.
    delete[] players;
}

void Group::printlevel0()
{
    cout << "Group 0 level 0:" << std::endl
         << *(this->players[0].Find(0).get()) << std::endl;
}