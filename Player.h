#ifndef PLAYER_H
#define PLAYER_H
#include "Group.h"

class Group;

class Player
{
    int player_id;
    int player_level;
    int player_score;
    shared_ptr<Group> player_group;

public:
    Player();
    Player(int id, int score, shared_ptr<Group> group);
    Player(const Player &) = default;
    ~Player() = default;
    Player &operator=(const Player &) = default;

    int GetId();
    int GetLevel();
    int GetScore();
    shared_ptr<Group> GetGroup();
    void SetGroup(shared_ptr<Group> new_group);
    void IncrementLevel(int increment);
    void SetScore(int new_score);

    //friend void LTRInOrderForPlayers(AVLNode<Player> *node, int **array, int *index);
    //friend void RTLInOrderForPlayers(AVLNode<AVLTree<Player>> *node, int **array, int *index);
};

#endif