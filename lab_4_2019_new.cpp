#include <vector>
#include <memory>
#include <map>
#include <set>
#include <functional>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <utility>
#include <iterator> 
#include <list>
#include <cmath>
#include <stack>
#include <queue>
#include<ostream>

#include "lab4.h"

int main()
{
	/******************************************************************************/
	/*
	������� 1. ���������� ������ ������� ��� ������ �� ������ ���������
	������������������� ������� ����� ���������:
	�	��� ������� ������ ����,
	�	��� � ��������� �� ������� ������ ���� (��������� ������������� �����������
		=> � ���� ������ ������� �������� �������� �� ������)
	���������: if constexpr
	*/
	{	//��������:

		std::vector<std::string> vs = { "A", "B", "C" };
		PrintAnyCont(vs);

		std::string* ar[] = { new std::string("D"), new std::string("E"), new std::string("F") };
		PrintAnyCont(ar);	
     
		for(size_t i=0u; i < sizeof(ar)/sizeof(std::string*); ++i){
      delete ar[i];
    }
	}

	/******************************************************************************/
	/*
	������� 2. ���������� ������ ������� ������ �� ������ �������� ��������� ������
	�������� (stack, queue, priority_queue)
	���������: if constexpr, is_same
	*/
	{
      std::stack<int> s;
      s.push(1);
      s.push(3);
      s.push(5);
		std::queue<int> q;
	  q.push(7);
	  q.push(8);
	  q.push(9);
		std::priority_queue<int> pq;
	  pq.push(101);
	  pq.push(12);
	  pq.push(13);
			std::cout << "- - -" << std::endl;
		PrintAdapter<std::stack,int>(s);
			std::cout << "- - -" << std::endl;
		PrintAdapter<std::queue, int>(q);
			std::cout << "- - -" << std::endl;
		PrintAdapter<std::priority_queue, int>(pq);
			std::cout << "- - -" << std::endl;
	}

	/******************************************************************************/
	/*
	������� 3. ���������� ������ ������� �������� ���� ��������.
	���� ������ ��������� �������� ��������, �� ��� �������� ������� ����� ���������
	�� �������� ������� ���������. ��� ���� �������� ������� � ������ �������� ������ ����
	������ � ���� �� ����.
	���������: if constexpr, is_same
	*/
	{

		int a = 5;
		long l = 42l;
		double b = 0.3f;
		std::vector<long> v{ 1,5,9 };

		std::cout << strange_sum(a,b) << std::endl;
		std::ignore = strange_sum(v, l);
		for (const auto& i : v) { std::cout << i << std::endl; }
			std::cout << "- - -" << std::endl;
	}

	/******************************************************************************/
	/*
	������� 4. variadic template � �������. ������� pack-� ����������
	���������� �������, ������� ����� �������� ����� ���������� ���������� ������ ����,
	�������� a) variadic template, b) �������.
	*/
	{	//��������: 

		

		MyPrint(4, 8.8, (int)A(1), std::string("dfg"));  //a)
			std::cout << "- - -" << std::endl;

		MyPrint2(4, 8.8, A(42), std::string("dfg"));  //b)
			std::cout << "- - -" << std::endl;
	}

	/******************************************************************************/
	/*
	������� 5. ������� �� vector (list, deque) ��� ��������, �������� ������� ���������
	� ���������� pack-�.
	*/
	{
		std::vector<int> v = { 1,2,3,1,4,1,5 };
		EraseAll(v, 1, 4);

		std::list<int> l = { 1,2,3,1,4,1,5 };
		EraseAll(l, 1, 4);		

	}

	/******************************************************************************/
	/*
	������� 6. ������� ������� ���������� ��������� � set � try_insertAll()
	������� ������ ��������� ����� ���������� ��������� ��� ������� � �������� �� �������� � set.
	���� ������� �������� ��� ��������� ��������, ������� ���������� true, ����� false.
	*/
	{   //��������:

		std::set<int> my_set{ 1, 2, 3 };
		bool b1 = try_insert_all(my_set, 4, 5, 6); // ��������� ��� ��������.
													 // ���������� true
		bool b2 = try_insert_all(my_set, 7, 8, 2); // ��������� 7, 8.
													 // ���������� false, ��������� 2 ��� ������������
		;
	}

	/******************************************************************************/
	/*
	������� 7. �������� ��������� ���� ���������� � �������� ��������
	�������� ������� InRange() ����� �������, �����:
	*/
	{
		bool b1 = InRange(10, 20, 1, 15, 30);		// --> false
		bool b2 = InRange(10, 20, 11, 12, 13);		// --> true
		bool b3 = InRange(5.0, 5.5, 5.1, 5.2, 5.3);	// --> true
		
	}

	/******************************************************************************/

	

	//������� 8. std::tuple
	//�������� ����� book (�����, ��������, ��� �������...). 
	//�������� ���������� ����� �������, ����� ����� ��������� � ������������� ����.
	//����� ����������� ������������ ������, ����� ������������ ������� ���������, �� ����
	//�����������, �������� operator<. ��� ���������� ��������� ������� ������������ �������
	//� ������ ���� ������!!! 

	//���������: ��� ������������ ������ ������������ ������ std::tuple,
	//��� ��� ��� std::tuple ����������� ��������� ==,!=,<,<=,>,>=
	//,������� ���������� ��� ������� ��������������� (� ������� ���������� ������).

	//��� �������� ������������ ����������
	{

		book<int, std::string, float> b1, b2, b3;
		b1.set(1, "Gimme, gimme", 42.0f);
		b2.set(3, "Gimme just a little smile", 3.14159264f);
		b3.set(0, "That's all i've ask of you", 0.7f);

		b1.print();
		std::cout << "- - -" << std::endl;
		b2.print();
		std::cout << "- - -" << std::endl;
		b3.print();
		std::cout << "- - -" << std::endl;

		std::set<decltype(b1)> library;
		library.insert(b1);
		library.insert(b2);
		library.insert(b3);

		std::cout << "---printing by order---" << std::endl;

		for ( const auto& i : library) {
			i.print();
			std::cout << "---" << std::endl;
		}
	}

	/******************************************************************************/

	//������� 9. shared_ptr � weak_ptr+
	//������� ��������������� ������ ����������� ������ human. � ������ ��������:
	//��� - string
	//�������� �������: ��� ��� ��� ���...
	//�������� - shared_ptr (�������� �� ������ ��������...)
	//���� - ��������� �� weak_ptr (����� �������� ����������� ������������)

	//������ ������ human:
	//����������� - ��� ������������� ����� � ��������
	//����������� �����������, �������� ������������, move ???
	//����������� ����� child() - 
	//				������ ������� ������� � ������� ������� ��� ����������� ��������
	//				+ ������������ ��� ����� ������� � ���������� � ��������

	//������ ����������� ����������� ��������������� ������ ��� ���������� ����������
	{
		//������� ������ � ����-�� ���������� => "����-���� ��� �� ����, ��������, ���� � ���"
		//(�� ���� �� ����� ���� ��� ���� � ��� ����):


		//std::shared_ptr<human> grandM1(new human("Eva"));
		//...

		//� ��� ��������� ���� - child():


		//� � ����� � ���� ������� ���� ����:


		//...

		std::shared_ptr<human> grandM1(new human("Lili Potter",false));
		std::shared_ptr<human> grandF1(new human("James Potter",false));
		std::shared_ptr<human> Jinney(new human("Jinney Whizley"));

		auto Bilbo = human::child(grandF1, grandM1, "Bilbo Baggins");
		auto Harry = human::child(grandF1, grandM1, "Harry Potter");
		auto Harry_son = human::child(Harry, Jinney, "Potter jn.");

		auto Frodo = human::child(Bilbo, nullptr, "Frodo Baggins");
		auto Santa = human::child(Frodo, nullptr, "Santa Claus");

		human::print(grandM1);

		~(*Harry); // KILL HIM!!!

		std::cout << std::endl;
		human::print(grandF1);

		std::cout << std::endl;
		human::print_parents(Santa);
		std::cout << std::endl;

		human::print_cow_with_moo();
	}// !9



	std::cin.get();
	return 0;
}