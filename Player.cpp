#include "Player.h"

// Player::Player() : player_id(-1), player_level(-1), player_group(-1) {}
Player::Player(int p_id, int p_score, int p_group)
    : player_id(p_id), player_level(0), player_score(p_score), player_group(p_group) {}
int Player::GetId() const
{
    return (this != 0) ? this->player_id : -1;
}
int Player::GetLevel() const
{
    return (this != 0) ? this->player_level : -1;
}
int Player::GetGroup() const
{
    return (this != 0) ? this->player_group : -1;
}
int Player::GetScore() const
{
    return (this != 0) ? this->player_score : -1;
}
void Player::SetGroup(int new_group)
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
std::ostream &operator<<(std::ostream &os, const Player &p)
{

    os << "(I=" << p.GetId() << ",L=" << p.GetLevel() << ",S=" << p.GetScore() << ",G=" << p.GetGroup() << ")";
    return os;
}