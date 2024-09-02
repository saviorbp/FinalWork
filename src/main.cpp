#include "dataProcessor.h"
#include <iostream>
#include <filesystem>

int main(int argc, char *argv[])
{
    std::cout << argv[0] << argv[1] << std::endl;
    if (argc != 2)
    {
        std::cerr << "Uso: " << argv[0] << " /caminho/para/diretorio/contendo/arquivos" << std::endl;
        return 1;
    }
    std::string csvFilePath = argv[1];
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
