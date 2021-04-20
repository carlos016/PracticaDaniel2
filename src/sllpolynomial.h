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
SllPolynomial::SllPolynomial(const vector_t<double>& v, const double eps):

sll_t<pair_double_t>()

{

  for(int i{v.get_size() - 1}; i > -1; i--){
    if(IsNotZero(v[i], eps)){
      pair_double_t pair_aux (v[i],i);
      push_front(new SllPolyNode (pair_aux));
    }
  }
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
  SllPolyNode* aux{get_head()};
  while(aux != NULL){
    result += aux->get_data().get_val() * pow(x, aux->get_data().get_inx());
    aux = aux->get_next();
  }
  return result;
}

// Comparación si son iguales dos polinomios representados por listas simples
bool SllPolynomial::IsEqual(const SllPolynomial& sllpol,
			    const double eps) const {
  bool differents = false;
  int aux_size1{0};
  int aux_size2{0};
  SllPolyNode* aux{get_head()};
  while(aux != NULL){
    aux_size1++;
    aux = aux->get_next();
  }
  aux = sllpol.get_head();
  while(aux != NULL){
    aux_size2++;
    aux = aux->get_next();
  }
  if(aux_size1 != aux_size2){
    differents = true;
  }
  else{
    aux = get_head();
    SllPolyNode* aux2{sllpol.get_head()};
    while(aux != NULL && aux2 != NULL){
      //inicializo valores de aux 1
      double coef1{aux->get_data().get_val()};
      int index1{aux->get_data().get_inx()};
      //inicializo valores de aux 2
      double coef2{aux->get_data().get_val()};
      int index2{aux->get_data().get_inx()};

      if(index1 == index2 && coef1 == coef2){
        aux = aux->get_next();
        aux2 = aux2->get_next();
      }
      else{
        aux = NULL;
        aux2 = NULL;
        differents = true;
      }
    }
  }

  return !differents;
}

// FASE IV
// Generar nuevo polinomio suma del polinomio invocante mas otro polinomio
void SllPolynomial::Sum(const SllPolynomial& sllpol, SllPolynomial& sllpolsum, const double eps) {

  SllPolyNode* aux{get_head()};
  SllPolyNode* aux2{sllpol.get_head()};
  int contadorAux{0};
  int contadorAux2{0};
  //Contamos la cantidad de elementos de cada lista
  while (aux != NULL){
    contadorAux++;
    aux = aux->get_next();
  }

  while (aux2 != NULL){
    contadorAux2++;
    aux2 = aux2->get_next();
  }
  //Creamos los vectores donde se almacenaran los elementos de la lista
  vector_t<pair_t<double> > vectorSll(contadorAux);
  vector_t<pair_t<double> > vectorSll2(contadorAux2);
  //Rellenamos los vectores
  aux = get_head();
  for(int i{0}; i < vectorSll.get_size(); i++){
    pair_t<double> parAux (aux->get_data().get_val(), aux->get_data().get_inx());
    vectorSll[i] = parAux;
    aux = aux->get_next();
  }

  aux2 = sllpol.get_head();
  for(int i{0}; i < vectorSll2.get_size(); i++){
    pair_t<double> parAux2 (aux2->get_data().get_val(), aux2->get_data().get_inx());
    vectorSll2[i] = parAux2;
    aux2 = aux2->get_next();
  }

  //Realizamos la suma
  bool introducido = false;
  for(int i{0}; i < vectorSll.get_size(); i++){
    for(int j{0}; j < vectorSll2.get_size(); j++){
      if(vectorSll[i].get_inx() == vectorSll2[j].get_inx()){
        pair_double_t parAux(vectorSll[i].get_val() + vectorSll2[j].get_val(), vectorSll[i].get_inx());
        sllpolsum.push_front(new SllPolyNode (parAux));
        introducido = true;
      }
    }
    if(!introducido){
      pair_double_t parAux(vectorSll[i].get_val(), vectorSll[i].get_inx());
      sllpolsum.push_front(new SllPolyNode (parAux));
    }
  }

  introducido = false;
  int indice = -1;
  SllPolyNode* aux3 = sllpolsum.get_head();

  for(int i{0}; i < vectorSll2.get_size(); i++){
    introducido = false;
    while(aux3 != NULL){
      if(aux3->get_data().get_inx() == vectorSll2[i].get_inx()){
        introducido = true;
        indice = i;
      }
      aux3 = aux3->get_next();
    }
    if(!introducido){
      pair_double_t parAux(vectorSll2[indice].get_val(), vectorSll2[indice].get_inx());
      sllpolsum.push_front(new SllPolyNode (parAux));
    }
    aux3 = sllpolsum.get_head();
  }

  /*introducido = false;
  int indice = -1;
  SllPolyNode* aux3 = sllpolsum.get_head();
  while(aux3 != NULL){
    introducido = false;
    for(int i{0}; i < vectorSll2.get_size(); i++){
      if(aux3->get_data().get_inx() == vectorSll2[i].get_inx()){
        introducido = true;
        indice = i;
      }
    }
    if(!introducido){
      pair_double_t parAux(vectorSll2[indice].get_val(), vectorSll2[indice].get_inx());
      sllpolsum.push_front(new SllPolyNode (parAux));
    }
    aux3 = aux3->get_next();
  }*/

}

#endif  // SLLPOLYNOMIAL_H_
