#include "Group.h"
#include "AVLTree.h"
#include <memory>
using std::make_shared;
using std::shared_ptr;

Group::Group(int g_id, int scale) : group_id(g_id), group_size(0), scale(scale)
{
    if (scale > MAX_SCALE)
        throw FAILURE;
    playersbyid = new HashTable<shared_ptr<Player>>();
    levelsinscorei = new AVLTree[scale + 1];
    for (int i = 0; i <= scale; i++)
    {
        levelsinscorei[i] = AVLTree();
    }
}

int Group::GetId()
{
    return (this != 0) ? this->group_id : -1;
}
int Group::GetSize()
{
    return (this != 0) ? this->group_size : -1;
}
HashTable<shared_ptr<Player>> *Group::GetPlayersByID()
{
    return (this != 0) ? this->playersbyid : nullptr;
}
void Group::SetSize(int new_size)
{
    this->group_size = new_size;
}
StatusType Group::AddPlayerToGroup(shared_ptr<Player> p)
{
    int p_level = p.get()->GetLevel();
    int p_score = p.get()->GetScore();
    AVLNode *node;
    //* do the same insert twice: once for players[0] and once for players[p_score]
    for (int i = 0; i < p_score + 1; i += p_score)
    {
        if (p_level == 0)
        {
            node = levelsinscorei[i].GetLowestNodePointer(); // O(1) (level 0 is lowest)
            if (node == nullptr)                             //* this level exist in the tree
            {                                                //* create new node in the tree, insert level 0, tree is empty => O(1)
                if (!levelsinscorei[i].Insert(p_level))   //* if Insert return false => allocation error
                    return ALLOCATION_ERROR;
                node = levelsinscorei[i].GetLowestNodePointer(); // level 0 will be the first node in the tree => the root
            }
        }
        else // only in IncreasePlayerIDLevel , O(log n)
        {
            node = levelsinscorei[i].Find_aux(levelsinscorei[i].GetRoot(), p_level);
            if (node == nullptr)
            {
                if (!levelsinscorei[i].Insert(p_level))
                    return ALLOCATION_ERROR;
                node = levelsinscorei[i].Find_aux(levelsinscorei[i].GetRoot(), p_level);
            }
        }
        node->IncreasePlayers(1);
        levelsinscorei[i].UpdateAllRankes(levelsinscorei[i].GetRoot()); 
    }
    this->playersbyid->Insert(p.get()->GetId(), p);
    this->group_size++;

    return SUCCESS;
}
StatusType Group::RemovePlayerFromGroup(int p_id, int p_level)
{
    shared_ptr<Player> sp_p = playersbyid->Search(p_id);
    if (sp_p != nullptr)
    {
        int score = sp_p.get()->GetScore();
        AVLNode *root0 = levelsinscorei[0].GetRoot(), *rootscore = levelsinscorei[score].GetRoot();
        if (root0 && rootscore)
        {
            AVLNode *levelall = this->levelsinscorei[0].Find_aux(root0, p_level),
                         *levelscore = levelsinscorei[score].Find_aux(rootscore, p_level);
            if (levelall && levelscore)
            {
                levelall->IncreasePlayers(-1);
                levelscore->IncreasePlayers(-1);
                if (p_level != 0)
                {
                    if (levelall->GetPlayers() == 0)
                        levelsinscorei[0].Remove(p_level);
                    if (levelscore->GetPlayers() == 0)
                        levelsinscorei[score].Remove(p_level);
                }
                this->group_size--;
                this->playersbyid->Delete(p_id);
                return SUCCESS;
            }
        }
    }
    return FAILURE;
}
std::ostream &operator<<(std::ostream &os, const Group &g)
{
    os << "GROUP " << g.group_id << " | Total Players = " << g.group_size << std::endl;
    if (g.group_size > 0)
    {
        os << "Players by ID" << std::endl
           << (*(g.playersbyid)) << std::endl;
        os << "All Players Levels" << std::endl;
        g.levelsinscorei[0].printTree(os);
        for (int i = 1; i <= g.scale; i++)
        {
            if (g.levelsinscorei[i].GetTreeSize() > 0)
            {
                os << std::endl
                   << "Score " << i << " Players Levels" << std::endl;
                g.levelsinscorei[i].printTree(os);
                os << std::endl;
            }
        }
    }
    return os;
}

StatusType Group::GetPercentOfPlayersWithScoreInBounds(int score, int lowerLevel, int higherLevel, double *players)
{
    int total_players_in_bound, total_players_with_score_in_bound;
    total_players_in_bound = this->levelsinscorei[0].GetNumOfPlayersInBound(lowerLevel, higherLevel);
    if (total_players_in_bound == 0)
        return FAILURE;
    if (score < 1 || scale < score)
        total_players_with_score_in_bound = 0;
    else
    {
        total_players_with_score_in_bound = this->levelsinscorei[score].GetNumOfPlayersInBound(lowerLevel, higherLevel);
    }
    *players = ((double)total_players_with_score_in_bound / (double)total_players_in_bound) * 100;
    return SUCCESS;
}

StatusType Group::AverageHighestPlayerLevel(int m, double *avgLevel)
{
    return levelsinscorei[0].AverageHighest(m, avgLevel);
}

shared_ptr<Player> *Group::GetAllPlayersInArray()
{
    shared_ptr<Player> *all_players = new shared_ptr<Player>[group_size];  
    shared_ptr<Player> *hts = this->playersbyid->GetDataArray();
    int n = this->playersbyid->GetSize();
    for (int i = 0; i < n; i++)
    {
        all_players[i] = hts[i];
    }
    return all_players;
}

void Group::MergeWith(Group *sub)
{
    for (int i = 0; i <= scale; i++)
    {
        int n1 = this->levelsinscorei[i].GetTreeSize(),
            n2 = sub->levelsinscorei[i].GetTreeSize(),
            i1 = 0, i2 = 0, j = 0;
        if (n1 + n2 == 0)
            continue;
        int *keys1 = this->levelsinscorei[i].GetKeysArray(),
            *keys2 = sub->levelsinscorei[i].GetKeysArray(),
            *merged_keys = new int[n1 + n2];
        int *players1 = this->levelsinscorei[i].GetPlayersArray(),
            *players2 = sub->levelsinscorei[i].GetPlayersArray(),
            *merged_players = new int[n1 + n2];
        //* merging hashtables by each level:
        while (i1 < n1 && i2 < n2)
        {
            if (keys1[i1] < keys2[i2])
            {
                merged_players[j] = players1[i1];
                merged_keys[j] = keys1[i1];
                i1++;
            }
            else if (keys1[i1] > keys2[i2])
            {
                merged_players[j] = players2[i2];
                merged_keys[j] = keys2[i2];
                i2++;
            }
            else
            {
                merged_players[j] = players1[i1] + players2[i2];
                merged_keys[j] = keys1[i1];
                i1++;
                i2++;
            }
            j++;
        }
        while (i1 < n1)
        {
            merged_players[j] = players1[i1];
            merged_keys[j] = keys1[i1];
            i1++;
            j++;
        }
        while (i2 < n2)
        {
            merged_players[j] = players2[i2];
            merged_keys[j] = keys2[i2];
            i2++;
            j++;
        }
        AVLTree merged_tree = AVLTree(merged_keys, merged_players, j);
        delete[] keys1;
        delete[] keys2;
        delete[] players1;
        delete[] players2;
        delete[] merged_players;
        delete[] merged_keys;
        merged_tree.UpdateAllRankes(merged_tree.GetRoot());
        //! I hope this won`t cause problems:
        this->levelsinscorei[i] = merged_tree;
    }
    shared_ptr<Player> *players = sub->GetPlayersByID()->GetDataArray();
    int n = sub->GetPlayersByID()->GetSize();
    for (int i = 0; i < n; i++)
        players[i].get()->SetGroup(this->GetId());
    this->playersbyid->MergeWith(sub->playersbyid);
    delete[] players;
    //delete sub;
}

Group::~Group()
{
    //* Should work, players is an array.
    //DeleteSharedPtrPlayerHashTable<shared_ptr<Player>>(playersbyid);
    delete playersbyid;
    delete[] levelsinscorei;
}
