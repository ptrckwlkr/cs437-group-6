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
    resources.LoadTexture("tileset", "../data/Tiles/tilesheet(variation).png");
    resources.LoadTexture("playerTexture", "../data/Sprites/playerSprite.png");
    resources.LoadTexture("skeletonTexture", "../data/Sprites/skeletonSprite.png");
    resources.LoadTexture("ghostTexture", "../data/Sprites/ghost.png");
    resources.LoadTexture("orcTexture", "../data/Sprites/orcSprite.png");
    resources.LoadTexture("bloodTexture", "../data/Sprites/blood.png");
    resources.LoadTexture("goldTexture", "../data/Sprites/treasure.png");
    resources.LoadTexture("potionTexture", "../data/Sprites/potions.png");
    resources.LoadTexture("swordTexture", "../data/Sprites/sword.png");
    resources.LoadTexture("moneyTexture", "../data/Sprites/dollar.png");
    resources.LoadTexture("smokeTexture", "../data/Sprites/smoke.png");
    resources.LoadTexture("sreepTexture", "../data/Sprites/boss.png");
    resources.LoadTexture("explosionTexture", "../data/Sprites/explosion.png");
    resources.LoadTexture("shop", "../data/Sprites/shop.png");
    resources.LoadTexture("crimson_rogue_head", "../data/Sprites/sets/crimson_rogue/transparent/Crimson_hl_t.png");
    resources.LoadTexture("crimson_rogue_armor", "../data/Sprites/sets/crimson_rogue/transparent/Crimson_ar_t.png");
    resources.LoadTexture("crimson_rogue_shoulders", "../data/Sprites/sets/crimson_rogue/transparent/Crimson_sh_t.png");
    resources.LoadTexture("crimson_rogue_pants", "../data/Sprites/sets/crimson_rogue/transparent/Crimson_pn_t.png");
    resources.LoadTexture("crimson_rogue_boots", "../data/Sprites/sets/crimson_rogue/transparent/Crimson_bts_t.png");
    resources.LoadTexture("crimson_rogue_gloves", "../data/Sprites/sets/crimson_rogue/transparent/Crimson_gl_t.png");
    resources.LoadTexture("forest_priest_head", "../data/Sprites/sets/forest_priest/transparent/c_hlm_01t.PNG");
    resources.LoadTexture("forest_priest_armor", "../data/Sprites/sets/forest_priest/transparent/c_arm_01t.PNG");
    resources.LoadTexture("forest_priest_shoulders", "../data/Sprites/sets/forest_priest/transparent/c_sh_01t.png");
    resources.LoadTexture("forest_priest_pants", "../data/Sprites/sets/forest_priest/transparent/c_pn_01_t.PNG");
    resources.LoadTexture("forest_priest_boots", "../data/Sprites/sets/forest_priest/transparent/c_bt_01t.PNG");
    resources.LoadTexture("forest_priest_gloves", "../data/Sprites/sets/forest_priest/transparent/c_gl_01t.PNG");
    resources.LoadTexture("guard_head", "../data/Sprites/sets/guard/transparent/fantom_h_t.png");
    resources.LoadTexture("guard_armor", "../data/Sprites/sets/guard/transparent/fantom_ar_t.png");
    resources.LoadTexture("guard_shoulders", "../data/Sprites/sets/guard/transparent/fantom_sh_t.png");
    resources.LoadTexture("guard_pants", "../data/Sprites/sets/guard/transparent/fantom_pn_t.png");
    resources.LoadTexture("guard_boots", "../data/Sprites/sets/guard/transparent/fantom_bt_t.png");
    resources.LoadTexture("guard_gloves", "../data/Sprites/sets/guard/transparent/fantom_gl_t.png");
    resources.LoadTexture("iron_hunter_head", "../data/Sprites/sets/iron_hunter/transparent/h_hl_01t.png");
    resources.LoadTexture("iron_hunter_armor", "../data/Sprites/sets/iron_hunter/transparent/h_arm_01t.PNG");
    resources.LoadTexture("iron_hunter_shoulders", "../data/Sprites/sets/iron_hunter/transparent/h_sh_01t.PNG");
    resources.LoadTexture("iron_hunter_pants", "../data/Sprites/sets/iron_hunter/transparent/h_pn_01t.PNG");
    resources.LoadTexture("iron_hunter_boots", "../data/Sprites/sets/iron_hunter/transparent/h_bt_01t.png");
    resources.LoadTexture("iron_hunter_gloves", "../data/Sprites/sets/iron_hunter/transparent/h_gl_01t.png");
    resources.LoadTexture("renegade_head", "../data/Sprites/sets/renegade/transparent/ren_hl_t_01.png");
    resources.LoadTexture("renegade_armor", "../data/Sprites/sets/renegade/transparent/ren_a_t_01.png");
    resources.LoadTexture("renegade_shoulders", "../data/Sprites/sets/renegade/transparent/ren_sh_t_01.png");
    resources.LoadTexture("renegade_pants", "../data/Sprites/sets/renegade/transparent/ren_pn_t_01.png");
    resources.LoadTexture("renegade_boots", "../data/Sprites/sets/renegade/transparent/ren_bt_t_01.png");
    resources.LoadTexture("renegade_gloves", "../data/Sprites/sets/renegade/transparent/ren_gl_t_01.png");
    resources.LoadTexture("cultist_head", "../data/Sprites/sets/cultist/transparent/hood_cl_t_01.PNG");
    resources.LoadTexture("cultist_armor", "../data/Sprites/sets/cultist/transparent/armor_cl_t_01.PNG");
    resources.LoadTexture("cultist_shoulders", "../data/Sprites/sets/cultist/transparent/shoulders_cl_t_01.PNG");
    resources.LoadTexture("cultist_pants", "../data/Sprites/sets/cultist/transparent/pants_cl_t_01.PNG");
    resources.LoadTexture("cultist_boots", "../data/Sprites/sets/cultist/transparent/boot_cl_t_01.PNG");
    resources.LoadTexture("cultist_gloves", "../data/Sprites/sets/cultist/transparent/gloves_cl_t_01.PNG");
    resources.LoadTexture("gatekeeper_head", "../data/Sprites/sets/gatekeeper/transparent/L_hlm_01t.png");
    resources.LoadTexture("gatekeeper_armor", "../data/Sprites/sets/gatekeeper/transparent/L_arm_01t.PNG");
    resources.LoadTexture("gatekeeper_shoulders", "../data/Sprites/sets/gatekeeper/transparent/L_shl_01t.png");
    resources.LoadTexture("gatekeeper_pants", "../data/Sprites/sets/gatekeeper/transparent/L_pns_01t.png");
    resources.LoadTexture("gatekeeper_boots", "../data/Sprites/sets/gatekeeper/transparent/L_bt_01t.png");
    resources.LoadTexture("gatekeeper_gloves", "../data/Sprites/sets/gatekeeper/transparent/L_gl_01t.PNG");
    resources.LoadTexture("illusionist_head", "../data/Sprites/sets/illusionist/transparent/illusionist_h_t.png");
    resources.LoadTexture("illusionist_armor", "../data/Sprites/sets/illusionist/transparent/illusionist_ar_t.png");
    resources.LoadTexture("illusionist_shoulders", "../data/Sprites/sets/illusionist/transparent/illusionist_sh_t.png");
    resources.LoadTexture("illusionist_pants", "../data/Sprites/sets/illusionist/transparent/illusionist_pn_t.png");
    resources.LoadTexture("illusionist_boots", "../data/Sprites/sets/illusionist/transparent/illusionist_bt_t.png");
    resources.LoadTexture("illusionist_gloves", "../data/Sprites/sets/illusionist/transparent/illusionist_gl_t.png");
    resources.LoadTexture("marauder_head", "../data/Sprites/sets/marauder/transparent/iron_hl_t.png");
    resources.LoadTexture("marauder_armor", "../data/Sprites/sets/marauder/transparent/iron_ar_c.png");
    resources.LoadTexture("marauder_shoulders", "../data/Sprites/sets/marauder/transparent/iron_sh_t.png");
    resources.LoadTexture("marauder_pants", "../data/Sprites/sets/marauder/transparent/iron_pn_t.png");
    resources.LoadTexture("marauder_boots", "../data/Sprites/sets/marauder/transparent/iron_bt_t.png");
    resources.LoadTexture("marauder_gloves", "../data/Sprites/sets/marauder/transparent/iron_gl_t.png");
    resources.LoadTexture("sharpshooter_head", "../data/Sprites/sets/sharpshooter/transparent/sharpshooter_h_t.PNG");
    resources.LoadTexture("sharpshooter_armor", "../data/Sprites/sets/sharpshooter/transparent/sharpshooter_ar_t.PNG");
    resources.LoadTexture("sharpshooter_shoulders", "../data/Sprites/sets/sharpshooter/transparent/sharpshooter_sh_t.PNG");
    resources.LoadTexture("sharpshooter_pants", "../data/Sprites/sets/sharpshooter/transparent/sharpshooter_pnc_t.PNG");
    resources.LoadTexture("sharpshooter_boots", "../data/Sprites/sets/sharpshooter/transparent/sharpshooter_bt_t.PNG");
    resources.LoadTexture("sharpshooter_gloves", "../data/Sprites/sets/sharpshooter/transparent/sharpshooter_gl_t.PNG");
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
    resources.LoadSound("swordswing", "../data/Sounds/sword_swing_fast_001.wav");
    resources.LoadSound("ghostdisappate", "../data/Sounds/Wind 8 (fast).wav");
    resources.LoadSound("ghosthiss", "../data/Sounds/Insect Wounded 2.wav");
    resources.LoadSound("orcinjured", "../data/Sounds/Orc Wounded 4.wav");

}
