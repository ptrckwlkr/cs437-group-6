#include "ResourceManager.h"

void ResourceManager::LoadTexture( std::string name, std:: string fileName ){
    sf::Texture tex; 

  if ( tex.loadFromFile (fileName))
    {
        this->_textures[name]= tex;
    }
}

sf::Texture &ResourceManager::GetTexture( std::string name)
{
        return this->_textures.at(name);
}

    
void ResourceManager::LoadFont( std::string name, std::string fileName)
{
    sf::Font font;

    if ( font.loadFromFile (fileName))
    {
        this->_fonts[name ]= font;
    }
}

sf::Font &ResourceManager::GetFont( std::string name)
{
    return this->_fonts.at(name);
}