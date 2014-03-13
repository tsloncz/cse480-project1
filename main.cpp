#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
using namespace std;

const int block_size = 4;

void nested_loop_join(ifstream &a, ifstream &b, ofstream &out);
void sort_merge_join(ifstream &a, ifstream &b, ofstream &out);

int main()
{
    ifstream a("a.txt");
    ifstream b("b.txt");
    ofstream nlj("nested-loop-join.txt");
    ofstream smj("sort-merge-join.txt");
        
    if(!a)
    {
        cout << "Unable to open file a.txt" << endl;
    }
    if(!b)
    {
        cout << "Unable to open file b.txt" << endl;
    }
    if(!nlj)
    {
        cout << "Unable to create file nested-loop-join.txt" << endl;
    }
    if(!smj)
    {
        cout << "Unable to create file sort-merge-join.txt" << endl;
    }

    nested_loop_join(a, b, nlj);

    a.clear();
    a.seekg(0);
    b.clear();
    b.seekg(0);

    sort_merge_join(a, b, smj);

    a.close();
    b.close();
    nlj.close();
    smj.close();
    return 0;
}

void nested_loop_join(ifstream &a, ifstream &b, ofstream &out)
{
    char a_block[block_size + 1];
    char b_block[block_size + 1];
    a_block[block_size] = '\0';
    b_block[block_size] = '\0';

    while(a.good())
    {
        a.read(a_block, block_size);
        a.ignore(1);
        while(b.good())
        {
            b.read(b_block, block_size);
            b.ignore(1);
            if(strcmp(a_block, b_block) == 0 && a.good()
               && b.good())
            {
                out.write(a_block, block_size);
                out << endl;
            }
        }
        b.clear();
        b.seekg(0);
    }
    return;
}

// Assume files are sorted for now
void sort_merge_join(ifstream &a, ifstream &b, ofstream &out)
{
    char a_block[block_size + 1];
    char b_block[block_size + 1];
    a_block[block_size] = '\0';
    b_block[block_size] = '\0';
    bool read_from_a = true;
    bool read_from_b = true;
    while(a.good() && b.good())
    {
        if(read_from_a)
        {
            a.read(a_block, block_size);
            a.ignore(1);
        }
        if(read_from_b)
        {        
            b.read(b_block, block_size);
            b.ignore(1);
        }

        int a_number = atoi(a_block);
        int b_number = atoi(b_block);
        if(a.good() && b.good())
        {
            if(a_number == b_number)
            {
                out.write(a_block, block_size);
                out << endl;
                read_from_a = true;
                read_from_b = true;
            }
            else if(a_number < b_number)
            {
                read_from_a = true;
                read_from_b = false;
            }
            else if(a_number > b_number)
            {
                read_from_a = false;
                read_from_b = true;
            }
        }
    }
    return;
}
