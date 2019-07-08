#include <fstream>
#include <iostream>
#include <string>
//#include <ctime>
using namespace std;

//[a,b]
#define random(a,b) ((rand()%(b-a+1))+a)
#define N 500000

string url  = "-0123456789abcdefghijklmnopqrstuvwxyz";

void generateUrl(string file)
{
	ofstream out(file);
	int n = 0;
	if (out.is_open()){
		for (int i = 0; i < N; ++i){
			int size = random(1,64);//64bit
			string s = "https://www.";
			for (int j = 0, l = 1; j < size; ++j){
				s += url[random(l,36)];//1+10+26-1=36
				l = (s[s.size()-1] == '-' || j >= size-1) ? 1: 0;
			}
			s+=".com/";
			out << s <<endl;
		}
		out.close();
	}
}

int main(void)
{
	srand(1);
	generateUrl("a.txt");
	generateUrl("b.txt");

	return 0;
}
