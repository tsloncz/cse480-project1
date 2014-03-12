#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
using namespace std;

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
	while(a.good())
	{
		string a_line;
		getline(a, a_line);
		while(b.good())
		{
			string b_line;
			getline(b, b_line);
			if(a.good() && b.good() && a_line == b_line)
			{
				out << a_line << endl;
				cout << a_line << endl;
			}
		}
		b.clear();
		b.seekg(0);
	}
	return;
}

