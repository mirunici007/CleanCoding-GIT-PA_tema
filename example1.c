///Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf
#include <stdlib.h>
#include <stdio.h>

typedef struct ListaRestaurante
{
    int restaurant_id;               /// pentru simplitate, folosim variabile de tip int pentru a numi restaurantele/locatiile
    struct ListaRestaurante *next;
}RESTAURANT;

typedef struct LantRestaurante
{
    int nr_noduri;
    int *vizitate;
    RESTAURANT **lista;
}RESTAURANT_GRAF;

typedef struct stiva
{
    int top;
    int capacitate_max;
    int *elemente_stiva;
} STIVA;

RESTAURANT *creeazaNod(int numar_restaurant)
{
    RESTAURANT *nod = malloc(sizeof(RESTAURANT));

    nod->restaurant_id = numar_restaurant;
    nod->next = NULL;

    return nod;
}

void adaugaLaturi(RESTAURANT_GRAF *graf,int plecare,int destinatie)
{
    RESTAURANT *nod = creeazaNod(destinatie);

    nod->next = graf->lista[plecare - 1];
    graf->lista[plecare - 1] = nod;

    nod = creeazaNod(plecare);

    nod->next = graf->lista[destinatie - 1];
    graf->lista[destinatie - 1] = nod;
}

RESTAURANT_GRAF *creeazaGraf(int nr_noduri)
{
    int contor;
    RESTAURANT_GRAF *graf_rest = malloc(sizeof(RESTAURANT_GRAF));

    graf_rest->nr_noduri = nr_noduri;
    graf_rest->lista = malloc(sizeof(RESTAURANT *)*nr_noduri);
    graf_rest->vizitate = malloc(sizeof(int) * nr_noduri);

    for (contor = 0; contor < nr_noduri; contor++)
    {
        graf_rest->lista[contor] = NULL;
        graf_rest->vizitate[contor] = 0;
    }

    return graf_rest;
}

STIVA *creeazaStiva(int capacitate_stiva)
{
    STIVA *stiva = malloc(sizeof(STIVA));
    stiva->elemente_stiva = malloc(capacitate_stiva*sizeof(int));
    stiva->top = -1;
    stiva->capacitate_max = capacitate_stiva;

    return stiva;
}

void adaugaElement(int restaurant_id,STIVA *stiva_rest)
{
    stiva_rest->top = stiva_rest->top + 1;
    stiva_rest->elemente_stiva[stiva_rest->top] = restaurant_id;
}

int parcurgeNoduri(RESTAURANT_GRAF *graf_rest,STIVA *stiva_rest,int id_inceput,int *drum,int nod_sfarsit)
{
    RESTAURANT *noduri_vecine = graf_rest->lista[id_inceput];
    RESTAURANT *lista_auxiliara = noduri_vecine;

    graf_rest->vizitate[id_inceput] = 1;
    adaugaElement(id_inceput + 1, stiva_rest);
    drum[stiva_rest->top] = id_inceput + 1;

    if (id_inceput == nod_sfarsit)
    {
        return 1;
    }

    while (lista_auxiliara != NULL)
    {
        int nod_vecin = lista_auxiliara->restaurant_id;
        if (graf_rest->vizitate[nod_vecin - 1] == 0)
        {
            if (parcurgeNoduri(graf_rest, stiva_rest, nod_vecin - 1, drum, nod_sfarsit))
            {
                return 1;
            }
        }
        lista_auxiliara = lista_auxiliara->next;
    }

    graf_rest->vizitate[id_inceput] = 0;
    stiva_rest->top--;

    return 0;
}

void adaugaMuchii(RESTAURANT_GRAF *graf_rest,int numar_muchii,int nr_noduri)
{
    int plecare, destinatie, contor;
    printf("Adauga nodul de plecare si nodul de sosire pentru fiecare dintre cele %d munchii (notate de la 1 la %d):\n", numar_muchii, nr_noduri);
    for (contor = 0; contor < numar_muchii ; contor++)
    {
        scanf("%d%d", &plecare, &destinatie);
        adaugaLaturi(graf_rest, plecare, destinatie);
    }
}

void stergeRestauranteVizitate(RESTAURANT_GRAF *graf_rest, int nr_noduri)
{
    for (int contor=0; contor < nr_noduri; contor++)
    {
        graf_rest->vizitate[contor] = 0;
    }
}

void existaDrum(RESTAURANT_GRAF *graf_rest, int nr_noduri, STIVA *stiva, int nod_start, int nod_final)
{
    int *drum = malloc(nr_noduri * sizeof(int));

    if (parcurgeNoduri(graf_rest, stiva, nod_start - 1, drum, nod_final - 1))
    {
        printf("Drumul parcurs: ");
        for (int i = 0; i <= stiva->top; i++)
        {
            printf("%d ", drum[i]);
        }
        printf("\n");
    }
    else
    {
        printf("Nu exista drum intre restaurantele %d si %d.\n", nod_start, nod_final);
    }

    free(drum);
}


int main()
{
    int nr_noduri;
    int numar_muchii;
    int plecare, destinatie;

    printf("Cate noduri are graficul? ");
    scanf("%d", &nr_noduri);

    printf("Cate muchii are graficul? ");
    scanf("%d", &numar_muchii);

    RESTAURANT_GRAF *graf_rest = creeazaGraf(nr_noduri);

    STIVA *stiva = creeazaStiva(2 * nr_noduri);

    adaugaMuchii(graf_rest, numar_muchii, nr_noduri);

    printf("Introduceti nodul de plecare si nodul de sosire al drumului de cautat(notate de la 1 la %d): ", nr_noduri);
    scanf("%d%d", &plecare, &destinatie);

    existaDrum(graf_rest, nr_noduri, stiva, plecare, destinatie);
    return 0;
}
