#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <cstring>
using namespace std;

const int block_size = 3;

void nested_loop_join(ifstream &a, ifstream &b, ofstream &out);
void sort_merge_join(ifstream &a, ifstream &b, ofstream &out);

int main()
{
	ifstream a("a.txt");
	ifstream b("b.txt");
	ofstream out("out.txt");
	if(!a)
	{
		cout << "Unable to open file a.txt" << endl;
	}
	if(!b)
	{
		cout << "Unable to open file b.txt" << endl;
	}
	if(!out)
	{
		cout << "Unable to create file out.txt" << endl;
	}

	sort_merge_join(a, b, out);
	a.close();
	b.close();
	out.close();
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
                        bool eq = true;
                        for(int i = 0; i < block_size; i++)
                        {
                            if(a_block[i] != b_block[i])
                            {
                                eq = false;
                                break;
                            }
                        }
                        if(strcmp(a_block, b_block) == 0 && a.good() && b.good())
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
    int i = 0;
    int j = 0;
    while(a.good() && b.good())
    {
        a.read(a_block, block_size);
        a.ignore(1);
        b.read(b_block, block_size);
        b.ignore(1);

        int a_number = atoi(a_block);
        int b_number = atoi(b_block);       
        if(a.good() && b.good())
        {
            if(a_number == b_number)
            {
                out.write(a_block, block_size);
                out << endl;
                i++;
                j++;
            }
            else if(a_number < b_number)
            {
                i++;
            }
            else if(a_number > b_number)
            {
                j++;
            }
        }
    }
    return;
}
