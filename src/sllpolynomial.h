// AUTOR:
// FECHA:
// EMAIL:
// VERSION: 2.0
// ASIGNATURA: Algoritmos y Estructuras de Datos
// PRÁCTICA Nº: 4
// ESTILO: Google C++ Style Guide
// COMENTARIOS:
//

#ifndef SLLPOLYNOMIAL_H_
#define SLLPOLYNOMIAL_H_

#include <iostream>
#include <math.h>  // fabs, pow

#include "pair_t.h"
#include "sll_t.h"
#include "vector_t.h"

#define EPS 1.0e-6

typedef pair_t<double> pair_double_t;  // Campo data_ de SllPolynomial
typedef sll_node_t<pair_double_t> SllPolyNode;  // Nodos de SllPolynomial

// Clase para polinomios basados en listas simples de pares
class SllPolynomial : public sll_t<pair_double_t> {
 public:
  // constructores
  SllPolynomial(void) : sll_t() {};
  SllPolynomial(const vector_t<double>&, const double = EPS);

  // destructor
  ~SllPolynomial() {};

  // E/S
  void Write(std::ostream& = std::cout) const;

  // operaciones
  double Eval(const double) const;
  bool IsEqual(const SllPolynomial&, const double = EPS) const;
  void Sum(const SllPolynomial&, SllPolynomial&, const double = EPS);
};


bool IsNotZero(const double val, const double eps = EPS) {
  return fabs(val) > eps;
}

// FASE II
// constructor
SllPolynomial::SllPolynomial(const vector_t<double>& v, const double eps) {

  std::cout << "\n\n\nAqui empieza el constructor odioso:\n\n\n";

  vector_t<pair_double_t> paresAux(v.get_size());
  vector_t<SllPolyNode> nodosAux(v.get_size());

/*  pair_double_t parAux;
  //SllPolyNode nodoAux(parAux);
  SllPolyNode nodoAux;

  sll_t<pair_double_t> listaAux;
*/
  for(int i{0}; i < v.get_size(); i++){
    /*std::cout << "\nIteración " << i << ": \n";
    parAux.set(v[i], i);
    std::cout << "Par rellenado: " << parAux << "\n";
    nodoAux.set_data(parAux);
    std::cout << "Nodo rellenado: ";
    nodoAux.write(std::cout);
    std::cout << "\n";*/

    std::cout << "\nIteración " << i << ": \n";
    paresAux[i].set(v[i], i);
    std::cout << "Pares rellenado: " << paresAux << "\n";
    nodosAux[i].set_data(paresAux[i]);
    std::cout << "Nodos rellenado: ";
    nodosAux[i].write(std::cout);
    std::cout << "\n";

    //push_front(&nodoAux);
    push_front(&nodosAux[i]);
    //listaAux.push_front(nodoAux);
  }
  std::cout << "\nAquí está la lista rellena: ";
  //listaAux.write(std::cout);
  std::cout << "\n";
  std::cout << "\n\n\nAqui termina el constructor odioso\n\n\n";
}


// E/S
void SllPolynomial::Write(std::ostream& os) const {
  os << "[ ";
  bool first{true};
  SllPolyNode* aux{get_head()};
  while (aux != NULL) {
    int inx{aux->get_data().get_inx()};
    double val{aux->get_data().get_val()};
    if (val > 0)
      os << (!first ? " + " : "") << val;
    else
      os << (!first ? " - " : "-") << fabs(val);
    os << (inx > 1 ? " x^" : (inx == 1) ? " x" : "");
    if (inx > 1)
      os << inx;
    first = false;
    aux = aux->get_next();
  }
  os << " ]" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const SllPolynomial& p) {
  p.Write(os);
  return os;
}


// Operaciones con polinomios

// FASE III
// Evaluación de un polinomio representado por lista simple
double SllPolynomial::Eval(const double x) const {
  double result{0.0};
  // poner el código aquí

  return result;
}

// Comparación si son iguales dos polinomios representados por listas simples
bool SllPolynomial::IsEqual(const SllPolynomial& sllpol,
			    const double eps) const {
  bool differents = false;
  // poner el código aquí

  return !differents;
}

// FASE IV
// Generar nuevo polinomio suma del polinomio invocante mas otro polinomio
void SllPolynomial::Sum(const SllPolynomial& sllpol,
			SllPolynomial& sllpolsum,
			const double eps) {
  // poner el código aquí

}


#endif  // SLLPOLYNOMIAL_H_
