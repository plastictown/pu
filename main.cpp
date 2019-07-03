#include <iostream>
#include <map>

using namespace std;

int main(){
	
	std::map<int, int> m;
	m.insert(1,2);
	
	auto&[k,v] = *(m.begin());
	
	
	return 0;
}