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

    int GetId() const;
    int GetLevel() const;
    int GetScore() const;
    int GetGroup() const;
    void SetGroup(int new_group);
    void IncrementLevel(int increment);
    void SetScore(int new_score);
    friend std::ostream &operator<<(std::ostream &os, const Player &p);
    //friend void LTRInOrderForPlayers(AVLNode<Player> *node, int **array, int *index);
    //friend void RTLInOrderForPlayers(AVLNode<AVLTree<Player>> *node, int **array, int *index);
};

#endif