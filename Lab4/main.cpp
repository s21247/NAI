#include <chrono>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <random>
#include <tuple>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

pair<unsigned long long int, unsigned long long int> convertToPair(vector<int> vektor) {
    unsigned long long int x = 0;
    unsigned long long int y = 0;
    for (int i = 0; i < 64; i++) {
        if (vektor[i] == 1)
            x += pow(2.0, i);
    }
    for (int i = 64; i < vektor.size(); i++) {
        if (vektor[i] == 1)
            y += pow(2.0, i - 64);
    }
    return { x, y };
}

vector<int> convertToVector(pair<unsigned long long int, unsigned long long int> numbers) {
    vector<int> result = {};
    unsigned long long int one = numbers.first;
    unsigned long long int two = numbers.second;

    do {
        result.push_back(one % 2);
        one /= 2;
    } while (one != 0);
    do {
        result.push_back(two % 2);
        two /= 2;
    } while (two != 0);
    return result;
}

double  fitness(pair<int, int> firstPoint, pair<int, int> secondPoint) {
    return sqrt((secondPoint.first - firstPoint.first) * (secondPoint.first - firstPoint.first) + (secondPoint.second - firstPoint.second) * (secondPoint.second - firstPoint.second));
}

vector<int> generateRandomVector(int n) {
    vector<int> vec = {};
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        int randomNumber = rand() % 2;
        vec.push_back(randomNumber);
    }
    return vec;
}

int main() {
    vector <int> numbers = generateRandomVector(128);
    pair<unsigned long long int, unsigned long long int>para = convertToPair(numbers);
    cout << para.first << endl;
    cout << para.second << endl;
    cout << "Wektory" << endl;
    vector<int> vec2 = convertToVector({ 15,10 });
    for (int i = 0; i < vec2.size(); i++) {
        cout << vec2[i] << endl;
    }
    cout << "Dystans" << endl;
    cout << fitness({ 1,1 }, { 2,2 });
}
