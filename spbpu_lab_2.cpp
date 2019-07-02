//============================================================================
// Name				 : spbpu_lab_2.cpp
// Author			 : Mikhail Domchenkov
// Version		 :
// Copyright	 : copyright Mikhail Domchenkov, 2019
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <list>
#include <iterator>
#include <cstdint>
#include <climits>
#include <memory>
#include <typeinfo>
using namespace std;

#include "cycled_queue.h"
#include "my_unique_ptr.h"

constexpr unsigned factorial(unsigned i) {
	return (i == 1) ? 1 : i * factorial(i - 1);
}

constexpr unsigned _pow(unsigned v, unsigned p) {
	return (p == 0) ? 1 : v * _pow(v, p - 1);
}

constexpr unsigned str_len(const char* str) {
	return (*str == '\0') ? 0 : 1 + str_len(str + 1);
}

constexpr int bint_from_str(const char* str, unsigned d) {
	return (*str == '\0') ? 0 : (*str == '0') ? bint_from_str(str + 1, d - 1) : _pow(2, d) + bint_from_str(str + 1, d - 1);
}

constexpr int operator""_from_binary(const char* str) {
	return bint_from_str(str, str_len(str));
}

std::string operator""_toBinStr(unsigned long long val) {
	unsigned long long bin = 0;
	for (size_t i = 0u; i < (sizeof(val)*CHAR_BIT -1); ++i)
		bin += (val & (1<<i)) ? _pow(10, i) : 0;
	return std::string("0b")+std::to_string(bin);
}
std::string operator""_toBinStr_1(unsigned long long val) {
	std::string res("0b");
	
	for (long long i = sizeof(val)*CHAR_BIT - 1; i >=0; --i)

	{
		res.push_back(((val & (1l<<i)) ? 1 : 0));
		//val >>= 1;
	}
	return res;
}
constexpr int bint_from_str_1(const char* str, unsigned d) {
	return (*str == '\0') ? d : bint_from_str_1(str + 1,(d <<1) | (*str-'0'));
}
constexpr int operator""_from_binary_1(const char* str) {
	return bint_from_str(str, 0);
}


std::unique_ptr<std::string> operator~(std::unique_ptr<std::string>& p){
	*p += "_1";
	return std::move(p);
}


template <typename T> 
 class CC {
 public:
	 constexpr CC() :
		 min(std::numeric_limits<T>::min()),
		 max(std::numeric_limits<T>::max()) {}
	 constexpr CC(const T min_, const T max_) :
		 min(min_), max(max_) {}
	 constexpr T get_min() const { return min; }
	 constexpr T get_max() const { return max; }
	 constexpr bool in_range(const T& val) const {return (val >= min && val <= max); }
   constexpr T get_in_range(const T& val) const {return (in_range(val))?val:
     (val < min)? min: max;}
 private:
	 const T min;
	 const T max;
};


int main() {

	std::cout << "-init-" << std::endl;

	//Задание 1. Сырые строковые литералы (Raw String Literals)
	//Выведите строку, например: my name is "Marina"
	//а) без использования Raw String Literals
	//б) посредством Raw String Literals
	//в) добавьте разделители (Delimeter)

	{

		std::cout << "my name is \"Marina\"" << std::endl;
		std::cout << R"(my name is "Marina")" << std::endl;
		std::cout << R"moo(my name is "Marina")moo" << std::endl;

	}
  std::cout << "- - -" << std::endl;
	//////////////////////////////////////////////////////////////////////////////////////////////
	//Задание 2. Реализуйте вычисление факториала с помощью constexpr-функции.
	//
	//Подсказки/напоминания: 
	//		- constexpr – функция должна состоять из единственной инструкции return <выражение>; (пока!)
	//		- но это выражение может включать вызов другой constexpr – функции, в частности рекурсивный
	//			вызов 
	//		- если параметр рекурсивной constexpr- функции - это константа, компилятор вычислит результат
	//			на этапе компиляции

	//Проверьте тот факт, что компилятор вычисляет значение на этапе компиляции (если в качестве
	//				параметра используется константа, известная компилятору на этапе компиляции).
	//				Для проверки достаточно создать встроенный массив с размерностью, вычисляемой
	//				посредством constexpr-функции:

	std::cout << factorial(5) << std::endl;

	{	//Например:
		int ar[factorial(3)];

		//или
		constexpr int n = factorial(5);
		int ar1[n];

		//попробуйте:
		int m = 7;
		//constexpr int n1 = factorial(m);
		//int ar1[n1];

		//а так?
		int n2 = factorial(m);
	}
  std::cout << "- - -" << std::endl;
	//////////////////////////////////////////////////////////////////////////////////////////////
	//Задание 3a. Перевод с помощью пользовательского литерала из двоичного представления строкового
	//в значение, например: строку "100000000" -> в значение 256
	//Проверить результат посредством префикса 0b
	//Чтобы вызов пользовательского литерала выглядел просто и читаемо, например: 100000000_b
	//логично использовать пользовательский литерал с единственным параметром - const char*

	//Так как речь идет о литералах, логично вычислять значения на этапе компиляции
	// => реализуйте пользовательский литерал посредством constexpr - функций
	//Подсказка/напоминание: 
	//		- constexpr – функция должна состоять из единственной инструкции return <выражение>;
	//		- но это выражение может включать вызов другой constexpr – функции,
	//		- которая может быть рекурсивной (если параметр такой функции - это константа,
	//			компилятор вычислит результат вызова рекурсивной функции на этапе компиляции)

	{

		constexpr auto i = 100000000_from_binary;
		std::cout << i << std::endl;


	}
  std::cout << "- - -" << std::endl;
	//Задание 3b. Перевод в строковое двоичное представление, например: 256 -> "0b100000000"
	//Так как строка может быть любой длины, логичнее и проще возвращать объект std::string
	//=> возвращаемое значение не может быть constexpr!
	//Подсказка: манипулятора std::bin пока нет => преобразование в двоичную строку
	//придется делать вручную
	//Подсказка: количество разрядов в байте определяет константа CHAR_BIT - <cstdint>

	{
		std::string sBin= 15_toBinStr;

		std::cout << sBin << std::endl;
	}
  std::cout << "- - -" << std::endl;
	//////////////////////////////////////////////////////////////////////////////////////////////
	//Задание 4а. constexpr - объекты 
	//Создать класс (шаблон класса?) для хранения и манипулирования диапазоном значений.
	//В классе должны быть:
	//	переменные для хранения минимального и максимального значений,
	//	методы для получения каждого из значений
	//	метод для проверки - попадает ли указанное значение в диапазон
	//	метод, который получает любое значение данного типа и формирует результирующее значение:
	//							если принадлежит диапазону, то его и возвращаем
	//							если меньше минимального значения, возвращаем минимальное
	//							если больше максимального значения, возвращаем максимальное

	//Проверьте тот факт, что компилятор вычисляет значение на этапе компиляции. 
	//				Для проверки достаточно создать встроенный массив с размерностью, вычисляемой
	//				посредством constexpr-метода:
	{

		constexpr CC<int> cc{0,5};
    constexpr int min_ = cc.get_min();
    constexpr int max_ = cc.get_max();
    constexpr bool in_range = cc.in_range(4);
    constexpr auto check_in_range = cc.get_in_range(6);
    
    std::cout
      << "min = " << min_ << std::endl
      << "max = " << max_ << std::endl
      << "in_range = " << in_range << std::endl
      << "get_in_range = " << check_in_range << std::endl;
    
    int check[cc.get_max()];
	}
  
  std::cout << "- - -" << std::endl;

	//////////////////////////////////////////////////////////////////////////////////////////////
	//Задание 5. unique_ptr
	{

		//5.а - обеспечьте корректное выполнение фрагмента
		{
			std::vector<std::string*> v = { new std::string("aa"), new std::string("bb"), new std::string("cc") };
			//Распечатайте все строки

			for(const auto& p: v){
        std::cout << *p << std::endl;
      }

			for (auto p : v) {
				delete p;
			}
		}
    
    std::cout << "- - -" << std::endl;

		//5.b - модифицируйте задание 5.а:
		 //обеспечьте посредством std::unique_ptr: 
		 //эффективное заполнение (вспомните про разные способы формирования std::unique_ptr), 
		 //безопасное хранение указателей на динамически создаваемые объекты std::string, 
		 //манипулирование,
		 //и освобождение ресурсов
     
     using sptr = std::unique_ptr<std::string>;

	 std::vector<sptr> v;
	 v.reserve(3);
	 v.emplace_back(std::make_unique<std::string>("aa"));
	 v.emplace_back(std::make_unique<std::string>("bb"));
	 v.emplace_back(std::make_unique<std::string>("cc"));

		{
			//Распечатайте все строки
      for(const auto& p: v){
        std::cout << *p << std::endl;
      }

			//??? Уничтожение динамически созданных объектов?
	        //Уничтожатся автоматически
		} //???
    std::cout << "- - -" << std::endl;
		{//5.c - дополните задание 5.b добавьте возможность изменять хранящиеся строки
		 //следующим образом (например, добавить указанный суффикс: "AAA" -> "AAA_1")

			for (auto&& p : v) {
				p = std::move(~p); // Корректно ли?
        std::cout << *p << std::endl;
			}

		}

		{//5.d - динамический массив объектов	

		 //Создайте unique_ptr, который является оберткой для динамического массива
		 //с элементами std::string
		 //С помощью unique_ptr::operator[] заполните обернутый массив значениями
		 //Когда происходит освобождения памяти?

			std::unique_ptr<std::string[]> pstr(new std::string[3]);
			pstr[0] = "A";
			pstr[1] = "B";
			pstr[2] = "C";

		}

		{//5.e - массивы динамических объектов и пользовательская delete-функция (функтор)
		 //Задан стековый массив указателей на динамически созданные объекты
		 //Создайте unique_ptr для такого массива
		 //Реализуйте пользовательскую delete-функцию (функтор) для корректного 
		 //освобождения памяти

			std::string* arStrPtr[] = { new std::string("aa"), new std::string("bb"), new std::string("cc") };
			auto deleter = [arStrPtr](std::string* data)
			{
				for (int i = 0; i < sizeof(arStrPtr) / sizeof(std::string*); ++i) {
					delete arStrPtr[i];
				}
			};
			std::unique_ptr<std::string[], decltype(deleter)> pstr((std::string*)arStrPtr, deleter);

		}

    // TODO:
    
		{//5.f Создайте и заполните вектор, содержащий unique_ptr для указателей на std::string
			//Посредством алгоритмя copy() скопируйте элементы вектора в пустой список с элементами 
			//того же типа
			//Подсказка: перемещающие итераторы и шаблон std::make_move_iterator
        using upstr_t = std::unique_ptr<std::string> ;
        std::vector<upstr_t> v(3);
        v[0] = std::move(std::make_unique<std::string>("11"));
        v[1] = std::move(std::make_unique<std::string>("22"));
        v[2] = std::move(std::make_unique<std::string>("33"));
        
        std::list<upstr_t> l;
        std::copy(
          std::make_move_iterator(v.begin()),
          std::make_move_iterator(v.end()),
          std::inserter(l, l.begin())
        );
		}

	}

	////////////////////////////////////////////////////////////////////////////////
	//Задание 6.shared_ptr + пользовательская delete-функция 

	//Реализовать возможность записи в файл данных (строчек) из разных источников 
	//(для упрощения пусть источниками являются два массива)
	//Так как все "писатели" будут по очереди записывать свои данные в один и тот же файл,
	//логично предоставить им возможность пользоваться одним и тем же указателем FILE* =>
	//безопасной оберткой для такого указателя является shared_ptr
	//а. Первый владелец должен открыть/создать файл для записи
	//б. Все остальные писатели должны присоединиться к использованию
	//в. Последний владелец указателя должен закрыть файл

	//Подсказка: имитировать порядок записи можно с помощью функции rand()
	/*
	{

	//"писатели":
	//Создать writer1, writer2


	//например, источники данных:
	char ar1[] = "Writer1";
	char ar2[] = "Writer2";

	//заданное число итераций случайным образом позволяем одному из "писателей" записать в файл
	//свою строчку
	//Подсказка: строчки удобно записывать в файл посредством функции fputs()

	}//закрытие файла???

	*/

	std::cout << std::endl << "-fini-" << std::endl;
	std::cin.get();
	return 0;
}
