#ifndef UNION_FIND_H
#define UNION_FIND_H
#include <memory>
using std::make_shared;
using std::shared_ptr;

template <typename T>
class Node; // Node for Inverted Tree
template <typename T>
class UnionFind;

template <typename T>
class Node // Node for Inverted Tree
{
    int key;
    int tree_size;
    T data;
    Node *parent;

    Node();
    Node(int new_key, T new_data) : key(new_key), tree_size(1), data(new_data), parent(nullptr) {}
    Node(const Node<T> &) = default;
    Node &operator=(const Node &) = default;
    ~Node() = default;

    int GetKey() const { return (this != 0) ? key : -1; }
    int GetTreeSize() const { return (this != 0) ? tree_size : 0; }
    T GetData() { return this->data; }
    void SetTreeSize(int new_size) { tree_size = new_size; }
    void SetData(T new_data) { data = new_data; }
    void SetParent(Node *new_parent) { parent = new_parent; }
    Node *GetParent() const { return (this != 0) ? parent : nullptr; }

    friend class UnionFind<T>;
};

template <typename T>
class UnionFind
{
    Node<T> ** groups;
    int size;

public:
    UnionFind() = delete;
    UnionFind(int k)
    {
        size = k;
        groups = new Node<T> *[k];
        for (int i = 0; i < k; i++)
        {
            shared_ptr<T> group = make_shared<T>(i + 1);
            groups[i] = new Node<T>(i + 1, group);
        }
    }
    UnionFind(const UnionFind<T> &) = default;
    UnionFind &operator=(const UnionFind<T> &) = default;
    ~UnionFind() = default;

    T Find(int i)
    {
        if(i < 1 || size < i) throw std::exception(); // maybe our own exception
        Node<T>* root = groups[i];
        while (root->GetParent() != nullptr)
            root = root->GetParent();
        Node<T> *temp = groups[i];
        while(temp->GetParent() != nullptr)
        {
            Node<T> *t = temp;
            temp = temp->GetParent();
            t->SetParent(root);
            t->SetTreeSize(root->GetTreeSize());
        }
        return root->GetData();
    }

    T Union(int i, int j)
    {
        if ((i < 1 || size < i) || (j < 1 || size < j)) throw std::exception(); // maybe our own exception
        Node<T> *root_i = groups[i], *root_j = groups[j];
        while (root_i->GetParent() != nullptr)
            root_i = root_i->GetParent();
        while (root_j->GetParent() != nullptr)
            root_j = root_j->GetParent();
        if(root_i == root_j) throw std::exception(); // maybe our own exception
        T t;
        int i_size = root_i->GetTreeSize(), j_size = root_j->GetTreeSize(), new_size = i_size + j_size;
        if (i_size >= J_size)
        {
            root_j->SetParent(root_i);
            t = root_i->GetData();
        }
        else
        {
            root_i->SetParent(root_j);
            t = root_j->GetData();
        }
        root_i->SetTreeSize(new_size);
        root_j->SetTreeSize(new_size);
        return t;
    }
};

#endif