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

	//������� 1. ����� ��������� �������� (Raw String Literals)
	//�������� ������, ��������: my name is "Marina"
	//�) ��� ������������� Raw String Literals
	//�) ����������� Raw String Literals
	//�) �������� ����������� (Delimeter)

	{

		std::cout << "my name is \"Marina\"" << std::endl;
		std::cout << R"(my name is "Marina")" << std::endl;
		std::cout << R"moo(my name is "Marina")moo" << std::endl;

	}
  std::cout << "- - -" << std::endl;
	//////////////////////////////////////////////////////////////////////////////////////////////
	//������� 2. ���������� ���������� ���������� � ������� constexpr-�������.
	//
	//���������/�����������: 
	//		- constexpr � ������� ������ �������� �� ������������ ���������� return <���������>; (����!)
	//		- �� ��� ��������� ����� �������� ����� ������ constexpr � �������, � ��������� �����������
	//			����� 
	//		- ���� �������� ����������� constexpr- ������� - ��� ���������, ���������� �������� ���������
	//			�� ����� ����������

	//��������� ��� ����, ��� ���������� ��������� �������� �� ����� ���������� (���� � ��������
	//				��������� ������������ ���������, ��������� ����������� �� ����� ����������).
	//				��� �������� ���������� ������� ���������� ������ � ������������, �����������
	//				����������� constexpr-�������:

	std::cout << factorial(5) << std::endl;

	{	//��������:
		int ar[factorial(3)];

		//���
		constexpr int n = factorial(5);
		int ar1[n];

		//����������:
		int m = 7;
		//constexpr int n1 = factorial(m);
		//int ar1[n1];

		//� ���?
		int n2 = factorial(m);
	}
  std::cout << "- - -" << std::endl;
	//////////////////////////////////////////////////////////////////////////////////////////////
	//������� 3a. ������� � ������� ����������������� �������� �� ��������� ������������� ����������
	//� ��������, ��������: ������ "100000000" -> � �������� 256
	//��������� ��������� ����������� �������� 0b
	//����� ����� ����������������� �������� �������� ������ � �������, ��������: 100000000_b
	//������� ������������ ���������������� ������� � ������������ ���������� - const char*

	//��� ��� ���� ���� � ���������, ������� ��������� �������� �� ����� ����������
	// => ���������� ���������������� ������� ����������� constexpr - �������
	//���������/�����������: 
	//		- constexpr � ������� ������ �������� �� ������������ ���������� return <���������>;
	//		- �� ��� ��������� ����� �������� ����� ������ constexpr � �������,
	//		- ������� ����� ���� ����������� (���� �������� ����� ������� - ��� ���������,
	//			���������� �������� ��������� ������ ����������� ������� �� ����� ����������)

	{

		constexpr auto i = 100000000_from_binary;
		std::cout << i << std::endl;


	}
  std::cout << "- - -" << std::endl;
	//������� 3b. ������� � ��������� �������� �������������, ��������: 256 -> "0b100000000"
	//��� ��� ������ ����� ���� ����� �����, �������� � ����� ���������� ������ std::string
	//=> ������������ �������� �� ����� ���� constexpr!
	//���������: ������������ std::bin ���� ��� => �������������� � �������� ������
	//�������� ������ �������
	//���������: ���������� �������� � ����� ���������� ��������� CHAR_BIT - <cstdint>

	{
		std::string sBin= 15_toBinStr;

		std::cout << sBin << std::endl;
	}
  std::cout << "- - -" << std::endl;
	//////////////////////////////////////////////////////////////////////////////////////////////
	//������� 4�. constexpr - ������� 
	//������� ����� (������ ������?) ��� �������� � ��������������� ���������� ��������.
	//� ������ ������ ����:
	//	���������� ��� �������� ������������ � ������������� ��������,
	//	������ ��� ��������� ������� �� ��������
	//	����� ��� �������� - �������� �� ��������� �������� � ��������
	//	�����, ������� �������� ����� �������� ������� ���� � ��������� �������������� ��������:
	//							���� ����������� ���������, �� ��� � ����������
	//							���� ������ ������������ ��������, ���������� �����������
	//							���� ������ ������������� ��������, ���������� ������������

	//��������� ��� ����, ��� ���������� ��������� �������� �� ����� ����������. 
	//				��� �������� ���������� ������� ���������� ������ � ������������, �����������
	//				����������� constexpr-������:
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
	//������� 5. unique_ptr
	{

		//5.� - ���������� ���������� ���������� ���������
		{
			std::vector<std::string*> v = { new std::string("aa"), new std::string("bb"), new std::string("cc") };
			//������������ ��� ������

			for(const auto& p: v){
        std::cout << *p << std::endl;
      }

			for (auto p : v) {
				delete p;
			}
		}
    
    std::cout << "- - -" << std::endl;

		//5.b - ������������� ������� 5.�:
		 //���������� ����������� std::unique_ptr: 
		 //����������� ���������� (��������� ��� ������ ������� ������������ std::unique_ptr), 
		 //���������� �������� ���������� �� ����������� ����������� ������� std::string, 
		 //���������������,
		 //� ������������ ��������
     
     using sptr = std::unique_ptr<std::string>;

	 std::vector<sptr> v;
	 v.reserve(3);
	 v.emplace_back(std::make_unique<std::string>("aa"));
	 v.emplace_back(std::make_unique<std::string>("bb"));
	 v.emplace_back(std::make_unique<std::string>("cc"));

		{
			//������������ ��� ������
      for(const auto& p: v){
        std::cout << *p << std::endl;
      }

			//??? ����������� ����������� ��������� ��������?
	        //����������� �������������
		} //???
    std::cout << "- - -" << std::endl;
		{//5.c - ��������� ������� 5.b �������� ����������� �������� ���������� ������
		 //��������� ������� (��������, �������� ��������� �������: "AAA" -> "AAA_1")

			for (auto&& p : v) {
				p = std::move(~p); // ��������� ��?
        std::cout << *p << std::endl;
			}

		}

		{//5.d - ������������ ������ ��������	

		 //�������� unique_ptr, ������� �������� �������� ��� ������������� �������
		 //� ���������� std::string
		 //� ������� unique_ptr::operator[] ��������� ��������� ������ ����������
		 //����� ���������� ������������ ������?

			std::unique_ptr<std::string[]> pstr(new std::string[3]);
			pstr[0] = "A";
			pstr[1] = "B";
			pstr[2] = "C";

		}

		{//5.e - ������� ������������ �������� � ���������������� delete-������� (�������)
		 //����� �������� ������ ���������� �� ����������� ��������� �������
		 //�������� unique_ptr ��� ������ �������
		 //���������� ���������������� delete-������� (�������) ��� ����������� 
		 //������������ ������

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
    
		{//5.f �������� � ��������� ������, ���������� unique_ptr ��� ���������� �� std::string
			//����������� ��������� copy() ���������� �������� ������� � ������ ������ � ���������� 
			//���� �� ����
			//���������: ������������ ��������� � ������ std::make_move_iterator
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
	//������� 6.shared_ptr + ���������������� delete-������� 

	//����������� ����������� ������ � ���� ������ (�������) �� ������ ���������� 
	//(��� ��������� ����� ����������� �������� ��� �������)
	//��� ��� ��� "��������" ����� �� ������� ���������� ���� ������ � ���� � ��� �� ����,
	//������� ������������ �� ����������� ������������ ����� � ��� �� ���������� FILE* =>
	//���������� �������� ��� ������ ��������� �������� shared_ptr
	//�. ������ �������� ������ �������/������� ���� ��� ������
	//�. ��� ��������� �������� ������ �������������� � �������������
	//�. ��������� �������� ��������� ������ ������� ����

	//���������: ����������� ������� ������ ����� � ������� ������� rand()
	/*
	{

	//"��������":
	//������� writer1, writer2


	//��������, ��������� ������:
	char ar1[] = "Writer1";
	char ar2[] = "Writer2";

	//�������� ����� �������� ��������� ������� ��������� ������ �� "���������" �������� � ����
	//���� �������
	//���������: ������� ������ ���������� � ���� ����������� ������� fputs()

	}//�������� �����???

	*/

	std::cout << std::endl << "-fini-" << std::endl;
	std::cin.get();
	return 0;
}
