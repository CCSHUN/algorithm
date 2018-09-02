#include <iostream>
#include <sys/stat.h>
#include <fstream>
#include <vector>
#include <dirent.h>
#include <cstdio>
//#include <unistd.h>
using namespace std;
//100M
#define PER_FILE_SIZE  102400
#define URL_BUFFER 256

unsigned long get_file_size(string file_name)
{
	if (!file_name.size())
		return 0;
	struct stat file_info;
	return stat(file_name.c_str(),&file_info) ? 0 : file_info.st_size;
}

unsigned long get_count_to_split(unsigned long file_size)
{
	return file_size <= PER_FILE_SIZE? 1 : file_size / PER_FILE_SIZE;
}

unsigned long rkdr_hash(const char* str)
{
	unsigned int seed = 131;
	unsigned int hash = 0;
	while (*str){
		hash = hash*seed+(*str++);
	}
	return (hash & 0x7FFFFFFF);
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

bool split_big_file(string file_name, string suffix, string store_path, unsigned long count_to_split)
{
	if (!file_name.size())
		return false;
	ifstream in(file_name);
	if (!in.is_open())
		return false;
	string line;
	while (getline(in, line)){
		string split_file_name = store_path;
		split_file_name += to_string(rkdr_hash(line.c_str()) % count_to_split);
		split_file_name += suffix;
		ofstream out(split_file_name, ios::app);
		if (!out.is_open()){
			in.close();
			return false;
		}
		out << line << endl;
		out.close();
	}
	in.close();
	return true;
}

int main(void)
{
	string store_path = "./split_file/";
	unsigned long count_to_split = max(get_count_to_split(get_file_size("a.txt")),\
			get_count_to_split(get_file_size("b.txt")));
	split_big_file("a.txt", ".a.txt", store_path, count_to_split);
	split_big_file("b.txt", ".b.txt", store_path, count_to_split);

	return 0;
}

//bool r_split_file(string file_name, int file_idx, int hash_idx, string store_path)
//{
//	char suffix[64] = {0};
//	snprintf(suffix, sizeof(suffix), "-%d-%d.txt", file_idx, hash_idx);
//	if (!split_big_file(file_name, suffix, hash_idx, store_path))
//		return false;
//	vector<string> files_name = get_folder_file_name_list(store_path, suffix);
//	for (int i = 0; i < files_name.size(); ++i){
//		string split_file_name = store_path;
//		split_file_name += files_name[i];
//		unsigned long size = get_file_size(split_file_name);
//		cout << split_file_name << ": " << size <<"," << PER_FILE_SIZE <<endl;
//		if (size/*get_file_size(split_file_name)*/ > PER_FILE_SIZE) {
//			cout << "come in"<<endl;
//			r_split_file(files_name[i], file_idx, hash_idx+1, store_path);
//		}
//	}
//	return true;
//}
//
