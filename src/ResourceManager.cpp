#include "ResourceManager.h"

// declare instance of ResourceManager to be used by other classes
ResourceManager resources;

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

void ResourceManager::LoadSprite( std::string name, std::string fileName){
    sf::Texture texture;
    if (texture.loadFromFile(fileName) ){
        this->_sprites[name] = sf::Sprite(texture);
    }
}

sf::Sprite &ResourceManager::GetSprite( std::string name){
    return this->_sprites.at(name);

}

void ResourceManager::LoadXML(std::string name, std::string filename)
{
	// Read the xml file into a vector
	std::ifstream theFile(filename);
	std::shared_ptr <std::vector<char>> buffer = std::make_shared<std::vector<char>>
		((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
	(*buffer).push_back('\0');

	// Parse the buffer using the xml file parsing library into doc 
	std::shared_ptr<rapidxml::xml_document<>> doc = std::make_shared<rapidxml::xml_document<>>();
	(*doc).parse<0>(&(*buffer)[0]);

	this->_xmldocs[name] = doc;
	this->_xmlbuffers[name] = buffer;
}


std::shared_ptr<rapidxml::xml_document<>> &ResourceManager::GetXMLDoc(std::string name)
{
	return this->_xmldocs.at(name);
}


std::shared_ptr <std::vector<char>> &ResourceManager::GetXMLBuffer(std::string name)
{
	return this->_xmlbuffers.at(name);
}