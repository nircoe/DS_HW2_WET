#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <iostream>

template <class T>
class HashTable;

template <class T>
class Node
{
    int key;
    T data;
    Node<T> *next;

public:
    Node() = delete;
    Node(int key, const T data = 0, Node<T> *next = nullptr) : key(key), data(data), next(next) {}
    Node(const Node<T> &node) = default;
    ~Node() = default;
    Node<T> &operator=(const Node<T> &node) = default;
    friend class HashTable<T>;
    friend std::ostream &operator<<(std::ostream &os, const Node<T> &nd)
    {
        os << nd.key;
        return os;
    }
    int GetKey()
    {
        return (this != 0) ? this->key : -1;
    }
    T GetData()
    {
        return (this != 0) ? this->data : 0;
    }
    Node<T> *GetNext()
    {
        return (this != 0) ? this->next : nullptr;
    }
};

template <class T>
class HashTable
{
    int size;
    int K;
    Node<T> **arr;
    void InitArr(int k)
    {
        arr = new Node<T> *[k];
        for (int i = 0; i < k; i++)
            arr[i] = nullptr;
    }
    void deleteArray(int k)
    {
        for (int i = 0; i < k; i++)
        {
            Node<T> *current = this->arr[i];
            Node<T> *temp;
            while (current != nullptr)
            {
                temp = current->next;
                delete current;
                current = temp;
            }
        }
        delete arr;
    }
    void resize()
    {
        int old_k = this->K;
        if (size == K) //* full array
            this->K *= 2;
        else if (size <= K / 4 && K > 2) //* almost empty array
            this->K /= 2;
        else
            return;
        this->K++; //* keep K odd.
        Node<T> **new_arr = new Node<T> *[this->K];
        for (int i = 0; i < K; i++)
            new_arr[i] = nullptr;
        //* re-hash all the nodes data to the new array.
        for (int i = 0; i < old_k; i++)
        {
            Node<T> *temp = arr[i];
            while (temp != nullptr)
            {
                int new_hash = hash(temp->GetKey());
                new_arr[new_hash] = new Node<T>(temp->GetKey(), temp->GetData(), new_arr[new_hash]);
                temp = temp->next;
            }
        }
        deleteArray(old_k);
        this->arr = new_arr;
    }
    int hash(int key)
    {
        return key % K;
    }

public:
    HashTable(int k = 2) : K(k), size(0)
    {
        InitArr(K);
    }
    int Insert(int key, T element = 0)
    {
        if (this->Search(key))
            return -1;
        int index = hash(key);
        //* push new node
        Node<T> *prev = arr[index];
        arr[index] = new Node<T>(key, element, prev);
        this->size++;
        this->resize();
        return index;
    }
    bool Delete(int key)
    {
        int index = hash(key);
        Node<T> *current = arr[index];
        if (current->key == key)
        {
            arr[index] = current->next;
        }
        else
        {
            Node<T> *prev = current;
            current = current->next;
            while (current != nullptr)
            {
                if (current->key == key)
                {
                    prev->next = current->next;
                    break;
                }
                prev = current;
                current = current->next;
            }
        }
        if (current != nullptr)
        {
            delete current;
            this->size--;
            this->resize();
            return true;
        }
        return false;
    }
    T Search(int key)
    {
        int index = hash(key);
        Node<T> *current = arr[index];
        while (current != nullptr)
        {
            if (current->key == key)
                return current->data;
            current = current->next;
        }
        return 0;
    }

    ~HashTable()
    {
        deleteArray(K);
    }

    friend std::ostream &operator<<(std::ostream &os, const HashTable<T> &ht)
    {
        for (int i = 0; i < ht.K; i++)
        {
            os << i << ": ";
            Node<T> *temp = ht.arr[i];
            while (temp != nullptr)
            {
                os << "-> " << *temp;
                temp = temp->GetNext();
            }
            os << std::endl;
        }
        return os;
    }
};

#endif
