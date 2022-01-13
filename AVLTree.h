#ifndef AVL_TREE_H
#define AVL_TREE_H
#include "AVLExceptions.h"
#include "library2.h"
#include "Group.h"
#include <memory>
#include <functional>
using std::cout;
using std::endl;

class Group;

template <typename T>
class AVLNode;
template <typename T>
class AVLTree;

template <typename type>
AVLTree<type> *MergeTrees(AVLTree<type> &tr1, AVLTree<type> &tr2);
template <typename type>
void DeletePlayersByIdTree(AVLNode<type> *node);
template <typename type>
void DeletePlayersByLevelTree(AVLNode<type> *node);
template <typename type>
void DeleteGroupsTree(AVLNode<type> *node);
template <typename type>
void LTRInOrderForGroups(AVLNode<type> *node, int **array, int *index, int size);
template <typename type>
void LTRInOrderForPlayers(AVLNode<type> *node, int **array, int *index);
template <typename type>
void RTLInOrderForPlayers(AVLNode<type> *node, int **array, int *index);
//template <typename type>
//double GetNumOfPlayersInBound(AVLTree<type> tree, int lowerLevel, int higherLevel);
template <typename type>
StatusType AverageHighest(AVLTree<type> tree, int m, double *avgLevel);

template <typename T>
class AVLNode
{
    int key;
    T data;
    AVLNode *right;
    AVLNode *left;
    AVLNode *parent;
    int height;
    int players;
    int counter;
    int sum;

    AVLNode();
    AVLNode(int new_key, T new_data) : key(new_key), data(new_data),
                                       right(nullptr), left(nullptr), parent(nullptr),
                                       height(0), players(0), counter(0), sum(0) {}
    AVLNode(const AVLNode<T> &) = default;
    AVLNode &operator=(const AVLNode &) = default;
    ~AVLNode() = default;

    int GetMax(int a, int b) { return a > b ? a : b; }
    int GetKey() const { return (this != 0) ? key : -1; }
    T GetData() { return this->data; }
    T &GetDataRef() { return this->data; }
    void SetData(T new_data) { data = new_data; }
    void SetLeft(AVLNode *new_left) { left = new_left; }
    AVLNode *GetLeft() const { return (this != 0) ? left : nullptr; }
    void SetRight(AVLNode *new_right) { right = new_right; }
    AVLNode *GetRight() const { return (this != 0) ? right : nullptr; }
    void SetParent(AVLNode *new_parent) { parent = new_parent; }
    AVLNode *GetParent() const { return (this != 0) ? parent : nullptr; }
    int GetPlayers() { return (this != 0) ? players : 0; }
    void IncreasePlayers(int extra)
    {
        players += extra;
        this->updateNode();
    }
    int GetCounter() { return (this != 0) ? counter : 0; }
    int GetSum() { return (this != 0) ? sum : 0; }
    int GetHeight() const { return (this != 0) ? height : -1; }
    int BalanceFactor() const { return this->GetLeft()->GetHeight() - this->GetRight()->GetHeight(); }
    void updateNode()
    {
        this->height = 1 + GetMax(this->GetLeft()->GetHeight(), this->GetRight()->GetHeight());
        this->counter = players + this->GetLeft()->GetCounter() + this->GetRight()->GetCounter();
        this->sum = this->GetPlayers() * this->GetKey() + this->GetLeft()->GetSum() + this->GetRight()->GetSum();
    }
    friend std::ostream &operator<<(std::ostream &os, const AVLNode &nd)
    {
        os << "{" << nd.data << "}(" << nd.key << ")";
        return os;
    }
    //void ClearNode() { right = left = parent = nullptr; }

    friend class AVLTree<T>;
    friend class Group;

    template <typename type>
    friend void DeletePlayersByIdTree(AVLNode<type> *node);
    template <typename type>
    friend void DeletePlayersByLevelTree(AVLNode<type> *node);
    template <typename type>
    friend void DeleteGroupsTree(AVLNode<type> *node);
    template <typename type>
    friend void LTRInOrderForGroups(AVLNode<type> *node, int **array, int *index, int size);
    template <typename type>
    friend void LTRInOrderForPlayers(AVLNode<type> *node, int **array, int *index);
    template <typename type>
    friend void RTLInOrderForPlayers(AVLNode<type> *node, int **array, int *index);
    //template <typename type>
    //friend double GetNumOfPlayersInBound(AVLTree<type> tree, int lowerLevel, int higherLevel);
    template <typename type>
    friend StatusType AverageHighest(AVLTree<type> tree, int m, double *avgLevel);
};

template <typename T>
class AVLTree
{
private:
    AVLNode<T> *root;
    AVLNode<T> *highest;
    AVLNode<T> *lowest;
    int size;

    AVLNode<T> *GetLowestNode(AVLNode<T> *current)
    {
        while (current->GetLeft())
            current = current->GetLeft();
        return current;
    }
    AVLNode<T> *GetGreatestNode(AVLNode<T> *current)
    {
        while (current->GetRight())
            current = current->GetRight();
        return current;
    }
    AVLNode<T> *RotateLeft(AVLNode<T> *A)
    {
        AVLNode<T> *B = A->GetRight();
        AVLNode<T> *Bl = B->GetLeft();
        A->SetRight(Bl);
        if (Bl)
            Bl->SetParent(A);
        B->SetLeft(A);
        if (!A->GetParent()) //A is the root if the tree
        {
            this->root = B; //B is the new root
            B->SetParent(nullptr);
        }
        else
        {
            if (A->GetParent()->GetLeft() == A) //A is the left child of his parent
            {
                A->GetParent()->SetLeft(B);
            }
            else //A is the right child of his parent
            {
                A->GetParent()->SetRight(B);
            }
            B->SetParent(A->GetParent());
        }
        A->SetParent(B);
        A->updateNode();
        B->updateNode();
        return B;
    }
    AVLNode<T> *RotateRight(AVLNode<T> *B)
    {
        AVLNode<T> *A = B->GetLeft();
        AVLNode<T> *Ar = A->GetRight();
        B->SetLeft(Ar);
        if (Ar)
            Ar->SetParent(B);
        A->SetRight(B);

        if (!B->GetParent()) //B is the root of the tree
        {
            this->root = A; //A is the new root
            A->SetParent(nullptr);
        }
        else //we are in a sub-tree
        {
            if (B->GetParent()->GetLeft() == B) //B is the left child of his parent
                B->GetParent()->SetLeft(A);
            else //root is right child of his parent
                B->GetParent()->SetRight(A);
            A->SetParent(B->GetParent());
        }
        B->SetParent(A);
        B->updateNode();
        A->updateNode();
        return A;
    }
    AVLNode<T> *Find_aux(AVLNode<T> *current, int key)
    {
        if (current != nullptr)
        {
            const int k = current->GetKey();
            if (k == key)
                return current; // Found the node :)
            else if (key < k)
                return Find_aux(current->GetLeft(), key);
            else
                return Find_aux(current->GetRight(), key);
        }
        return nullptr; //didnt found the node :(
    }
    AVLNode<T> *Balance(AVLNode<T> *current)
    {
        int BF = current->BalanceFactor();
        if (BF > 1)
        {
            if (current->GetLeft()->BalanceFactor() < 0)
            {
                current->SetLeft(RotateLeft(current->GetLeft())); //do LR rotation
            }
            return RotateRight(current);
        }
        else if (BF < -1)
        {
            if (current->GetRight()->BalanceFactor() > 0)
            {
                current->SetRight(RotateRight(current->GetRight())); // do RL rotation
            }
            return RotateLeft(current);
        }
        return current;
    }
    AVLNode<T> *InsertNode(AVLNode<T> *current, AVLNode<T> *to_insert)
    {
        if (current == nullptr)
            return to_insert;
        AVLNode<T> *sub_tree;
        if (to_insert->GetKey() < current->GetKey()) // go left
        {
            sub_tree = InsertNode(current->GetLeft(), to_insert);
            current->SetLeft(sub_tree);
            if (sub_tree)
                sub_tree->SetParent(current);
        }
        else if (to_insert->GetKey() > current->GetKey()) // go right
        {
            sub_tree = InsertNode(current->GetRight(), to_insert);
            current->SetRight(sub_tree);
            if (sub_tree)
                sub_tree->SetParent(current);
        }
        else //equal keys not allowed
            return current;
        current->updateNode();
        return Balance(current);
    }
    AVLNode<T> *RemoveNode(AVLNode<T> *current, int key_to_remove)
    {
        //Regular remove from BST tree:
        if (current == nullptr)
            return current;
        if (current->GetKey() > key_to_remove) //remove from left sub-tree
        {
            current->SetLeft(RemoveNode(current->GetLeft(), key_to_remove));
        }
        else if (current->GetKey() < key_to_remove) //remove from right sub-tree
        {
            current->SetRight(RemoveNode(current->GetRight(), key_to_remove));
        }
        else //found node to delete
        {
            if (current->GetLeft() == nullptr || current->GetRight() == nullptr) // node with one child or leaf
            {
                AVLNode<T> *child = current->GetLeft() ? current->GetLeft() : current->GetRight();
                if (child == nullptr) //node is leaf
                {

                    //disconnect current from his parent
                    AVLNode<T> *parent = current->GetParent();
                    if (parent) //current is not the root of the tree
                    {
                        parent->GetLeft() == current ? parent->SetLeft(nullptr) : parent->SetRight(nullptr);
                    }
                    current->SetParent(nullptr);
                }
                else //node has one child
                {
                    //copy content of child to current node
                    AVLNode<T> *parent = current->GetParent();
                    if (parent)
                    {
                        parent->GetLeft() == current ? parent->SetLeft(child) : parent->SetRight(child);
                    }
                    child->SetParent(parent);
                }
                delete current;
                current = child;
            }
            else //node has two children
            {
                AVLNode<T> *replacement = GetGreatestNode(current->left);
                AVLNode<T> *rep_parent = replacement->GetParent();
                AVLNode<T> *rep_son = replacement->GetLeft();
                AVLNode<T> *parent = current->GetParent();
                AVLNode<T> *current_right = current->GetRight();
                AVLNode<T> *current_left = current->GetLeft();
                if (current_left == replacement)
                {
                    if(replacement)
                        replacement->SetParent(parent);
                    if(current)
                    {
                        current->SetParent(replacement);
                        current->SetLeft(rep_son);
                        current->SetRight(nullptr);
                    }
                    if(rep_son)
                        rep_son->SetParent(current);
                    if(replacement)
                    {
                        replacement->SetLeft(current);
                        replacement->SetRight(current_right);
                    }
                    if(current_right)
                        current_right->SetParent(replacement);
                    if (parent)
                        parent->GetLeft() == current ? parent->SetLeft(replacement) : parent->SetRight(replacement);
                }
                else
                {
                    replacement->SetParent(parent);
                    if (parent)
                        parent->GetLeft() == current ? parent->SetLeft(replacement) : parent->SetRight(replacement);
                    current->SetParent(rep_parent);
                    current->SetLeft(rep_son);
                    current->SetRight(nullptr);
                    rep_parent->SetRight(current);
                    if (rep_son)
                        rep_son->SetParent(current);
                    replacement->SetRight(current_right);
                    replacement->SetLeft(current_left);
                    if (current_right)
                        current_right->SetParent(replacement);
                    current_left->SetParent(replacement);
                }
                replacement->left = RemoveNode(replacement->left, key_to_remove);
                current = replacement;
            }
        }
        //tree had one node
        if (current == nullptr)
            return current;

        current->updateNode();
        return Balance(current);
    }
    void GetDataArray_AUX(AVLNode<T> *node, T *array, int *index)
    {
        if (!node)
            return;
        GetDataArray_AUX(node->GetLeft(), array, index);
        array[(*index)++] = node->GetData();
        //array.get()[(*index)++].reset(new T(*(node->GetData().get())));
        GetDataArray_AUX(node->GetRight(), array, index);
    }
    void GetKeysArray_AUX(AVLNode<T> *node, int *array, int *index)
    {
        if (!node)
            return;
        GetKeysArray_AUX(node->GetLeft(), array, index);
        array[(*index)++] = node->GetKey();
        GetKeysArray_AUX(node->GetRight(), array, index);
    }
    void GetPlayersArray_AUX(AVLNode<T> *node, int *array, int *index)
    {
        if(!node)
            return;
        GetPlayersArray_AUX(node->GetLeft(), array, index);
        array[(*index)++] = node->GetPlayers();
        GetPlayersArray_AUX(node->GetRight(), array, index);
    }
    AVLNode<T> *SortedArrayToAVLTree(int *keys, T *data, int start, int end)
    {
        if (start > end)
            return nullptr;
        int mid = (start + end) / 2;
        AVLNode<T> *current = new AVLNode<T>(keys[mid], data[mid]);
        AVLNode<T> *left_child = SortedArrayToAVLTree(keys, data, start, mid - 1);
        current->SetLeft(left_child);
        if (left_child)
            left_child->SetParent(current);
        AVLNode<T> *right_child = SortedArrayToAVLTree(keys, data, mid + 1, end);
        current->SetRight(right_child);
        if (right_child)
            right_child->SetParent(current);
        current->updateNode();
        return current;
    }
    AVLNode<T> *SortedPlayersArrayToAVLTree(int *keys, int *players, int start, int end, int fixed_data) //for AVLTree<int> with node counter
    {
        if (start > end)
            return nullptr;
        int mid = (start + end) / 2;
        AVLNode<T> *current = new AVLNode<T>(keys[mid], fixed_data);
        AVLNode<T> *left_child = SortedPlayersArrayToAVLTree(keys, players, start, mid - 1, fixed_data);
        current->SetLeft(left_child);
        if(left_child)
            left_child->SetParent(current);
        AVLNode<T> *right_child = SortedPlayersArrayToAVLTree(keys, players, mid + 1, end, fixed_data);
        current->SetRight(right_child);
        if(right_child)
            right_child->SetParent(current);
        current->IncreasePlayers(players[mid]);
        return current;
    }

    void SetHighest(AVLNode<T> *new_highest)
    {
        highest = new_highest;
    }
    void SetLowest(AVLNode<T> *new_lowest)
    {
        lowest = new_lowest;
    }
    void PostOrderDelete(AVLNode<T> *node)
    {
        if (node != nullptr)
        {
            PostOrderDelete(node->GetLeft());
            PostOrderDelete(node->GetRight());
            delete node;
        }
    }
    void UpdateAllRankes(AVLNode<T> *current)
    {
        if (current == nullptr)
            return;
        UpdateAllRankes(current->left);
        UpdateAllRankes(current->right);
        current->updateNode();
    }
    void PostOrderApply_aux(AVLNode<T> *current, std::function<void(T)> func)
    {
        if (current == nullptr)
            return;
        PostOrderApply_aux(current->left, func);
        PostOrderApply_aux(current->right, func);
        func(current->data);
    }
    void InOrderApply_aux(AVLNode<T> *current, std::function<void(T)> func)
    {
        if (current == nullptr)
            return;
        InOrderApply_aux(current->left, func);
        func(current->data);
        InOrderApply_aux(current->right, func);
    }
    void PreOrderApply_aux(AVLNode<T> *current, std::function<void(T)> func)
    {
        if (current == nullptr)
            return;
        func(current->data);
        PreOrderApply_aux(current->left, func);
        PreOrderApply_aux(current->right, func);
    }
    void Print_aux(AVLNode<T> *current)
    {
        if (current == nullptr)
            return;
        Print_aux(current->left);
        cout << *current << "  ";
        Print_aux(current->right);
    }

public:
    AVLTree() : root(nullptr), highest(nullptr), lowest(nullptr), size(0) {}
    AVLTree(int *keys, T *data, int size_of_array) // Sorted Array to AVL Tree Constructor
    {
        if (size_of_array == 0)
            throw FAILURE_exception();
        //make sure the array is sorted
        for (int i = 1; i < size_of_array; i++)
        {
            if (keys[i - 1] >= keys[i])
                throw FAILURE_exception();
        }
        this->root = SortedArrayToAVLTree(keys, data, 0, size_of_array - 1);
        this->highest = GetGreatestNode(root);
        this->lowest = GetLowestNode(root);
        this->size = size_of_array;
    }
    AVLTree(int *keys, int *players, int size_of_array, int fixed_data)
    {
        if(size_of_array == 0)
            throw FAILURE_exception();
        for (int i = 1; i < size_of_array;i++)
            if(keys[i-1] >= keys[i])
                throw FAILURE_exception();
        this->root = SortedPlayersArrayToAVLTree(keys, players, 0, size_of_array - 1, fixed_data);
        this->highest = GetGreatestNode(root);
        this->lowest = GetLowestNode(root);
        this->size = size_of_array;
    }
    AVLNode<T> *CopyTree(AVLNode<T> *copy, AVLNode<T> *node_parent)
    {
        if (!copy)
            return nullptr;
        AVLNode<T> *copied_node = new AVLNode<T>(copy->GetKey(), copy->GetData());
        copied_node->SetParent(node_parent);
        copied_node->height = copy->height;
        copied_node->players = copy->players;
        copied_node->sum = copy->sum;
        copied_node->counter = copy->counter;
        copied_node->SetLeft(CopyTree(copy->GetLeft(), copied_node));
        copied_node->SetRight(CopyTree(copy->GetRight(), copied_node));
        return copied_node;
    }
    AVLTree &operator=(const AVLTree &copy)
    {
        if (this == &copy)
            return *this;
        this->PostOrderDelete(this->root);
        this->root = this->CopyTree(copy.root, nullptr);
        this->highest = GetGreatestNode(this->root);
        this->lowest = GetLowestNode(this->root);
        this->size = copy.size;
        return *this;
    }
    ~AVLTree()
    {
        try
        {
            PostOrderDelete(root);
            size = -1;
        }
        catch (const std::exception &e)
        {
        }
    }
    void addPlayerTo(int key, int extra)
    {
        AVLNode<T> *node = Find_aux(this->root, key);
        if (node)
            node->IncreasePlayers(extra);
    }

    AVLNode<T> *GetRoot() const
    {
        return (this != 0) ? root : nullptr;
    }
    int GetTreeSize() const
    {
        return size;
    }
    T GetRootData() const
    {
        return root->GetData();
    }
    T &GetRootDataRef() const
    {
        return root->GetDataRef();
    }
    T GetHighest() const
    {
        return highest->GetData();
    }
    T GetLowest() const
    {
        return lowest->GetData();
    }
    AVLNode<T> *GetHighestNodePointer()
    {
        return highest;
    }
    AVLNode<T> *GetLowestNodePointer()
    {
        return lowest;
    }
    bool IsEmpty()
    {
        return root != nullptr;
    }
    T Find(int key)
    {
        AVLNode<T> *node = Find_aux(this->root, key);
        if (node)
            return node->GetData();
        return nullptr;
    }
    bool Exists(int key)
    {
        if (Find(key) == nullptr)
            return false;
        return true;
    }
    bool Insert(int new_key, T new_data)
    {
        AVLNode<T> *new_node = new AVLNode<T>(new_key, new_data);
        if (!root) //empty tree, special case
        {
            root = new_node;
            highest = new_node;
            lowest = new_node;
            size++;
            return true;
        }
        else
        {
            root = InsertNode(root, new_node);
            // if we insert object that his key is bigger then the highest
            if (new_node->GetKey() > highest->GetKey())
                highest = new_node;
            // if we insert object that his key is smaller then the lowest
            else if (new_node->GetKey() < lowest->GetKey())
                lowest = new_node;
        }
        size++;
        return true; // was return false, but it is success , no?
        //return false; // previous code
    }
    bool Remove(int key)
    {
        // if we remove the highest :
        if (this->highest->GetKey() == key) // change the highest if he will removed
        {
            if (this->highest->GetParent() == nullptr)
            {
                AVLNode<T> *new_highest = highest->GetLeft();
                if (new_highest)
                    while (new_highest->GetRight() != nullptr)
                        new_highest = new_highest->GetRight();
                this->highest = new_highest;
            }
            else
                this->highest = highest->GetParent();
        }
        // if we remove the lowest :
        if (this->lowest->GetKey() == key) // change the lowest if he will removed
        {
            if (this->lowest->GetParent() == nullptr)
            {
                AVLNode<T> *new_lowest = lowest->GetRight();
                while (new_lowest->GetLeft() != nullptr)
                    new_lowest = new_lowest->GetLeft();
                this->lowest = new_lowest;
            }
            else
                this->lowest = lowest->GetParent();
        }
        root = RemoveNode(root, key); // it will return nullptr only if root == nullptr
        size--;
        if (size == 0)
            root = nullptr;
        else if (!root) // RemoveNode failure, root was nullptr, tree is empty
            return false;
        return true; // RemoveNode succeed
    }
    void Print()
    {
        Print_aux(root);
        std::cout << std::endl;
    }
    T *GetDataArray()
    {
        int index = 0;
        T *array = new T[size];
        GetDataArray_AUX(root, array, &index);
        return array;
    }
    int *GetKeysArray()
    {
        int index = 0;
        int *array = new int[size];
        GetKeysArray_AUX(root, array, &index);
        return array;
    }
    int *GetPlayersArray()
    {
        int index = 0;
        int *array = new int[size];
        GetPlayersArray_AUX(root, array, &index);
        return array;
    }
    void PostOrderApply(std::function<void(T)> func)
    {
        PostOrderApply_aux(root, func);
    }
    void InOrderApply(std::function<void(T)> func)
    {
        InOrderApply_aux(root, func);
    }
    void PreOrderApply(std::function<void(T)> func)
    {
        PreOrderApply_aux(root, func);
    }

    int higherBound_aux(AVLNode<T> *current, int higherLevel)
    {
        if (current != nullptr)
        {
            const int k = current->GetKey();
            if (k == higherLevel)
            {
                return current->GetRight()->GetPlayers(); // Found the node :)
            }
            else if (higherLevel < k)
            {
                return current->players + current->GetRight()->GetCounter() + higherBound_aux(current->GetLeft(), higherLevel);
            }
            else
                return higherBound_aux(current->GetRight(), higherLevel);
        }
        return 0; //didnt found the node :(
    }
    int lowerBound_aux(AVLNode<T> *current, int lowerLevel)
    {
        if (current != nullptr)
        {
            const int k = current->GetKey();
            if (k == lowerLevel)
            {
                return current->GetLeft()->GetPlayers(); // Found the node :)
            }
            else if (lowerLevel < k)
            {
                return lowerBound_aux(current->GetLeft(), lowerLevel);
            }
            else
                return current->players + current->GetLeft()->GetCounter() + lowerBound_aux(current->GetRight(), lowerLevel);
        }
        return 0; //didnt found the node :(
    }

    int GetNumOfPlayersInBound(int lowerLevel, int higherLevel)
    {
        AVLNode<T> *root = this->root;
        int higher_than = higherBound_aux(root, higherLevel);
        int lower_than = lowerBound_aux(root, lowerLevel);

        //cout << "root is " << root->key << " with counter " << root->GetCounter() << endl;
        //cout << root->GetCounter() << " - " << lower_than << " - " << higher_than << endl;
        return root->GetCounter() - lower_than - higher_than;
    }

    void printTree_AUX(std::ostream &os, AVLNode<T> *node)
    {
        if(!node)
            return;
        printTree_AUX(os, node->GetLeft());
        os << "Level = " << node->GetKey() << " | Players = " << node->GetPlayers();
        os << " | Counter = " << node->GetCounter() << " | Sum = " << node->GetSum() << std::endl;
        printTree_AUX(os, node->GetRight());
    }
    //template <typename T>
    void printTree(std::ostream &os)
    {
      printTree_AUX(os, this->GetRoot());
    }

    friend class Group;
    friend class Player;

    template <typename type>
    friend AVLTree<type> *MergeTrees(AVLTree<type> &tr1, AVLTree<type> &tr2);
    template <typename type>
    friend void DeletePlayersByIdTree(AVLNode<type> *node);
    template <typename type>
    friend void DeletePlayersByLevelTree(AVLNode<type> *node);
    template <typename type>
    friend void DeleteGroupsTree(AVLNode<type> *node);
    template <typename type>
    friend void LTRInOrderForGroups(AVLNode<type> *node, int **array, int *index, int size);
    template <typename type>
    friend void LTRInOrderForPlayers(AVLNode<type> *node, int **array, int *index);
    template <typename type>
    friend void RTLInOrderForPlayers(AVLNode<type> *node, int **array, int *index);
    //template <typename type>
    //friend double GetNumOfPlayersInBound(AVLTree<type> tree, int lowerLevel, int higherLevel);
    template <typename type>
    friend StatusType AverageHighest(AVLTree<type> tree, int m, double *avgLevel);
};

template <typename type>
void DeletePlayersByIdTree(AVLNode<type> *node)
{
    if (!node)
        return;
    DeletePlayersByIdTree(node->GetLeft());
    node->GetData().get()->GetGroup().reset();
    node->GetData().get()->SetGroup(nullptr);
    DeletePlayersByIdTree(node->GetRight());
    node->GetData().reset();
}
template <typename type>
void DeletePlayersByLevelTree(AVLNode<type> *node)
{
    if (!node)
        return;
    DeletePlayersByLevelTree(node->GetLeft());
    DeletePlayersByIdTree(node->GetData().get()->GetRoot());
    DeletePlayersByLevelTree(node->GetRight());
    node->GetData().reset();
}
template <typename type>
void DeleteGroupsTree(AVLNode<type> *node)
{
    if (!node)
        return;
    DeleteGroupsTree(node->GetLeft());
    DeletePlayersByLevelTree(node->GetData().get()->GetPlayerByLevel()->GetRoot());
    DeleteGroupsTree(node->GetRight());
    node->GetData().reset();
}

template <typename type>
void LTRInOrderForGroups(AVLNode<type> *node, int **array, int *index, int size)
{
    if (!node || *index >= size)
        return;
    LTRInOrderForGroups(node->GetLeft(), array, index, size);
    int id = node->GetData().get()->GetPlayerByLevel()->GetHighest().get()->GetLowest().get()->GetId();
    (*array)[*index] = id;
    ++(*index);
    // not gonna get nullptr in GetHighest() and GetLowest() because there are players in this group
    LTRInOrderForGroups(node->GetRight(), array, index, size);
}

template <typename type>
void LTRInOrderForPlayers(AVLNode<type> *node, int **array, int *index) // left to right
{
    if (!node)
        return;
    LTRInOrderForPlayers(node->GetLeft(), array, index);
    (*array)[(*index)++] = node->GetData().get()->GetId();
    LTRInOrderForPlayers(node->GetRight(), array, index);
}

template <typename type>
void RTLInOrderForPlayers(AVLNode<type> *node, int **array, int *index) // right to left
{
    if (!node)
        return;
    RTLInOrderForPlayers(node->GetRight(), array, index);
    LTRInOrderForPlayers(node->GetData().get()->GetRoot(), array, index);
    RTLInOrderForPlayers(node->GetLeft(), array, index);
}

template <typename type>
StatusType AverageHighest(AVLTree<type> tree, int m, double *avgLevel)
{
    AVLNode<type> *node = tree.GetRoot();
    double sum = 0;
    int num = 0;
    while (node != nullptr)
    {
        if ((num + node->GetCounter()) < m) // failure
            return FAILURE;
        else if ((num + node->GetCounter()) == m) // found
        {
            *avgLevel = (double)((sum + node->GetSum())) / (double)(m);
            return SUCCESS;
        }
        else if (node->GetRight() != nullptr) // num + node->GetCounter() > m
        {
            if (num + node->GetRight()->GetCounter() + node->GetPlayers() == m) // found
            {
                *avgLevel = (double)(sum + node->GetRight()->GetSum() + (node->GetPlayers() * node->GetKey())) / (double)(m);
                return SUCCESS;
            }
            else if (num + node->GetRight()->GetCounter() + node->GetPlayers() < m) // go left
            {
                sum += (double)(node->GetRight()->GetSum() + (node->GetPlayers() * node->GetKey()));
                num += node->GetPlayers() + node->GetRight()->GetCounter();
                node = node->GetLeft();
            }
            else if (num + node->GetRight()->GetCounter() + node->GetPlayers() > m)
            {
                if (num + node->GetRight()->GetCounter() >= m) // go right
                {
                    node = node->GetRight();
                }
                else // ( num + node->GetRight()->GetCounter() + node->GetPlayers() ) > m > ( num + node->GetRight()->GetCounter() )
                {
                    int diff = m - (num + node->GetRight()->GetCounter());
                    sum += (double)(node->GetRight()->GetSum() + (diff * node->GetKey()));
                    *avgLevel = sum / (double)(m);
                    return SUCCESS;
                }
            }
        }
        else // no right
        {
            if (num + node->GetPlayers() == m) // found
            {
                sum += (double)(node->GetPlayers() * node->GetKey());
                *avgLevel = sum / (double)(m);
                return SUCCESS;
            }
            else if (num + node->GetPlayers() < m) // go left
            {
                sum += (double)(node->GetPlayers() * node->GetKey());
                num += node->GetPlayers();
                node = node->GetLeft(); // maybe there is no left, will break the while loop and failed, not supposed to happend
            }
            else // num + node->GetPlayers() > m > num
            {
                int diff = m - num;
                sum += (double)(diff * node->GetKey());
                *avgLevel = sum / (double)(m);
                return SUCCESS;
            }
        }
    }
    // not supposed to get here :
    if (num != m)
        return FAILURE;
    *avgLevel = sum / (double)(m); // if accedently got here and num == n
    return SUCCESS;
}

#endif