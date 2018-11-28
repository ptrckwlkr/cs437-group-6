#ifndef CSCI437_RESOURCEMANAGER_H
#define CSCI437_RESOURCEMANAGER_H

#include <map> 
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../rapidxml/rapidxml.hpp"
#include "fstream"
#include <memory>

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

        void LoadSprite( std::string name, std::string fileName);
        sf::Sprite &GetSprite( std:: string name);

	void LoadSound( std::string name, std::string fileName);
	sf::Sound &GetSound( std:: string name);

	void LoadXML(std::string name, std::string filename);
	std::shared_ptr<rapidxml::xml_document<>> &GetXMLDoc(std::string name);
	std::shared_ptr <std::vector<char>> &GetXMLBuffer(std::string name);

    private:
        std::map<std::string, sf::Texture> _textures;
        std::map<std::string, sf::Font> _fonts;
        std::map<std::string, sf::Sprite> _sprites;
	std::map<std::string, sf::SoundBuffer> _soundbuffers;
	std::map<std::string, sf::Sound> _sounds;

		std::map<std::string, std::shared_ptr<rapidxml::xml_document<>>> _xmldocs;
		std::map<std::string, std::shared_ptr<std::vector<char>>> _xmlbuffers;
};


#endif //CSCI437_RESOURCEMANAGER_H
