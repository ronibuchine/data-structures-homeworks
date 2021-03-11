#include "HSubject.h"

int HSubject::h1(string key)
{
    int sum = 0;
    for (int i = 0; i < key.size(); i++ ) // hash functions sums up chars in key and mods with size of table
        sum += static_cast<int>(key[i]);
    return sum % table.size();
}

int HSubject::h2(string key)
{
    int sum = 0;
    for (int i = 0; i < key.size(); i++) // hash functions sums up chars in key and mods with size of table
        sum += static_cast<int>(key[i]);
    return (prime(sum) * sum) % table.size();

}

int HSubject::hash(string key, int step)
{
    return h1(key) + step;
}

int HSubject::search(string key)
{
    for (int i = 0; i < table.size(); i++)
    {
        int index = hash(key, (i * h2(key))) % table.size();
        if (table[index].key == key && table[index].flag == full)
            return index;
    }
    return -1; // if item is not found 
}

void HSubject::insert(item<string, list<string> > entry)
{
    for (int i = 0; i < table.size(); i++)
    {
        int index = hash(entry.key, (i * h2(entry.key))) % table.size();
        if (table[index].flag == deleted || table[index].flag == (state)0)              // makes sure there is room in the table and finds an empty space to insert the item which has been set to full
        {
            entry.flag = full;
            table[index] = entry;
            return;
        }
    }
    throw "table full";
    
}

void HSubject::remove(string key)
{
    for (int i = 0; i < table.size(); i++)
    {
        int index = hash(key, (i * h2(key))) % table.size();
        if (table[index].key == key && table[index].flag == full)               // finds the item to be removed and changes its flag
            table[index].flag = deleted;
    }    
}

void HSubject::update(item<string, list<string> > entry)
{
    throw "unimplemented";
}

void HSubject::print()
{
    for (int i = 0; i < table.size(); i++)
    {
        if (table[i].flag == full)
        {
            cout << table[i].key << ':';
            for (list<string>::iterator it = table[i].data.begin(); it != table[i].data.end(); it++)
            {
                cout << *it << ' ';
            }                                                                     // goes through the list of strings and prints all the discussions
            cout << endl;
        }
    }
}

void HSubject::printS(string key)
{    
    if (search(key) != -1)
    {            
        for (list<string>::iterator it = table[search(key)].data.begin(); it != table[search(key)].data.end(); it++)
        {
            cout << *it << ' ';
        }                                                 
        cout << endl; return;
    }    
    cout << "ERROR" << endl;
}

void HSubject::printN(string key, int n)
{
    if (search(key) != -1)
    {
        int i = 0;       
        for (list<string>::iterator it = table[search(key)].data.begin(); i < n && i < table[search(key)].data.size(); it++, i++)     // goes until i reaches the end of that particular list or reaches n
        {
            cout << *it << ' ';
        }
        cout << endl;
        return;
    }
    cout << "ERROR" << endl;
}

void HSubject::startNewTable()
{
    for (int i = 0; i < table.size(); i++)
        table[i].flag = (state)0;                                                // sets each item to be empty essentially clearing the table
}

void HSubject::addSubjectAndTitle(string key, string discussion)
{
    if (search(key) != -1)
    {
        table[search(key)].data.push_front(discussion);
        return;
    }                                                                                   // adds new discussion to the beginning of existing list in table
    list<string>* l = new list<string>(); l->push_back(discussion);                     // if llist not in table a new one is created and inserted
    item<string, list<string> >* i = new item<string, list<string> >(key, *l, full);
    insert(*i);
}
