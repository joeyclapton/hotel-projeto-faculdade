#include <stdio.h>
#include <stdlib.h>
int createClient();

int main()
{
    struct CLIENT {
        int  clientID,
             clientPoins;
        char clientName[200],
             clientAdress[200],
             clientPhone[30];
    }client;

    void createClient() {
        // implementar
            // gerador de id's
            // verificação de cliente
        printf("\n---------- Cadastrar novo cliente ----------\n");
        client.clientID = 0;
        printf("\nNome do cliente.....: ");
        fflush(stdin);
        fgets(client.clientName, 200, stdin);

        printf("\nEndereço.....: ");
        fflush(stdin);
        fgets(client.clientAdress, 200, stdin);

        printf("\nTelefone.....: ");
        fflush(stdin);
        fgets(client.clientPhone, 200, stdin);

        FILE *clients;
        clients = fopen("clients.txt", "a");

        fprintf(clients, "%d", client.clientID);
        fprintf(clients, "%s", client.clientName);
        fprintf(clients, "%s", client.clientAdress);
        fprintf(clients, "%s", client.clientPhone);

        if(clients == NULL){
            printf("Erro na abertura do arquivo. Contacte o administrador do sistema \n");
            system("pause");
            exit(1);
        }



        fclose(clients);
    }

    createClient();


    return 0;
}
