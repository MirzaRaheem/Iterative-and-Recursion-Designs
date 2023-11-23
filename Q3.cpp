#include<iostream>
#include<iomanip>
#include <cstdlib> 
using namespace std;

// Function prototype
template <typename T>
void update_scale(T &m1, T &m2, T m3 = 10);

void print_real(float number, int fieldspace, int precision);

int main(void) {
    float a, b;
    cout << " Please input two real numbers: ";
    cin >> a >> b;

    print_real(a, 7, 3);
    print_real(b, 7, 3);

    // call the function update_scale with ONLY the actual parameters a and b
    update_scale(a, b);

    print_real(a, 7, 3);
    print_real(b, 7, 3);

    return 0;
}

// Function definition for print_real
void print_real(float number, int fieldspace, int precision) {
    cout << fixed << setprecision(precision) << setw(fieldspace) << number << endl;
}

// Function definition for update_scale
template <typename T>
void update_scale(T &m1, T &m2, T m3) {
    T original_m1 = m1;
    T original_m2 = m2;

    m1 = (original_m1 + original_m2) * m3;
    m2 = (original_m1 - original_m2) * m3;
}
