
#include <stdio.h>
#include <stdlib.h>

void createClient()
{
    struct CLIENT {
        int clientID;
        char clientName[200],
             clientAdress[200],
             clientPhone[30];
    }client;

    void createClient() {
        printf("\n---------- Cadastrar novo cliente ----------\n");

        printf("\nNome do cliente.....: ");
        fflush(stdin);
        fgets(client.clientName, 200, stdin);

        printf("\nEndereço.....: ");
        fflush(stdin);
        fgets(client.clientAdress, 200, stdin);

        printf("\nTelefone.....: ");
        fflush(stdin);
        fgets(client.clientPhone, 200, stdin);
    }

    printf("\n---------- Dados do cliente ----------\n");
    printf("\nNome: %s", client.clientName);
    printf("\nEndereço: %s", client.clientAdress);
    printf("\nTelefone: %s", client.clientPhone);

}
