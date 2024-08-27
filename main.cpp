/*
Os arquivos Comma-separated values, também conhecido como CSV, são arquivos de texto de formato regulamentado pelo RFC 4180[1], que faz uma ordenação de bytes separando valores através de um delimitador (vírgulas, ponto-e-vírgula ou tabulação) [2].
Este formato é utilizado por vários aplicativos, tipicamente ferramentas de escritório. Microsoft Excel e LibreOffice Calc podem exportar/importar dados de suas planilhas neste formato.
Um arquivo CSV abriga um sem número de "registros", separados por quebras de linha (cada "registro" permanece numa linha do arquivo) e cada registro possui um ou mais "campos", separados por um delimitador, os mais comuns sendo a vírgula (","), o ponto e vírgula (";") e o caractere "tab" (\t).
Arquivos separados por vírgula e ponto e vírgula normalmente recebem a extensão "CSV" e arquivos separados por "tab" a extensão "TSV". Há também bases de dados nesses formatos que recebem a extensão "TXT". 
Arquivos CSV são simples e funcionam na maior parte das aplicações que lidam com dados estruturados.
*/

#include <iostream>
#include "csvfilehandler/csv_file_handler.hpp"

// Pega argumentos do terminal
int main(int argc, char* argv[]) {
  setlocale(LC_ALL,"");
  // Inicia no stack um objeto da classe CSVFileHandler, passa para o construtor o segundo argumento passado no terminal
  CSVFileHandler csvFile = CSVFileHandler(argv[1]);
  for (int i = 0; i < 313; i++) {
    for (int j = 0; j < 6; j++) {
      std::cout << csvFile.csvMatrix[i][j] << " ";
    }
    std::cout << std::endl;
  }
}
