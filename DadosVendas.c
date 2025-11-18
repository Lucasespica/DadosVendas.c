#include "Arvore.h"

int gerarIDUnico(Arv *Pai)
{
    int id;
    bool idExiste;

    do
    {
        id = rand() % 9999 + 1000;
        idExiste = false;

    }
    while (idExiste);

    return id;
}

void gerarMatricula()
{
    char letra = 'A' + (rand() % 26);
    int numero = rand() % 1000;
    sprintf(matricula, "%c%03d", letra, numero); //arrumar depois
}
int main()
{
    srand((unsigned)time(NULL));
    Arv *teste = criaArv();
    int id = gerarIDUnico(teste);
    printf("%d", id);

}
