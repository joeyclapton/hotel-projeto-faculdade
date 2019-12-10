#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
--------------------------------------------
Estrutura de data
---------- ---------------------------------
*/
typedef struct date DATE;
struct date{
    int d;
    int m;
    int y;
};
/*
--------------------------------------------
Estrutura dos clientes
---------- ---------------------------------
*/
typedef struct client CLIENT;
struct client{
    int id;
    char name[200],
         adress[200],
         phone[200];
};

/*
--------------------------------------------
Estrutura dos funcionários
---------- ---------------------------------
*/
typedef struct employee EMPLOYEE;
struct employee{
    int id;
    float salary;
    char phone[200],
         job[50],
         name[200];
};

/*
--------------------------------------------
Estrutura das estadias
---------- ---------------------------------
*/
typedef struct stay STAY;
struct stay{
    int id,
        dailyAmount,
        idClient,
        roomNumber;
    DATE entry,
         out;
};

/*
--------------------------------------------
Estrutura dos quartos
---------- ---------------------------------
*/
typedef struct room ROOM;
struct room{
    int roomNumber,
        guestsAmount,
        dailyValue,
        status;
};

/*
--------------------------------------------
Funções complementares
---------- ---------------------------------
*/
void headerDefault();
void menu();
void clearBuffer();
void msgErrorOpenFile() ;
void lowStay();

/*
--------------------------------------------
Funções de cadastro
---------- ---------------------------------
*/
void createClient();
void createEmployee();
void createRoom();
void createStay();

/*
--------------------------------------------
Funções de pesquisa
---------- ---------------------------------
*/
void searchClientByName();
void searchEmployeeByName();

/*
--------------------------------------------
Funções de relatorios
---------- ---------------------------------
*/
void pointsFidelity();
void showStaysClient();

int main()
{
    int option;

    do {

        headerDefault();
        menu();
        fflush(stdin);
        scanf("%d", &option);
        getchar();

        switch( option ) {

            case 1:
                createClient();
            break;

            case 2:
                createEmployee();
            break;

            case 3:
                createRoom();
            break;

            case 4:
                createStay();
            break;

            case 5:
                searchClientByName();
            break;

            case 6:
                searchEmployeeByName();
            break;

            case 7:
                showStaysClient();
            break;

            case 8:
                lowStay();
            break;

            case 9:
                pointsFidelity();
            break;

            case 0:
                printf("\n\nPrograma finalizado com sucesso\n\n");
            break;

            default:
                printf("\nOpção inválida! Escolha as opções do Menu");
            break;

        }

    } while( option != 0 );
}

// Cabeçalho padrão
void headerDefault() {

    printf("\n--------------------------------------------");
    printf("\nHOTEL Descanso garantido - V0.0.1\n");
    printf("\n15:30 3/12/2019");
    printf("\n--------------------------------------------\n");

}

// Menu de opções
void menu() {

    printf("\nEscolha uma opção \n");
    printf("\n1 - Cadastrar cliente");
    printf("\n2 - Cadastrar funcionário(a)");
    printf("\n3 - Cadastrar quarto");
    printf("\n4 - Cadastrar estadia");
    printf("\n5 - Pesquisar cliente");
    printf("\n6 - Pesquisar funcionário");
    printf("\n7 - Pesquisar estadia(s) de um cliente");
    printf("\n8 - Dar baixa em uma estadia");
    printf("\n9 - Ver pontos de fidelidade de um cliente");
    printf("\n\n0 - SAIR");
    printf("\n\nSelecione a opção.....: ");

}

// Limpar o buffer do teclado
void clearBuffer() {
    fflush(stdin);
}

void msgErrorOpenFile() {
    printf("\nErro na abertura do arquivo!");
    printf("\nContate o administrador do sistema!\n");
}
// Criar cliente
void createClient() {

    FILE *clientFile;
    CLIENT c;

    clientFile = fopen("clients.dat", "ab");

    headerDefault();

    if( clientFile == NULL ) {

        msgErrorOpenFile();
        exit(1);

    } else {

        c.id = (rand() % 9999) + 10000;

        clearBuffer();
        printf("Digite o nome do cliente.....: ");
        gets(c.name);

        clearBuffer();
        printf("Telefone.....: ");
        gets(c.phone);

        clearBuffer();
        printf("Endereço.....: ");
        gets(c.adress);

        fwrite(&c, sizeof(CLIENT), 1, clientFile);

        fclose(clientFile);
    }
}

// Criar funcionário
void createEmployee() {

    FILE *employeeFile;
    EMPLOYEE e;

    employeeFile = fopen("employees.dat", "ab");

    headerDefault();

    if( employeeFile == NULL ) {

        msgErrorOpenFile();
        exit(1);

    } else {

        e.id = (rand() % 9999) + 10000;

        clearBuffer();
        printf("Digite o nome do funcionário(a).....: ");
        gets(e.name);

        clearBuffer();
        printf("Telefone.....: ");
        gets(e.phone);

        clearBuffer();
        printf("Cargo.....: ");
        printf("\n> recepcionista");
        printf("\n> aux. de limpeza ");
        printf("\n> garçom ");
        printf("\n> gerente ");
        printf("\n\nDigite o cargo.....: ");
        gets(e.job);

        clearBuffer();
        printf("Salário.....: ");
        scanf("%f", &e.salary);

        fwrite(&e, sizeof(EMPLOYEE), 1, employeeFile);

        fclose(employeeFile);
    }
}

// Criar quarto
void createRoom() {

     FILE *roomFile;
     ROOM r;

    roomFile = fopen("rooms.dat", "ab");

    headerDefault();

    if( roomFile == NULL ) {

        msgErrorOpenFile();
        exit(1);

    } else {

        clearBuffer();
        printf("Número do quarto.....: ");
        scanf("%d", &r.roomNumber);

        clearBuffer();
        printf("Quantidade de hospedes.....: ");
        scanf("%d", &r.guestsAmount);

        clearBuffer();
        printf("Valor da diária.....: ");
        scanf("%d", &r.dailyValue);

        clearBuffer();
        printf("\nStatus: ");
        printf("\n\n0 - desocupado");
        printf("\n1 - ocupado");
        printf("\nDigite o status.....: ");
        scanf("%d", &r.status);

        fwrite(&r, sizeof(ROOM), 1, roomFile);

        fclose(roomFile);
    }

}

// Criar estadia
void createStay() {

    char name[200];
    int  guests, dailys, roomNumber;

    FILE *roomFile;
    FILE *clientFile;
    FILE *stayFile;

    ROOM r;
    STAY s;
    CLIENT c;

    roomFile = fopen("rooms.dat", "rb");
    clientFile = fopen("clients.dat", "rb");
    stayFile = fopen("stays.dat", "ab");

    if( roomFile == NULL ) {

        msgErrorOpenFile();
        exit(1);

    } else {

        clearBuffer();
        printf("\nDigite o nome do cliente: ");
        gets(name);

        while( fread(&c, sizeof(CLIENT), 1, clientFile) == 1 ) {

            if( strcmp(name, c.name) == 0 ) {

                clearBuffer();
                printf("\nDigite a quantidade de hospedes.....: ");
                scanf("%d", &guests);
                printf("\nDigite o número do quarto.....: ");
                scanf("%d", &roomNumber);
                while( fread(&r, sizeof(ROOM), 1, roomFile) == 1 ) {

                    if( r.roomNumber == roomNumber && guests == r.guestsAmount ) {

                        if ( r.status == 0 ) {

                            s.id = (rand() % 9999) + 10000;

                            printf("\nDigite a data de entrada: ");
                            printf("\nDia: ");
                            scanf("%d", &s.entry.d);
                            printf("\nMês: ");
                            scanf("%d", &s.entry.m);
                            printf("\nAno: ");
                            scanf("%d", &s.entry.y);

                            printf("\nDigite a data de saída: ");
                            printf("\nDia: ");
                            scanf("%d", &s.out.d);
                            printf("\nMês: ");
                            scanf("%d", &s.out.m);
                            printf("\nAno: ");
                            scanf("%d", &s.out.y);

                            s.dailyAmount = s.out.d > s.entry.d ? s.out.d - s.entry.d : s.entry.d - s.out.d;
                            s.idClient = c.id;
                            s.roomNumber = r.roomNumber;

                            r.status = 1;

                            fwrite(&s, sizeof(STAY), 1, stayFile);

                            printf("Estadia cadastrada com sucesso!");

                        } else {
                        }
                    } else {


                    }

                }


            }

        }

    }
    fclose(clientFile);
    fclose(roomFile);
    fclose(stayFile);
    getchar();
    // fwrite(&r, sizeof(ROOM), 1, roomFile);

}

// Pesquisar cliente por nome
void searchClientByName() {

    FILE *clientFile;
    CLIENT c;

    char name[200];

    clientFile = fopen("clients.dat", "rb");

    headerDefault();

    if( clientFile == NULL ) {

        msgErrorOpenFile();
        exit(1);

    } else {

        clearBuffer();
        printf("\nDigite o nome do cliente.....: ");
        gets(name);

        while( fread(&c, sizeof(CLIENT), 1, clientFile) == 1 ) {

            if( strcmp(name, c.name) == 0 ) {
                printf("\n\n-----------------------------------------------------\n");
                printf("\nDados do cliente");
                printf("\nCódigo: %d\n", c.id);
                printf("Nome: %s\n", c.name);
                printf("Endereço: %s\n", c.adress);
                printf("Telefone: %s\n", c.phone);
                printf("\n-----------------------------------------------------\n\n");
            }

        }

    }
    fclose(clientFile);
    getchar();

}


// Pesquisar funcionário pelo nome
void searchEmployeeByName() {

    FILE *employeeFile;
    EMPLOYEE e;

    char name[200];

    employeeFile = fopen("employees.dat", "rb");

    headerDefault();

    if( employeeFile == NULL ) {

        msgErrorOpenFile();
        exit(1);

    } else {

        clearBuffer();
        printf("\nDigite o nome do funcionário.....: ");
        gets(name);

        while( fread(&e, sizeof(EMPLOYEE), 1, employeeFile) == 1 ) {

            if( strcmp(name, e.name) == 0 ) {
                printf("\n\n-----------------------------------------------------\n");
                printf("\nDados do cliente");
                printf("\nCódigo: %d\n", e.id);
                printf("Nome: %s\n", e.name);
                printf("Telefone: %s\n", e.phone);
                printf("Cargo: %s\n", e.job);
                printf("Salário: %2.f\n", e.salary);
                printf("\n-----------------------------------------------------\n\n");
                printf("\nTecle ENTER para continuar.");
            }

        }

    }
    fclose(employeeFile);
    getchar();

}

void showStaysClient() {

    FILE *staysFile;
    STAY s;

    int idClient;

    staysFile = fopen("stays.dat", "rb");

    headerDefault();

    if( staysFile == NULL ) {

        msgErrorOpenFile();
        exit(1);

    } else {

        clearBuffer();
        printf("\nDigite o código do cliente.....: ");
        scanf("%d", &idClient);

        while( fread(&s, sizeof(STAY), 1, staysFile) == 1 ) {

                if(idClient == s.idClient) {
                    printf("\n\n-----------------------------------------------------\n");
                    printf("\nDados do cliente");
                    printf("\nCódigo: %d\n", s.id);
                    printf("Código do cliente: %d\n", s.idClient);
                    printf("Número do quarto: %d\n", s.roomNumber);
                    printf("Quantidade de diárias: %d\n", s.dailyAmount);
                    printf("Data de entrada: %d%d%d\n", s.entry.d, s.entry.m, s.entry.y);
                    printf("Data de saída: %d%d%d\n", s.out.d, s.out.m, s.out.y);
                    printf("\n-----------------------------------------------------\n\n");
                }


        }

    }
    fclose(staysFile);
    getchar();

}

void lowStay() {

    FILE *staysFile;
    FILE *roomFile;
    STAY s;
    ROOM r;

    int idStay;
    int total;
    int roomNumber;

    staysFile = fopen("stays.dat", "rb");
    roomFile = fopen("rooms.dat", "rb");

    headerDefault();

    if( staysFile == NULL ) {

        msgErrorOpenFile();
        exit(1);

    } else {

        clearBuffer();
        printf("\nDigite o código da estadia a ser finalizada.....: ");
        scanf("%d", &idStay);

        while( fread(&s, sizeof(STAY), 1, staysFile) == 1 ) {

            if(idStay == s.id) {

                roomNumber = s.roomNumber;

            }
        }

    }

        while( fread(&r, sizeof(ROOM), 1, roomFile) == 1 ) {

            if(roomNumber == r.roomNumber) {

                r.status = 0;
                printf("Baixa em estadia dada com sucesso!");
            }
        }

    fclose(roomFile);
    fclose(staysFile);
    getchar();

}

void pointsFidelity() {

    FILE *staysFile;
    STAY s;

    int points = 0;
    int idClient;

    staysFile = fopen("stays.dat", "rb");

    headerDefault();

    if( staysFile == NULL ) {

        msgErrorOpenFile();
        exit(1);

    } else {

        clearBuffer();
        printf("\nDigite o código do cliente.....: ");
        scanf("%d", &idClient);

        while( fread(&s, sizeof(STAY), 1, staysFile) == 1 ) {

                if(idClient == s.idClient) {
                    printf("\n\n-----------------------------------------------------\n");
                    printf("Código do cliente: %d\n", s.idClient);
                    printf("Quantidade de pontos anteriores: %d\n", points += s.dailyAmount * 10);
                    printf("\n-----------------------------------------------------\n\n");
                }


        }

        printf("\nTotal: %d", points);

    }
    fclose(staysFile);
    getchar();

}
