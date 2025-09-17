#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

void menuInicial();
void limpaTela() {
    system("CLS");
}

void iniciaTabuleiro(char tabuleiro[10][10], char mascara[10][10]) {
    for (int linha = 0; linha < 10; linha++) {
        for (int coluna = 0; coluna < 10; coluna++) {
            tabuleiro[linha][coluna] = 'A';
            mascara[linha][coluna] = '*';
        }
    }
}

void exibeMapa() {
    cout << "   ";
    for (int cont = 0; cont < 10; cont++) {
        cout << cont << " ";
    }
    cout << "\n";
}

void exibeTabuleiro(char tabuleiro[10][10], char mascara[10][10], bool mostraMascara) {
    char azul[] = { 0x1b, '[', '1', ';', '3', '4', 'm', 0 };
    char amarelo[] = { 0x1b, '[', '1', ';', '3', '3', 'm', 0 };
    char verde[] = { 0x1b, '[', '1', ';', '3', '2', 'm', 0 };
    char vermelho[] = { 0x1b, '[', '1', ';', '3', '1', 'm', 0 };
    char normal[] = { 0x1b, '[', '0', ';', '3', '9', 'm', 0 };

    for (int linha = 0; linha < 10; linha++) {
        cout << linha << " ";
        for (int coluna = 0; coluna < 10; coluna++) {
            switch (mascara[linha][coluna]) {
                case 'A':
                    cout << azul << " " << mascara[linha][coluna] << normal;
                    break;
                case 'P':
                    cout << amarelo << " " << mascara[linha][coluna] << normal;
                    break;
                case 'M':
                    cout << verde << " " << mascara[linha][coluna] << normal;
                    break;
                case 'G':
                    cout << vermelho << " " << mascara[linha][coluna] << normal;
                    break;
                default:
                    cout << " " << mascara[linha][coluna];
                    break;
            }
        }
        cout << "\n";
    }

    if (mostraMascara) {
        for (int linha = 0; linha < 10; linha++) {
            cout << " ";
            for (int coluna = 0; coluna < 10; coluna++) {
                cout << " " << tabuleiro[linha][coluna];
            }
            cout << "\n";
        }
    }
}

void posicionaBarcos(char tabuleiro[10][10]) {
    srand(static_cast<unsigned>(time(0)));

    for (int i = 0; i < 10;) {
        int linha = rand() % 10;
        int coluna = rand() % 10;
        if (tabuleiro[linha][coluna] == 'A') {
            tabuleiro[linha][coluna] = 'P';
            i++;
        }
    }

    for (int i = 0; i < 7;) {
        int linha = rand() % 10;
        int coluna = rand() % 10;
        if (tabuleiro[linha][coluna] == 'A') {
            tabuleiro[linha][coluna] = 'M';
            i++;
        }
    }

    for (int i = 0; i < 5;) {
        int linha = rand() % 10;
        int coluna = rand() % 10;
        if (tabuleiro[linha][coluna] == 'A') {
            tabuleiro[linha][coluna] = 'G';
            i++;
        }
    }
}

void verificaTiro(char tabuleiro[10][10], int linhaJogada, int colunaJogada, int &pontos, string &mensagem) {
    switch (tabuleiro[linhaJogada][colunaJogada]) {
        case 'P':
            pontos += 10;
            mensagem = "Voce acertou um Barco Pequeno! (10 pts)";
            break;
        case 'M':
            pontos += 20;
            mensagem = "Voce acertou um Barco Medio! (20 pts)";
            break;
        case 'G':
            pontos += 50;
            mensagem = "Voce acertou um Barco Grande! (50 pts)";
            break;
        case 'A':
            mensagem = "Voce acertou a agua.";
            break;
    }
}

void sobre(){

    limpaTela();
    cout << "====Sobre o Jogo de Batalha Naval ====\n\n";
    cout << "Bem-vindo ao jogo de Batalha Naval!\n\n";
    cout << "Este jogo foi desenvolvido como um projeto educacional para\n";
    cout << "demonstrar conceitos de programacao em C++. O objetivo do jogo\n";
    cout << "eh afundar todos os barcos do oponente em um tabuleiro de 10x10.\n\n";
    cout << "Voce terah 10 tentativas para adivinhar a localizacao dos barcos\n";
    cout << "e ganhar pontos com base no tamanho do barco atingido:\n";
    cout << "- Barco Pequeno (P): 10 pontos\n";
    cout << "- Barco Medio (M): 20 pontos\n";
    cout << "- Barco Grande (G): 50 pontos\n\n";
    cout << "Divirta-se jogando e aprimorando suas habilidades de programacao!\n\n";
    cout << "Criado por Thiago Petenusso Viana em 01/07/2024\n";
    cout << "Pressione ENTER para voltar ao menu.\n";
    cin.ignore();  // Aguarda a entrada do usuário para voltar ao menu
    cin.get();
    menuInicial();
}



void jogo(string nomeDoJogador) {
    char tabuleiro[10][10], mascara[10][10];
    int pontos = 0, tentativas = 0, maximoDeTentativas = 10, opcao;
    string mensagem = "Bem-vindo ao jogo!";

    iniciaTabuleiro(tabuleiro, mascara);
    posicionaBarcos(tabuleiro);

    while (tentativas < maximoDeTentativas) {
        limpaTela();
        exibeMapa();
        exibeTabuleiro(tabuleiro, mascara, false);

        cout << "\nPontos: " << pontos << ", Tentativas Restantes: " << maximoDeTentativas - tentativas << "\n";
        cout << mensagem << "\n";

        int linhaJogada = -1, colunaJogada = -1;

        while (true) {
            cout << "\n" << nomeDoJogador << ", digite uma linha (0-9): ";
            cin >> linhaJogada;

            if (cin.fail() || linhaJogada < 0 || linhaJogada > 9) {
                cout << "Digite uma linha valida!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                break;
            }
        }

        while (true) {
            cout << "Digite uma coluna (0-9): ";
            cin >> colunaJogada;

            if (cin.fail() || colunaJogada < 0 || colunaJogada > 9) {
                cout << "Digite uma coluna valida!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                break;
            }
        }

        verificaTiro(tabuleiro, linhaJogada, colunaJogada, pontos, mensagem);
        mascara[linhaJogada][colunaJogada] = tabuleiro[linhaJogada][colunaJogada];

        tentativas++;
    }

    limpaTela();
    cout << "Fim de jogo, o que deseja fazer?\n";
    cout << "1 - Jogar Novamente\n";
    cout << "2 - Ir para o Menu\n";
    cout << "3 - Sair\n";
    cin >> opcao;

    switch (opcao) {
        case 1:
            jogo(nomeDoJogador);
            break;
        case 2:
            limpaTela();
            sobre();
            break;
        case 3:
            return;
    }
}

void menuInicial() {
    int opcao = 0;
    string nomeDoJogador;

    while (opcao < 1 || opcao > 3) {
        limpaTela();
        cout << "Bem-vindo ao jogo de Batalha Naval!\n";
        cout << "1 - Jogar\n";
        cout << "2 - Sobre\n";
        cout << "3 - Sair\n";
        cout << "Escolha uma opcao e tecle ENTER: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                cout << "Qual seu nome?\n";
                cin >> nomeDoJogador;
                jogo(nomeDoJogador);
                break;
            case 2:
                sobre();
                break;
            case 3:
                cout << "Até mais!\n";
                return;
        }
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    menuInicial();
    return 0;
}
