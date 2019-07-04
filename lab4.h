#pragma once
#ifndef __LAB4_HDR__
#define __LAB4_HDR__

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


struct A {
	A(int n) :
		m_n(n) {}
	operator int() { return m_n; }
	friend std::ostream& operator << (std::ostream& out, const A& a);
	int m_n;
};

std::ostream& operator << (std::ostream& out, const A& a) {
	out << a.m_n;
	return out;
}

//--- 1 ---//
template<typename T>
void PrintAnyCont(const T& c) {
	for (const auto& el : c) {
		if constexpr (std::is_pointer<std::decay<T>::type>::value) {
			std::cout << *el << std::endl;
		}
		else {
			std::cout << el << std::endl;
		}// !else
	}// !for
}// !PrintAnyCont

//--- 2 ---//
template<template <typename> typename Cont, typename Type>
void PrintAdapter(const Cont<typename Type>& cont) {
	struct inner_t : public Cont<typename Type> {
		using Cont<typename Type>::c;
	};// !struct
	const auto& inner = static_cast<const inner_t&>(cont).c;

	for (const auto& el : inner) {
		std::cout << el << std::endl;
	}// !for
}// !PrintAdapter

//--- 3 ---//
template <typename First, typename Second>
auto strange_sum(First& first, const Second& second) {
	if constexpr (std::is_same<std::decay<First>::type, std::vector<Second>>::value) {
		for (auto& i : first) { i += second; }
		return first;
	}
	else {
		return first + second;
	}// !else
}// !strange_sum


//--- 4 ---//
template<typename Current, typename... Args>
void MyPrint(const Current& current, Args... args) {
	std::cout << current << std::endl;
	MyPrint(args...);
}

void MyPrint() {

}

template<typename... Args>
void MyPrint2(const Args& ... args) {
	((std::cout << args << std::endl), ...);
}

//--- 5 ---//
template <typename C, typename Current, typename... Args>
void EraseAll(C& cont, Current current, Args... args) {
	auto it = std::remove_if(std::begin(cont), std::end(cont), [&current](const auto& val) {return val == current; });
	cont.erase(it, std::end(cont));

	EraseAll(cont, args...);
}

template<typename C>
void EraseAll(C& cont) {
	// stub
}

//--- 6 ---//
template< typename Set, typename Current, typename... Args>
bool try_insert_all(Set& s, Current current, Args... args) {
	auto[i, r] = s.insert(current);
	return (r && try_insert_all(s, args...));
}

template<typename Set>
bool try_insert_all(Set& s) {
	return true;
}
//--- 7 ---//
template <typename Min, typename Max, typename Current, typename... Args>
bool InRange(Min min, Max max, Current cur, Args... args) {
	bool in_range = (cur >= min && cur <= max);
	return (in_range && InRange(min, max, args...));
}

template <typename Min, typename Max>
bool InRange(Min min, Max max) {
	return true;
}

//--- 8 ---//
template<typename Tuple, size_t N>
void print_tuple(const Tuple& t) {
	std::cout << std::get<N>(t) << std::endl;
	if constexpr (N > 0)
		print_tuple<Tuple, N - 1>(t);
}


template<typename... Args> struct book {

	void set(Args... args) {
		m_data = std::make_tuple(args...);
	}
	bool operator < (const book<Args...>& other) const {
		return (m_data < other.m_data);
	}
	void print() const {
		print_tuple<decltype(m_data), std::tuple_size<decltype(m_data)>::value - 1>(m_data);
	}

	std::tuple<Args...> m_data;
};

//--- 9 ---//

class human {
public:
	typedef  std::shared_ptr<human> human_ptr;

	//- ctor -//
	human(const std::string name_, bool alive_ = true) :
		name{ name_ }, alive{ alive_ }{}
	
	//- set_father -//
	void set_father(const human_ptr& f) {
		father = f;
	}
	
	//- set_mother -//
	void set_mother(const human_ptr& m) {
		mother = m;
	}

	//- add_child -//
	void add_child(const human_ptr& c) {
		if (c)
			childs.push_back(std::weak_ptr<human>(c));
	}

	//- kill / resurrect -//
	void operator ~() { alive = !alive; }
	
	//- create new child from two parents -//
	static human_ptr child(
		human_ptr father_,
		human_ptr mother_,
		const std::string& name_) {
		human_ptr ch{ new human{name_} };
		ch->set_father(father_);
		ch->set_mother(mother_);
		if (father_)
			father_->add_child(ch);
		if (mother_)
			mother_->add_child(ch);
		return ch;
	}

	//- recursive printing -//
	static void print(const human_ptr& top, size_t spaces = 0u) {
		if (top == nullptr)
			return;
		for (size_t i = 0; i < spaces; ++i) std::cout << "--";
		std::cout << "-> " << top->name << " : " << ((top->alive) ? "still alive" : "DEAD") << std::endl;
		if (!top->childs.empty()) {
			for (const auto& c : top->childs) {
				if (auto cc = c.lock()) {
					print(cc, spaces + 1u);
				}
			}// !for
		}// !if(empty)
	}// !print

	static void print_parents(const human_ptr& bottom, size_t spaces = 0u) {
		if (bottom == nullptr)
			return;

		for (size_t i = 0; i < spaces; ++i) std::cout << "--";
		std::cout << "-> " << bottom->name << " : " << ((bottom->alive) ? "still alive" : "DEAD") << std::endl;

		if (bottom->mother) {
			print_parents(bottom->mother, spaces + 1);
		}		
		if (bottom->father) {
			print_parents(bottom->father, spaces + 1);
		}
	}

	static void print_cow_with_moo() {
		std::string cow =			
R"(                  ________________________
         (__)    /                        \
         (oo)   (        Moooooooo!        )
  /-------\/  --'\________________________/
 / |     ||
*  ||----||
   ^^    ^^)";
		std::cout << cow << std::endl;
	}

private:
	std::string name;
	bool alive;
	human_ptr father;
	human_ptr mother;
	std::list<std::weak_ptr<human>> childs;
};






#endif // !__LAB4_HDR__