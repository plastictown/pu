//============================================================================
// Name        : spbpu_lab_2.cpp
// Author      : Mikhail Domchenkov
// Version     :
// Copyright   : copyright Mikhail Domchenkov, 2019
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <list>
#include <iterator>
using namespace std;

#include "cycled_queue.h"
#include "my_unique_ptr.h"

int main() {

  std::cout << "-init-" << std::endl;

  my_unique_ptr<std::string> ptr(new std::string("abc"));
  std::cout << ptr->c_str() << std::endl;
  ptr->assign("new string");

  std::string s = *ptr;

  //my_unique_ptr<std::string> ptr2 = ptr;

  if (!ptr)std::cout << "no object!" << std::endl;

  my_unique_ptr<std::string> ptr3(new std::string("bla-bla"));

  //ptr3 = ptr;

  std::vector<my_unique_ptr<std::string>> v(5);
  v[0] = my_unique_ptr<std::string>(new string("rvalue"));

  std::list<my_unique_ptr<std::string>> l;

  l.insert(l.end()
    , std::make_move_iterator(v.begin())
    , std::make_move_iterator(v.end()));

	std::cout << "-fini-" << std::endl;
  std::cin.get();
	return 0;
}
