/*
Nome..: Joao Pedro Flausino de Lima
Data..: 30/08/2021
Enunciado.: Projeto Final.
*/

#include <stdio.h>

#include <string.h>

#include <ctype.h>

#include <stdlib.h>

// registros de dados
typedef struct data {
   int dia;
   int mes;
   int ano;
}
Data;

typedef struct pessoa {
   char nome[50];
   char cpf[15];
   Data dtNasc;
}
Pessoa;

typedef struct carro {
   Pessoa p;
   char placa[10];
   char modelo[25];
   int anofab;
   float preco;
}
Carro;

// protótipos das funções
int validarCPF(char s[]);
int validarPlaca(char v[]);
int validarData(int day, int month, int year);
int validarAnofab(int j);
Carro cadastrarCarro();
void estatistica(Carro c[], int P);
void mostrar(Pessoa p, Carro c);
int menu(Pessoa people[], Carro car[], int pa);
void flush_in();

// funções gerais
//cadatro pessoa
//cadastro carro
Carro cadastrarCarro() {
   Carro c;
   Pessoa p;
   int j, x = 0, y = 0;
   int val = 0, val1 = 0;
   int day, month, year;
   char aux[50];
   char vet[10];
   printf("Nome..: ");
   flush_in();
   gets(c.p.nome);
   do {
      printf("CPF...: ");
      gets(aux);
      val = validarCPF(aux);
   } while (val == 0);
   strcpy(c.p.cpf, aux);
   do {
      printf("Data..: ");
      scanf("%d/%d/%d", & day, & month, & year);
      val1 = validarData(day, month, year);
   } while (val1 == 0);
   c.p.dtNasc.dia = day;
   c.p.dtNasc.mes = month;
   c.p.dtNasc.ano = year;
   flush_in();
   do {
      printf("placa.:");
      gets(vet);
      x = validarPlaca(vet);
   } while (x == 0);
   strcpy(c.placa, vet);
   printf("modelo.:");
   gets(c.modelo);
   do {
      printf("Ano de Fabricacao.:");
      scanf("%d", & j);
      y = validarAnofab(j);
   } while (y == 0);
   c.anofab = j;
   printf("preco.:");
   scanf("%f", & c.preco);

   return c;
}

//mostrar
void mostrar(Pessoa p, Carro c) {
   printf("\n\n------------------------");
   printf("\n>>Nome.: %s", c.p.nome);
   printf("\n>>CPF..: %s", c.p.cpf);
   printf("\n>>Data.: %d/%d/%d", c.p.dtNasc.dia, c.p.dtNasc.mes, c.p.dtNasc.ano);
   printf("\n>>placa.: %s", c.placa);
   printf("\n>>modelo..: %s", c.modelo);
   printf("\n>>anofab.: %d", c.anofab);
   printf("\n>>preco.: %f", c.preco);
   printf("\n\n------------------------");
}

//validar
int validarCPF(char s[]) {
   int i = 0,
      cont = 0,
      tam = 0;
   tam = strlen(s);
   if (tam != 11) {
      return 0;
   }

   for (i = 0; i < tam; i++) {
      if (!(s[i] >= '0' && s[i] <= '9')) {
         return 0;
      }
   }
   return 1;
}

int validarPlaca(char v[]) {
   int i = 0,
      cont = 0,
      tam = 0;
   tam = strlen(v);
   if (tam != 8) {
      return 0;
   }
   for (i = 0; i < tam; i++) {
      if (i < 3) {
         if (!(v[i] >= 'a' && v[i] <= 'z')) {
            return 0;
         }
      } else if (i == 3) {
         if (!(v[i] == '-')) {
            return 0;
         }
      } else if (i > 4 || i < 8) {
         if (!(v[i] >= '0' && v[i] <= '9')) {
            return 0;
         }
      }
   }

}

int validarData(int day, int month, int year) {
   if (day < 1 || day > 30) {
      return 0;
   } else
   if (month < 1 || month > 12) {
      return 0;
   } else
   if (year < 1900 || year > 2021) {
      return 0;
   } else {
      return 1;
   }
}

int validarAnofab(int j) {
   if (j < 1886 || j > 2021) {
      return 0;
   } else {
      return 1;
   }
}

//menu
int menu(Pessoa people[], Carro car[], int pa) {
   int opc = 0;
   char comp[10];
   char test[25];
   int i = 0;

   printf("\n\n------------------------");
   printf("\nnumero de cadastros atual : %d", pa);
   printf("\n1-cadastrar novo veiculo");
   printf("\n2-mostrar todos os cadastros");
   printf("\n3-consultar carro por placa");
   printf("\n4-consultar carro por modelo");
   printf("\n5-porcentagem de carros por ano de fabricacao");
   printf("\n6-sair");
   printf("\n------------------------\n");

   scanf("%d", & opc);
   switch (opc) {
   case 1:
      car[pa] = cadastrarCarro();
      pa++;
      printf("\ncadastro concluido !!\n");
      break;

   case 2:
      if (pa == 0) {
         printf("\nnenhum cadastro concluido\n");
         break;
      }
      for (i = 0; i < pa; i++) {
         mostrar(people[i], car[i]);
      }
      break;

      //consulta todos os vetores por placa
   case 3:
      if (pa == 0) {
         printf("\nnenhum cadastro concluido\n");
      }
      flush_in();
      gets(comp);
      for (i = 0; i < pa; i++) {
         if (strcmp(comp, car[i].placa) == 0) {
            mostrar(people[i], car[i]);
         }
      }
      break;
      //consulta todos os vetores por modelo
   case 4:
      if (pa == 0) {
         printf("\nnenhum cadastro concluido\n");
         break;
      }
      flush_in();
      gets(test);
      for (i = 0; i < pa; i++) {
         if (strcmp(test, car[i].modelo) == 0) {
            mostrar(people[i], car[i]);
         }
      }
      break;
      //consulta todos os vetores por ano de fabricacao     
   case 5:
      estatistica(car, pa);
      break;
   }
   return opc;
}

//limpeza de buffer do teclado
void flush_in() {
   int ch;
   while ((ch = fgetc(stdin)) != EOF && ch != '\n') {}
}

void estatistica(Carro c[], int P) {
   int Ano[50];
   int quantidade[50];
   int i = 0;
   int j = 0;
   int cont = 0;
   //zerar todos os valores do vetor
   for (i = 0; i < 50; i++) {
      quantidade[i] = 0;
   }

   if (!(P == 0)) {
      for (i = 0; i < P; i++) {
         for (j = 1886; j < 2021; j++) {
            if (c[i].anofab == j) {
               Ano[i] = j;
               quantidade[i]++;
            }
         };
      }
   }
   for (i = 0; i < P; i++) {
      printf("\n%d : %d\n", Ano[i], quantidade[i]);
   }
}

// função principal
int main() {
   int posAtual = 0;
   int opc = 0;
   Pessoa vet[50];
   Carro tam[50];

   //ponto de retorno do switch 
   do {
      opc = menu(vet, tam, posAtual);
      if (opc == 1) {
         posAtual++;
      }
   } while (opc != 6);
   return 0;
}