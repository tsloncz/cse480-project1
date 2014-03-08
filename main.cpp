#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void nested_loop_join(ifstream &a, ifstream &b, ofstream &out,
                      string condition, int page_size);
void sort_merge_join(ifstream &a, ifstream &b, ofstream &out,
                     string condition, int page_size);

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

	a.close();
	b.close();
	out.close();
	return 0;
}

