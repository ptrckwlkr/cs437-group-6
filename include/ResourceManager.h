#ifndef CSCI437_RESOURCEMANAGER_H
#define CSCI437_RESOURCEMANAGER_H

#include <map> 
#include <SFML/Graphics.hpp> 

class ResourceManager{

    public: 

    public:  
        ResourceManager(){}
        ~ResourceManager(){}

        //use to load textures and sprites 
        void LoadTexture( std::string name, std::string fileName );
        sf::Texture &GetTexture( std:: string name);

        void LoadFont( std::string name, std::string fileName );
        sf::Font &GetFont( std:: string name);



    private:
        std::map<std::string, sf::Texture> _textures;
        std::map<std::string, sf::Font> _fonts;


};


#endif //CSCI437_RESOURCEMANAGER_H