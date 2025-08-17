#include <bits/stdc++.h>
#include <iostream>
using namespace std;
// baseado em https://www.ime.unicamp.br/~marcia/AlgebraLinear/aplicacao_criptografia.html
struct Matrizes {
    char letras[26];    
    int valor[26];      
    int chave[2][2] = {{1, 2}, {3, 5}};             
    int chave_inversa[2][2] = {{21, 2}, {3, 25}};   
};

void Preencher(Matrizes &mat) {
    for (int i = 0; i < 26; i++) {
        mat.letras[i] = 'A' + i;  
        mat.valor[i] = i;  
    }
}


string cifrar(Matrizes &mat, string mensagem) {
    string resultado;
    int tamanho = mensagem.size();

    for (int i = 0; i < tamanho; i += 2) {
        int mens[2] = {0};

        for (int j = 0; j < 26; j++) {
            if (mat.letras[j] == mensagem[i]) {
                mens[0] = mat.valor[j];  
            }
            if (i + 1 < tamanho && mat.letras[j] == mensagem[i + 1]) {
                mens[1] = mat.valor[j];  
            }
        }

        int c1 = (mat.chave[0][0] * mens[0] + mat.chave[0][1] * mens[1]) % 26;
        int c2 = (mat.chave[1][0] * mens[0] + mat.chave[1][1] * mens[1]) % 26;

        if (c1 < 0) c1 += 26;
        if (c2 < 0) c2 += 26;

        resultado.push_back(mat.letras[c1]);
        if (i + 1 < tamanho) resultado.push_back(mat.letras[c2]);
    }
    return resultado;
}

string decifrar(Matrizes &mat, string mensagem) {
    string resultado;
    int tamanho = mensagem.size();

    for (int i = 0; i < tamanho; i += 2) {
        int mens[2] = {0};

        for (int j = 0; j < 26; j++) {
            if (mat.letras[j] == mensagem[i]) {
                mens[0] = mat.valor[j];  
            }
            if (i + 1 < tamanho && mat.letras[j] == mensagem[i + 1]) {
                mens[1] = mat.valor[j];  
            }
        }

        int c1 = (mat.chave_inversa[0][0] * mens[0] + mat.chave_inversa[0][1] * mens[1]) % 26;
        int c2 = (mat.chave_inversa[1][0] * mens[0] + mat.chave_inversa[1][1] * mens[1]) % 26;

        if (c1 < 0) c1 += 26;
        if (c2 < 0) c2 += 26;

        resultado.push_back(mat.letras[c1]);
        if (i + 1 < tamanho) resultado.push_back(mat.letras[c2]);
    }
    return resultado;
}

int main() {
    Matrizes nova_matriz;
    Preencher(nova_matriz);

    string entrada;
    cout << "Digite uma palavra em MAIUSCULAS para codificar: ";
    cin >> entrada;

    string cifrado = cifrar(nova_matriz, entrada);
    string decifrado = decifrar(nova_matriz, cifrado);

    cout << "\nTexto Original : " << entrada << endl;
    cout << "Texto Cifrado  : " << cifrado << endl;
    cout << "Texto Decifrado: " << decifrado << endl;

    return 0;
}
