/*
 * define.cpp
 *
 *  Created on: 18/05/2012
 *      Author: F. Viviani Martins
 */

#include "define.h"
//
// FUNCOES
//
// Dado 'n', aloca 'n' bytes de memoria e devolve o ponteiro para ela. Caso haja falta de memoria, finaliza o programa
void *malloc_void(int n)
{
   if (n == 0)
      return NULL;
   void *p;
   p = malloc(n);
   if (p == NULL) {
      cout << endl << "ERRO_MEMORIA <> nao e' possivel alocar mais memoria" << endl;
      exit(ERRO_MEMORIA);
   }
   return p;
}
// Dado 'dir', verifica se o diretorio 'dir' existe, retornando 0 em caso positivo e 1 caso negativo
short verifica_dir(string dir)
{
   if (dir[dir.length()-1] == '/')
      dir = dir.substr(0, dir.length() - 1);
   string str;       // Manipula strings
   char c;
   FILE *arq;
   str = "ls ";
   c = dir.find_last_of('/');
   if ((int) c > 0 && (unsigned int) c < dir.length()) {
      str += dir.substr(0, (int) c);
      dir = dir.substr(((int) c) + 1, dir.length());
   }
   str += " | grep -w " + dir + " | wc -l > temp.verifica_dir.at";
   system(str.c_str());
   arq = fopen("temp.verifica_dir.at", "r");
   if (arq == NULL) {
      cout << "ERRO_LOGICA <> verifica_dir() > nao foi possivel abrir o arquivo temp.verifica_dir.at" << endl;
      exit(ERRO_LOGICA);
   }
   c = fgetc(arq);
   fclose(arq);
   system("rm temp.verifica_dir.at*");
   if (c == '0')
      return 1; // Nao existe
   return 0; // Existe
}
// Dados dois pares, calcula e devolve a distancia entre eles
float distancia(PAR c1, PAR c2)
{
   return sqrt(pow(c1.x - c2.x, 2) + pow(c1.y - c2.y, 2));
}
// Dados dois pares, devolve true caso eles sejam iguais e false caso contrario
bool igual(PAR c1, PAR c2)
{
	if (c1.x == c2.x && c1.y == c2.y)
		return true;
	return false;
}
