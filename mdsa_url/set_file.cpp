#include <iostream>
#include <set>
#include <vector>
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>
#include <algorithm>
using namespace std;
#define PER_FILE_SIZE 202400

set<string> get_file_hash_set(string file_name)
{
	set<string> url;
	ifstream in(file_name);
	if (!file_name.size() || !in.is_open())
		return url;
	string line;
	while (getline(in, line)){
		url.insert(line);
	}
	in.close();
	return url;
}

set<string> get_same_url_set(set<string> a, set<string> b)
{
	set<string> c;
	set_intersection(a.begin(), a.end(), b.begin(), b.end(), inserter(c, c.begin()));
	return c;
}

bool str_ends_with(string s, string sub)
{
    return s.rfind(sub)==(s.length()-sub.length());
}

vector<string> get_folder_file_name_list(string folder, string ends_with)
{
    struct dirent *ptr = NULL;
    DIR *dir = opendir(folder.c_str());
    vector<string> files_name;
    while ((ptr=readdir(dir))!=NULL){
        if (ptr->d_name[0] == '.')
            continue;
        if (str_ends_with(ptr->d_name, ends_with))
            files_name.push_back(ptr->d_name);
    }
    closedir(dir);
    return files_name;
}

unsigned long get_file_size(string file_name)
{
    if (!file_name.size())
        return 0;
    struct stat file_info;
    return stat(file_name.c_str(),&file_info) ? 0 : file_info.st_size;
}


bool write_same_url_to_file(string folder, string same_url_file_name)
{
	vector<string> files_name_a = get_folder_file_name_list(folder, ".a.txt");
	vector<string> files_name_b = get_folder_file_name_list(folder, ".b.txt");
	vector<string>::iterator iter;
	ofstream out(same_url_file_name, ios::app);
	if (!out.is_open())
		return false;
	for (int i = 0; i < files_name_a.size(); ++i){
		string s = files_name_a[i];
		s[s.size()-5] = 'b';
		if (get_file_size(files_name_a[i]) <= PER_FILE_SIZE \
				&& (iter = find(files_name_b.begin(), files_name_b.end(),s))\
			   	!= files_name_b.end()\
				&& get_file_size(*iter) <= PER_FILE_SIZE){
			set<string> a_set = get_file_hash_set(folder+files_name_a[i]);
			set<string> b_set = get_file_hash_set(folder+*iter);
			set<string> same_url_set = get_same_url_set(a_set, b_set);
			set<string>::iterator it = same_url_set.begin();
			for (; it != same_url_set.end(); ++it){
				out << *it << endl;
				cout<<*it<<endl;
			}
		}
	}
	out.close();
	return true;
}

int main(void)
{
	bool ans = write_same_url_to_file("./split_file/", "same_url.txt");
	if (ans)
		cout<<"success!"<<endl;
	else
		cout<<"failed."<<endl;
	return 0;	
}
