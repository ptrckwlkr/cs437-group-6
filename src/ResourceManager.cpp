#include <macros.h>
#include "ResourceManager.h"

// declare instance of ResourceManager to be used by other classes
ResourceManager resources;

void ResourceManager::LoadTexture(std::string name, std::string fileName) {
    sf::Texture tex;

    if (tex.loadFromFile(fileName)) {
        this->_textures[name] = tex;
    }
}

sf::Texture &ResourceManager::GetTexture(std::string name) {
    return this->_textures.at(name);
}


void ResourceManager::LoadFont(std::string name, std::string fileName) {
    sf::Font font;

    if (font.loadFromFile(fileName)) {
        this->_fonts[name] = font;
    }
}

sf::Font &ResourceManager::GetFont(std::string name) {
    return this->_fonts.at(name);
}

void ResourceManager::LoadSprite(std::string name, std::string fileName) {
    sf::Texture texture;
    if (texture.loadFromFile(fileName)) {
        this->_sprites[name] = sf::Sprite(texture);
    }
}

sf::Sprite &ResourceManager::GetSprite(std::string name) {
    return this->_sprites.at(name);

}

void ResourceManager::LoadSound(std::string name, std::string fileName) {
    sf::SoundBuffer snd;
    if (snd.loadFromFile(fileName)) {
        this->_soundbuffers[name] = snd;
        this->_sounds[name] = sf::Sound(this->_soundbuffers.at(name));
    }
}

sf::Sound &ResourceManager::GetSound(std::string name) {
    return this->_sounds.at(name);
}


void ResourceManager::LoadMusic(std::string name, std::string fileName) {
    auto music = std::make_shared<sf::Music>();
    if (music->openFromFile(fileName)) {
        this->_music[name] = music;
    }
}

std::shared_ptr<sf::Music> &ResourceManager::GetMusic(std::string name) {
    return this->_music.at(name);
}


void ResourceManager::LoadXML(std::string name, std::string filename) {
    // Read the xml file into a vector
    std::ifstream theFile(filename);
    std::shared_ptr<std::vector<char>> buffer = std::make_shared<std::vector<char>>
            ((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
    (*buffer).push_back('\0');

    // Parse the buffer using the xml file parsing library into doc
    std::shared_ptr<rapidxml::xml_document<>> doc = std::make_shared<rapidxml::xml_document<>>();
    (*doc).parse<0>(&(*buffer)[0]);

    this->_xmldocs[name] = doc;
    this->_xmlbuffers[name] = buffer;
}


std::shared_ptr<rapidxml::xml_document<>> &ResourceManager::GetXMLDoc(std::string name) {
    return this->_xmldocs.at(name);
}


std::shared_ptr<std::vector<char>> &ResourceManager::GetXMLBuffer(std::string name) {
    return this->_xmlbuffers.at(name);
}

void ResourceManager::LoadAllResources()
{
    resources.LoadFont("old_school", "../data/Fonts/Old-School-Adventures.ttf");
    resources.LoadXML("text", "../data/xml/game-text.xml");
    resources.LoadTexture("map", "../data/Images/map.png");
    resources.LoadTexture("fog", "../data/Images/vignette.png");
    resources.LoadTexture("tileset", "../data/Tiles/tilesheet.png");
    resources.LoadTexture("playerTexture", "../data/Sprites/playerSprite.png");
    resources.LoadTexture("skeletonTexture", "../data/Sprites/skeletonSprite.png");
    resources.LoadTexture("bloodTexture", "../data/Sprites/blood.png");
    resources.LoadTexture("swordTexture", "../data/Sprites/sword.png");
    resources.LoadTexture("shop", "../data/Sprites/shop.png");
    resources.LoadTexture("renegade_head", "../data/Sprites/sets/renegade/transparent/ren_hl_t_01.png");
    resources.LoadTexture("renegade_armor", "../data/Sprites/sets/renegade/transparent/ren_a_t_01.png");
    resources.LoadTexture("renegade_shoulders", "../data/Sprites/sets/renegade/transparent/ren_sh_t_01.png");
    resources.LoadTexture("renegade_pants", "../data/Sprites/sets/renegade/transparent/ren_pn_t_01.png");
    resources.LoadTexture("renegade_boots", "../data/Sprites/sets/renegade/transparent/ren_bt_t_01.png");
    resources.LoadTexture("renegade_gloves", "../data/Sprites/sets/renegade/transparent/ren_gl_t_01.png");
    resources.LoadTexture("mountains","../data/Images/mountain_world.png" );
    resources.LoadTexture("marker","../data/Images/marker.png" );
    resources.LoadMusic("vanquisher", "../data/Music/BRPG_Vanquisher_FULL_Loop.wav");
    resources.LoadMusic("takecourage_noper", "../data/Music/BRPG_Take_Courage_noPer_Loop.wav");
    resources.LoadXML("enemies", "../data/xml/enemies.xml");
    resources.LoadXML("level-params", "../data/xml/level-parameters.xml");
    resources.LoadSound("coins", "../data/Sounds/Coins 1.wav");
    resources.LoadSound("bonebreak", "../data/Sounds/Impact Bonebreak.wav");
    resources.LoadSound("monsterdeath", "../data/Sounds/dsbgdth1.wav");
    resources.LoadSound("fireball", "../data/Sounds/Spell - Fireball 1.wav");
}
