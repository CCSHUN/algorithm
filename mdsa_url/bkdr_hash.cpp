#include <iostream>
using namespace std;

unsigned int BKDRHash(char* str)
{
	unsigned int seed = 131;
	unsigned int hash = 0;
	while (*str){
		hash = hash * seed + (*str++);
	}
	return (hash & 0x7FFFFFFF);
}

int main (void){
	char hashStr[] = "Hello,World!";
	cout<<BKDRHash(hashStr)<<endl;

	return 0;
}
