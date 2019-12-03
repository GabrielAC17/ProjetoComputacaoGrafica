//============================================================================
// Name        : convert.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "mesh.h"
using namespace std;

int main(int argc, char* argv[]) {

int i;
mesh m;

if(argc < 3) {
	printf("Observacoes:\n");
	printf("- Apos editar um arquivo no meshlab, use o filtro para remover vertices nao referenciados.\n");
	printf("- Salve o arquivo no formato obj marcando apenas a opcao textCoord da coluna wedge.\n");
	printf("\n- Dependendo da configuracao do sistema, o meshlab pode salvar dados utilizando virgulas ao inves de pontos.\n");
	printf("Verifique o arquivo. Caso isso tenha ocorrido, corrija com: sed 's/,/./g' arquivo-virgula.obj > arquivo-ponto.obj\n");

	printf("\nModo de uso:\n");
	printf("rng2obj: converter <in.rng> <header.txt> <out.obj>\n");
	printf("\nobj2rng: converter <in.obj> <header.txt> <out.rng>\n");
	printf("\nm2obj: converter <in.m> <out.obj>\n\n");
	exit(0);
}

for(i=0; argv[1][i] != '\0'; i++)
	argv[1][i] = tolower(argv[1][i]);

if( strstr(argv[1],".rng") != NULL ) {
	if (m.loadRng(argv[1])) {
		m.saveTxt(argv[2]);
	    	m.saveObj(argv[3]);
		//m.saveRng(argv[3]);
	}
}
else if ( strstr(argv[1],".obj") != NULL ) {
	printf("\nDependendo da configuracao do sistema, o meshlab pode salvar dados utilizando virgulas ao inves de pontos.\n");
	printf("Verifique o arquivo. Caso isso tenha ocorrido, utilize o comando: sed 's/,/./g' arquivo-virgula.obj > arquivo-ponto.obj\n");
	printf("Se o arquivo esta correto aperte qualquer tecla para continuar, senao cancele.\n");
	getchar();
	if (m.loadObj(argv[1]))
	{
		m.loadTxt(argv[2]);
		m.saveRng(argv[3]);
	}
}
else if ( strstr(argv[1],".m2") != NULL ) {
	if (m.loadM2(argv[1]))
		//m.saveM3_m2(argv[2]);
		m.savePly(argv[2]);
}
else if ( strstr(argv[1],".m") != NULL ) {
	if (m.loadM(argv[1]))
		m.saveM3_m(argv[2]);
		//m.saveObj(argv[2]);
}
//cout << "done." << endl;
return 0;
}
