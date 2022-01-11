#ifndef UNION_FIND_H
#define UNION_FIND_H
#include <memory>
#include "Group.h"
using std::make_shared;
using std::shared_ptr;

class Group;

class UnionFind
{
    int *parents;
    shared_ptr<Group> *groups;
    int size;

public:
    UnionFind() : parents(nullptr), groups(nullptr), size(-1){};
    UnionFind(int k) : size(k)
    {
        parents = new int[k + 1];
        groups = new shared_ptr<Group>[k + 1];
        groups[0] = make_shared<Group>(0);
        parents[0] = 0;
        for (int i = 1; i <= k; i++)
        {
            parents[i] = i;
            groups[i] = make_shared<Group>(i);
        }
    }
    UnionFind(const UnionFind &) = default;
    UnionFind &operator=(const UnionFind &) = default;
    ~UnionFind() = default;
    int GetSize()
    {
        return (this != 0) ? this->size : -1;
    }
    shared_ptr<Group> GetMainGroup()
    {
        return this->groups[0];
    }
    shared_ptr<Group> Find(int i)
    {
        if (i < 1 || size < i)
            return nullptr;
        int parent = parents[i];
        while (parents[parent] != parent)
            parent = parents[parent];
        int former_parent = parents[i];
        while (parents[former_parent] != former_parent)
        {
            int temp = former_parent;
            former_parent = parents[former_parent];
            parents[temp] = parent;
        }
        return groups[parent];
    }

    shared_ptr<Group> Union(int i, int j)
    {
        if ((i < 1 || size < i) || (j < 1 || size < j))
            return nullptr;
        int parent_i = parents[i], parent_j = parents[j];
        while (parents[parent_i] != parent_i)
            parent_i = parents[parent_i];
        while (parents[parent_j] != parent_j)
            parent_j = parents[parent_j];
        if (parent_i == parent_j)
            return groups[parent_i];
        int parent_of_union = parent_i;
        if (groups[parent_i].get()->GetSize() >= groups[parent_j].get()->GetSize())
        {
            parents[parent_j] = parent_i;
            
        }
        else
        {
            parent_of_union = parent_j;
            parents[parent_i] = parent_j;
        }
        return groups[parent_of_union];
    }
};

#endif