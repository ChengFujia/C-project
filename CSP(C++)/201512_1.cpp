#include <iostream>
#include <sstream>
using namespace std;

int main()
{
	string input;
	int result=0;
	cin >> input;
	//getline(cin,input)
	//stringstream ss(input);
	for(int i=0;i<input.size();i++)
		result += (int)input[i] - 48;
	cout << result << endl;;
	return 0;
}