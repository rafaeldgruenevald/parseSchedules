/*
Os arquivos Comma-separated values, também conhecido como CSV, são arquivos de texto de formato regulamentado pelo RFC 4180[1], que faz uma ordenação de bytes separando valores através de um delimitador (vírgulas, ponto-e-vírgula ou tabulação) [2].
Este formato é utilizado por vários aplicativos, tipicamente ferramentas de escritório. Microsoft Excel e LibreOffice Calc podem exportar/importar dados de suas planilhas neste formato.
Um arquivo CSV abriga um sem número de "registros", separados por quebras de linha (cada "registro" permanece numa linha do arquivo) e cada registro possui um ou mais "campos", separados por um delimitador, os mais comuns sendo a vírgula (","), o ponto e vírgula (";") e o caractere "tab" (\t).
Arquivos separados por vírgula e ponto e vírgula normalmente recebem a extensão "CSV" e arquivos separados por "tab" a extensão "TSV". Há também bases de dados nesses formatos que recebem a extensão "TXT".
Arquivos CSV são simples e funcionam na maior parte das aplicações que lidam com dados estruturados.
*/

#include <ios>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iterator>
#include <ostream>
#include <string>
#include <vector>
#include <unordered_map>

#define MAXCHAR 200
#define COLUNAS 6
#define LINHAS 180

// Pega argumentos do terminal
int main(int argc, char* argv[]) {
  std::ifstream inHorario;
  std::ifstream inAlocacao;
  std::ofstream outFile;

  std::unordered_map<std::string, std::string> labs;
  std::unordered_map<std::string, int> ordem;

  std::vector<std::vector<std::string>> out(LINHAS, std::vector<std::string>(COLUNAS));

  std::string delimitadorCSV = ",";
  std::string delimitadorESP = " ";

  std::string aula;
  std::string lab;
  std::string hora;

  char linha[MAXCHAR];
  std::string horas[] = {"07:30", "08:20", "09:10", "10:20", "11:10", "13:10", "14:00", "14:50", "16:00", "16:50", "17:40"};

  int contador, ord = 0;
  int clinha = 0;

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

  // abrindo o arquivo de saida
  outFile.open(argv[3], std::ios::out); 
  if (! outFile) { std::cout << "Arquivo " << argv[3] << " não pode ser aberto" << std::endl;
    return -1;
  }

  while (inAlocacao.getline(linha, MAXCHAR)) {
    std::string strLinha(linha);
    contador = 0;
    if (clinha < 3) {
        clinha++;
    }

    while(contador < 3) {
        std::string campo = strLinha.substr(0, strLinha.find(delimitadorCSV));
        switch (contador) {
        case 0:
            if (*campo.rbegin() == ' ') {
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

        strLinha.erase(0, strLinha.find(delimitadorCSV) + delimitadorCSV.length());
        contador++;
    }
    //std::cout << std::endl;
    labs[aula] = lab;
    if (ordem.find(lab) == ordem.end() && clinha > 2) {
        out[ord * 15][0] = lab + delimitadorCSV;
        out[(ord * 15) + 2][0] = delimitadorCSV + "Segunda" + delimitadorCSV;
        out[(ord * 15) + 2][1] = "Terça" + delimitadorCSV;
        out[(ord * 15) + 2][2] = "Quarta" + delimitadorCSV;
        out[(ord * 15) + 2][3] = "Quinta" + delimitadorCSV;
        out[(ord * 15) + 2][4] = "Sexta";
        for (int i = 1; i <= 11; i++) {
            out[((ord * 15) + 2) + i][0] = horas[i - 1] + delimitadorCSV;
        }
        ordem[lab] = ord;
        ord++;
        //std::cout << lab << std::endl;
    }
  }

  // lendo cada linha dos horarios
  while(inHorario.getline(linha, MAXCHAR)) {
    // zera o contador
    contador = 0;
    // converte uma array de chars para um objeto string
    std::string strLinha(linha);
    // procura pela primeira ocorrencia do dilimitador na linha, caso nao exista retorna 'npos'
    int posHora = 0;
    std::string aula;
    while(contador < 6) {
      std::string campo = strLinha.substr(0, strLinha.find(delimitadorCSV));
      if (contador == 0) {
        for (int i = 1; i <= 11; i++) {
          if (campo == horas[i]) {
            posHora = i;
            break;
          }
        }
      } else {
        if (contador == 5) {
          campo = strLinha;
          strLinha = "";
        }
        aula = campo.substr(0, campo.find(" "));
        if (labs.find(aula) == labs.end()) {
          aula = campo.substr(0, campo.find(" ")) + " ";
          campo.erase(0, campo.find(delimitadorESP) + delimitadorESP.length());
          while (campo.find(delimitadorESP) != std::string::npos) {
            aula += campo.substr(0, campo.find(" "));
            if (labs.find(aula) != labs.end()) break; 
            aula += " ";
            campo.erase(0, campo.find(delimitadorESP) + delimitadorESP.length());
          }
          std::cout << aula << std::endl;
        }
        if (labs.find(aula) != labs.end() && aula != "") {
          int ord = (((ordem[labs[aula]] * 15) + 3) + posHora);
          //std::cout << ord << " " << contador << " " << aula << std::endl;
          if (out[ord][contador] != "") {
            out[ord][contador] = aula + " / " + out[ord][contador];
          } else {
            out[ord][contador] = aula + delimitadorCSV;
          }
        }
      }
      strLinha.erase(0, strLinha.find(delimitadorCSV) + delimitadorCSV.length());
      contador++;
    }
    //std::cout << std::endl;
  }
  // escrevendo no arquivo de saida

  for (int i = 0; i < LINHAS; i++) {
    for (int j = 0; j < COLUNAS; j++) {
      if (out[i][j] != "") {
        outFile << out[i][j];
      } else if (j < 5){
        outFile << delimitadorCSV;
      }
    }
    outFile << '\n';
  }
  inHorario.close();
  inAlocacao.close();
  outFile.close();
}
