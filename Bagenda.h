#define _Bagenda_

template <typename TIPO>
  struct agenda {
    TIPO *itens;
    int qtde;
};

// Inicializa a agenda. Inicializações: Define que agenda está sem nenhum item
template <typename TIPO>
void inicializa_agenda(agenda <TIPO> &ag) {
  ag.qtde = 0;
}

// insere o item na agenda (protótipo)
// Retorna true caso consiga inserir o dado na agenda, false caso contrário
template <typename TIPO>
bool insere(agenda <TIPO> &ag, TIPO dado,int max_ag) {
    if (ag.qtde < max_ag){
      ag.itens[ag.qtde]=dado;
      ag.qtde++;
      return true;
    }
    else
      return false;
}

template <typename TIPO>
void remove(agenda <TIPO> &ag,int ID_pesquisa, TIPO dado){
  for(int i=0;i<ag.qtde;i++){
    if(ag.itens[i].ID==ID_pesquisa){
      ag.itens[i]=dado;
    }
  }
}

template <typename TIPO>
void imprime(agenda <TIPO> &ag) {
  for(int i=0;i<ag.qtde;i++){
    cout<<ag.itens[i];
    }
}

template <typename TIPO>
void ordenar(agenda <TIPO> &ag){
  string min;
  int mini, i, j;
  for(i=0;i<ag.qtde-1;i++){  //PERCORRER POSIÇÕES
    mini=i;
    for(j=i+1;j<ag.qtde;j++){  //MENOR NOME
      if(ag.itens[j].nome<ag.itens[mini].nome){
        mini=j;
      }
    }
    if(i!=mini){
    TIPO dado1;
    dado1=ag.itens[i];
    ag.itens[i]=ag.itens[mini];
    ag.itens[mini]=dado1;
    }
    
  }
}

template <typename TIPO>
int pesquisa(agenda <TIPO> &ag,int id,string nome){
  for(int i=0;i<ag.qtde;i++){
    if(id==0){
      if(ag.itens[i].nome==nome){
        return i;
      }
    }
    else{
      if(ag.itens[i].ID==id){
        
        return i;
      }
    }
  }
  return -1;
}
