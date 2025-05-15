#include <stdio.h>
#include <windows.h>

#define TAM 10
#define NAVIO_TAM 3
#define VALOR_NAVIO 3

void println() {
    printf("\n\n");
}

void printSeparator() {
    printf("\n ─────────────────────────────────── \n");
}

// Função para verificar se o navio cabe no tabuleiro
int verifica_posicao_valida(int linha, int coluna, int orientacao) {
    if (orientacao == 0) // horizontal
        return coluna + NAVIO_TAM <= TAM;
    else // vertical
        return linha + NAVIO_TAM <= TAM;
}

// Função para verificar se já há navio nas posições desejadas
int verifica_sobreposicao(int tabuleiro[TAM][TAM], int linha, int coluna, int orientacao) {
    for (int i = 0; i < NAVIO_TAM; i++) {
        if (orientacao == 0) {
            if (tabuleiro[linha][coluna + i] != 0) return 1;
        } else {
            if (tabuleiro[linha + i][coluna] != 0) return 1;
        }
    }
    return 0;
}

// Posiciona o navio no tabuleiro
void posiciona_navio(int tabuleiro[TAM][TAM], int linha, int coluna, int orientacao) {
    for (int i = 0; i < NAVIO_TAM; i++) {
        if (orientacao == 0) {
            tabuleiro[linha][coluna + i] = VALOR_NAVIO;
        } else {
            tabuleiro[linha + i][coluna] = VALOR_NAVIO;
        }
    }
}

// Exibe o tabuleiro com emojis
void exibir_tabuleiro(int tabuleiro[TAM][TAM]) {
    println();
    printSeparator();
    printf("     🗺️  Tabuleiro Batalha Naval");
    printSeparator();
    println();
    

    // Cabeçalho de colunas
    printf("    ");
    for (int j = 0; j < TAM; j++) {
        printf("%2d ", j);
    }
    printf("\n");

    // Linha superior
    printf("   +");
    for (int j = 0; j < TAM; j++) {
        printf("---");
    }
    printf("+\n");

    for (int i = 0; i < TAM; i++) {
        printf("%2d |", i);
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == 0)
                printf("🌊 ");
            else if (tabuleiro[i][j] == VALOR_NAVIO)
                printf("🚢 ");
            else
                printf("❓ "); // Para valores não esperados
        }
        printf("|\n");
    }

    // Linha inferior
    printf("   +");
    for (int j = 0; j < TAM; j++) {
        printf("---");
    }
    printf("+\n");


}


int main() {
    // Configura o console para UTF-8 pra funcionar os caracteres especiais
    UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();
    SetConsoleOutputCP(CPAGE_UTF8);

    // Inicializa o tabuleiro
    int tabuleiro[TAM][TAM] = {0};    

    // Coordenadas iniciais dos navios
    int linha_navio_v = 2, coluna_navio_v = 4;
    int linha_navio_h = 6, coluna_navio_h = 3;

    // Validação
    if (!verifica_posicao_valida(linha_navio_v, coluna_navio_v, 1)) {
        printf("❌ Erro: navio vertical fora dos limites!");
        return 1;
    }
    if (verifica_sobreposicao(tabuleiro, linha_navio_v, coluna_navio_v, 1)) {
        printf("❌ Erro: sobreposição detectada para o navio vertical!");
        return 1;
    }

    if (!verifica_posicao_valida(linha_navio_h, coluna_navio_h, 0)) {
        printf("❌ Erro: navio horizontal fora dos limites!\n");
        return 1;
    }
    if (verifica_sobreposicao(tabuleiro, linha_navio_h, coluna_navio_h, 0)) {
        printf("❌ Erro: sobreposição detectada para o navio horizontal!");
        return 1;
    }

    // Posiciona navios
    posiciona_navio(tabuleiro, linha_navio_v, coluna_navio_v, 1); // vertical
    posiciona_navio(tabuleiro, linha_navio_h, coluna_navio_h, 0); // horizontal

    // Coordenadas
    println();
    printf("📍 Coordenadas dos Navios:");
    println();
    
    printf("   🚢 Vertical: ");
    for (int i = 0; i < NAVIO_TAM; i++) {
        printf("(%d,%d) ", linha_navio_v + i, coluna_navio_v);
    }

    printf("\n   🚢 Horizontal: ");
    for (int i = 0; i < NAVIO_TAM; i++) {
        printf("(%d,%d) ", linha_navio_h, coluna_navio_h + i);
    }

    // Exibir tabuleiro
    exibir_tabuleiro(tabuleiro);
    println();

    // Restaurar codificação padrão do console
    SetConsoleOutputCP(CPAGE_DEFAULT);

    return 0;
}
