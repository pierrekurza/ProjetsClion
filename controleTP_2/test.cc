class Vect {
  int _x,_y;
public:
  Vect(int x, int y) {_x=x; _y=y;}
};
class A {
  Vect v;
public:
  // initialiser v à (10,10) en utilisant uniquement le constructeur
  A() { }
  // initialiser v à (20,20) en utilisant uniquement le constructeur
  void init() { }
};
class B {
  Vect v;
public:
  // initialiser v à (15,15) en utilisant une affectation
  B() { }
  // initialiser v à (25,25) en utilisant une affectation
  void init() { }
};
