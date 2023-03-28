#include "includes.h"



void append_disciplina(Aux_di *di){
    char nome[DIM];
    char prof[DIM];
    int codigo;
    int creditos;
    printf("Digite o nome da Disciplina: ");
    scanf("%s",nome);
    printf("\nDigite o nome do professor: ");
    scanf("%s",prof);
    printf("\nDigite o codigo da disciplina: ");
    scanf("%d",&codigo);
    printf("\nDigite o numero de creditos da disciplina: ");
    scanf("%d",&creditos);
    Disciplina *aux=di->first;
    while(aux!=NULL){
        if(aux->codigo==codigo){
            printf("Essa Disciplina ja esta na cadastrada\n");
            return ;
        }
        aux=aux->prox;
    }
    Disciplina *new;
    new = (Disciplina*)malloc(sizeof(Disciplina));
    if(di->first==NULL){
        di->first=new;
        di->end=new;
        strcpy(new->nome,nome);
        strcpy(new->prof,prof);
        new->codigo=codigo;
        new->creditos=creditos;
        new->prox=NULL;
        return;
    }
    strcpy(new->nome,nome);
    strcpy(new->prof,prof);
    new->codigo=codigo;
    new->creditos=creditos;
    new->prox=NULL;
    di->end->prox=new;
    di->end=new;
}

void append_aluno(Aux_al *al){
    char nome[DIM];
    int codigo;
    char cpf[CPF];
    printf("Digite o nome: ");
    scanf("%s",nome);
    printf("\nDigite o codigo do aluno: ");
    scanf("%d",&codigo);
    printf("\nDigite o cpf: ");
    scanf("%s",cpf);
    Aluno *aux=al->first;
    while(aux!=NULL){
        if(aux->codigo==codigo){
            printf("Esse aluno ja esta cadastrado\n");
            return ;
        }
        aux=aux->prox;
    }
    Aluno *new;
    new = (Aluno*)malloc(sizeof(Aluno));
    if(al->first==NULL){
        al->first=new;
        al->end=new;
        strcpy(new->nome,nome);
        new->codigo=codigo;
        new->prox=NULL;
        strcpy(new->cpf,cpf);
        return;
    }
    strcpy(new->nome,nome);
    new->codigo=codigo;
    new->prox=NULL;
    strcpy(new->cpf,cpf);
    al->end->prox=new;
    al->end=new;
}

void print_al(Aux_al *al){
    Aluno *aux=al->first;
    while(aux!=NULL){
        printf("%s - %d\n",aux->nome,aux->codigo);
        aux=aux->prox;
    }
    return;
}

void print_di(Aux_di *di){
    Disciplina *aux=di->first;
    while(aux!=NULL){
        printf("%s - %d\n",aux->nome,aux->codigo);
        aux=aux->prox;
    }
    return;
}

void cadastrar_alunos(Aux_al *al){
    int continuar;
    do{
        append_aluno(al);
        printf("\nDeseja cadastrar mais alunos? (digite 0 para nao ou 1 para sim) ");
        scanf("%d",&continuar);
    }
    while(continuar);
}

void cadastrar_disciplinas(Aux_di *di){
    int continuar;
    do{
        append_disciplina(di);
        printf("\nDeseja cadastrar mais disciplinas? (digite 0 para nao ou 1 para sim) ");
        scanf("%d",&continuar);
    }
    while(continuar);
}

void remove_al(Aux_al *al){
    int codigo;
    Aluno *aux=al->first,*aux2;
    printf("digite o codigo do aluno:");
    scanf("%d",&codigo);
    if(aux==NULL) return;
    if(aux->codigo==codigo){
        al->first=al->first->prox;
        free(aux);
        return;
    }
    else{
        while(aux->prox!=NULL){
            if(aux->prox->codigo==codigo){
                aux2=aux->prox;
                aux->prox=aux->prox->prox;
                free(aux2);
                return;
            }
            aux=aux->prox;
        }
        printf("Nao foi possivel encontrar o aluno com codigo %d. Digite novamente\n",codigo);
        return;
    }
}

void remove_di(Aux_di *di){
    int codigo;
    Disciplina *aux=di->first,*aux2;
    printf("digite o codigo da disciplina:");
    scanf("%d",&codigo);
    if(aux==NULL)return;
    if(aux->codigo==codigo){
        di->first=di->first->prox;
        free(aux);
        return;
    }
    else{
        while(aux->prox!=NULL){
            if(aux->prox->codigo==codigo){
                aux2=aux->prox;
                aux->prox=aux->prox->prox;
                free(aux2);
                return;
            }
            aux=aux->prox;
        }
        printf("Nao foi possivel encontrar o aluno com codigo %d. Digite novamente\n",codigo);
        return;
    }
}

Aluno * buscar_aluno(int codigo, Aux_al *al){
    Aluno *aux=al->first;
    while(aux!=NULL){
        if(aux->codigo==codigo){
            return aux;
        }
        aux=aux->prox;
    }
    return NULL;
}

Disciplina *buscar_disciplina(int codigo, Aux_di* di){
    Disciplina *aux=di->first;
    while(aux!=NULL){
        if(aux->codigo==codigo){
            return aux;
        }
        aux=aux->prox;
    }
    return NULL;
}

void free_al(Aux_al *al){
    Aluno *aux=al->first;
    while(aux!=NULL){
        Aluno *temp = aux;
        aux = aux->prox;
        free(temp);
    }
    free(al);
}

void free_di(Aux_di *di){
    Disciplina *aux=di->first;
    while(aux!=NULL){
        Disciplina *temp = aux;
        aux = aux->prox;
        free(temp);
    }
    free(di);
}