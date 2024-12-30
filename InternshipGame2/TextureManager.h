#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <iostream>

class TextureManager {
private:
    static sf::Texture invalid;
    std::unordered_map<std::string, sf::Texture> textures;

public:
    bool loadTexture(const std::string& name, const std::string& filePath) {
        sf::Texture texture;
        if (!texture.loadFromFile(filePath)) {
            std::cerr << "Failed to load texture: " << filePath << std::endl;
            return false;
        }
        std::cout << "Loaded texture: " << filePath << std::endl;
        textures[name] = std::move(texture);
        return true;
    }

    sf::Texture& getTexture(const std::string& name) { // виправити гавнокод з nullptr 
        auto it = textures.find(name);
        if (it != textures.end()) {
            return it->second;
        }
        else {
            return invalid;// for error texture
        }
    }

    void initializeInvalidTexture() {
        if (!invalid.loadFromFile("assets/invalid.png")) {
            std::cerr << "Failed to load invalid texture!" << std::endl;
            invalid.create(100, 100);
            sf::Image image;
            image.create(100, 100, sf::Color::Magenta);
            invalid.update(image);
        }
    }
};

