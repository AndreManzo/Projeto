#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <iostream>

struct reg {
	char nome  [50];   
	char tel   [20];
	char end   [50];
	char ped   [50];
	char status;
	int cod;
};

int tamanho(FILE *arq) {
	fseek(arq,0,SEEK_END);
	return ftell(arq)/sizeof(reg);
}

void linha() {
	printf("==========================================================================");
}

void cadastrar(FILE *arq) {
	reg contato;
	char confirma;
	printf("Cadastrando Novo Registro!\n");
	printf("Número do Registro.......:%d\n\n",tamanho(arq)+1);
	linha();
	printf("\n\n");
	fflush(stdin);
	
	printf("Nome ....................:");
	gets(contato.nome);
	
	printf("Telefone.................:");
	gets(contato.tel);

	printf("Endereço.................:");
	gets(contato.end);
	
	printf("Pedido...................:");
	gets(contato.ped);
	
	
	printf("\nConfirma <s/n>...........:");
	scanf(" %c",&confirma);
	if (toupper(confirma) == 'S') {
		
		printf("Gravando.....\n\n");
		fseek(arq,0,SEEK_END);
		contato.status='S';
		contato.cod=(tamanho(arq)+1);
		fwrite(&contato,sizeof(reg),1,arq);
	}
	else {
		printf("\n");
	}
	system("pause");
}

void consultar(FILE *arq) {
	reg contato;
	int nr;
	printf("Consulta pelo Código\n");
	printf("Informe o Código...:");
	scanf("%d",&nr);
	printf("\n");
	if ((nr <= tamanho(arq)) && (nr > 0)) {
		fseek(arq,(nr - 1) * sizeof(reg),SEEK_SET);
		fread(&contato,sizeof(reg),1,arq);
		linha();
		printf("\n\n");
		printf("Código do Cliente........:%d\n\n",contato.cod);
		printf("Nome ....................:%s\n",contato.nome);
		printf("Telefone.................:%s\n",contato.tel);
		printf("Endereço.................:%s\n",contato.end);
		printf("Pedido...................:%s\n",contato.ped);

		printf("\n\n");			
	}
	else {
		linha();
		printf("\n\nNúmero de Registro Inválido!\n\n");
	}
	system("pause");
}

void excluir(FILE *arq) {
	reg contato;
	char confirma;
	int nr;
	printf("Informe o pedido que deseja excluir:");
	scanf("%d",&nr);
	printf("\n");
	linha();
	printf("\n\n");
	if ((nr <= tamanho(arq)) && (nr > 0)) {
		fseek (arq,(nr-1)*sizeof(reg),SEEK_SET);
		fread(&contato,sizeof (reg),1,arq);
		if (contato.status == 'S') {
			printf("Nome ....................:%s\n",contato.nome);
			printf("Telefone.................:%s\n",contato.tel);
			printf("Endereço.................:%s\n",contato.end);
			printf("Pedido...................:%s\n",contato.ped);	
			getchar();
			printf("\n");
			linha();
			printf("\n\n");
			printf("Confirma <s/n>:");
			scanf("%c",&confirma);						
			if (toupper (confirma) == 'S') {
					printf("\nExcluido.....\n\n");
					fseek(arq,(nr-1)*sizeof(reg),SEEK_SET);
					contato.status = 'N';
					fwrite(&contato,sizeof(reg),1,arq);
			}
			else {
				printf("\n");
			}
		}
		else {
			printf("Pedido excluído!\n\n");
		}
	}
	else {
		printf("Número de Registro Inválido!\n\n");
	}
	system("pause");
}



void gerararqtxt(FILE *arq) {
	char nomearq[20];
	printf("Nome do Arquivo Texto:");
	scanf("%s",nomearq);
	strcat(nomearq,".txt");
	FILE *arqtxt = fopen(nomearq,"w");
	if (!arqtxt) {
		printf("\nNão foi possível criar esse arquivo!\n\n");
		system("pause");
	}
	fprintf(arqtxt,"Lanchonete  do  bombinha\n");			
	int nr;
	reg contato;
	for (nr=0;nr<tamanho(arq);nr++) {
		fseek(arq,nr * sizeof(reg),SEEK_SET);
		fread(&contato,sizeof(reg),1,arq);
		fprintf(arqtxt,"\n");
		
		fprintf(arqtxt,"Código...................: %d\n\n",contato.cod);
		fprintf(arqtxt,"Nome ....................: %s\n",contato.nome);
		fprintf(arqtxt,"Telefone.................: %s\n",contato.tel);
		fprintf(arqtxt,"Endereço.................: %s\n",contato.end);
		fprintf(arqtxt,"Pedido...................: %s\n",contato.ped);
		fprintf(arqtxt,"===================================================================================\n");
	}
		fclose(arqtxt);
}


int main() {
	setlocale(LC_ALL,"Portuguese");
	int op;
	FILE *arq;
	
	if ((arq = fopen("dados.dat","rb+")) == NULL)
		if ((arq = fopen("dados.dat","wb+")) == NULL) {
			printf("Falha ao abrir o arquivo!\n\n");
			system("pause");
		}
	
	do {
		system("cls");
		linha();
		printf("\n\n");
		printf("======================= \n");
		printf(" lanchonetedo bombinha \n");
		printf("======================= \n");

		printf("CLIENTES CADASTRADOS: %d\n\n",tamanho(arq));
		printf("1.Cadastrar\n");
		printf("2.Consultar\n");
		printf("3.Gerar Arquivo\n");
		printf("4.Excluir pedido\n");
		printf("5.Sair\n\n");
		linha();
		printf("\n\n");
		printf("Opção:");
		scanf("%d",&op);
		printf("\n");
		switch (op) {
			case 1:
				cadastrar(arq);
				break;
			case 2:
				consultar(arq);
				break;
			case 3:
				gerararqtxt(arq);
				break;
			case 4:
				excluir(arq);
				break;
			case 5:
				fclose(arq);
		}
	} while (op != 7);
	system("pause");
	return 0;
}
