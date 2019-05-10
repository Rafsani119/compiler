#include<bits/stdc++.h>
using namespace std;

int Size;
class SymbolInfo
{
private:
    string name;
    string type;
public:
    SymbolInfo()
    {
        name = "FFFFFF";
        type = "FFFFFF";
    }
    SymbolInfo *next;
    string get_name();
    string get_type();
    void set_name(string arg);
    void set_type(string arg);

};


void SymbolInfo::set_name(string arg)
{
    name = arg;
}

void SymbolInfo::set_type(string arg)
{
    type = arg;
}

string SymbolInfo::get_name()
{
    return name;
}

string SymbolInfo::get_type()
{
    return type;
}


int hashFunc(string x, int M)
{
    int sum,i;
    for (sum=0, i=0; i < x.length(); i++)
        sum += x[i];
    return sum % M;
}


class Scope_table
{
public:
    SymbolInfo **aray;
    int id;
    Scope_table *parent_scope;

    Scope_table(int n);
    bool Insert(string name, string type);
    SymbolInfo* Look_up(string str);
    bool Delete(string str);
    void Print();


};

Scope_table::Scope_table(int n)
{
    aray = new SymbolInfo*[n];
    for(int i=0; i<n; i++)
    {
        aray[i] = new SymbolInfo();
    }
    Size = n;
}

bool Scope_table::Insert(string name, string type)
{
    int hash_val;
    hash_val = hashFunc(name,Size);
    //cout << hash_val << endl;
    if(aray[hash_val]->get_name() == "FFFFFF")
    {
        SymbolInfo *p;
        p = new SymbolInfo();
        p->set_name(name);
        p->set_type(type);
        aray[hash_val] = p;
        cout << "Inserted in ScopeTable# "<< id << "at position " << hash_val << "," << 0 << endl;
    }
    else
    {
        SymbolInfo *mark;
        mark = aray[hash_val];
        int i =1;
        while(mark->next != NULL)
        {
            i++;
            if(mark->get_name() == name)
                return false;
            mark = mark->next;
            if(mark->get_name() == name)
                return false;
        }
        SymbolInfo *p = new SymbolInfo();

        p->set_name(name);
        p->set_type(type);

        mark->next = p;
        cout << "Inserted in ScopeTable# "<< id << "at position " << hash_val << "," << i << endl;
    }
}


void Scope_table::Print()
{
    SymbolInfo *p;
    for(int i=0; i<Size; i++)
    {
        cout << i << " --> ";
        p = aray[i];
        while(p != NULL)
        {
            if(p ->get_name() == "FFFFFF")
                break;
            cout << "<" << p->get_name() << " : " << p->get_type() << " > ";
            p = p->next;
        }
        cout << endl;
    }
}


SymbolInfo* Scope_table::Look_up(string str)
{
    int hash_val = hashFunc(str,Size);
    SymbolInfo* p;
    int i=0;
    p = aray[hash_val];
    while(p != NULL )
    {
        if(str == p->get_name())
        {
            cout << "Found in ScopeTable#" << id << "at position" << hash_val << "," << i << endl;
            return p;
        }
        else
        {
            i++;
            p= p->next;
        }
    }
    cout << "not found\n";
    return NULL;
}



bool Scope_table::Delete(string str)
{
    int hash_val = hashFunc(str,Size);
    SymbolInfo *prev,*curr ;
    int i = 0;
    prev = aray[hash_val];
    curr = aray[hash_val];
    while(curr != NULL )
    {
        if(str == curr->get_name())
        {
            cout << "Found in ScopeTable# " << id << " at position" << hash_val << "," << i << endl;
            if(i  == 0)
            {
                aray[hash_val] =curr->next;
            }
            else
            {
                prev->next = curr->next;
                delete curr;
            }
            return true;
        }
        else
        {
            i++;
            prev = curr;
            curr=curr->next;
        }
    }
    cout << "not found\n";
    return false;
}



class Symbol_table
{
public:
    Symbol_table(int n);
    int table_no;
    Scope_table *current;
    void Enter_scope();
    void Exit_scope();
    bool Insert(string name, string type);
    bool Remove(string str);
    SymbolInfo* LookUp(string str);
    void print_current();
    void PrintAll();

};

Symbol_table::Symbol_table(int n)
{
    Scope_table *newTable = new Scope_table(n);
    newTable->parent_scope = NULL;
    current = newTable;
    current->id = 1;
    table_no=1;


}


void Symbol_table::Enter_scope()
{
    table_no++;
    Scope_table *newTable = new Scope_table(Size);
    newTable->parent_scope = current;
    current = newTable;
    current->id=table_no;
    cout << "New ScopeTable with id " << current->id <<  " created" << endl;

}

void Symbol_table::Exit_scope()
{
    Scope_table *p;
    p = current;
    current = current->parent_scope;
    delete p;
    table_no--;
}

bool Symbol_table::Insert(string name, string type)
{
    return current->Insert(name,type);
}

bool Symbol_table::Remove(string str)
{
    return current->Delete(str);
}


void Symbol_table::print_current()
{
    cout << "ScopeTable# " << current->id << endl;
    current->Print();
}

void Symbol_table::PrintAll()
{
    Scope_table *p = current;
    while (p!= NULL)
    {
        cout << "ScopeTable# " << p->id << endl;
        p->Print();
        p=p->parent_scope;
    }
}



int main()
{

    /*Scope_table x(7);
    x.Insert("foo","string");
    x.Insert("xx","int");

    x.Insert("xx","int");
    x.Print();
    //cout <<  x.Look_up("i")->get_type();
    x.Delete("xx");
   // cout << endl << x.Insert("foo","string") << endl;
    x.Insert("i","int");
    x.Print();*/
    Symbol_table x(7);
    x.Insert("foo","string");
    x.print_current();
    //x.Remove("foo");
    //x.print_current();
    x.Enter_scope();

    x.Insert("i","int");
    x.print_current();
    //x.Exit_scope();
    x.PrintAll();


    return 0;
}
