#pragma once
#include <SFML/Audio.hpp>

#include <string>
#include <vector>
#include <cmath>

typedef sf::SoundBuffer CESound;


// Sound
CESound hitsound;
CESound grazeSound;
CESound deadnotice1;
CESound deadnotice2;

CESound one;
CESound two;
CESound three;
CESound four;
CESound five;
CESound six;
CESound seven;
CESound eight;
CESound nine;
CESound zero;
CESound ten;
CESound eleven;
CESound twelve;
CESound teen;

CESound twenty;
CESound thirty;
CESound forty;
CESound fifty;
CESound sixty;
CESound seventy;
CESound eighty;
CESound ninety;
CESound hundred;
CESound thousand;


void PlayThisSound(std::string snd)
{
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(snd))
    {
        std::cout << "Unable to play sound " << snd << "\n";
        return;
    }
    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();
}

void SayNumber(uint32_t number)
{
    uint32_t numberOfDigits = log10(number)+1;
    bool useHundred = false;
    bool useThousand = false;

    std::vector<sf::Sound> sounds;

    if (numberOfDigits > 6) return;
    
    if (numberOfDigits > 4) {
        bool useHundred = true;
        bool useThousand = true;
    }
    else if (numberOfDigits == 3) {
        bool useHundred = true;
    }

    
}