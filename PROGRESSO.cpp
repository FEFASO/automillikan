/*
 * PROGRESSO.cpp
 *
 *  Created on: 19/05/2012
 *      Author: F. Viviani Martins
 */

#include "PROGRESSO.h"

#include <iostream>
using namespace std;

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CONSTRUTORES E DESTRUTORES
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Dado Inicia um progresso
PROGRESSO::PROGRESSO(const char *mensagem, int progresso_total)
{
   this->clocks_ini = clock();               // Inicia a contagem de clocks
   this->progresso_total = progresso_total;  // Armazena progresso total o progresso atual
   this->dezena_anterior = 0;
   cout << mensagem << "0% . " << flush;
}

PROGRESSO::~PROGRESSO()
{
   ;
}
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// METODOS
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Dado o progresso atual, escreve na tela em porcentagem o quanto ja' foi feito do progresso
void PROGRESSO::atualiza(int progresso_atual)
{
   short dezena_atual = progresso_atual * 10 / this->progresso_total;
   if (dezena_atual > this->dezena_anterior) {
      cout << dezena_atual * 10 << "% . " << flush;
      ++this->dezena_anterior;
   }
}
// Finaliza um progresso
void PROGRESSO::finaliza()
{
   long double tempo_total = (long double) (clock() - this->clocks_ini) / (long double) CLOCKS_PER_SEC;
   cout << "Tempo total: ";
   if (tempo_total > 60.0)
      cout << tempo_total / 60.0 << " minutos" << endl << flush;
   else
      cout << tempo_total << " segundos" << endl << flush;
}
