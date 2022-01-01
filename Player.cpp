#include "Player.h"

Player::Player() : player_id(-1), player_level(-1), player_group(nullptr) {}
Player::Player(int p_id, int p_score, shared_ptr<Group> p_group)
    : player_id(p_id), player_level(0), player_score(p_score), player_group(p_group) {}
int Player::GetId()
{
    return (this != 0) ? this->player_id : -1;
}
int Player::GetLevel()
{
    return (this != 0) ? this->player_level : -1;
}
shared_ptr<Group> Player::GetGroup()
{
    return (this != 0) ? this->player_group : nullptr;
}
int Player::GetScore()
{
    return (this != 0) ? this->player_score : -1;
}
void Player::SetGroup(shared_ptr<Group> new_group)
{
    this->player_group = new_group;
}
void Player::IncrementLevel(int increment)
{
    this->player_level += increment;
}
void Player::SetScore(int new_score)
{
    this->player_score = new_score;
}