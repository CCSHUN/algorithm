#include <iostream>
#include <vector>
#include <string>
#include <dirent.h>
using namespace std;
 
vector<string> list_folder_file_name(string folder)
{
	struct dirent *ptr = NULL;
	DIR *dir = opendir(folder.c_str());
	vector<string> files_name;
	while ((ptr=readdir(dir))!=NULL){
		if (ptr->d_name[0] == '.')
			continue;
		files_name.push_back(ptr->d_name);
	}
	closedir(dir);
	return files_name;
}

int main(int argc, char * argv[])
{
	vector<string> files_name = list_folder_file_name("./");
    for (int i = 0; i < files_name.size(); ++i){
		cout<<files_name[i]<<endl;
	}
	return 0;
}
