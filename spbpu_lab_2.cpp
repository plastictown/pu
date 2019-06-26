//============================================================================
// Name        : spbpu_lab_2.cpp
// Author      : Mikhail Domchenkov
// Version     :
// Copyright   : copyright Mikhail Domchenkov, 2019
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#include "cycled_queue.h"

int main() {

  cout << "-init-" << endl;

  MyQueue<std::string> q={"abc", "cba", "bca","abc", "cba", "bca","abc", "cba", "bca","abc", "cba", "bca","abc", "cba", "bca"};

  for(auto i = 0; i < 25; ++i){
      std:: cout << "size = " << q.get_size()
	  << "; cap = " << q.get_capacity()
	  << std::endl;

      q.push("new string");
  }

	cout << "-fini-" << endl;
	return 0;
}
