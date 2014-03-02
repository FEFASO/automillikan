//============================================================================
// Name        : AutoMillikan.cpp
// Author      : F. Viviani Martins
// Copyright   : Your copyright notice
//============================================================================

#include "define.h"
#include <time.h>
#include "VIDEO.h"

int main() {
   //
   // Carrega videos dentro do diretorio DIR_VIDEOS
   VIDEO videos;
   //
   // Leitura da escada de processamento
   videos.leitura_infoProc();
   //
   // Imprime VIDEOs na tela
   videos.printf();
   //
   // Processamento das imagens dos videos
   time_t clocks_ini = clock();
   for (VIDEO *atual = videos.get_prx(); atual->get_nFrame() != CABECA ; atual = atual->get_prx()) {
      if (atual->get_infoProc(ANALISAR) == NAO)
         continue;
      cout << endl;
      cout << "Nome                          : " << atual->get_nome() << endl;
      cout << "Diretorio                     : " << atual->get_dir() << endl;
      atual->quebra_frames();
      atual->converte_cinza();
      atual->inicia_video();
      cout << "Numero de frames              : " << atual->get_nFrame() << endl;
      cout << "Dimensao das imagens          : " << atual->get_lrgIMAGEM() << " x " << atual->get_altIMAGEM() << endl;
      atual->filtro_menosmedia(1.0, 2.0);
      atual->filtro_limite();
      atual->identifica_gotas();
      atual->gotas_brancas();
      atual->rastrea_gotas();
      atual->determina_velocidades();
      //atual->salva();
      //atual->libera_memoria();
   }
   float tempo = (float) (clock() - clocks_ini) / (float) CLOCKS_PER_SEC;
   cout << "A analise do video demorou    : ";
   if (tempo >= 60.0)
      cout << tempo / 60.0 << " minutos" << endl;
   else
      cout << tempo << " segundos" << endl;
	return SUCESSO;
}
