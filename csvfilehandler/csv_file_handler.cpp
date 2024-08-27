#include "csv_file_handler.hpp"
#include <fstream>

// Construtor da classe, quando criar um objeto, passa o nome do arquivo, o mesmo eh aberto e depois andamos pelas linhas uma a uma

CSVFileHandler::CSVFileHandler(std::string filename) {
    char line[MAXCHAR];
    std::ifstream inFile;
    inFile.open(filename, std::ios::in);
    if (! inFile) {
      // ERRO ERRO PERIGO JOGA TUDO PRO ALTO E FODASE
      throw std::runtime_error("Arquivo nao pode ser aberto :()");
    }
    int i = 0;
    while (inFile.getline(line, MAXCHAR)) {
      // Chama func pra tirar essa buxa de stream e guardar isso em uma matriz
      getCSVLineFields(csvMatrix[i], line);
      i++;
    }
    inFile.close();
}

void CSVFileHandler::getCSVLineFields(std::string camps[6], char line[MAXCHAR]) {
  int pos = 0;
  for (int i = 0; line[i] != '\0'; i++) {
    if (line[i] != ',') {
      camps[pos] += line[i];
    } else {
      pos++;
    }
  } 
}
