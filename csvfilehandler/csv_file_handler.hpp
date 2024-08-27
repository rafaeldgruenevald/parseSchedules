#ifndef CSVFileHandler_H
#define CSVFileHandler_H

#include <string>

#define MAXCHAR 200

/**
 *  @name CSV File Handler 
 *
 *  O 'CSV File Handler' eh uma classe que permite voce passar um nome de arquivo
 *  e ele assume que o mesmo eh um csv, realizando assim diversas modificações.
*/
class CSVFileHandler {
private:
  void getCSVLineFields(std::string camps[6], char line[MAXCHAR]);
public:
  std::string csvMatrix[313][6];
  CSVFileHandler(std::string filename); 
};
#endif
