#include <iostream>
#include <math.h>
#define M_PI 3.1415926535
#include <vector>
#include <cstdio>
#include <random>
#include <functional>
using namespace std;

random_device rd;
mt19937 gen(rd());

ostream& operator << (ostream& o, vector<double>v) {
	for (auto e : v) {
		o << e << ",";
	}
	return o;
}

vector<double> hill_climbing(function<double(vector<double>)> f, function<bool(vector<double>)> f_domain, vector<double> p0, int iterations)
{
	auto p = p0;
	uniform_int_distribution<> distrib(0, p.size() - 1);
	uniform_real_distribution<> distrib_r(-0.1, 0.1);

	if (!f_domain(p)) throw std::invalid_argument("The p0 point must be in domain");
	for (int i = 0; i < iterations; i++) {
		auto p2 = p;
		p2[distrib(gen)] += distrib_r(gen);
		if (f_domain(p2)) {
			double y2 = f(p2);
			if (y2 < f(p)) {
				p = p2;
			}
		}
	}
	return p;
}

vector<double> simulated_annealing(function<double(vector<double>)> f,function<bool(vector<double>)> f_domain,vector<double> p0,int iterations,function<vector<double>(vector<double>)> N,function<double(int)> T)
{
	auto s_current = p0;
	auto s_global_best = p0;

	uniform_real_distribution<> u_k(0.0, 1.0);

	if (!f_domain(s_current)) throw std::invalid_argument("The p0 point must be in domain");

	for (int k = 0; k < iterations; k++) {
		auto s_next = N(s_current);
		if (f(s_next) < f(s_current)) {
			s_current = s_next;
		}
		else {
			double u = u_k(gen);
			if (u < exp(-abs(f(s_next) - f(s_current)) / T(k))) {
				s_current = s_next;
			}
			else {

			}
		}
		if (f(s_current) < f(s_global_best)) {
			s_global_best = s_current;
		}
		cout << s_current << " " << f(s_current) << endl;
	}
	return s_global_best;
}



auto boothFunction = [](vector <double> v) {
	double x = v.at(0);
	double y = v.at(1);
	double results;
	results = pow((x + (2 * y) - 7), 2) + pow(((2 * x) + y - 5), 2);
	return results;
};

auto leviFunction = [](vector<double> v) {
	double x = v.at(0);
	double y = v.at(1);
	double results;
	results = pow(sin(3 * M_PI * x), 2) + pow((x - 1), 2) * (1 + pow(sin(3 * M_PI * y), 2)) + pow((y - 1), 2) * (1 + pow(sin(2 * M_PI * y), 2));
	return results;
};

auto levi_domain = [](vector<double> v) {
	return (abs(v[0]) <= 10) && (abs(v[1]) <= 10);
};
auto booth_domain = [](vector<double> v) {
	return (abs(v[0]) <= 10) && (abs(v[1]) <= 10);
};



int main() {
	using namespace std;
	vector <double> numbers;
	int wybor;
	int iteracje;
	uniform_real_distribution<> distrib_r(-10, 10);
	cout << "Wybierz funkcje optymalizacyjna:" << endl << " 1. hill climbing" << endl << " 2. simulated annealing " << endl;
	cin >> wybor;

	auto function1 = [](vector<double> v) {
		return 100 - (v[0] * v[0] + v[1] * v[1]);
	};

	switch (wybor)
	{
	case 1:
	{
		cout << "Wybierz test:" << endl << " 1. Booth" << endl << " 2. Levi " << endl;
		cin >> wybor;
		switch (wybor)
		{
		case 1: {
			cout << "Podaj ilosc iteracji" << endl;
			cin >> iteracje;

			vector<double> booth_p0 = { distrib_r(gen),distrib_r(gen) };
			auto result = hill_climbing(boothFunction, booth_domain, booth_p0, iteracje);
			cout << "(" << result << ") = " << boothFunction(result) << endl;
			return 0;
			break;}
		case 2: {
			cout << "Podaj ilosc iteracji" << endl;
			cin >> iteracje;
			vector<double> levi_p0 = { distrib_r(gen),distrib_r(gen) };
			auto result = hill_climbing(leviFunction, levi_domain, levi_p0, iteracje);
			cout << "(" << result << ") = " << leviFunction(result) << endl;
			return 0;
			break;
		}
		default: {
			cout << "error" << endl;
			return 0;
			break;
		}
		}
	}
	case 2: {
		cout << "Wybierz test:" << endl << " 1. Booth" << endl << " 2. Levi " << endl;
		cin >> wybor;
		switch (wybor)
		{
		case 1: {
			cout << "Podaj ilosc iteracji" << endl;
			cin >> iteracje;
			vector<double> booth_p0 = { distrib_r(gen),distrib_r(gen) };
			auto result = simulated_annealing(boothFunction, booth_domain, booth_p0, iteracje, [](auto p) {
				normal_distribution<double> n(0.0, 0.3);
				for (auto& e : p) {
					e = e + n(gen);
				}
				return p;
			},
				[](int k) { return 1000.0 / k; });
				cout << "(" << result << ") = " << boothFunction(result) << endl;
				return 0;
				break;
				}
		case 2: {
			cout << "Podaj ilosc iteracji" << endl;
			cin >> iteracje;
			vector<double> levi_p0 = { distrib_r(gen),distrib_r(gen) };
			auto result = simulated_annealing(leviFunction, levi_domain, levi_p0, iteracje, [](auto p) {
				normal_distribution<double> n(0.0, 0.3);
				for (auto& e : p) {
					e = e + n(gen);
				}
				return p;
				},
				[](int k) { return 1000.0 / k; });
			cout << "(" << result << ") = " << leviFunction(result) << endl;
			return 0;
			break;
		}
		default: {
			cout << "error" << endl;
			return 0;
			break;
		}
		}

	default: {
		cout << "error" << endl;
		return 0;
		break;
	}}
	}
}
