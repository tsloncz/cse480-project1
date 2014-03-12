#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
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

	nested_loop_join(a, b, out);
	a.close();
	b.close();
	out.close();
	return 0;
}

void nested_loop_join(ifstream &a, ifstream &b, ofstream &out)
{
        char a_block[block_size];
        char b_block[block_size];

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
                        if(eq && a.good() && b.good())
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
