#ifndef CSCI437_ANIMATION_H
#define CSCI437_ANIMATION_H

#include <SFML/Graphics.hpp>

class Animation 
{
    private:
    int numFrames = 9;
    sf::Texture texture;
    sf::IntRect frames[numFrames];
    float timeAni = 0.1f;
    int iFrame = 0;

    public:

    Animation ( std::string file, int x, int y, int width, int height){
        texture.loadFromFile(file);
        for ( int i =0; i< numFrames; i++){
            frames[i] = {x + i * width, y, width, height};
            //TODO: finish creating animation, probably will be moved to player 

        }

    void SetSprite( sf::Sprite& sprite) const{};


};

#endif //CSCI437_ANIMATION_H