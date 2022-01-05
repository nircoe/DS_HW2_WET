#ifndef PLAYER_H
#define PLAYER_H
#include "Group.h"

class Group;

class Player
{
    int player_id;
    int player_level;
    int player_score;
    int player_group;

public:
    Player() = delete;
    Player(int id, int score, int group);
    Player(const Player &) = default;
    ~Player() = default;
    Player &operator=(const Player &) = default;

    int GetId();
    int GetLevel();
    int GetScore();
    int GetGroup();
    void SetGroup(int new_group);
    void IncrementLevel(int increment);
    void SetScore(int new_score);

    //friend void LTRInOrderForPlayers(AVLNode<Player> *node, int **array, int *index);
    //friend void RTLInOrderForPlayers(AVLNode<AVLTree<Player>> *node, int **array, int *index);
};

#endif