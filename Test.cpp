#include "HashTable.h"
#include "Player.h"
#include "Group.h"
#include "AVLTree.h"

#include <iostream>
#include <time.h>
#include <math.h>
#include <vector>
#include <memory>

using std::cout;
using std::endl;
using std::make_shared;
using std::vector;

void delete_sp(shared_ptr<Player> sp)
{
    sp.reset();
}
void print_p(shared_ptr<Player> sp)
{
    cout << *sp.get() << " ";
}

int main()
{
    try
    {
        AVLTree<shared_ptr<Player>> *tr = new AVLTree<shared_ptr<Player>>();
        shared_ptr<Player> sp = make_shared<Player>(3, 3, 3);
        cout << sp.use_count() << endl;
        tr->Insert(1, sp);
        tr->Insert(2, sp);
        // tr->Remove(1);
        // tr->Print();
        cout << sp.use_count() << endl;
        sp.reset();
        cout << sp.use_count() << endl;
        tr->PostOrderApply(std::function<void(shared_ptr<Player>)>(&delete_sp));
        delete tr;
        // tr->InOrderApply(std::function<void(shared_ptr<Player>)>(&print_p));
        cout << endl;
        cout << tr->GetTreeSize() << endl;
        // delete tr;
        // cout << *sp.get() << endl;
        cout << "FINISH" << endl;
        /*
        shared_ptr<Player> sp = make_shared<Player>(3, 4, 5);
        HashTable<shared_ptr<Player>> ht = HashTable<shared_ptr<Player>>();
        HashTable<shared_ptr<Player>> ht2 = HashTable<shared_ptr<Player>>();
        ht.Insert(3, sp);
        ht2.Insert(3, sp);
        ht.Delete(3);
        cout << ht << endl;
        cout << ht2 << endl;
        cout << *ht.Search(3).get() << endl;
        */

        /*
        int rounds = 100;
        srand(time(NULL));
        int num, op = 1, index;
        HashTable<int> ht = HashTable<int>();
        vector<int> v = {};
        for (int i = 0; i < rounds; i++)
        {
            std::cout << "\x1B[2J\x1B[H";
            if (op > 0 || v.size() <= 1) //* INSERT
            {
                num = rand();
                ht.Insert(num);
                v.push_back(num);
            }
            // std::cout << "Inserting:  " << num << std::endl;
            else //* DELETE
            {
                int t1 = rand();
                int t2 = v.size();
                index = t1 % t2;
                num = v[index];
                ht.Delete(num);
                v.erase(v.begin() + index);
            }
            std::cout << ht << std::endl;
            op = rand() % 3;
            _sleep(500);
        }
        */
    }
    catch (const std::exception &e)
    {
        std::cout << "FUCK!!!!!!!!!!!!!!!!" << std::endl;
        std::cout << e.what();
    }
    return 0;
}