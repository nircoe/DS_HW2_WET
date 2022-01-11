#include "PlayersManager.h"

PlayersManager::PlayersManager(int k, int scale)
{
    numOfGroups = k;
    maxScore = scale;
    groups = new UnionFind(k, scale);
    playersbyid = new HashTable<shared_ptr<Player>>();
}

PlayersManager::~PlayersManager()
{
    delete groups;
    delete playersbyid;
}

StatusType PlayersManager::MergeGroups(int GroupID1, int GroupID2)
{
    if(GroupID1 <= 0 || GroupID2 <= 0 || GroupID1 > numOfGroups || GroupID2 > numOfGroups)
        return INVALID_INPUT;
    if(groups->Union(GroupID1, GroupID2) == nullptr)
        return FAILURE;
    return SUCCESS;
}
StatusType PlayersManager::AddPlayer(int PlayerID, int GroupID, int score)
{
    if (GroupID <= 0 || score <= 0 || GroupID > numOfGroups || score > maxScore)
        return INVALID_INPUT;
    shared_ptr<Player> player = this->playersbyid->Search(PlayerID);
    if (player != nullptr)
        return FAILURE;
    player = make_shared<Player>(PlayerID, score, GroupID);
    this->playersbyid->Insert(PlayerID, player);
    shared_ptr<Group> group = this->groups->Find(GroupID), mainGroup = this->groups->GetMainGroup();
    //shared_ptr<Group> g1 = this->groups.Find(1);
    //cout << *(g1.get()) << std::endl;
    if (group.get()->AddPlayerToGroup(player) != SUCCESS ||
        mainGroup.get()->AddPlayerToGroup(player) != SUCCESS)
        return ALLOCATION_ERROR;
    return SUCCESS;
} 
StatusType PlayersManager::RemovePlayer(int PlayerID)
{
    shared_ptr<Player> player = this->playersbyid->Search(PlayerID);
    if (player == nullptr)
        return FAILURE;
    shared_ptr<Group> group = this->groups->Find(player.get()->GetGroup()),
                      mainGroup = this->groups->GetMainGroup();
    int p_level = player.get()->GetLevel();
    
    if (playersbyid->Delete(PlayerID) != true ||
        group.get()->RemovePlayerFromGroup(PlayerID, p_level) != SUCCESS ||
        mainGroup.get()->RemovePlayerFromGroup(PlayerID, p_level) != SUCCESS)
        return FAILURE;
    return SUCCESS;
}
StatusType PlayersManager::IncreasePlayerIDLevel(int PlayerID, int LevelIncrease)
{
    shared_ptr<Player> player = this->playersbyid->Search(PlayerID);
    if (player == nullptr)
        return FAILURE;
    int p_level = player.get()->GetLevel();
    shared_ptr<Group> group = this->groups->Find(player.get()->GetGroup()),
                      mainGroup = this->groups->GetMainGroup();
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
    if (NewScore <= 0 || NewScore > maxScore)
        return INVALID_INPUT;
    shared_ptr<Player> player = this->playersbyid->Search(PlayerID);
    if (player == 0)
        return FAILURE;
    int p_level = player.get()->GetLevel();
    shared_ptr<Group> group = this->groups->Find(player.get()->GetGroup()),
                      mainGroup = this->groups->GetMainGroup();
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
    if (GroupID < 0 || GroupID > numOfGroups)
        return INVALID_INPUT;
    shared_ptr<Group> group = (GroupID == 0) ? this->groups->GetMainGroup() : this->groups->Find(GroupID);
    return group.get()->GetPercentOfPlayersWithScoreInBounds(score, lowerLevel, higherLevel, players);
}
StatusType PlayersManager::AverageHighestPlayerLevelByGroup(int GroupID, int m, double *avgLevel)
{
    if (GroupID < 0 || GroupID > numOfGroups)
        return INVALID_INPUT;
    shared_ptr<Group> group = (GroupID == 0) ? this->groups->GetMainGroup() : this->groups->Find(GroupID);
    return group.get()->AverageHighestPlayerLevel(m, avgLevel);
}
void PlayersManager::Quit(PlayersManager *pm)
{
    delete pm;
}

void PlayersManager::printgroup1()
{
    shared_ptr<Group> group = this->groups->Find(1);
    group.get()->printlevel0();
}