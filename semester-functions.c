#include "includes.h"


Semestre* create_sem(char*nome){
    Semestre *sem=(Semestre*)calloc(1,sizeof(Semestre));
    strcpy(sem->nome,nome);
    return sem;
}

Aluno_Disciplina* create_node(){
    return (Aluno_Disciplina*)calloc(1,sizeof(Aluno_Disciplina));
}

Aluno_Disciplina* buscar_aluno_disciplina(Aluno *aluno,Disciplina *disciplina,Semestre *sem){
    Aluno_Disciplina *aux=sem->first;
    while(aux!=NULL){
        if(aux->aluno==aluno && aux->disciplina==disciplina){
            return aux;
        }
        aux=aux->prox;
    }
    return NULL;
}

int append_aluno_disciplina(Aluno *aluno,Disciplina *disciplina,Semestre *sem){
    Aluno_Disciplina *aux=sem->first;
    if(aux==NULL){
        Aluno_Disciplina *new = create_node();
        new->aluno=aluno;
        new->disciplina=disciplina;
        sem->first=new;
        sem->end=new;
        return 1;
    }
    if(buscar_aluno_disciplina(aluno,disciplina,sem)!=NULL) return 0;
    Aluno_Disciplina *new= create_node();
    new->aluno=aluno;
    new->disciplina=disciplina;
    sem->end->prox=new;
    sem->end=new;
    return 1;
}

void free_semestre(Semestre *sem){
    Aluno_Disciplina *aux=sem->first,*temp;
    while(aux!=NULL){
        temp=aux;
        aux=aux->prox;
        free(temp);
    }
    free(sem);
}

void insercao_semestre(Semestre *sem,Aux_al *al,Aux_di *di){
    int continuar;
    do{
        int codigo_al,codigo_di,printar;
        Aluno *aluno;
        Disciplina *disciplina;
        printf("\nVoce deseja ver a lista de alunos? (digite 0 para nao ou 1 para sim) ");
        scanf("%d",&printar);
        if(printar==1) print_al(al);
        printf("Digite o codigo do aluno: ");
        scanf("%d",&codigo_al);
        aluno=buscar_aluno(codigo_al,al);
        if(aluno==NULL) {
            printf("\nAluno nao encontrado\n");
            printf("\nDeseja tentar novamente? (digite 0 para nao ou 1 para sim) ");
            scanf("%d",&continuar);
            if(continuar==0) break;
            else continue;
        }
        printar=0;
        printf("\nVoce deseja ver a lista de disciplinas? (digite 0 para nao ou 1 para sim) ");
        scanf("%d",&printar);
        if(printar==1) print_di(di);
        printf("Digite o codigo da disciplina que voce deseja cadastrar o aluno: ");
        scanf("%d",&codigo_di);
        disciplina= buscar_disciplina(codigo_di,di);
        if(disciplina==NULL){
            printf("\nDisciplina nao encontrada\n");
            printf("\nDeseja tentar novamente? (digite 0 para nao ou 1 para sim) ");
            scanf("%d",&continuar);
            if(continuar==0) break;
            else continue;
        }
        if(!append_aluno_disciplina(aluno,disciplina,sem)){
            printf("\nO aluno ja esta cadastrado\n");
        }
        printf("\nDeseja cadastrar mais alunos em disciplinas? (digite 0 para nao ou 1 para sim) ");
        scanf("%d",&continuar);
    }
    while(continuar);
    return;

}

int remove_aluno_disciplina(Semestre *sem,Aux_al *al,Aux_di *di){
    int codigo_al,codigo_di;
    printf("\nDigite o codigo do Aluno: ");
    scanf("%d",&codigo_al);
    Aluno *aluno=buscar_aluno(codigo_al,al);
    if(aluno==NULL){
        printf("\nNao foi encontrado esse aluno, deseja tentar novamente? (digite 0 para nao ou 1 para sim) ");
        int novamente;
        scanf("%d",&novamente);
        if(novamente==0)return 0;
        else{
            remove_aluno_disciplina(sem,al,di);
            return 0;
        }
    }
    printf("\nDigite o codigo da Disciplina: ");
    scanf("%d",&codigo_di);
    Disciplina *disciplina=buscar_disciplina(codigo_di,di);
    if(disciplina==NULL){
        printf("\nNao foi encontrada essa disciplina, deseja tentar novamente? (digite 0 para nao ou 1 para sim) ");
        int novamente;
        scanf("%d",&novamente);
        if(novamente==1)return 0;
        else{
            remove_aluno_disciplina(sem,al,di);
            return 0;
        }
    }
    Aluno_Disciplina *aux=sem->first,*aux2;
    if(aux==NULL){
        printf("nao ha nenhum aluno cadastrado a nenhuma disciplina nesse semestre");
        return 0;
    }
    if(aux->aluno==aluno && aux->disciplina==disciplina){
        sem->first=sem->first->prox;
        free(aux);
        printf("\nAluno Removido\n");
        return 0;
    }
    while(aux->prox!=NULL){
        if(aux->prox->aluno==aluno && aux->prox->disciplina==disciplina){
            aux2=aux->prox;
            aux->prox=aux->prox->prox;
            free(aux2);
            printf("\nAluno Removido\n");
            return 1;
        }
        aux=aux->prox;
    }
    printf("\nNenhum aluno encontrado nessa disciplina\n");
    return 0;
}

void print_dis_al(Aux_al *al,Aux_di *di,Semestre *sem){
    int codigo,key=0;
    Aluno *aluno;
    Disciplina *aux=di->first;
    printf("Digite o codigo do aluno: ");
    scanf("%d",&codigo);
    aluno=buscar_aluno(codigo,al);
    if(aluno==NULL){
        printf("\nNao foi possivel encontrar um aluno com codigo %d\n",codigo);
        return;
    }
    printf("\n=============================\n\n");
    printf("Disciplinas cadastradas do aluno %s:\n\n",aluno->nome);
    while(aux!=NULL){
        if(buscar_aluno_disciplina(aluno,aux,sem)!=NULL){
            printf("%s - %s\n\n",aluno->nome,aux->nome);
            key=1;
        }
        aux=aux->prox;
    }
    if(key==0) printf("Nenhuma Disciplina Cadastrada\n\n");
    printf("=============================\n");
    return;
}

void print_alu_di(Aux_al *al,Aux_di *di,Semestre *sem){
    int codigo,key=0;
    Aluno *aux=al->first;
    Disciplina *disciplina;
    printf("Digite o codigo da disciplina: ");
    scanf("%d",&codigo);
    disciplina=buscar_disciplina(codigo,di);
    if(disciplina==NULL){
        printf("\nNao foi possivel encontrar uma disciplina com codigo %d\n",codigo);
        return;
    }
    printf("\n=============================\n\n");
    printf("Alunos cadastrados em %s:\n\n",disciplina->nome);
    while(aux!=NULL){
        if(buscar_aluno_disciplina(aux,disciplina,sem)!=NULL){
            printf("%s - %s\n\n",aux->nome,disciplina->nome);
            key=1;
        }
        aux=aux->prox;
    }
    if(key==0) printf("Nenhum aluno cadastrado\n\n");
    printf("=============================\n");
    return;
}

void menu_semestre(Semestre *sem,Aux_al *al,Aux_di *di){
    printf("\nVoce esta no semestre %s\nO que voce deseja fazer?\n",sem->nome);
    printf("1 - cadastrar um aluno em uma disciplina\n2 - Remover um aluno de uma disciplina\n3 - Consultar as disciplinas de um aluno\n4 - Consultar os alunos cadastrados em uma disciplina\n5 - Sair\n");
    int opcao;
    scanf("%d",&opcao);
    switch (opcao){
        case 1:
            insercao_semestre(sem,al,di);
            break;
        case 2:
            remove_aluno_disciplina(sem,al,di);
            break;
        case 3:
            print_dis_al(al,di,sem);
            break;
        case 4:
            print_alu_di(al,di,sem);
            break;
        case 5:
            return;
        default:
            break;
    }
    menu_semestre(sem,al,di);
}

void menu_alunos(Aux_al *al,Aux_di *di, Semestre *sem){
    printf("Voce esta no menu principal\nO que voce deseja fazer?");
    printf("\n0 - Entrar em um semestre\n1 - Ver os alunos cadastrados\n2 - Ver as disciplinas cadastradas\n3 - adicionar novos alunos\n4 - adiconar novas disciplinas\n5 - remover algum aluno\n6 - remover alguma disciplina\n7 - Salvar\n8 - Sair\n");
    int opcao;
    scanf("%d",&opcao);
    switch (opcao){
        case 0:
            if(sem -> first != NULL){
                int choice;
                printf("Voce ja fez alteracoes em um semestre anterior. Deseja salva-las?\n0 - Nao\n1 - Sim\n2 - Cancelar\n");
                scanf("%d",&choice);
                if(choice == 1) save_sem(sem);
                if(choice == 2) {menu_alunos(al,di, sem); return;}
            }
            sem=create_sem("");
            printf("\nQual semestre voce quer entrar?\n");
            char nome[DIM2];
            scanf("%s",nome);
            sem=completar_semestre(nome,al,di);
            menu_semestre(sem,al,di);
            break;
        case 1:
            print_al(al);
            break;
        case 2:
            print_di(di);
            break;
        case 3:
            cadastrar_alunos(al);
            break;
        case 4:
            cadastrar_disciplinas(di);
            break;
        case 5:
            remove_al(al);
            break;
        case 6:
            remove_di(di);
            break;
        case 7:
            save_sem(sem);
            return;
        case 8:
            save_sem(sem);
            free_semestre(sem);
            break;
        default:
            break;
    }
    menu_alunos(al,di, sem);
}
