#include <iostream>
using namespace std;
#include <locale.h>
#include <windows.h>
#include "Bagenda.h"
#define MAX 100
#define N_CPF 11
#define N_CNPJ 14
#define N_CEL 11
#define N_TEL 10

struct pessoal {
    int ID;
    long long int cel, CPF;
    string nome;
};

struct comercial {
    int ID;
    long long int tel, CNPJ;
    string nome;
};

int tipo_contato(string tipo_operacao){ //SELECIONA QUAL AGENDA INSERIR O CONTATO
  int tipo_contato;

  while(true){
    cout << "Qual tipo de contato você deseja "<<tipo_operacao<<" ? 1 - Pessoal\t2 - Comercial\n";
    cin >> tipo_contato;
    if(tipo_contato==1){
      return 1;
    }
    if(tipo_contato==2){
      return 2;
    }
  }
}

int tipo_pesquisa(){ //SELECIONA QUAL DADO A SER PESQUISADO
  int tipo_pesquisa;

  while(true){
    cout << "Qual tipo de pesquisa você deseja ?"<<" 1 - ID\t2 - Nome\n";
    cin >> tipo_pesquisa;
    if(tipo_pesquisa==1){
      return 1;
    }
    if(tipo_pesquisa==2){
      return 2;
    }
  }
}

bool conta_digitos(long long int dado, int n_esperado){ //VERIFICA SE O NÚMERO DE DÍGITOS É O CORRETO
    int n_digitos = 0;
    while(dado!=0){
        dado /= 10;
        n_digitos++;
    }
    if (n_digitos == n_esperado)
        return true;
    else
        return false;
}

istream & operator >> (istream & in,pessoal &ag){//SOBRECARGA PARA INSERIR PESSOAL
  cout << "Insira o ID: ";
  in >> ag.ID;
  cout << "Insira o CPF: ";
  do{
    in >> ag.CPF;
    if (conta_digitos(ag.CPF, N_CPF) == false)
        cout << "Número de dígitos inválido. Tente novamente. ";
  }
  while(conta_digitos(ag.CPF, N_CPF) == false);
  cout << "Insira o nome: ";
  in >> ag.nome;
  cout << "Insira o celular: ";
  do{
    in >> ag.cel;
    if (conta_digitos(ag.cel, N_CEL) == false)
        cout << "Número de dígitos inválido. Tente novamente. ";
  }
  while(conta_digitos(ag.cel, N_CEL) == false);
  return in;
}

istream & operator >> (istream & in,comercial &ag){//SOBRECARGA PARA IMPRIMIR COMERCIAL
  cout << "Insira o ID: ";
  in >> ag.ID;
  cout << "Insira o CNPJ: ";
  do{
    in >> ag.CNPJ;
    if (conta_digitos(ag.CNPJ, N_CNPJ) == false)
        cout << "Número de dígitos inválido. Tente novamente. ";
  }
  while(conta_digitos(ag.CNPJ, N_CNPJ) == false);
  cout << "Insira o nome: ";
  in >> ag.nome;
  cout << "Insira o telefone: ";
  do{
    in >> ag.tel;
    if (conta_digitos(ag.tel, N_TEL) == false)
        cout << "Número de dígitos inválido. Tente novamente. ";
  }
  while(conta_digitos(ag.tel, N_TEL) == false);
  return in;
}

ostream & operator << (ostream & out,pessoal &ag){//SOBRECARGA PARA IMPRIMIR PESSOAL
  cout << "\nID: ";
  out << ag.ID;
  cout << "\nCPF: ";
  out << ag.CPF;
  cout << "\nnome: ";
  out << ag.nome;
  cout << "\ncelular: ";
  out << ag.cel;
  cout<<endl;
  return out;
}

ostream & operator << (ostream & out,comercial &ag){//SOBRECARGA PARA IMPRIMIR COMERCIAL
  cout << "\nID: ";
  out << ag.ID;
  cout << "\nCNPJ: ";
  out << ag.CNPJ;
  cout << "\nNome: ";
  out << ag.nome;
  cout << "\nTelefone: ";
  out << ag.tel;
  cout<<endl;
  return out;
}

int main() {
    setlocale(LC_ALL,"Portuguese");
    int max_ag;
    int operacao;
    cout << "Quantas posições para as agendas? ";
    do{
        cin >> max_ag;
    }
    while(max_ag < 1);
    agenda<pessoal> ag1;
    agenda<comercial> ag2;
    ag1.itens = new pessoal[max_ag];
    ag2.itens = new comercial[max_ag];
    inicializa_agenda(ag1);
    inicializa_agenda(ag2);
    string tipo_operacao;

    do {
      //system("cls");
      cout << "\n\nSelecione uma operação:\n1 - Inserir item\n2 - Remover item\n3 - Pesquisar\n4 - Ordenar agenda\n5 - Mostrar todos os itens\n6 - Encerrar\n";
      cin >> operacao;

      switch(operacao) {  //ESCOLHE A OPERAÇÃO A SER REALIZADA

      case 1:  //OPERAÇÃO DE INSERÇÃO
        tipo_operacao="inserir";

        if(tipo_contato(tipo_operacao)==1){  //INSERIR TIPO PESSOAL
          pessoal ag_temp1;
          cin>>ag_temp1;
          if (insere(ag1, ag_temp1, max_ag) == true)
            cout << "Item inserido com sucesso";
          else
            cout << "Erro: não foi possível inserir o item na agenda";
        }
        else{ // INSERE TIPO COMERCIAL
          comercial ag_temp2;
          cin>>ag_temp2;
          if (insere(ag2, ag_temp2, max_ag) == true)
            cout << "Item inserido com sucesso";
          else
            cout << "Erro: não foi possível inserir os dados na agenda";
        }
        break;
//-----------------------------------------------------------------------------------
        case 2: //OPERAÇÃO DE REMOÇÃO
          int ID_pesquisa;
          tipo_operacao="remover";

          if(tipo_contato(tipo_operacao)==1){  //REMOVE TIPO PESSOAL
            pessoal ag_temp1;

            cout<<"Digite o ID a ser removido: ";
            cin>>ID_pesquisa;
          }
          else{ // REMOVE TIPO COMERCIAL
            comercial ag_temp2;

            cout<<"Digite o ID a ser excluído: ";
            cin>>ID_pesquisa;

            ag_temp2.ID=0;
            ag_temp2.CNPJ=0;
            ag_temp2.nome="";
            ag_temp2.tel=0;
            remove(ag2,ID_pesquisa,ag_temp2);
          }
        break;
//-------------------------------------------------------------------------------------------
        case 3:  //OPERAÇÃO DE PESQUISA
        {
        tipo_operacao="pesquisar";
        int id=0;
        string nome="";

        if(tipo_contato(tipo_operacao)==1){  //PESQUISA TIPO PESSOAL
          if(tipo_pesquisa()==1){
            cout<<"Digite o ID: ";
            cin>>id;
            pesquisa(ag1,id,nome);
          }
          else{
            cout<<"Digite o nome: ";
            cin>>nome;
            pesquisa(ag1,id,nome);
          }
        }
        else{ //PESQUISA TIPO COMERCIAL
          if(tipo_pesquisa()==1){
            cout<<"Digite o ID: ";
            cin>>id;
            pesquisa(ag2,id,nome);
          }
          else{
            cout<<"Digite o nome: ";
            cin>>nome;
            pesquisa(ag2,id,nome);
          }
        }
        break;
        }
//--------------------------------------------------------------------------------------------
        case 4:

        break;

        case 5:
          tipo_operacao="imprimir";
          if(tipo_contato(tipo_operacao)==1){  //IMPRIMI TIPO PESSOAL
            cout<<"\nAgenda Pessoal:\n";
            imprime(ag1);
          }
          else{
            cout<<"\nAgenda Comercial:\n";
            imprime(ag2);
          }
        break;
        }
    }
   while(operacao != 6);
    delete []ag1.itens;
    delete []ag2.itens;
    return 0;
}
