#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>

//--------------------------------------------------------DEFINES--------------------------------------------------------
#define MAXMED 10
#define MAXPAC 250
#define MAXCONSULT 10
//-----------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------TYPEDEF--------------------------------------------------------
typedef struct MEDICO medico;
typedef struct PACIENTE paciente;
typedef struct CONSULTA consulta;
//-----------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------DECLARACAO DE FUNCOES------------------------------------------------
int menu();
int inserir_med(medico *tab_m,int n_m,paciente *tab_p,int n_p);
int inserir_pac(medico *tab_m,int n_m,paciente *tab_p,int n_p);
int edit_med(medico *tab_m,int n_m);
int edit_pac(paciente *tab_p,int n_p,medico *tab_m,int n_m);
int elim_med(medico *tab_m,int n_m);
int elim_pac(paciente *tab_p,int n_p);
medico obtem_info_med(medico *tab_m,int n_m);
paciente obtem_info_pac(paciente *tab_p,int n_p,medico *tab_m,int n_m);
consulta obtem_info_consult(paciente *tab_p,int n_p,int i);
int verifica_nome_igual_med(medico *tab_m,int n_m,char nome_med[]);
int verifica_nome_igual_pac(paciente *tab_p,int n_p,char nome_pac[]);
int marc_consult(consulta *tab_c,int n_c,medico *tab_m,int n_m,paciente *tab_p,int n_p);
int lista_med(medico *tab_m,int n_m);
int lista_pac(paciente *tab_p,int n_p,consulta *tab_c,int n_c);
int lista_med_esp(medico *tab_m,int n_m);
int num_med_esp(medico *tab_m,int n_m);
int num_consult_idade(paciente *tab_p,int n_p);
void clrscr();
//-----------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------ESTRUTURAS------------------------------------------------------
struct dados_pessoais{
        char nome[50];
        int idade;
};

struct dados_pessoais_pm{
        char nome_p[50];
        int idade_p;
        char nome_m[50];
        int idade_m;
};

struct dados_consul{
        int media_consult_dia;
        int tempo_medio_consul;
};
struct horario{
        char segunda[10];
        char terca[10];
        char quarta[10];
        char quinta[10];
        char sexta[10];
        char sabado[10];
        char domingo[10];
};

struct histo_consultas{
        char tipo_consul[10];
        char data[10];
        char medico[30];
        char espec[20];
        char descricao[100];
};

struct MEDICO{
        struct dados_pessoais Dados_Pessoais;
        char espec[20];
        struct horario hor_trab;
        int num_pac;
        struct dados_consul Dados_Consultas;
        int idade_inicio_trab;
        int anos_trab;
};

struct PACIENTE{
        struct dados_pessoais Dados_Pessoais;
};

struct CONSULTA{
        struct dados_pessoais_pm Dados_Pessoais_PM;
        struct histo_consultas Historico_Consultas;
};
//-----------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------MAIN------------------------------------------------------------
int main()
{
        int op_menu,tam=3;
        char op_inserir,op_editar,op_eliminar;
        int total_m=0,total_p=0,total_c=0;

        medico m[MAXMED];
        paciente p[MAXPAC];
        consulta c[MAXCONSULT];

        do{
                clrscr();
                printf("\t\t<<<----------Gestao de uma clinica medica---------->>>\n\n");
                op_menu=menu();     //Escolha da opção no menu
        switch(op_menu){

                case 1:
                        clrscr();
                        printf("-->Prima m se deseja ADICIONAR um novo medico\n");
                        printf("\t\t\tou\n");
                        printf("-->Prima p se deseja ADICIONAR um novo paciente.\n");
                        scanf("%s",&op_inserir);

                        if(op_inserir=='m')
                        {
                                total_m=inserir_med(m,total_m,p,total_p);
                                clrscr();
                        }
                        else
                                if(op_inserir=='p')
                                {
                                        total_p=inserir_pac(m,total_m,p,total_p);
                                        clrscr();
                                }
                                else{
                                        printf("Opcao invalida\n");
                                        system("pause");
                                        clrscr();
                                }
                                clrscr();
                        break;

                case 2:
                        clrscr();
                        printf("-->Prima m se deseja EDITAR um medico\n");
                        printf("\t\t\tou\n");
                        printf("-->Prima p se deseja EDITAR um paciente\n");
                        scanf("%s",&op_editar);

                        if(op_editar=='m')
                                total_m=edit_med(m,total_m);
                        else
                                if(op_editar=='p')
                                        total_p=edit_pac(p,total_p,m,total_m);
                                else{
                                        printf("Opcao invalida\n");
                                        system("pause");
                                        clrscr();
                                }
                        break;

                case 3:
                        clrscr();
                        printf("-->Prima m se deseja ELIMINAR um medico\n");
                        printf("\t\t\tou\n");
                        printf("-->Prima p se deseja ELIMINAR um paciente\n");
                        scanf("%s",&op_eliminar);

                        if(op_eliminar=='m')
                                total_m=elim_med(m,total_m);
                        else
                                if(op_eliminar=='p')
                                        total_p=elim_pac(p,total_p);
                                else
                                {
                                        printf("Opcao invalida\n");
                                        system("pause");
                                        clrscr();
                                }
                        break;

                  case 4:
                          clrscr();
                          total_c=marc_consult(c,total_c,m,total_m,p,total_p);
              break;

              case 5:
                          clrscr();
                          total_p=lista_pac(p,total_p,c,total_c);
                          break;

                  case 6:
                          clrscr();
                          total_m=lista_med(m,total_m);
                          break;

                  case 7:
                          clrscr();
                          total_m=lista_med_esp(m,total_m);
                          break;

                  case 8:
                          clrscr();
                          total_m=num_med_esp(m,total_m);
                          break;

                  /*case 9:
                          clrscr();
                          total_p=num_consult_idade(p,total_p);
                          break;*/

                  case 0:
                            clrscr();
                                printf("\n\t\tFim do programa\n\n");
                                system("pause");
                          break;

                default:
                        printf("OPCAO INEXISTENTE\n\n");
        }
        }while(op_menu!=0);
        return 0;
}
//-----------------------------------------------------------------------------------------------------------------------

//-----------------------------------------------FUNÇÕES-----------------------------------------------------------------
int menu()
{
        int i;

        printf("_______________________________________________________________________________\n");
        printf(" 1 - Adicionar medico/paciente\n");
        printf("_______________________________________________________________________________\n");
        printf(" 2 - Editar medico/paciente\n");
        printf("_______________________________________________________________________________\n");
        printf(" 3 - Eliminar medico/paciente\n");
        printf("_______________________________________________________________________________\n");
        printf(" 4 - Marcacao de uma nova consulta\n");
        printf("_______________________________________________________________________________\n");
        printf(" 5 - Listagem completa dos pacientes\n");
        printf("_______________________________________________________________________________\n");
        printf(" 6 - Listagem completa dos medicos\n");
        printf("_______________________________________________________________________________\n");
        printf(" 7 - Listagem dos medicos de uma determinada especialidade\n");
        printf("_______________________________________________________________________________\n");
        printf(" 8 - Numero de medicos por especialidade\n");
        printf("_______________________________________________________________________________\n");
        printf(" 9 - Numero de consultas por faixa etaria\n");
        printf("_______________________________________________________________________________\n");
        printf(" 0 - Sair do programa\n\n");

        printf("INTRODUZA A OPCAO DESEJADA(0,1,2,3,4,5,6,7,8,9): ");
        do{
                fflush(stdin);
                scanf("%d",&i);
        }while(i<0 && i>9);

        return i;
}
int inserir_med(medico *tab_m,int n_m,paciente *tab_p,int n_p)
{
        if(n_m>=MAXMED)
        {
                clrscr();
                printf("Tabela completa\n");
                system("pause");
                return n_m;
        }
        else
        {
                clrscr();
                printf("Medico \n\n");
                *(tab_m+n_m)=obtem_info_med(tab_m,n_m);
                printf("\n\nMEDICO ADICIONADO\n");
                system("pause");
                return n_m+1;
        }
}

int inserir_pac(medico *tab_m,int n_m,paciente *tab_p,int n_p)
{
        if(n_p>=MAXPAC)
        {
                clrscr();
                printf("Tabela completa\n");
                system("pause");
                return n_p;
        }
        else
        {
                clrscr();
                printf("Paciente \n\n");
                *(tab_p+n_p)=obtem_info_pac(tab_p,n_p,tab_m,n_m);
                printf("\n\nPACIENTE ADICIONADO\n");
                system("pause");
                return n_p+1;
        }
}

int edit_med(medico *tab_m,int n_m)
{
        char nome_m[50];
        int i;
        if(n_m==0)
        {
                clrscr();
                printf("\n\nNao existe medicos para editar\n");
                system("pause");
                return n_m;
        }
                printf("Qual o nome do MEDICO que deseja editar: \n");
                fflush(stdin);
                gets(nome_m);
        for(i=0; i<n_m && (strcmp(nome_m,tab_m[i].Dados_Pessoais.nome)!=0); i++);
        if(i==n_m)
        {
                printf("Medico nao encontrado\n");
                system("pause");
                return n_m;
        }
        clrscr();
        printf("Medico\n\n");
        *(tab_m+i)=obtem_info_med(tab_m,n_m);
        printf("\n\nMEDICO EDITADO\n");
        system("pause");
        return n_m;

}

int edit_pac(paciente *tab_p,int n_p,medico *tab_m,int n_m)
{
        char nome_p[50];
        int i;
        if(n_p==0)
        {
                clrscr();
                printf("\n\nNao existe pacientes para editar\n");
                system("pause");
                return n_p;
        }

                printf("Qual o nome do PACIENTE que deseja editar: \n");
                fflush(stdin);
                gets(nome_p);
        for(i=0; i<n_p && (strcmp(nome_p,tab_p[i].Dados_Pessoais.nome)!=0); i++);
        if(i==n_p)
        {
                printf("Paciente nao encontrado\n");
                system("pause");
                return n_p;
        }
        clrscr();
        printf("Paciente\n\n");
        *(tab_p+i)=obtem_info_pac(tab_p,n_p,tab_m,n_m);
        printf("\n\nPACIENTE EDITADO\n");
        system("pause");
        return n_p;

}

int elim_med(medico *tab_m,int n_m)
{
        char nome_m[50];
        int i,pos;
        if(n_m==0)
        {
                clrscr();
                printf("Nao existe medicos para eliminar\n");
                system("pause");
                return n_m;
        }
        printf("Qual o nome do MEDICO que deseja eliminar: \n");
        fflush(stdin);
        gets(nome_m);
        for(i=0; i<n_m && (strcmp(nome_m, tab_m[i].Dados_Pessoais.nome)!=0); i++)
                pos=i;
        if(i==n_m)
        {
                printf("\n\nNao existe o medico que deseja eliminar\n");
                system("pause");
                return n_m;
        }
        else
        {
                *(tab_m+i)=*(tab_m+(n_m-1));
                printf("\n\nMEDICO ELIMINADO\n");
                system("pause");
                return n_m-1;
        }
}

int elim_pac(paciente *tab_p,int n_p)
{
        char nome_p[50];
        int i,pos;
        if(n_p==0)
        {
                clrscr();
                printf("Nao existe pacientes para eliminar\n");
                system("pause");
                return n_p;
        }
        printf("Qual o nome do PACIENTE que deseja eliminar: \n");
        fflush(stdin);
        gets(nome_p);
        for(i=0; i<n_p && (strcmp(nome_p, tab_p[i].Dados_Pessoais.nome)!=0); i++)
                pos=i;
        if(i==n_p)
        {
                printf("\n\nNao existe o paciente que deseja eliminar\n");
                system("pause");
                return n_p;
        }
        else
        {
                *(tab_p+i)=*(tab_p+(n_p-1));
                printf("\n\nPACIENTE ELIMINADO\n");
                system("pause");
                return n_p-1;
        }
}

medico obtem_info_med(medico *tab_m,int n_m)
{
        medico x;
        char hora_trab[10];
        char nome_med[50];
        int res;

        do{
                printf("Nome: \n");
                fflush(stdin);
                gets(nome_med);
                res=verifica_nome_igual_med(tab_m,n_m,nome_med);
        }while(res==1);
        strcpy(x.Dados_Pessoais.nome,nome_med);
        do{
                printf("Idade(entre 30 e 70): \n");
                fflush(stdin);
                scanf("%d",&x.Dados_Pessoais.idade);
        }while(x.Dados_Pessoais.idade<30 || x.Dados_Pessoais.idade>70);//considerando que um medico trabalha entre os 30 e 70 anos
        printf("Especialidade: \n");
        fflush(stdin);
        gets(x.espec);
        printf("Horario de trabalho(introduza manha,tarde,todo dia,folga): \n");
        do{
                        printf("-->Segunda: ");
                        fflush(stdin);
                        gets(hora_trab);
        }while((strcmp(hora_trab,"manha")!=0) && (strcmp(hora_trab,"tarde")!=0) && (strcmp(hora_trab,"todo dia")!=0) && (strcmp(hora_trab,"folga")!=0));
        strcpy(x.hor_trab.segunda,hora_trab);
        do{
                        printf("\n-->Terca: ");
                        fflush(stdin);
                        gets(hora_trab);
        }while((strcmp(hora_trab,"manha")!=0) && (strcmp(hora_trab,"tarde")!=0) && (strcmp(hora_trab,"todo dia")!=0) && (strcmp(hora_trab,"folga")!=0));
        strcpy(x.hor_trab.terca,hora_trab);
        do{
                        printf("\n-->Quarta: ");
                        fflush(stdin);
                        gets(hora_trab);
        }while((strcmp(hora_trab,"manha")!=0) && (strcmp(hora_trab,"tarde")!=0) && (strcmp(hora_trab,"todo dia")!=0) && (strcmp(hora_trab,"folga")!=0));
        strcpy(x.hor_trab.quarta,hora_trab);
        do{
                        printf("\n-->Quinta: ");
                        fflush(stdin);
                        gets(hora_trab);
        }while((strcmp(hora_trab,"manha")!=0) && (strcmp(hora_trab,"tarde")!=0) && (strcmp(hora_trab,"todo dia")!=0) && (strcmp(hora_trab,"folga")!=0));
        strcpy(x.hor_trab.quinta,hora_trab);
        do{
                        printf("\n-->Sexta: ");
                        fflush(stdin);
                        gets(hora_trab);
        }while((strcmp(hora_trab,"manha")!=0) && (strcmp(hora_trab,"tarde")!=0) && (strcmp(hora_trab,"todo dia")!=0) && (strcmp(hora_trab,"folga")!=0));
        strcpy(x.hor_trab.sexta,hora_trab);
        do{
                        printf("\n-->Sabado: ");
                        fflush(stdin);
                        gets(hora_trab);
        }while((strcmp(hora_trab,"manha")!=0) && (strcmp(hora_trab,"tarde")!=0) && (strcmp(hora_trab,"todo dia")!=0) && (strcmp(hora_trab,"folga")!=0));
        strcpy(x.hor_trab.sabado,hora_trab);
        do{
                        printf("\n-->Domingo: ");
                        fflush(stdin);
                        gets(hora_trab);
        }while((strcmp(hora_trab,"manha")!=0) && (strcmp(hora_trab,"tarde")!=0) && (strcmp(hora_trab,"todo dia")!=0) && (strcmp(hora_trab,"folga")!=0));
        strcpy(x.hor_trab.domingo,hora_trab);
        do{
                printf("Numero de pacientes: \n");
                fflush(stdin);
                scanf("%d",&(x.num_pac));
        }while(x.num_pac>MAXPAC);
        printf("Media de consultas por dia: \n");
        fflush(stdin);
        scanf("%d",&(x.Dados_Consultas.media_consult_dia));
        printf("Tempo medio por consulta: \n");
        fflush(stdin);
        scanf("%d",&(x.Dados_Consultas.tempo_medio_consul));
        do{
                printf("Idade em que comecou a trabalhar: \n");
                fflush(stdin);
                scanf("%d",&x.idade_inicio_trab);
        }while(x.idade_inicio_trab<30 || x.idade_inicio_trab>x.Dados_Pessoais.idade);
        x.anos_trab=x.Dados_Pessoais.idade - x.idade_inicio_trab;
        printf("Anos a trabalhar no activo: %d\n",x.anos_trab);
        system("pause");

        return x;
}

paciente obtem_info_pac(paciente *tab_p,int n_p,medico *tab_m,int n_m)
{
        paciente y;
        char nome_pac[50];
        int res;

        do{
                printf("Nome: \n");
                fflush(stdin);
                gets(nome_pac);
                res=verifica_nome_igual_pac(tab_p,n_p,nome_pac);
        }while(res==1);
        strcpy(y.Dados_Pessoais.nome,nome_pac);
        do{
                printf("Idade(entre 30 e 70): \n");
                fflush(stdin);
                scanf("%d",&(y.Dados_Pessoais.idade));
        }while(y.Dados_Pessoais.idade<0 || y.Dados_Pessoais.idade>100); //considerando que a idade 0 é um recem nascido com meses de vida

        return y;
}

consulta obtem_info_consult(paciente *tab_p,int n_p,int i)
{
        consulta c;
        char tipo_consulta[10];

        printf("Nome do paciente: %s",c.Dados_Pessoais_PM.nome_p);
        printf("\tIdade do paciente: %d\n",c.Dados_Pessoais_PM.idade_p);
        printf("Nome do medico: %s",c.Dados_Pessoais_PM.nome_m);
        printf("\tIdade do medico: %d\n",c.Dados_Pessoais_PM.idade_m);
        printf("Historico das ultimas 10 consultas\n");
        do{
                printf("--->Tipo de consulta(introduza normal ou urgente): \n");
                fflush(stdin);
                gets(tipo_consulta);
        }while((strcmp(tipo_consulta,"normal")!=0) && (strcmp(tipo_consulta,"urgente")!=0));
        strcpy(c.Historico_Consultas.tipo_consul,tipo_consulta);
        printf("--->Data(dd/mm/yyyy): \n");
        fflush(stdin);
        gets(c.Historico_Consultas.data);
        printf("--->Medico: \n",c.Dados_Pessoais_PM.nome_m);
        printf("--->Especialidade: \n");
        fflush(stdin);
        gets(c.Historico_Consultas.espec);
        printf("--->Descricao da consulta: \n");
        fflush(stdin);
        gets(c.Historico_Consultas.descricao);
        system("pause");

        return c;
}

int verifica_nome_igual_med(medico *tab_m,int n_m,char nome_med[])
{
        int i;

        for(i=0;i<n_m && (strcmp(tab_m[i].Dados_Pessoais.nome,nome_med)!=0);i++);
        if(i==n_m)
                return 0;
        else
        {
                printf("Este nome ja existe\n");
                system("pause");
                return 1;
        }
}

int verifica_nome_igual_pac(paciente *tab_p,int n_p,char nome_pac[])
{
        int i;

        for(i=0;i<n_p && (strcmp(tab_p[i].Dados_Pessoais.nome,nome_pac)!=0);i++);
        if(i==n_p)
                return 0;
        else
        {
                printf("Este nome ja existe\n");
                system("pause");
                return 1;
        }
}
int marc_consult(consulta *tab_c,int n_c,medico *tab_m,int n_m,paciente *tab_p,int n_p)
{
        int i,j;
        char nome_pac[50];
        char nome_med[50];
        if(n_c>MAXCONSULT)
        {
                printf("Tabela Completa\n");
                system("pause");
                return n_c;
        }

        if(n_m==0 || n_p==0)
        {
                printf("Inexistencia de medico(s)/paciente(s)\n");
                system("pause");
                return n_c;
        }
        printf("\t\t<<<----------Marcacao de uma consulta---------->>>\n\n");
        printf("Nome do paciente: \n");
        fflush(stdin);
        gets(nome_pac);
        for(i=0;i<n_p && strcmp(tab_p[i].Dados_Pessoais.nome,nome_pac)!=0;i++);
        if(i==n_p)
        {
                printf("Nao existe o paciente introduzido");
                system("pause");
                return n_c;
        }
        else
        {
                strcpy(tab_c[i].Dados_Pessoais_PM.nome_p,nome_pac);
                tab_c[i].Dados_Pessoais_PM.idade_p=tab_p[i].Dados_Pessoais.idade;
        }
        printf("Nome do medico: \n");
        fflush(stdin);
        gets(nome_med);
        for(j=0;j<n_m && strcmp(tab_m[j].Dados_Pessoais.nome,nome_med)!=0;j++);
        if(j==n_m)
        {
                printf("Nao existe o medico introduzido");
                system("pause");
                return n_c;
        }
        else
        {
                strcpy(tab_c[j].Dados_Pessoais_PM.nome_m,nome_med);
                tab_c[j].Dados_Pessoais_PM.idade_m=tab_m[j].Dados_Pessoais.idade;
        }
        *(tab_c+n_c)=obtem_info_consult(tab_p,n_p,i);

        return n_c+1;
}
int lista_med(medico *tab_m,int n_m)
{
        int i,j=1;
        if(n_m==0)
                {
                        clrscr();
                        printf("--->Lista inexistente porque ainda nao existem medicos\n\n");
                        system("pause");
                        return n_m;
                }
        clrscr();
        for(i=0;i<n_m;i++)
        {
                printf("-->Medico %d\n",j);
                printf("Nome: %s\n",tab_m[i].Dados_Pessoais.nome);
                printf("Idade: %d\n",tab_m[i].Dados_Pessoais.idade);
                printf("Especialidade: %s\n",tab_m[i].espec);
                printf("Horario de trabalho: %s\n",tab_m[i].hor_trab);
                printf("Numero de pacientes: %d\n",tab_m[i].num_pac);
                printf("Media de consultas por dia: %d\n",tab_m[i].Dados_Consultas.media_consult_dia);
                printf("Tempo medio por consulta: %d\n",tab_m[i].Dados_Consultas.tempo_medio_consul);
                printf("Idade em que comecou a trabalhar: %d\n",tab_m[i].idade_inicio_trab);
                printf("Anos a trabalhar no activo: %d\n\n\n",tab_m[i].anos_trab);
                j++;
        }
        system("pause");
        return n_m;
}

int lista_pac(paciente *tab_p,int n_p,consulta *tab_c,int n_c)
{
        int i,j=1;
        if(n_p==0)
                {
                        clrscr();
                        printf("--->Lista inexistente porque ainda nao existem pacientes\n\n");
                        system("pause");
                        return n_p;
                }
        clrscr();
        for(i=0;i<n_p;i++)
        {
                printf("-->Paciente %d\n\n",j);
                printf("Nome: %s\n",tab_p[i].Dados_Pessoais.nome);
                printf("Idade: %d\n",tab_p[i].Dados_Pessoais.idade);
                j++;
        }
        system("pause");
        return n_p;
}

int lista_med_esp(medico *tab_m,int n_m)
{
        char nome_esp[30];
        int j;
        if(n_m==0)
                {
                        clrscr();
                        printf("--->Lista inexistente porque ainda nao existem medicos\n\n");
                        system("pause");
                        return n_m;
                }
        clrscr();
        printf("Qual a especialidade que deseja listar: \n");
        fflush(stdin);
        gets(nome_esp);
        for(j=0;j<n_m;j++)
        {
                if(strcmp(nome_esp,tab_m[j].espec)==0)
                        printf("Nome: %s\t\tEspecialidade: %s\n",tab_m[j].Dados_Pessoais.nome,tab_m[j].espec);
        }
        system("pause");
        return n_m;
}

int num_med_esp(medico *tab_m,int n_m)
{
        int i,j;
        clrscr();
        if(n_m==0)
        {
                printf("Nao ha medicos\n");
                system("pause");
                return n_m;
        }
        for(i=0;i<n_m;i++)
        {
                printf("Especialidade: %s",tab_m[i].espec);
                        for(j=0;j<n_m;j++)
                                printf("\tNome: %s\n",tab_m[i].Dados_Pessoais.nome);
                printf("\n\n");
        }
        system("pause");
        return n_m;
}

int num_consult_idade(paciente *tab_p,int n_p)
{

        return n_p;
}

void clrscr()
{
 HANDLE h_stdout;
 CONSOLE_SCREEN_BUFFER_INFO csbi;
 DWORD dwConSize;
 COORD coordScreen = { 0, 0 };
 DWORD dwCharsWritten;

 h_stdout = GetStdHandle(STD_OUTPUT_HANDLE);

 GetConsoleScreenBufferInfo( h_stdout, &csbi );
 dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

 FillConsoleOutputCharacter( h_stdout, (TCHAR) ' ', dwConSize, coordScreen, &dwCharsWritten );

 SetConsoleCursorPosition( h_stdout, coordScreen );
}
