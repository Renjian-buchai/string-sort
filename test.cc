#include <iostream>
#include <typeinfo>

auto a(int x) {
  (void)(x);
  return typeid(x).name();
}

void b(int x) { x == 0; }

int main() { std::cout << a(1) << " " << typeid(int).name(); }