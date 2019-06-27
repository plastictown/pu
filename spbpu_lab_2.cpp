//============================================================================
// Name        : spbpu_lab_2.cpp
// Author      : Mikhail Domchenkov
// Version     :
// Copyright   : copyright Mikhail Domchenkov, 2019
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <utility>
using namespace std;

#include "cycled_queue.h"

int main() {

  cout << "-init-" << endl;

  MyQueue<std::string> q={"abc", "cba", "bca","abc", "cba", "bca","abc", "cba", "bca","abc", "cba", "bca","abc", "cba", "bca"};

  for(auto i = 0; i < 25; ++i){
      q.push("new string");
  }

  MyQueue<std::string> q3; 
  q3 = q;

  while (true) {
    try
    {
      std::cout << q3.pop() << std::endl;
    }
    catch (std::exception& e) 
    {
      std::cout << e.what() << std::endl;
      break;
    }
  }
  
	cout << "-fini-" << endl;
  cin.get();
	return 0;
}
