
#include "define.h"
#include "Video.h"
//#include "PROGRESSO.h"

// -----------------------------------------------------------------------------
// Inicia membros estáticos
short Video::nVideo = 0;

// -----------------------------------------------------------------------------
// Construtor e destrutor

Video::Video()
{
   char c;              // Caracter para leitura de arquivos
   string str;          // Manipula strings
   string dir;          // Armazena o nome de um diretorio
   FILE *arq;           // Aponta para o arquivo que sera' lido
   //
   // Verifica se o diretorio DIR_VIDEOS ja' existe
/*   if (verifica_dir(DIR_VIDEOS)) { // Caso DIR_VIDEOS nao tenha sido encontrado: cria DIR_VIDEOS e sai do programa
      str = "mkdir ";
      str += DIR_VIDEOS;
      system(str.c_str());
      cout << endl << "ERRO_LEITURA <> nao foi encontrados nenhum video em '" << DIR_VIDEOS << "'" << endl;
      exit(ERRO_LEITURA);
   }
   //
   // Cria da cabeca da lista de VIDEOs
   this->nome = this->extensao = this->dir = this->dirFrame = "";
   this->nFrame = this->lrgIMAGEM = this->altIMAGEM = this->nGotas = CABECA;
   this->vFrame = NULL;
   this->gotas = NULL;
   this->prx = this; // Inicia lista circular em uma so' direcao
   for (int estado = 0; estado < N_INFOPROC; ++estado)
      this->infoProc[estado] = NAO;
   this->ddp.valor = this->densidade_oleo.valor = this->humidade_relativa.valor = this->temperatuda.valor = CABECA;
   this->taxaframes = CABECA;
   //
   // Procurando videos em DIR_VIDEOS e os inserindos na lista
   str = "ls -l ";
   str += DIR_VIDEOS;
   str += " | grep drwx > temp.DIR_VIDEOS_2.at";
   system(str.c_str());
   arq = fopen("temp.DIR_VIDEOS_2.at", "r");
   if (arq == NULL) {
      cout << endl << "ERRO_LOGICA <> nao foi possivel abrir \"temp.DIR_VIDEOS_2.at\" em VIDEO::VIDEO()" << endl;
      exit(ERRO_LOGICA);
   }
   while ((c = fgetc(arq)) != EOF) {
      if (c == 'd') {
         for (short i = 0; i < 8; )
            if (fgetc(arq) == ' ')
               ++i;
         ;
         dir = "";
         while ((c = fgetc(arq)) != '\n')
            dir += c;
         FILE *arq2;
         str = "ls ";
         str += DIR_VIDEOS + dir;
         str += " | grep .avi > temp.DIR_VIDEOS_" + dir + ".at";
         system(str.c_str());
         str = "temp.DIR_VIDEOS_" + dir + ".at";
         arq2 = fopen(str.c_str(), "r");
         if (arq2 == NULL) {
            cout << endl << "ERRO_LOGICA <> nao foi possivel abrir \"temp.temp.DIR_VIDEOS_" << dir;
            cout << ".at\" em VIDEO::VIDEO()" << endl;
            exit(ERRO_LOGICA);
         }
         VIDEO *novo;
         while ((c = fgetc(arq2)) != EOF) {
            for (str = c; (c = fgetc(arq2)) != '\n'; str += c)
               ;
            novo = new VIDEO(DIR_VIDEOS + dir + "/", str);
            novo->prx = this->prx;
            this->prx = novo;
            nVideo++;
         }
         fclose(arq2);
         str = "rm temp.DIR_VIDEOS_" + dir + ".at*";
         system(str.c_str());
      }
   }
   fclose(arq);
   str = "rm temp.DIR_VIDEOS_2.at*";
   system(str.c_str());
   //
   // Verificao se videos foram encontrados
   if (this->prx == this) {
      cout << endl << "ERRO_LEITURA <> nao foram encontrados nenhum video em '" << dir << "'" << endl;
      exit(ERRO_LEITURA);
   }*/
}

/*VIDEO::~VIDEO()
{
   //
   // Armazena as informacoes de escada de processamento de cada VIDEO carregado
   this->escreve_infoProc();
}
// Dado o diretorio e o nome de um video dentro computador, cria um objeto VIDEO referente
VIDEO::VIDEO(string dir, string nome)
{
   //
   // Verifica se 'nome' e' valido para um video
   int n = nome.find(".avi");
   if (n > (int) nome.length() || n <= 0) {
      cout << "ERRO_LOGICA <> VIDEO::VIDEO(string, string) > o 'nome' do video \"" << nome;
      cout << "\" e' invalido" << endl;
      exit(ERRO_LOGICA);
   }
   //
   // Armazenando informacoes dadas e iniciando os demais atributos do VIDEO envolvido
   this->nome = nome.substr(0, n);
   this->extensao = nome.substr(n, nome.length());
   this->dir = dir;
   this->dirFrame = this->dir + this->nome + "_" + DIR_FRAMES;;
   this->nFrame = 0;
   this->vFrame = NULL;
   this->gotas = new GOTA_VIDEO();
   this->lrgIMAGEM = this->altIMAGEM = this->nGotas = 0;
   this->prx = NULL;
   for (int estado = 0; estado < N_INFOPROC; ++estado)
      this->infoProc[estado] = NAO;
   this->infoProc[ANALISAR] = SIM;
   this->leitura_dadosAdicionais();
}
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ESCADA DE PROCESSAMENTO
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A partir do arquivo ARQ_INFOPROC, adquiri as informacoes de processamento dos VIDEOs
void VIDEO::leitura_infoProc()
{
   //
   // Verifica se foi utilizada a CABECA da lista para a chamada desta funcao
   if (this->nFrame != CABECA) {
      cout << endl << "ERRO_LOGICA <> VIDEO::filtro_menosmedia(string) > o objeto envolvido nao e' a cabeca da lista" << endl;
      exit(ERRO_LOGICA);
   }
   //
   // Atualiza estado dos VIDEOs
   char c;              // Caractere para a leitura do arquivo 'arq'
   FILE *arq;           // Aponta para o arquivo ARQ_INFOPROC
   string str;          // Manipula strings
   VIDEO *atual;        // Aponta para o video que esta sendo lido
   string dir_video;    // Diretorio do VIDEO atual
   string nome_video;   // Nome do VIDEO atual
   str = DIR_VIDEOS;
   str += ARQ_INFOPROC;
   arq = fopen(str.c_str(), "r");
   if (arq == NULL)
      return;
   dir_video = "";
   nome_video = "";
   atual = NULL;
   while ((c = fgetc(arq)) != EOF) {
      if (c == '#') { // Caractere que indica novas informacoes
         dir_video = "";
         nome_video = "";
         atual = NULL;
      }
      else if (c == 'D') { // Lendo diretorio do video
         if (dir_video != "") {
            cout << endl << "ERRO_LEITURA <> VIDEO::VIDEO() > arquivo estado.txt e' inconsistente" << endl;
            exit(ERRO_LEITURA);
         }
         if ((c = fgetc(arq)) != ':') {
            cout << endl << "ERRO_LEITURA <> VIDEO::VIDEO() > arquivo estado.txt e' inconsistente" << endl;
            exit(ERRO_LEITURA);
         }
         while ((c = fgetc(arq)) != ';')
            dir_video += c;
      }
      else if (c == 'A') { // Lendo nome de arquivo
         if (nome_video != "") {
            cout << endl << "ERRO_LEITURA <> VIDEO::VIDEO() > arquivo estado.txt e' inconsistente" << endl;
            exit(ERRO_LEITURA);
         }
         if ((c = fgetc(arq)) != ':') {
            cout << endl << "ERRO_LEITURA <> VIDEO::VIDEO() > arquivo estado.txt e' inconsistente" << endl;
            exit(ERRO_LEITURA);
         }
         while ((c = fgetc(arq)) != ';')
            nome_video += c;
         // Procurando video com diretorio 'dir' e nomeArq 'str' na lista de videos carregados
         for (atual = this->prx; atual->nFrame != CABECA; atual = atual->prx)
            if (dir_video == atual->dir && nome_video == atual->nome + atual->extensao)
               break;
         if (atual->nFrame == CABECA) {
            cout << endl << "ERRO_LEITURA <> Nao foi possivel encontrar na lista o video encontrado em 'estado.txt' > ";
            cout << dir_video + nome_video << endl;
            exit(ERRO_LEITURA);
         }
      }
      else if (c == 'R') { // Lendo se o video devera' ser analisado
         if (atual == NULL) {
            cout << endl << "ERRO_LEITURA <> VIDEO::VIDEO() > arquivo estado.txt e' inconsistente" << endl;
            exit(ERRO_LEITURA);
         }
         if ((c = fgetc(arq)) != ':') {
            cout << endl << "ERRO_LEITURA <> VIDEO::VIDEO() > arquivo estado.txt e' inconsistente" << endl;
            exit(ERRO_LEITURA);
         }
         if ((c = fgetc(arq)) != SIM && c != NAO) {
            cout << endl << "ERRO_LEITURA <> VIDEO::VIDEO() > arquivo estado.txt e' inconsistente" << endl;
            exit(ERRO_LEITURA);
         }
         atual->infoProc[ANALISAR] = c;
      }
      else if (c == 'Q') { // Lendo se o video ja' foi quebrado em frames
         if (atual == NULL) {
            cout << endl << "ERRO_LEITURA <> VIDEO::VIDEO() > arquivo estado.txt e' inconsistente" << endl;
            exit(ERRO_LEITURA);
         }
         if ((c = fgetc(arq)) != ':') {
            cout << endl << "ERRO_LEITURA <> VIDEO::VIDEO() > arquivo estado.txt e' inconsistente" << endl;
            exit(ERRO_LEITURA);
         }
         if ((c = fgetc(arq)) != SIM && c != NAO) {
            cout << "ERRO_LEITURA <> VIDEO::VIDEO() > arquivo estado.txt e' inconsistente" << endl;
            exit(ERRO_LEITURA);
         }
         atual->infoProc[QUEBRADO] = c;
      }
      else if (c == 'C') { // Lendo se os frames do video ja' foram convertidos para a escala cinza
         if (atual == NULL) {
            cout << endl << "ERRO_LEITURA <> VIDEO::VIDEO() > arquivo estado.txt e' inconsistente" << endl;
            exit(ERRO_LEITURA);
         }
         if ((c = fgetc(arq)) != ':') {
            cout << endl << "ERRO_LEITURA <> VIDEO::VIDEO() > arquivo estado.txt e' inconsistente" << endl;
            exit(ERRO_LEITURA);
         }
         if ((c = fgetc(arq)) != SIM && c != NAO) {
            cout << endl << "ERRO_LEITURA <> VIDEO::VIDEO() > arquivo estado.txt e' inconsistente" << endl;
            exit(ERRO_LEITURA);
         }
         atual->infoProc[ESCALA_CINZA] = c;

      }
      else if (c == 'M') { // Lendo se o video ja' sofreu a aplicacao do filtro medio
         if (atual == NULL) {
            cout << endl << "ERRO_LEITURA <> VIDEO::VIDEO() > arquivo estado.txt e' inconsistente" << endl;
            exit(ERRO_LEITURA);
         }
         if ((c = fgetc(arq)) != ':') {
            cout << endl << "ERRO_LEITURA <> VIDEO::VIDEO() > arquivo estado.txt e' inconsistente" << endl;
            exit(ERRO_LEITURA);
         }
         if ((c = fgetc(arq)) != SIM && c != NAO) {
            cout << endl << "ERRO_LEITURA <> VIDEO::VIDEO() > arquivo estado.txt e' inconsistente" << endl;
            exit(ERRO_LEITURA);
         }
         atual->infoProc[FILTRO_MEDIA] = c;
      }
      else if (c == 'L') { // Lendo se o video ja' sofreu a aplicacao do filtro limite
         if (atual == NULL) {
            cout << endl << "ERRO_LEITURA <> VIDEO::VIDEO() > arquivo estado.txt e' inconsistente" << endl;
            exit(ERRO_LEITURA);
         }
         if ((c = fgetc(arq)) != ':') {
            cout << endl << "ERRO_LEITURA <> VIDEO::VIDEO() > arquivo estado.txt e' inconsistente" << endl;
            exit(ERRO_LEITURA);
         }
         if ((c = fgetc(arq)) != SIM && c != NAO) {
            cout << endl << "ERRO_LEITURA <> VIDEO::VIDEO() > arquivo estado.txt e' inconsistente" << endl;
            exit(ERRO_LEITURA);
         }
         atual->infoProc[FILTRO_LIMITE] = c;
      }
      else if (c == 'G') { // Lendo se o video ja' sofreu a aplicacao do filtro limite
         if (atual == NULL) {
            cout << endl << "ERRO_LEITURA <> VIDEO::VIDEO() > arquivo estado.txt e' inconsistente" << endl;
            exit(ERRO_LEITURA);
         }
         if ((c = fgetc(arq)) != ':') {
            cout << endl << "ERRO_LEITURA <> VIDEO::VIDEO() > arquivo estado.txt e' inconsistente" << endl;
            exit(ERRO_LEITURA);
         }
         if ((c = fgetc(arq)) != SIM && c != NAO) {
            cout << endl << "ERRO_LEITURA <> VIDEO::VIDEO() > arquivo estado.txt e' inconsistente" << endl;
            exit(ERRO_LEITURA);
         }
         atual->infoProc[GOTAS_IDENTIFICADAS] = c;
      }
   }
   fclose(arq);
}
// Escreve no arquivo ARQ_INFO as informacoes de processamento de cada VIDEO carregado no programa
void VIDEO::escreve_infoProc()
{
   //
   // Verifica se foi utilizada a CABECA da lista para a chamada desta funcao
   if (this->nFrame != CABECA) {
      cout << endl << "ERRO_LOGICA <> VIDEO::filtro_menosmedia(string) > o objeto envolvido nao e' a cabeca da lista" << endl;
      exit(ERRO_LOGICA);
   }
   //
   // Escreve informacoes de processamento dos VIDEOs no arquivo DIR_INFOPROC
   FILE *saida;         // Arquivo de saida
   string str;          // Manipula string
   str = DIR_VIDEOS;
   str += ARQ_INFOPROC;
   saida = fopen(str.c_str(), "w");
   if (saida == NULL) {
      cout << "ERRO_LOGICA <> VIDEO::escreve_estaco() > nao foi possivel gravar o arquivo " << ARQ_INFOPROC << endl;
      exit(ERRO_LOGICA);
   }
   for (VIDEO *atual = this->prx; atual->nFrame != CABECA; atual = atual->prx) {
      fprintf(saida, "D:");
      for (unsigned short i = 0; i < atual->dir.length(); ++i)
         fprintf(saida, "%c", atual->dir[i]);
      fprintf(saida, ";\n");
      fprintf(saida, "A:");
      for (unsigned short i = 0; i < atual->nome.length(); ++i)
         fprintf(saida, "%c", atual->nome[i]);
      fprintf(saida, ".avi;\n");
      fprintf(saida, "R:");
      fprintf(saida, "%c", atual->infoProc[ANALISAR]);
      fprintf(saida, ";\n");
      if (atual->infoProc[QUEBRADO] == SIM) {
         fprintf(saida, "Q:");
         fprintf(saida, "%c", atual->infoProc[QUEBRADO]);
         fprintf(saida, ";\n");
      }
      if (atual->infoProc[ESCALA_CINZA] == SIM) {
         fprintf(saida, "C:");
         fprintf(saida, "%c", atual->infoProc[ESCALA_CINZA]);
         fprintf(saida, ";\n");
      }
      if (atual->infoProc[FILTRO_MEDIA] == SIM) {
         fprintf(saida, "M:");
         fprintf(saida, "%c", atual->infoProc[FILTRO_MEDIA]);
         fprintf(saida, ";\n");
      }
      if (atual->infoProc[FILTRO_LIMITE] == SIM) {
         fprintf(saida, "L:");
         fprintf(saida, "%c", atual->infoProc[FILTRO_LIMITE]);
         fprintf(saida, ";\n");
      }
      if (atual->infoProc[GOTAS_IDENTIFICADAS] == SIM) {
         fprintf(saida, "G:");
         fprintf(saida, "%c", atual->infoProc[GOTAS_IDENTIFICADAS]);
         fprintf(saida, ";\n");
      }
      fprintf(saida, "#\n");
   }
   fclose(saida);
}
// Le do arquivo 'dados.txt' os dados adicionais dados pelo usuario
void VIDEO::leitura_dadosAdicionais()
{
	//
	// Atualiza estado dos VIDEOs
	char c;              // Caractere para a leitura do arquivo 'arq'
	FILE *arq;           // Aponta para o arquivo ARQ_INFOPROC
	string str;          // Manipula strings
	str += this->dir;
	str += ARQ_DADOSAD;
	arq = fopen(str.c_str(), "r");
	if (arq == NULL)
		return;
	while ((c = fgetc(arq)) != EOF) {
		if (c == 'O') { // Lendo diretorio do video
			if ((c = fgetc(arq)) != ':') {
				cout << endl << "ERRO_LEITURA <> VIDEO::VIDEO() > arquivo estado.txt e' inconsistente" << endl;
				exit(ERRO_LEITURA);
			}
			fscanf(arq, "%f(%f)", &(this->densidade_oleo.valor), &(this->densidade_oleo.incerteza));
			if ((c = fgetc(arq)) != ';') {
				cout << endl << "ERRO_LEITURA <> VIDEO::VIDEO() > arquivo estado.txt e' inconsistente" << endl;
				exit(ERRO_LEITURA);
			}
		}
		else if (c == 'F') { // Lendo diretorio do video
			if ((c = fgetc(arq)) != ':') {
				cout << endl << "ERRO_LEITURA <> VIDEO::VIDEO() > arquivo estado.txt e' inconsistente" << endl;
				exit(ERRO_LEITURA);
			}
			fscanf(arq, "%d", &(this->taxaframes));
			if ((c = fgetc(arq)) != ';') {
				cout << endl << "ERRO_LEITURA <> VIDEO::VIDEO() > arquivo estado.txt e' inconsistente" << endl;
				exit(ERRO_LEITURA);
			}
		}
		else if (c == 'T') { // Lendo diretorio do video
			if ((c = fgetc(arq)) != ':') {
				cout << endl << "ERRO_LEITURA <> VIDEO::VIDEO() > arquivo estado.txt e' inconsistente" << endl;
				exit(ERRO_LEITURA);
			}
			fscanf(arq, "%f(%f)", &(this->temperatuda.valor), &(this->temperatuda.incerteza));
			if ((c = fgetc(arq)) != ';') {
				cout << endl << "ERRO_LEITURA <> VIDEO::VIDEO() > arquivo estado.txt e' inconsistente" << endl;
				exit(ERRO_LEITURA);
			}
		}
		else if (c == 'H') { // Lendo diretorio do video
			if ((c = fgetc(arq)) != ':') {
				cout << endl << "ERRO_LEITURA <> VIDEO::VIDEO() > arquivo estado.txt e' inconsistente" << endl;
				exit(ERRO_LEITURA);
			}
			fscanf(arq, "%f(%f)", &(this->humidade_relativa.valor), &(this->humidade_relativa.incerteza));
			if ((c = fgetc(arq)) != ';') {
				cout << endl << "ERRO_LEITURA <> VIDEO::VIDEO() > arquivo estado.txt e' inconsistente" << endl;
				exit(ERRO_LEITURA);
			}
		}
		else if (c == 'V') { // Lendo diretorio do video
			if ((c = fgetc(arq)) != ':') {
				cout << endl << "ERRO_LEITURA <> VIDEO::VIDEO() > arquivo estado.txt e' inconsistente" << endl;
				exit(ERRO_LEITURA);
			}
			fscanf(arq, "%f(%f)", &(this->ddp.valor), &(this->ddp.incerteza));
			if ((c = fgetc(arq)) != ';') {
				cout << endl << "ERRO_LEITURA <> VIDEO::VIDEO() > arquivo estado.txt e' inconsistente" << endl;
				exit(ERRO_LEITURA);
			}
		}
	}
	fclose(arq);
}
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// IMPRESSAO NA TELA E SALVAMENTO
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Imprime na tela as informacoes dos videos carregados
void VIDEO::printf()
{
   //
   // Verificando se foi utilizada a CABECA da lista para a chamada desta funcao
   if (this->nFrame != CABECA) {
      cout << endl << "ERRO_LOGICA <> VIDEO::filtro_menosmedia(string) > o objeto envolvido nao e' a cabeca da lista" << endl;
      exit(ERRO_LOGICA);
   }
   //
   // Imprimindo lista de VIDEOs e suas informcoes de prcessamento na tela
   cout << "--------------------------------------------------------------------------------";
   for (VIDEO *p = this->prx; p->nFrame != CABECA; p = p->prx) {
      cout << endl << "> " << p->dir + p->nome + p->extensao;
      if (p->infoProc[ANALISAR] == NAO) {
         cout << " :: NAO_ANALISAR";
         continue;
      }
      if (p->infoProc[QUEBRADO] == NAO)
         continue;
      cout << " :: QUEBRADO";
      if (p->infoProc[ESCALA_CINZA] == NAO)
         continue;
      cout << " > " << "ESCALA_CINZA";
      if (p->infoProc[FILTRO_MEDIA] == NAO)
         continue;
      cout << " > " << "FILTRO_MEDIA";
      if (p->infoProc[FILTRO_LIMITE] == NAO)
         continue;
      cout << " > " << "FILTRO_LIMITE";
   }
   cout << endl << "--------------------------------------------------------------------------------" << endl;
}
// Salva as imagens do video no diretorio 'this->dirFrames + DIR_FRAMES_FINAL'
void VIDEO::salva()
{
   PROGRESSO progresso("Salvando em final/            : ", this->nFrame);
   for (int id = 1; id <= this->nFrame; ++id) {
      ostringstream endereco_salvar;
      endereco_salvar << this->dirFrame << DIR_FRAMES_FINAL << id;
      this->vFrame[id-1]->salva(endereco_salvar.str());
      progresso.atualiza(id);
   }
   progresso.finaliza();
}
// Salva as imagens do video no diretorio 'this->dirFrames + diretorio'
void VIDEO::salva(string diretorio)
{
   if (diretorio[diretorio.length() - 1] != '/')
      diretorio += '/';
   string str;
   if (verifica_dir(this->dirFrame + diretorio)) {
      str = "mkdir " + this->dirFrame + diretorio;
      system(str.c_str());
   }
   str = "Salvando em " + diretorio;
   while (str.length() < 30)
      str += ' ';
   str += ": ";
   PROGRESSO progresso(str.c_str(), this->nFrame);
   for (int id = 0; id < this->nFrame; ++id) {
      ostringstream endereco_salvar;
      endereco_salvar << this->dirFrame << diretorio << id + 1;
      this->vFrame[id]->salva(endereco_salvar.str());
      progresso.atualiza(id + 1);
   }
   progresso.finaliza();
}
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// METODOS QUE DEVOLVEM ATRIBUTOS DO VIDEO <> GETs
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Devolve o valor do atributo nVideo
int VIDEO::get_nVideo()
{
   return nVideo;
}
// Devolve o nome do VIDEO do objeto envolvido
string VIDEO::get_nome()
{
   if (this == NULL) {
      cout << endl << "ERRO_LOGICA <> VIDEO::get_nome() > this == NULL" << endl;
      exit(ERRO_LOGICA);
   }
   return this->nome;
}
// Devolve o diretorio onde os VIDEOs inseridos na lista se encontram
string VIDEO::get_dir()
{
   if (this == NULL) {
      cout << endl << "ERRO_LOGICA <> VIDEO::get_dir() > this == NULL" << endl;
      exit(ERRO_LOGICA);
   }
   if (this->dir == "")
      return "nao existe nenhum video carregado";
   return this->dir;
}
// Devolve o atributo 'nFrame' do VIDEO envolvido
int VIDEO::get_nFrame()
{
   if (this == NULL) {
      cout << endl << "ERRO_LOGICA <> VIDEO::get_prx() > this == NULL" << endl;
      exit(ERRO_LOGICA);
   }
   return this->nFrame;
}
// Devolve a largura dos FRAMES do VIDEO envolvido
unsigned int VIDEO::get_lrgIMAGEM()
{
   if (this == NULL) {
      cout << endl << "ERRO_LOGICA <> VIDEO::get_lrgIMAGEM() > this == NULL" << endl;
      exit(ERRO_LOGICA);
   }
   return this->lrgIMAGEM;
}
// Devolve a altura dos FRAMES do VIDEO envolvido
unsigned int VIDEO::get_altIMAGEM()
{
   if (this == NULL) {
      cout << endl << "ERRO_LOGICA <> VIDEO::get_altIMAGEM() > this == NULL" << endl;
      exit(ERRO_LOGICA);
   }
   return this->altIMAGEM;
}
// Devolve o atributo 'prx' do VIDEO envolvido
VIDEO *VIDEO::get_prx()
{
   if (this == NULL) {
      cout << endl << "ERRO_LOGICA <> VIDEO::get_prx() > this == NULL" << endl;
      exit(ERRO_LOGICA);
   }
   return this->prx;
}
// Dado o 'nivel' desejado, devolve o atributo infoProc[nivel] do objeto envolvido
int VIDEO::get_infoProc(int nivel)
{
   if (this == NULL) {
      cout << endl << "ERRO_LOGICA <> VIDEO::get_estado(int estado) > this == NULL" << endl;
      exit(ERRO_LOGICA);
   }
   return this->infoProc[nivel];
}
// Devolve o atributo 'taxaframes' do VIDEO envolvido
int VIDEO::get_taxaframes()
{
	return this->taxaframes;
}
// Incrementa em +1 o valor do atributo nGotas
void VIDEO::inc_nGotas()
{
	++this->nGotas;
}
// Subtrai em -1 o valor do atributo nGotas
void VIDEO::sub_nGotas()
{
	--this->nGotas;
}
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MANIPULACAO DE IMAGEM E VIDEO
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Sendo o objeto envolvido um elemento da lista de VIDEOs diferente da CABECA, esta funcao o quebra em frames
void VIDEO::quebra_frames()
{
   //
   // Verificando se o objeto envolvido nao e' a CABECA da lista
   if (this->nFrame == CABECA) {
      cout << endl << "ERRO_LOGICA <> VIDEO::carrega_frames() > o objeto envolvido e' cabeca da lista" << endl;
      exit(ERRO_LOGICA);
   }
   string str;          // Variavel para manipulacao de string
   FILE *arq;           // Aponta para arquivos temporarios :: temp.*.at
   char c;              // Caractere para a leitura do arquivo 'arq'
   //
   // Verifica se o video ja' foi quebrado em frames e, caso nao, o programa cria diretorios necessarios e o quebra
   if (this->infoProc[QUEBRADO] == NAO) {
      cout << "Quebrando video em frames ..." << endl;
      //
      // Verifica se o diretorios de armazenamento dos frames ja' existem e, caso nao, os cria
      if (verifica_dir(this->dirFrame)) { // Se o diretorio nao existe, cria ele
         str = "mkdir " + this->dirFrame;
         system(str.c_str());
         str += DIR_FRAMES_CINZA;
         system(str.c_str());
         str = "mkdir " + this->dirFrame + DIR_FRAMES_FINAL;
         system(str.c_str());
      }
      else if (verifica_dir(this->dirFrame + DIR_FRAMES_CINZA)) {
         str = "mkdir " + this->dirFrame + DIR_FRAMES_CINZA;
         system(str.c_str());
      }
      else if (verifica_dir(this->dirFrame + DIR_FRAMES_FINAL)) {
         str = "mkdir " + this->dirFrame + DIR_FRAMES_FINAL;
         system(str.c_str());
      }
      //
      // Quebrando video em frames
      str = "ffmpeg -i " + this->dir + this->nome + this->extensao + " " + this->dirFrame + "%d.png";
      system(str.c_str());
      //
      // Atualizando estado do video
      this->infoProc[QUEBRADO] = SIM;
   }
   //
   // Conta o numero de frames criados para o video 'atual'
   str = "ls ";
   str += this->dirFrame + "*.png | wc -l > temp.CONTA_FRAMES.at";
   system(str.c_str());
   arq = fopen("temp.CONTA_FRAMES.at", "r");
   for (this->nFrame = 0; (c = fgetc(arq)) != '\n'; this->nFrame = this->nFrame * 10 + c - '0')
      ;
   fclose(arq);
   system("rm temp.CONTA_FRAMES.at*");
}
// Sendo o objeto envolvido um elemento da lista de VIDEOs diferente da CABECA e que
// ele ja' tenha sido quebrados em frames, converte todos eles para a escala cinza
void VIDEO::converte_cinza()
{
   //
   // Verificando se o objeto envolvido nao e' a CABECA da lista
   if (this->nFrame == CABECA) {
      cout << endl << "ERRO_LOGICA <> VIDEO::converte_cinza() > o objeto envolvido e' cabeca da lista" << endl;
      exit(ERRO_LOGICA);
   }
   //
   // Se o video ainda nao tiver sido convertido em imagem, nao sera' possivel continuar
   if (this->infoProc[QUEBRADO] == NAO) {
      cout << endl << "ERRO_LOGICA <> VIDEO::converte_cinza() > o video deve ser antes quebrado em imagens" << endl;
      exit(ERRO_LOGICA);
   }
   if (this->infoProc[ESCALA_CINZA] == SIM)
      return;
   PROGRESSO progresso("Convertendo para escala cinza : ", this->nFrame);
   string str;                            // Manipula strings
   for (int iFrame = 0; iFrame < this->nFrame; ++iFrame) {
      ostringstream intstr;               // Transforma int em string
      intstr << iFrame + 1;
      str = "convert -separate " + this->dirFrame + intstr.str() + ".png ";
      str += this->dirFrame + DIR_FRAMES_CINZA + intstr.str();
      system(str.c_str());
      progresso.atualiza(iFrame + 1);
   }
   progresso.finaliza();
   this->infoProc[ESCALA_CINZA] = SIM;
}
// Sendo o objeto envolvido um elemento da lista de VIDEOs diferente da CABECA, carrega as imagens para o video
// OBS: A leitura desta funcao e' indicada para quem quer entender o procedimento do programa
void VIDEO::inicia_video()
{
   //
   // Verifica se o objeto envolvido nao e' a CABECA da lista
   if (this->nFrame == CABECA) {
      cout << endl << "ERRO_LOGICA <> VIDEO::inicia_video() > o objeto envolvido e' cabeca da lista" << endl;
      exit(ERRO_LOGICA);
   }
   //
   // Se o video ainda nao tiver sido convertido em imagem, nao sera' possivel continuar
   if (this->infoProc[ESCALA_CINZA] == NAO) {
      cout << endl << "ERRO_LOGICA <> VIDEO::inicia_video() > o video deve ser antes convertido para escala cinza";
      cout << endl;
      exit(ERRO_LOGICA);
   }
   //
   // Carrega imagens
   PROGRESSO progresso("Preparando para processamento : ", this->nFrame);
   this->vFrame = (FRAME**) malloc_void(this->nFrame * sizeof(FRAME*));
   if (this->infoProc[FILTRO_MEDIA] == NAO) {
      for (int id = 0; id < this->nFrame; ++id) {
         ostringstream str;
         str << this->dirFrame << DIR_FRAMES_CINZA << id + 1 << "-0";
         this->vFrame[id] = new FRAME(str.str(), id);
         //
         // Inicia o frame com valores nulos, ou seja, uma imagem preta
         for (unsigned int lrg = 0; lrg < this->vFrame[0]->get_largura(); ++lrg)
            for (unsigned int alt = 0; alt < this->vFrame[0]->get_altura(); ++alt)
               this->vFrame[id]->set_pixel(lrg, alt, PRETO);
         progresso.atualiza(id + 1);
      }
   }
   else {
      for (int id = 0; id < this->nFrame; ++id) {
         ostringstream str;
         str << this->dirFrame << DIR_FRAMES_FINAL << id + 1;
         this->vFrame[id] = new FRAME(str.str(), id);
         progresso.atualiza(id + 1);
      }
   }
   progresso.finaliza();
   //
   // Adquire dimensoes da imagem
   this->lrgIMAGEM = this->vFrame[0]->get_largura();
   this->altIMAGEM = this->vFrame[0]->get_altura();
   //
   // Atualiza informacoes de processamento
   this->infoProc[VIDEO_INICIADO] = SIM;
}
// Sendo o objeto envolvido um video da lista que nao seja a CABECA, esta funcao calcula as medias de
// cada ponto fixo (lrg, alt) de (todos os frames) * porcao e as subtraem de seus repectivos pontos
// 'distancia': valores de cores que estao a uma 'distancia' do desvio padrao sao eliminados
void VIDEO::filtro_menosmedia(float porcao, float distancia)
{
   //
   // Verificando se o objeto envolvido nao e' a CABECA da lista
   if (this->nFrame == CABECA) {
      cout << endl << "ERRO_LOGICA <> VIDEO::filtro_menosmedia() > o objeto envolvido e' a cabeca da lista" << endl;
      exit(ERRO_LOGICA);
   }
   //
   // Verificando se os frames ja' foram convertidos para escala cinza
   if (this->infoProc[VIDEO_INICIADO] != SIM) {
      cout << endl << "ERRO_LOGICA <> VIDEO::filtro_menosmedia() > deve ser feita a conversao para a escala cinza ";
      cout << "antes de se aplicar o filtro menos media" << endl;
      exit(ERRO_LOGICA);
   }
   //
   // Verifica se o filtro menos media ja' foi aplicado
   if (this->infoProc[FILTRO_MEDIA] == SIM)
      return;
   //
   // Verifica consistencia dos parametros de entrada
   if (porcao > 1.0 || porcao < 0.0) {
      cout << endl << "ERRO_LOGICA <> VIDEO::filtro_menosmedia() > parametro inconsistente > porcao: ";
      cout << porcao << endl;
      exit(ERRO_LOGICA);
   }
   if (distancia < 0.0) {
      cout << endl << "ERRO_LOGICA <> VIDEO::filtro_menosmedia() > parametro inconsistente > distancia: ";
      cout << porcao << endl;
      exit(ERRO_LOGICA);
   }
   short ocorrencia[N_COR];      // Armazena a ocorrecia da cada cor em um ponto (lrg,alt) fixo
   FRAME **vImg;                 // Vetor de ponteiro para imagens que serao analisadas
   int considerar_nFrame;        // Numero dos n primeiros FRAMEs que serao considerados para o calculo do filtro
   string str;                   // Manipula strings
   PROGRESSO progresso("Aplicando filtro menos media  : ", N_CANAL * (this->lrgIMAGEM * this->altIMAGEM +this->nFrame));
   //
   // Aplicacao do filtro para cada um dos
   considerar_nFrame = this->nFrame * porcao;
   vImg = (FRAME**) malloc_void(this->nFrame * sizeof(FRAME*));
   for (int canal = 0; canal < N_CANAL; ++canal) {
      //
      // Carregando imagens referente ao canal atual para calculo da imagem media
      for (int iFrame = 0; iFrame < this->nFrame; ++iFrame) {
         ostringstream nome_img;  // Transforma int em string
         nome_img << this->dirFrame << DIR_FRAMES_CINZA << iFrame + 1 << '-' << canal;
         vImg[iFrame] = new FRAME(nome_img.str(), iFrame);
         progresso.atualiza(canal * (this->nFrame + this->lrgIMAGEM * this->altIMAGEM) + iFrame + 1);
      }
      //
      // Conta ocorrencia e calcula a media e o desvio padrao para cada ponto (lrg,alt) do VIDEO
      for (unsigned short lrg = 0; lrg < this->lrgIMAGEM; ++lrg) {
         for (unsigned short alt = 0; alt < this->altIMAGEM; ++alt) {
            float media = 0.0;      // Media e desvio padrao da cor do ponto (lrg,alt) atual
            float desvPad = 0.0;    // Desvio padrao da media
            short cor;
            //
            // Inicia 'ocorrencia[]' com valores nulos
            for (cor = 0; cor < N_COR; ++cor)
               ocorrencia[cor] = 0;
            //
            // Conta a ocorrencia de cada cor para todos os FRAMEs que serao analisados
            for (int iFrame = 0; iFrame < considerar_nFrame; ++iFrame) {
               cor = vImg[iFrame]->get_pixel(lrg,alt);
               media += cor;
               ++ocorrencia[cor];
            }
            media /= considerar_nFrame;
            //
            // Calcula o desvio padrao
            for (cor = 0; cor < N_COR; ++cor) {
               desvPad += pow(media - cor, 2) * ocorrencia[cor];
            }
            desvPad = sqrt(desvPad / (float) considerar_nFrame);
            //
            // Atualiza cor na imagem final dos FRAMEs
            for (int iFrame = 0; iFrame < this->nFrame; ++iFrame) {
               cor = vImg[iFrame]->get_pixel(lrg, alt);
               if (abs(cor - media) > distancia * desvPad)
                  cor += this->vFrame[iFrame]->get_pixel(lrg, alt);
               else
                  cor = 0;
               this->vFrame[iFrame]->set_pixel(lrg, alt, cor);
            }
            progresso.atualiza(this->nFrame + canal * (this->lrgIMAGEM * this->altIMAGEM + this->nFrame) + (lrg + 1) * (alt + 1));
         }
      }
      //
      // Liberando a memoria alocada pelas imagens que estao carregadas
      for (int iFrame = 0; iFrame < this->nFrame; ++iFrame)
         vImg[iFrame]->~FRAME();
   }
   free(vImg);
   progresso.finaliza();
   //
   // Atualizando informacoes de processamento
   this->infoProc[FILTRO_MEDIA] = SIM;
   //
   // Salva imagens final em um diretorio especifico
   *ostringstream dir;  // Transforma int em string
   dir << "media_" << porcao << '_' << distancia << '/';
   this->salva(dir.str());*
}
// Sendo o objeto envolvido um video da lista que nao seja a CABECA, esta funcao aplica o filtro limite
void VIDEO::filtro_limite()
{
   //
   // Verificando se o objeto envolvido nao e' a CABECA da lista
   if (this->nFrame == CABECA) {
      cout << endl << "ERRO_LOGICA <> VIDEO::filtro_limite() > o objeto envolvido e' a cabeca da lista" << endl;
      exit(ERRO_LOGICA);
   }
   //
   // Verificando se ja' foi aplicado o filtro menos media
   if (this->infoProc[FILTRO_MEDIA] != SIM) {
      cout << endl << "ERRO_LOGICA <> VIDEO::filtro_limite() > o filtro menos media deve ser aplicado ";
      cout << "antes de se aplicar o filtro limite" << endl;
      exit(ERRO_LOGICA);
   }
   if (this->infoProc[FILTRO_LIMITE] == SIM)
      return;
   PROGRESSO progresso("Aplicando filtro limite       : ", this->nFrame);
   unsigned short limite = 50;
   for (int iFrame = 0; iFrame < this->nFrame; ++iFrame) {
      for (unsigned int lrg = 0; lrg < this->lrgIMAGEM; ++lrg)
         for (unsigned int alt = 0; alt < this->altIMAGEM; ++alt)
            if (this->vFrame[iFrame]->get_pixel(lrg, alt) <= limite)
               this->vFrame[iFrame]->set_pixel(lrg, alt, 0);
            else
               this->vFrame[iFrame]->set_pixel(lrg, alt, BRANCO);
      progresso.atualiza(iFrame + 1);
   }
   progresso.finaliza();
   //
   // Atualizando informacoes de processamento
   this->infoProc[FILTRO_LIMITE] = SIM;
   //
   // Salva imagens final em um diretorio especifico
   //this->salva("final_limite");
}
// Identifica as GOTAs em todos os FRAMEs do VIDEO
void VIDEO::identifica_gotas()
{
   //
   // Verificando se o objeto envolvido nao e' a CABECA da lista
   if (this->nFrame == CABECA) {
      cout << endl << "ERRO_LOGICA <> VIDEO::filtro_limite() > o objeto envolvido e' a cabeca da lista" << endl;
      exit(ERRO_LOGICA);
   }
   //
   // Verificando se ja' foi aplicado o filtro menos media
   if (this->infoProc[FILTRO_LIMITE] != SIM) {
      cout << endl << "ERRO_LOGICA <> VIDEO::identifica_gotas() > o filtro limite deve ser aplicado ";
      cout << "antes de indentificar as gotas" << endl;
      exit(ERRO_LOGICA);
   }
   PROGRESSO progresso("Determinando gotas            : ", this->nFrame);
   for (int iFrame = 0; iFrame < this->nFrame; ++iFrame) {
      this->vFrame[iFrame]->identifica_gotas();
      progresso.atualiza(iFrame + 1);
   }
   progresso.finaliza();
}
// Rastrea gotas no video
void VIDEO::rastrea_gotas()
{
	//
	// Inicia a lista de gotas do VIDEO pegando todas as gotas no primeiro FRAME
	for (GOTA *gota = this->vFrame[0]->get_gotas()->get_prx(); gota != NULL; gota = gota->get_prx()) {
		++this->nGotas;
		this->insere(new GOTA_VIDEO(gota));
	}
	PROGRESSO progresso("Rastreando gotas              : ", this->nFrame);
	for (int iFrame = 1; iFrame < this->nFrame; ++iFrame) {
		//cout << endl << endl << "Frame " << iFrame + 1 << " > nGotas : " << this->vFrame[iFrame]->get_nGotas() << flush;
		for (GOTA *gota_atual = this->vFrame[iFrame]->get_gotas()->get_prx(); gota_atual != NULL; gota_atual = gota_atual->get_prx())
			gota_atual->encontra_possiveis_anteriores(this->vFrame[iFrame-1]->get_gotas()->get_prx());
		this->vFrame[iFrame]->get_gotas()->determina_anterior(this);
	      progresso.atualiza(iFrame + 1);
	}
	progresso.finaliza();
	cout << "Numero de gotas encontradas   : " << this->nGotas << endl;
}
// Faz com que todas as gotas voltem para cor BRANCA
void VIDEO::gotas_brancas()
{
   for (int iFrame = 0; iFrame < this->nFrame; ++iFrame)
      this->vFrame[iFrame]->gotas_brancas();
}
// Dada uma gota, a insere na lista 'gotas' do VIDEO
void VIDEO::insere(GOTA_VIDEO *gota)
{
   gota->set_prx(this->gotas->get_prx());
   this->gotas->set_prx(gota);
}
// Libera espaco alocado para as imagens
void VIDEO::libera_memoria()
{
	for (int iFrame = 0; iFrame < this->nFrame; ++iFrame)
		this->vFrame[iFrame]->libera_memoria();
}
// Determina velocidades das gotas
void VIDEO::determina_velocidades()
{
	//int i = 0;
	for (GOTA_VIDEO *gota = this->gotas->get_prx(); gota != NULL; gota = gota->get_prx()) {
		//cout << endl << "Gota " << ++i << " : ";
		//i++;
		//if (i == 10)
			gota->determina_velocidades(this);
	}
	cout << endl;
	cout << "Numero de gotas aproveitadas: " << this->nGotas << endl;
	cout << endl;
}
*/
