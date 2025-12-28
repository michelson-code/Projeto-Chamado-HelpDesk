#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <ctime>

using namespace std;

// Estrutura de dados para o Chamado
struct Chamado {
    int numero;
    string usuario;
    string setor;
    string descricao;
    int prioridade; // 1-Baixa, 2-Média, 3-Alta
    char status;    // A-Aberto, E-Em Atendimento, F-Fechado
};

// Variáveis Globais para controle
vector<Chamado> listaChamados;
int proximoSequencial = 1;

// Função para gerar o número de 7 dígitos (5 aleatórios + 2 sequenciais)
int gerarNumeroChamado(int seq) {
    int prefixo = (rand() % 90000) + 10000; // Gera entre 10000 e 99999
    string s_prefixo = to_string(prefixo);
    
    // Formata o sufixo para ter 2 dígitos (ex: 01, 02)
    string s_sufixo = (seq < 10) ? "0" + to_string(seq) : to_string(seq);
    
    return stoi(s_prefixo + s_sufixo);
}

// Função de comparação para ordenar a lista
// Prioridade alta primeiro, depois por ordem de chegada (sequencial)
bool compararChamados(const Chamado &a, const Chamado &b) {
    if (a.prioridade != b.prioridade) {
        return a.prioridade > b.prioridade; // Decrescente (3 > 2 > 1)
    }
    return (a.numero % 100) < (b.numero % 100); // Crescente pelos últimos 2 dígitos
}

void abrirChamado() {
    Chamado novo;
    novo.numero = gerarNumeroChamado(proximoSequencial);
    
    cout << "\n[Abertura] Numero do chamado gerado: " << novo.numero << endl;
    cout << "Nome do usuario: ";
    cin.ignore();
    getline(cin, novo.usuario);
    cout << "Setor: ";
    getline(cin, novo.setor);
    cout << "Descricao: ";
    getline(cin, novo.descricao);
    
    novo.prioridade = 1; // Padrao Baixa
    novo.status = 'A';   // Padrao Aberto
    
    listaChamados.push_back(novo);
    proximoSequencial++;
    sort(listaChamados.begin(), listaChamados.end(), compararChamados);
    cout << "Chamado aberto com sucesso!\n";
}

void localizarChamado() {
    int num;
    cout << "\nDigite o numero do chamado: ";
    cin >> num;
    
    for (auto &c : listaChamados) {
        if (c.numero == num) {
            cout << "\n--- Detalhes do Chamado ---\n";
            cout << "ID: " << c.numero << " | Status: " << c.status << endl;
            cout << "Usuario: " << c.usuario << " | Setor: " << c.setor << endl;
            cout << "Problema: " << c.descricao << endl;
            
            cout << "\nOpcoes: [A] Atualizar Prioridade | [E] Encerrar | [S] Sair: ";
            char op;
            cin >> op;
            op = toupper(op);
            
            if (op == 'A') {
                cout << "Nova Prioridade (1-Baixa, 2-Media, 3-Alta): ";
                cin >> c.prioridade;
                sort(listaChamados.begin(), listaChamados.end(), compararChamados);
                cout << "Prioridade atualizada!\n";
            } else if (op == 'E') {
                c.status = 'F';
                cout << "Chamado encerrado (Status F).\n";
            }
            return;
        }
    }
    cout << "Chamado nao encontrado.\n";
}

void excluirChamado() {
    int num;
    cout << "\nDigite o numero para EXCLUIR: ";
    cin >> num;
    
    for (auto it = listaChamados.begin(); it != listaChamados.end(); ++it) {
        if (it->numero == num) {
            listaChamados.erase(it);
            cout << "Chamado removido da lista.\n";
            return;
        }
    }
    cout << "Chamado nao encontrado.\n";
}

void imprimirTodos() {
    if (listaChamados.empty()) {
        cout << "\nLista vazia.\n";
        return;
    }
    
    cout << "\n" << setfill('=') << setw(70) << "" << endl;
    cout << setfill(' ') << left << setw(5) << "SEQ" << " | " 
         << setw(10) << "ID TOTAL" << " | " 
         << setw(15) << "USUARIO" << " | " 
         << setw(10) << "PRIO" << " | " << "STATUS" << endl;
    cout << setw(70) << setfill('-') << "" << setfill(' ') << endl;

    for (const auto &c : listaChamados) {
        string seq = to_string(c.numero).substr(5, 2);
        string p_nome = (c.prioridade == 3) ? "Alta" : (c.prioridade == 2 ? "Media" : "Baixa");
        
        cout << left << setw(5) << seq << " | " 
             << setw(10) << c.numero << " | " 
             << setw(15) << c.usuario << " | " 
             << setw(10) << p_nome << " | " << c.status << endl;
    }
}

int main() {
    srand(time(0)); // Inicializa semente aleatoria
    int opcao;
    
    do {
        cout << "\n--- HELP DESK IFNMG (C++) ---\n";
        cout << "1 - Abrir chamado\n";
        cout << "2 - Localizar chamado\n";
        cout << "3 - Excluir chamado\n";
        cout << "4 - Quantidade de chamados\n";
        cout << "5 - Imprimir chamados\n";
        cout << "6 - Sair\n";
        cout << "Escolha: ";
        cin >> opcao;
        
        switch(opcao) {
            case 1: abrirChamado(); break;
            case 2: localizarChamado(); break;
            case 3: excluirChamado(); break;
            case 4: cout << "\nTotal: " << listaChamados.size() << endl; break;
            case 5: imprimirTodos(); break;
        }
    } while (opcao != 6);
    
    return 0;
}