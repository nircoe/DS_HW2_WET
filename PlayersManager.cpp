#include "PlayersManager.h"

PlayersManager::PlayersManager(int k, int scale) : numOfGroups(k), maxScore(scale)
{
    groups = UnionFind<shared_ptr<Group>>(k);
    playersbyid = HashTable<shared_ptr<Player>>();
}

PlayersManager::~PlayersManager()
{
    groups.~UnionFind();
    playersbyid.~HashTable();
}

//TODO: fix ranks and add players to other group
StatusType PlayersManager::MergeGroups(int GroupID1, int GroupID2)
{
    if (GroupID1 > numOfGroups || GroupID2 > numOfGroups ||
        GroupID1 <= 0 || GroupID2 <= 0)
        return INVALID_INPUT;

    //TODO: need to complete
    Group *g1 = groups.Find(GroupID1).get();
    Group *g2 = groups.Find(GroupID2).get();
    Group *main_g, *sub_g;
    int n1 = g1->GetSize();
    int n2 = g2->GetSize();
    int sub_n;
    if (n1 > n2)
    {
        main_g = g1;
        sub_g = g2;
        sub_n = n2;
    }
    else
    {
        main_g = g2;
        sub_g = g1;
        sub_n = n1;
    }
    std::shared_ptr<Player> *players_in_sub = sub_g->GetAllPlayersInArray();
    for (int i = 0; i < sub_n; i++)
        players_in_sub[i].get()->SetGroup(main_g->GetId());

    groups.Union(GroupID1, GroupID2);

    return SUCCESS;
}
StatusType PlayersManager::AddPlayer(int PlayerID, int GroupID, int score)
{
    if (GroupID > numOfGroups || score > maxScore)
        return INVALID_INPUT;
    shared_ptr<Player> player = this->playersbyid.Search(PlayerID);
    if (player != 0)
        return FAILURE;
    player = make_shared<Player>(PlayerID, score, GroupID);
    this->playersbyid.Insert(PlayerID, player);
    shared_ptr<Group> group = this->groups.Find(GroupID), mainGroup = this->groups.GetMainGroup();
    if (group.get()->AddPlayerToGroup(player) != SUCCESS ||
        mainGroup.get()->AddPlayerToGroup(player) != SUCCESS)
        return ALLOCATION_ERROR;
    return SUCCESS;
}
StatusType PlayersManager::RemovePlayer(int PlayerID)
{
    shared_ptr<Player> player = this->playersbyid.Search(PlayerID);
    if (player == 0)
        return FAILURE;
    shared_ptr<Group> group = this->groups.Find(player.get()->GetGroup()),
                      mainGroup = this->groups.GetMainGroup();
    int p_level = player.get()->GetLevel();
    if (playersbyid.Delete(PlayerID) != true ||
        group.get()->RemovePlayerFromGroup(PlayerID, p_level) != SUCCESS ||
        mainGroup.get()->RemovePlayerFromGroup(PlayerID, p_level) != SUCCESS)
        return FAILURE;
    return SUCCESS;
}
StatusType PlayersManager::IncreasePlayerIDLevel(int PlayerID, int LevelIncrease)
{
    shared_ptr<Player> player = this->playersbyid.Search(PlayerID);
    if (player == 0)
        return FAILURE;
    int p_level = player.get()->GetLevel();
    shared_ptr<Group> group = this->groups.Find(player.get()->GetGroup()),
                      mainGroup = this->groups.GetMainGroup();
    if (group.get()->RemovePlayerFromGroup(PlayerID, p_level) != SUCCESS ||
        mainGroup.get()->RemovePlayerFromGroup(PlayerID, p_level) != SUCCESS)
        return FAILURE;
    player.get()->IncrementLevel(LevelIncrease);
    if (group.get()->AddPlayerToGroup(player) != SUCCESS ||
        mainGroup.get()->AddPlayerToGroup(player) != SUCCESS)
        return ALLOCATION_ERROR;
    return SUCCESS;
}
StatusType PlayersManager::ChangePlayerIDScore(int PlayerID, int NewScore)
{
    if (NewScore > maxScore)
        return INVALID_INPUT;
    shared_ptr<Player> player = this->playersbyid.Search(PlayerID);
    if (player == 0)
        return FAILURE;
    int p_level = player.get()->GetLevel();
    shared_ptr<Group> group = this->groups.Find(player.get()->GetGroup()),
                      mainGroup = this->groups.GetMainGroup();
    if (group.get()->RemovePlayerFromGroup(PlayerID, p_level) != SUCCESS ||
        mainGroup.get()->RemovePlayerFromGroup(PlayerID, p_level) != SUCCESS)
        return FAILURE;
    player.get()->SetScore(NewScore);
    if (group.get()->AddPlayerToGroup(player) != SUCCESS ||
        mainGroup.get()->AddPlayerToGroup(player) != SUCCESS)
        return ALLOCATION_ERROR;
    return SUCCESS;
}
StatusType PlayersManager::GetPercentOfPlayersWithScoreInBounds(int GroupID, int score, int lowerLevel, int higherLevel, double *players)
{
    if (GroupID > numOfGroups)
        return INVALID_INPUT;
    shared_ptr<Group> group = (GroupID == 0) ? this->groups.GetMainGroup() : this->groups.Find(GroupID);
    return group.get()->GetPercentOfPlayersWithScoreInBounds(score, lowerLevel, higherLevel, players);
}
StatusType PlayersManager::AverageHighestPlayerLevelByGroup(int GroupID, int m, double *avgLevel)
{
    if (GroupID > numOfGroups)
        return INVALID_INPUT;
    shared_ptr<Group> group = (GroupID == 0) ? this->groups.GetMainGroup() : this->groups.Find(GroupID);
}
void Quit()
{
}