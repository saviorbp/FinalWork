#ifndef dataProcessor_H
#define dataProcessor_H

#include "movieData.h"
#include <vector>
#include <string>

class dataProcessor {
public:
    void convertCsvToBinary(const std::string& csvFilePath, const std::string& binFilePath);
    std::vector<MovieData> extractAllMovies(const std::string& binFilePath);
    std::vector<MovieData> extractRandomMovies(const std::string& binFilePath, int n);
};

#endif // dataProcessor_H
