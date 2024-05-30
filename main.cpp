#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(int argc , char *argv[])
{
	ifstream fin; string file_system; long long inode; 

	assert(argc == 2);

	system("mkdir /tmp/estat");

	system((string("ls -i ") + argv[1] + " > /tmp/estat/ls.tmp").c_str());
	fin.open("/tmp/estat/ls.tmp") , fin >> inode , fin.close();
	system("rm /tmp/estat/ls.tmp");

	system((string("df ") + argv[1] + " > /tmp/estat/df.tmp").c_str());
	fin.open("/tmp/estat/df.tmp");
	while(fin >> file_system)
	{
		// cerr << "\'" << file_system << "\'\n";
		if(file_system.substr(0 , 4) == "/dev")
			break ;
	}
	fin.close();
	system("rm /tmp/estat/df.tmp");

	// cerr << "inode:" << inode << "\n";
	// cerr << "file_system:" << file_system << "\n";
	
	system((string("sudo debugfs -R \'stat <") + to_string(inode) + ">\' " + file_system + " > /tmp/estat/out.tmp").c_str());

	system("cat /tmp/estat/out.tmp && rm /tmp/estat/out.tmp");

	system("rmdir /tmp/estat");

	return 0;
}