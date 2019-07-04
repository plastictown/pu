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
	Задание 1. Реализуйте шаблон функции для вывода на печать элементов
	последовательностей которые могут содержать:
	•	как объекты любого типа,
	•	так и указатели на объекты любого типа (указатели распечатывать неинтересно
		=> в этом случае следует получать значение по адресу)
	Подсказки: if constexpr
	*/
	{	//Например:

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
	Задание 2. Реализуйте шаблон функции вывода на печать значений элементов любого
	адаптера (stack, queue, priority_queue)
	Подсказки: if constexpr, is_same
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
	Задание 3. Реализуйте шаблон функции сложения двух значений.
	Если первое слагаемое является вектором, то все элементы вектора нужно увеличить
	на значение второго параметра. При этом элементы вектора и второй параметр должны быть
	одного и того же типа.
	Подсказки: if constexpr, is_same
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
	Задание 4. variadic template – функция. Свертка pack-а параметров
	Реализуйте функцию, которая умеет печатать любое количество параметров любого типа,
	испоьзуя a) variadic template, b) свертку.
	*/
	{	//Например: 

		

		MyPrint(4, 8.8, (int)A(1), std::string("dfg"));  //a)
			std::cout << "- - -" << std::endl;

		MyPrint2(4, 8.8, A(42), std::string("dfg"));  //b)
			std::cout << "- - -" << std::endl;
	}

	/******************************************************************************/
	/*
	Задание 5. Удалите из vector (list, deque) все элементы, значения которых совпадают
	с элементами pack-а.
	*/
	{
		std::vector<int> v = { 1,2,3,1,4,1,5 };
		EraseAll(v, 1, 4);

		std::list<int> l = { 1,2,3,1,4,1,5 };
		EraseAll(l, 1, 4);		

	}

	/******************************************************************************/
	/*
	Задание 6. Попытка вставки нескольких элементов в set – try_insertAll()
	Функция должна принимать любое количество элементов для вставки и пытаться их вставить в set.
	Если удалось вставить все требуемые значения, функция возвращает true, иначе false.
	*/
	{   //Например:

		std::set<int> my_set{ 1, 2, 3 };
		bool b1 = try_insert_all(my_set, 4, 5, 6); // Вставляет все элементы.
													 // Возвращает true
		bool b2 = try_insert_all(my_set, 7, 8, 2); // Вставляет 7, 8.
													 // Возвращает false, поскольку 2 уже присутствует
		;
	}

	/******************************************************************************/
	/*
	Задание 7. Проверка попадания всех параметров в заданный диапазон
	Напишите функцию InRange() таким образом, чтобы:
	*/
	{
		bool b1 = InRange(10, 20, 1, 15, 30);		// --> false
		bool b2 = InRange(10, 20, 11, 12, 13);		// --> true
		bool b3 = InRange(5.0, 5.5, 5.1, 5.2, 5.3);	// --> true
		
	}

	/******************************************************************************/

	

	//Задание 8. std::tuple
	//Создайте класс book (автор, заглавие, год издания...). 
	//Создайте библиотеку таким образом, чтобы книги хранились в упорядоченном виде.
	//Чтобы упорядочить совокупность книжек, нужно сформировать условие сравнения, то есть
	//перегрузить, например operator<. При реализации оператора хочется сформировать условие
	//с учетом всех данных!!! 

	//Подсказка: Для упорядочения удобно использовать шаблон std::tuple,
	//так как для std::tuple перегружены операторы ==,!=,<,<=,>,>=
	//,которые сравнивают два кортежа лексиграфически (в порядке следования членов).

	//Для проверки распечатайте библиотеку
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

	//Задание 9. shared_ptr и weak_ptr+
	//Создаем генеалогическое дерево посредством класса human. В классе хранятся:
	//имя - string
	//возможно признак: жив или уже нет...
	//родители - shared_ptr (родители не всегда известны...)
	//дети - контейнер из weak_ptr (чтобы избежать циклических зависимостей)

	//Методы класса human:
	//конструктор - для инициализации имени и признака
	//конструктор копирования, оператор присваивания, move ???
	//статический метод child() - 
	//				должен создать создать и вернуть обертку для родившегося человека
	//				+ сформировать все связи ребенка с родителями и наоборот

	//Ввести возможность распечатать генеалогическое дерево для указанного индивидума
	{
		//История должна с кого-то начинаться => "Жили-были дед да баба, например, Адам и Ева"
		//(то есть на самом деле два деда и две бабы):


		//std::shared_ptr<human> grandM1(new human("Eva"));
		//...

		//у них появились дети - child():


		//а у детей в свою очередь свои дети:


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