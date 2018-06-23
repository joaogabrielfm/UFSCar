#ifndef LANCHE_HPP
#define LANCHE_HPP

#include "Food.hpp"
#include "Pilha.hpp"
#include <SFML/Graphics.hpp>

class Lanche : public Pilha {
  public:
    Lanche( const int tamanho );

    bool faltaApenasPaoSuperior() const;

    void setPosition( float x, float y );

  private:
    int tamanhoMaximo;
};

#endif