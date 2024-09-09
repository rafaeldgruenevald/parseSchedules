/*
Os arquivos Comma-separated values, tamb�m conhecido como CSV, s�o arquivos de texto de formato regulamentado pelo RFC 4180[1], que faz uma ordena��o de bytes separando valores atrav�s de um delimitador (v�rgulas, ponto-e-v�rgula ou tabula��o) [2].
Este formato � utilizado por v�rios aplicativos, tipicamente ferramentas de escrit�rio. Microsoft Excel e LibreOffice Calc podem exportar/importar dados de suas planilhas neste formato.
Um arquivo CSV abriga um sem n�mero de "registros", separados por quebras de linha (cada "registro" permanece numa linha do arquivo) e cada registro possui um ou mais "campos", separados por um delimitador, os mais comuns sendo a v�rgula (","), o ponto e v�rgula (";") e o caractere "tab" (\t).
Arquivos separados por v�rgula e ponto e v�rgula normalmente recebem a extens�o "CSV" e arquivos separados por "tab" a extens�o "TSV". H� tamb�m bases de dados nesses formatos que recebem a extens�o "TXT".
Arquivos CSV s�o simples e funcionam na maior parte das aplica��es que lidam com dados estruturados.
*/

#include <ios>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ostream>
#include <string>
#include <unordered_map>

#define MAXCHAR 200

// Pega argumentos do terminal
int main(int argc, char* argv[]) {
  std::ifstream inHorario;
  std::ifstream inAlocacao;
  std::unordered_map<std::string, std::string> labs;
  std::unordered_map<std::string, int> ordem;
  std::string aula;
  std::string lab;
  std::string hora;
  std::string delimitador = ",";
  int contador, ord = 0;
  int clinha = 0;
  char linha[MAXCHAR];
  setlocale(LC_ALL,"");

  // abrindo arquivo horario
  inHorario.open(argv[1], std::ios::in);
  if (! inHorario) {
    std::cerr << "Arquivo " << argv[1] << " nao pode ser aberto!" << std::endl;
  }
  // abrindo arquivo alocacao
  inAlocacao.open(argv[2], std::ios::in);
  if (! inAlocacao) {
    std::cerr << "Arquivo " << argv[2] << " nao pode ser aberto!" << std::endl;
  }

  while (inAlocacao.getline(linha, MAXCHAR)) {
    std::string strLinha(linha);
    contador = 0;
    if (clinha < 3) {
        clinha++;
    }

    while(contador < 3) {
        std::string campo = strLinha.substr(0, strLinha.find(delimitador));
        switch (contador) {
        case 0:
            if (campo[campo.length() - 1] == ' ') {
                campo.erase((campo.length() - 1), 1);
            }
            aula = campo;
            //std::cout << campo;
            break;
        case 2:
            if (campo[0] == ' ') {
                campo.erase(0,1);
            }
            lab = campo;
            //std::cout << campo;
            break;
        default:
            break;
        }

        strLinha.erase(0, strLinha.find(delimitador) + delimitador.length());
        contador++;
    }
    //std::cout << std::endl;
    labs[aula] = lab;
    if (ordem.find(lab) == ordem.end() && clinha > 2) {
        ordem[lab] = ord;
        ord++;
        std::cout << lab << " "<< ordem[lab] << std::endl;
    }
  }

  /*
  labs["INTRO"] = "2 Tro Geral";
  labs["TROFUN"] = "2 Tro Geral";
  labs["DESEN"] = "3 Tro Geral";
  labs["DIGIT"] = "6 Proc. Sinais";
  labs["PROJ INIC CIENT"] = "INFO. 7";
  labs["ELEM"] = "INFO. 7";
  labs["SIST M"] = "9 Micros";
  labs["SISCOM"] = "11 Comunicacoes";
  labs["TROANL"] = "1 Tro Geral";
  labs["ACIONA"] = "10 Acionamentos";
  labs["SIST MICRO II"] = "9 Micros";
  labs["TROPOT"] = "13 Potencia";
  labs["TCC"] = "INFO. 7";
  labs["SINAIS"] = "6 Proc. Sinais";
  labs["AUTOM"] = "14 Automacao";
  */

  // lendo cada linha dos horarios

  /*
  while(inHorario.getline(linha, MAXCHAR)) {
    // zera o contador
    contador = 0;
    // converte uma array de chars para um objeto string
    std::string strLinha(linha);
    // procura pela primeira ocorrencia do dilimitador na linha, caso nao exista retorna 'npos'
    while(contador < 6) {
      std::string campo = strLinha.substr(0, strLinha.find(delimitador));
      if (contador == 0) {
        hora = campo;
      } else {
        if (contador == 5) {
          campo = strLinha;
          strLinha = "";
        }
        std::string aula = campo.substr(0, campo.find(" "));
        if (labs.find(aula) != labs.end()) {
          std::cout << labs[aula] << " ";
        } else {
          std::cout << campo << " ";
        }
      }
      strLinha.erase(0, strLinha.find(delimitador) + delimitador.length());
      contador++;
    }
    std::cout << std::endl;
  }
  */
  inHorario.close();
  inAlocacao.close();
}
