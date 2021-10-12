#include <tuple>
#include <iostream>
#include <cstdlib>

auto func1 = [](int x){
    return x = 20 - abs(x); };
auto func2 = [](int i){
    int result;
    return result = (2 * (i%2) - 1)*i/2;
};

auto obliczenia = [](auto f1, auto f2, int n) {
    using namespace std;
    int max_x = f2(0);
    int max_y = f1(max_x);
    for (int i = 1; i < n; i++) {
        int x = f2(i);
        int y = f1(x);
        if (y > max_y) {
            max_x = x;
            max_y = y;
        }
    }
    return make_pair(max_x, max_y);
};


int main() {
    using namespace std;
    pair <int,int> result;
    result = obliczenia(func1, func2, 5);
    cout << result.first << " : " << result.second << endl;
}