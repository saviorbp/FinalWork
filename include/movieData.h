#ifndef MOVIEDATA_H
#define MOVIEDATA_H

#include <string>
#include <iostream>

class MovieData {
private:
    int id;
    std::string title;
    std::string genre;
    float vote_average;


public:
    MovieData() : id(0), vote_average(0.0f) {}

    MovieData(int id, const std::string& title, const std::string& genre, float vote_average) 
        : id(id), title(title), genre(genre), vote_average(vote_average) {}

    // Métodos getter
    int getId() const { return id; }
    std::string getTitle() const { return title; }
    std::string getGenre() const { return genre; }
    float getVoteAverage() const { return vote_average; }

    // Métodos setter
    void setId(int id) { this->id = id; }
    void setTitle(const std::string& title) { this->title = title; }
    void setGenre(const std::string& genre) { this->genre = genre; }
    void setVoteAverage(float vote_average) { this->vote_average = vote_average; }

    // Método para imprimir os dados do filme (útil para debug)
    void print() const {
        std::cout << "ID: " << id << ", Title: " << title 
                  << ", Genre: " << genre << ", Vote Average: " << vote_average << std::endl;
    }

    // Serialização para binário
    void serialize(std::ostream& os) const {
        os.write(reinterpret_cast<const char*>(&id), sizeof(id));
        int titleSize = title.size();
        os.write(reinterpret_cast<const char*>(&titleSize), sizeof(titleSize));
        os.write(title.c_str(), titleSize);
        int genreSize = genre.size();
        os.write(reinterpret_cast<const char*>(&genreSize), sizeof(genreSize));
        os.write(genre.c_str(), genreSize);
        os.write(reinterpret_cast<const char*>(&vote_average), sizeof(vote_average));
    }

    // Desserialização de binário
    void deserialize(std::istream& is) {
        is.read(reinterpret_cast<char*>(&id), sizeof(id));
        int titleSize;
        is.read(reinterpret_cast<char*>(&titleSize), sizeof(titleSize));
        title.resize(titleSize);
        is.read(&title[0], titleSize);
        int genreSize;
        is.read(reinterpret_cast<char*>(&genreSize), sizeof(genreSize));
        genre.resize(genreSize);
        is.read(&genre[0], genreSize);
        is.read(reinterpret_cast<char*>(&vote_average), sizeof(vote_average));
    }
};

#endif // MOVIEDATA_H
