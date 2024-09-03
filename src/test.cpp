#include "dataProcessor.h"
#include <iostream>
#include <filesystem>

int main()
{
    std::string csvFilePath = "/home/saviorbp/ed/FinalWork/data/movies_dataset.csv";
    std::filesystem::path directoryPath = std::filesystem::path(csvFilePath).parent_path();
    std::string binFilePath = (directoryPath / "movies_dataset.bin").string();

    // Verificar se o diretório e o arquivo CSV existem
    if (!std::filesystem::exists(csvFilePath) || !std::filesystem::exists(csvFilePath))
    {
        std::cerr << "Diretório ou arquivo CSV não encontrado!" << std::endl;
        return 1;
    }

    dataProcessor processor;

    // Convertendo CSV para binário
    processor.convertCsvToBinary(csvFilePath, binFilePath);
    std::cout << "CSV convertido para binário com sucesso!" << std::endl;

    // Extraindo todos os filmes
    auto movies = processor.extractAllMovies(binFilePath);
    std::cout << "Total de filmes extraídos: " << movies.size() << std::endl;

    // Extraindo N filmes aleatórios
    int n = 10; // Exemplo: extraindo 10 filmes
    auto randomMovies = processor.extractRandomMovies(binFilePath, n);
    std::cout << "Filmes aleatórios extraídos:" << std::endl;
    for (const auto &movie : randomMovies)
    {
        movie.print();
    }

    return 0;
}