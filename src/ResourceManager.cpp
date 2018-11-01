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

void sf::Font &ResourceManager::GetFont( std::string name)
{
    return this->_fonts.at(name);
}

void ResourceManager::LoadSprite( std::string name, std::string filename){
    sf::Sprite sprite;
    
    if ( sprite.loadFromFile (fileName))
    {
        this->_sprites[name ]= sprite;
    } 
}
sf::Sprite &GetSprite( std:: string name){
    
    return this->_sprites.at(name);
}
