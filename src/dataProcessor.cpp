#include "dataProcessor.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <random>

void dataProcessor::convertCsvToBinary(const std::string &csvFilePath, const std::string &binFilePath)
{
  std::ifstream csvFile(csvFilePath);
  std::ofstream binFile(binFilePath, std::ios::binary);

  if (!csvFile.is_open())
  {
    std::cerr << "Erro ao abrir o arquivo CSV!" << std::endl;
    return;
  }

  std::string line;
  std::getline(csvFile, line); // Ignorar a primeira linha (cabeçalho)
  while (std::getline(csvFile, line))
  {
    std::stringstream ss(line);
    std::string token;
    std::vector<std::string> tokens;

    while (std::getline(ss, token, ';'))
    {
      tokens.push_back(token);
    }

    if (tokens.size() < 17)
    {
      std::cerr << "Linha inválida: " << line << std::endl;
      continue;
    }

    try
    {
      int id = std::stoi(tokens[3]);
      std::string title = tokens[15];
      std::string genre = tokens[2]; // Aqui você pode precisar de um processamento adicional para extrair os gêneros corretamente
      float vote_average = std::stof(tokens[16]);

      MovieData movie(id, title, genre, vote_average);
      movie.serialize(binFile);
    }
    catch (const std::invalid_argument &e)
    {
      std::cerr << "Erro de conversão: " << e.what() << " na linha: " << line << std::endl;
      continue; // Ignorar a linha com erro e continuar
    }
  }

  csvFile.close();
  binFile.close();
}

std::vector<MovieData> dataProcessor::extractAllMovies(const std::string &binFilePath)
{
  std::ifstream binFile(binFilePath, std::ios::binary);
  std::vector<MovieData> movies;

  while (binFile.peek() != EOF)
  {
    MovieData movie;
    movie.deserialize(binFile);
    movies.push_back(movie);
  }

  binFile.close();
  return movies;
}

std::vector<MovieData> dataProcessor::extractRandomMovies(const std::string &binFilePath, int n)
{
  std::ifstream binFile(binFilePath, std::ios::binary);
  std::vector<MovieData> movies;
  std::random_device rd;  // Gerador de números aleatórios baseado em hardware
  std::mt19937 gen(rd()); // Inicializa o Mersenne Twister com uma semente aleatória
  std::uniform_int_distribution<> dis(0, 1000);

  while (binFile.peek() != EOF)
  {
    MovieData movie;
    movie.deserialize(binFile);
    movies.push_back(movie);
  }

  binFile.close();

  std::vector<MovieData> randomMovies;
  for (int i = 0; i < n; i++)
  {
    int index = dis(gen) % movies.size();
    randomMovies.push_back(movies[index]);
  }

  return randomMovies;
}
