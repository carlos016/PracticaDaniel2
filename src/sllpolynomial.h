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

  //SllPolynomial listaAux;

  sll_t<int> listaNodoAux;
  //Se suman de la lista los que tienen el mismo indice
  while(aux != NULL && aux2 != NULL){
    //aux2 = sllpol.get_head();
    //while(aux2 != NULL){
      if(aux->get_data().get_inx() == aux2->get_data().get_inx()){
        pair_double_t pair_aux ((aux->get_data().get_val() + aux2->get_data().get_val()), aux->get_data().get_inx());
        sllpolsum.push_front(new SllPolyNode (pair_aux));
        listaNodoAux.push_front(new sll_node_t<int> (aux->get_data().get_inx()));
        //listaAux.push_front(new SllPolyNode (pair_aux));
        aux = aux->get_next();
        aux2 = sllpol.get_head();
      }
      else{
        aux2 = aux2->get_next();
      }
    //}
  }
  std::cout << "Mira aquí a ver la suma: "; /*<< sllpolsum listaAux << "\n\n\n";*/
  listaNodoAux.write(std::cout);
  std::cout << "\n\n\n";

  sll_node_t<int>* puntNodoAux{listaNodoAux.get_head()};
  int contador = 0;
  //Se cuentan los nodos que se han sumado ya
  while (puntNodoAux != NULL){
    contador++;
    puntNodoAux = puntNodoAux->get_next();
  }
  //Se guarda un vector con los nodos que han sido sumados y añadidos
  vector_t<int> vectorNodoAux(contador);
  puntNodoAux = listaNodoAux.get_head();
  for(int i{0}; i < vectorNodoAux.get_size(); i++){
    vectorNodoAux[i] = listaNodoAux.pop_front()->get_data();
  }
  //std::cout << "LKOOOOOOO: " << vectorNodoAux;

  aux = get_head();
  aux2 = sllpol.get_head();

  /*while(aux != NULL && aux2 != NULL){
    for(int i{0}; i < vectorNodoAux.get_size(); i++){
      if(aux->get_data().get_inx() == vectorNodoAux[i]){
        sllpolsum.push_front(new SllPolyNode (pair_double_t (aux->get_data().get_val(), aux->get_data().get_inx())));
      }

      if(aux2->get_data().get_inx() == vectorNodoAux[i]){
        sllpolsum.push_front(new SllPolyNode (pair_double_t (aux2->get_data().get_val(), aux2->get_data().get_inx())));
      }
    }
    aux = aux->get_next();
    aux2 = aux2->get_next();
  }*/

    /*for(int i{0}; i < vectorNodoAux.get_size(); i++){
      if(puntNodoAux->get_data() == ){

      }
    }
    puntNodoAux = puntNodoAux->get_next();
  }*/

  //while(aux != NULL && aux2 != NULL){
    //for(int i{0} i < )
    //if(aux->get_da
  //}
}

#endif  // SLLPOLYNOMIAL_H_
