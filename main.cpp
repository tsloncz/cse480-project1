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
    ifstream r("R.txt");
    ifstream s("S.txt");
    ofstream t("T.txt");
        
    if(!r)
    {
        cout << "Unable to open file R.txt" << endl;
    }
    if(!s)
    {
        cout << "Unable to open file S.txt" << endl;
    }
    if(!t)
    {
        cout << "Unable to write to file T.txt" << endl;
    }

    sort_merge_join(r, s, t);

    r.close();
    s.close();
    t.close();
    return 0;
}

void nested_loop_join(ifstream &r, ifstream &s, ofstream &t)
{
    char r_block[block_size + 1];
    char s_block[block_size + 1];
    r_block[block_size] = '\0';
    s_block[block_size] = '\0';

    while(r.good())
    {
        r.read(r_block, block_size);
        r.ignore(1);
        while(s.good())
        {
            s.read(s_block, block_size);
            s.ignore(1);
            if(strcmp(r_block, s_block) == 0 && r.good()
               && s.good())
            {
                t.write(r_block, block_size);
                t << ", ";
                t.write(s_block, block_size);
                t << endl;
            }
        }
        s.clear();
        s.seekg(0);
    }
    return;
}

// Assume files are sorted for now
void sort_merge_join(ifstream &r, ifstream &s, ofstream &t)
{
    char r_block[block_size + 1];
    char s_block[block_size + 1];
    r_block[block_size] = '\0';
    s_block[block_size] = '\0';
    bool read_from_r = true;
    bool read_from_s = true;
    while(r.good() && s.good())
    {
        if(read_from_r)
        {
            r.read(r_block, block_size);
            r.ignore(1);
        }
        if(read_from_s)
        {        
            s.read(s_block, block_size);
            s.ignore(1);
        }

        int r_number = atoi(r_block);
        int s_number = atoi(s_block);
        if(r.good() && s.good())
        {
            if(r_number == s_number)
            {
                t.write(r_block, block_size);
                t << ", ";
                t.write(s_block, block_size);
                t << endl;
                read_from_r = true;
                read_from_s = true;
            }
            else if(r_number < s_number)
            {
                read_from_r = true;
                read_from_s = false;
            }
            else if(r_number > s_number)
            {
                read_from_r = false;
                read_from_s = true;
            }
        }
    }
    return;
}
