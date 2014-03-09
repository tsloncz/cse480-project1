#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
using namespace std;

void nested_loop_join(ifstream &a, ifstream &b, ofstream &out,
                      string join_attrib_a, string join_attrib_b);
void sort_merge_join(ifstream &a, ifstream &b, ofstream &out,
                     string join_attrib_a, string join_attrib_b);

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

	nested_loop_join(a, b, out, "F", "F");
	a.close();
	b.close();
	out.close();
	return 0;
}

void split(const string &s, char delim, vector<string> &elems)
{
	stringstream ss(s);
	string item;
	while(getline(ss, item, delim))
	{
		elems.push_back(item);
	}
	return;
}

void nested_loop_join(ifstream &a, ifstream &b, ofstream &out,
                      string join_attrib_a, string join_attrib_b)
{
	// Get the attributes for relation a
	string a_header;
	getline(a, a_header);
	vector<string> a_attributes;
	split(a_header, '\t', a_attributes);

	// Make sure join_attrib_a is in a_attributes
	int a_index = -1;
	for(int i = 0; i < a_attributes.size(); i++)
	{
		if(a_attributes[i] == join_attrib_a)
		{
			a_index = i;
		}
	}
	if(a_index == -1)
	{
		cout << join_attrib_a << " is not an attribute of relation a" << endl;
		exit(0);
	}

	// Get the attributes for relation b
	string b_header;
        getline(b, b_header);
        vector<string> b_attributes;
        split(b_header, '\t', b_attributes);

	// Make sure join_attrib_b is in b_attributes
        int b_index = -1;
        for(int i = 0; i < b_attributes.size(); i++)
        {
		if(b_attributes[i] == join_attrib_b)
		{
 			b_index = i;
                }
        }
        if(b_index == -1)
        {
                cout << join_attrib_b << " is not an attribute of relation b" << endl;
		exit(0);
        }

	// Save position after header
	streampos b_top = b.tellg();

	// Output headers for the join file
	for(int i = 0; i < a_attributes.size(); i++)
	{
		out << "a." << a_attributes[i] << '\t';
		cout << "a." << a_attributes[i] << '\t';
	}
	for(int i = 0; i < b_attributes.size(); i++)
	{
		if(i == b_attributes.size() - 1)
		{
			out << "b." << b_attributes[i] << endl;
			cout << "b." << b_attributes[i] << endl;
		}
		else
		{
			out << "b." << b_attributes[i] << '\t';
			cout << "b." << b_attributes[i] << '\t';
		}
	}

	while(a.good())
	{
		string a_line;
		getline(a, a_line);
		vector<string> a_tuple;
		split(a_line, '\t', a_tuple);
		while(b.good())
		{
			string b_line;
			getline(b, b_line);
			vector<string> b_tuple;
			split(b_line, '\t', b_tuple);
			if(a.good() && b.good() && a_tuple[a_index] == b_tuple[b_index])
			{
				out << a_line << '\t' << b_line << endl;
				cout << a_line << '\t' << b_line << endl;
			}
		}
		b.clear();
		b.seekg(b_top);
	}
	return;
}

