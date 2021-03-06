#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <iostream>
using std::cout;
using std::endl;

template <class T>
class HashTable;

template <class T>
class HTNode
{
    int key;
    T data;
    HTNode<T> *next;

public:
    HTNode() = delete;
    HTNode(int key, const T data = 0, HTNode<T> *next = nullptr) : key(key), data(data), next(next) {}
    HTNode(const HTNode<T> &HTNode) = default;
    ~HTNode() = default;
    HTNode<T> &operator=(const HTNode<T> &HTNode) = default;
    friend class HashTable<T>;
    friend std::ostream &operator<<(std::ostream &os, const HTNode<T> &nd)
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
    HTNode<T> *GetNext()
    {
        return (this != 0) ? this->next : nullptr;
    }
};

template <class T>
class HashTable
{
    int size;
    int K;
    HTNode<T> **arr;
    void InitArr(int k)
    {
        arr = new HTNode<T> *[k];
        for (int i = 0; i < k; i++)
            arr[i] = nullptr;
    }
    void deleteArray(int k)
    {
        for (int i = 0; i < k; i++)
        {
            HTNode<T> *current = this->arr[i];
            HTNode<T> *temp;
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
        HTNode<T> **new_arr = new HTNode<T> *[this->K];
        for (int i = 0; i < K; i++)
            new_arr[i] = nullptr;
        //* re-hash all the HTNodes data to the new array.
        for (int i = 0; i < old_k; i++)
        {
            HTNode<T> *temp = arr[i];
            while (temp != nullptr)
            {
                int new_hash = hash(temp->GetKey());
                new_arr[new_hash] = new HTNode<T>(temp->GetKey(), temp->GetData(), new_arr[new_hash]);
                temp = temp->next;
            }
        }
        deleteArray(old_k);
        this->arr = *(&new_arr);
    }
    int hash(int key)
    {
        return key % K;
    }

public:
    HashTable(int k = 2) : size(0), K(k)
    {
        InitArr(K);
    }
    int Insert(int key, T element = 0)
    {
        if (this->Search(key))
            return -1;
        int index = hash(key);
        //* push new HTNode
        HTNode<T> *prev = arr[index];
        arr[index] = new HTNode<T>(key, element, prev);
        this->size++;
        this->resize();
        return index;
    }
    bool Delete(int key)
    {
        int index = hash(key);
        HTNode<T> *current = arr[index];
        if (current->key == key)
        {
            arr[index] = current->next;
        }
        else
        {
            HTNode<T> *prev = current;
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
        HTNode<T> *current = arr[index];
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
        cout << "~HashTable" << endl;
        deleteArray(K);
    }

    friend std::ostream &operator<<(std::ostream &os, const HashTable<T> &ht)
    {
        for (int i = 0; i < ht.K; i++)
        {
            os << i << ": ";
            HTNode<T> *temp = ht.arr[i];
            while (temp != nullptr)
            {
                os << "-> " << *temp;
                temp = temp->GetNext();
            }
            os << std::endl;
        }
        return os;
    }
    T *GetDataArray()
    {
        T *data = new T[this->size];
        int i = 0;
        for (int j = 0; j < this->K; j++)
        {
            HTNode<T> *temp = this->arr[j];
            while (temp != nullptr)
            {
                data[i] = temp->data;
                i++;
            }
        }
        return data;
    }
    int GetSize()
    {
        return (this != 0) ? size : -1;
    }
    void MergeWith(HashTable<T> *sub)
    {
        for (int i = 0; i < sub->K; i++)
        {
            HTNode<T> *current = sub->arr[i];
            while (current != nullptr)
            {
                this->Insert(current->key, current->data);
                current = current->next;
            }
        }
    }
};
#endif
