#pragma once
#ifndef __LAB5_H__
#define __LAB5_H__

#include <functional>
#include <map>
#include <cmath>
#include <algorithm>

using namespace std::placeholders;

template<typename type>
constexpr type plus(type l, type r) {
	return l + r;
}

struct muld {
	constexpr double operator()(double l, double r) {
		return l * r;
	}
};

class calc{
 public:
	 double action(double l, char op, double r) {
		 if (ops.find(op) != ops.cend()) {
			 return ops[op](l, r);
		 }
		 return 0; // or throw exception
	 }
	 double action_with_output(double l, char op, double r) {
		 double result = action(l, op, r);
		 std::cout 
			 << l << " " 
			 << op << " " 
			 << r << " = " 
			 << result << std::endl;
		 return result;
	 }

 private:
	 std::map<char, std::function<double(double, double)>> ops =
	{ 
		{'+', plus<double>},
		{'-', std::minus()},
		{'*', muld()},
		{'/',[](double l, double r) {return l / r; }},
		{'^', std::powf},
		{'%', std::bind(std::remainderf, _1, _2)},
		{'?', std::bind(&calc::max, this, _1, _2)}
	};

	 double max(double l, double r) {
		 return std::max(l, r);
	}
};


#endif // !__LAB5_H__