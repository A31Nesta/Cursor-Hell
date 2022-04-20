#ifndef CURSER_SOUND_HPP
#define CURSER_SOUND_HPP


#include <SFML/Audio.hpp>

#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <cmath>
#include <thread>

typedef sf::SoundBuffer CESound;
typedef std::unordered_map<std::string, CESound> CESoundMap;

/**
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
/**/

struct CurserSoundPlayer
{
    std::vector<sf::Sound> numberSounds;
    void SayNumber(CESoundMap* soundMap, uint32_t number)
    {
        numberSounds.clear();
        uint32_t numberOfDigits = log10(number)+1;
        std::cout << "Number of digits: " << std::to_string(numberOfDigits) << "\n";
        bool useHundred = false;
        bool useThousand = false;

        uint8_t digit;
        std::string numStr = std::to_string(number);

        if (number > 9999) return;
        
        if (numberOfDigits >= 4) {
            useHundred = true;
            useThousand = true;
        }
        else if (numberOfDigits == 3) {
            useHundred = true;
        }

        sf::Sound s;

        // tens
        bool hasLastDigit = false;
        bool hasTen = false;
        uint8_t lastNum;
        if (numberOfDigits > 1) {
            std::cout << "Tens: " << numStr[numStr.size()-2] << "\n";
            switch (numStr[numStr.size()-2])
            {
            case '1':
                std::cout << "The number ends with a 10-19";
                hasTen = true;
                lastNum = numStr[numStr.size()-1] - '0';
                if (lastNum > 2) { // If the number if 13 or more
                    s.setBuffer(soundMap->at("teen"));
                    numberSounds.push_back(s);
                    hasLastDigit = true;
                }
                else {
                    if (lastNum == 0) {
                        s.setBuffer(soundMap->at("ten"));
                        numberSounds.push_back(s);
                    }
                    else if (lastNum == 1) {
                        s.setBuffer(soundMap->at("eleven"));
                        numberSounds.push_back(s);
                    }
                    else if (lastNum == 2) {
                        s.setBuffer(soundMap->at("twelve"));
                        numberSounds.push_back(s);
                    }
                }
                break;
            
            default:
                break;
            }
        }

        // last digit
        if (hasLastDigit || !hasTen) {
            switch (numStr[numStr.size()-1])
            {
            case '1':
                s.setBuffer(soundMap->at("one"));
                numberSounds.push_back(s);
                break;
            case '2':
                s.setBuffer(soundMap->at("two"));
                numberSounds.push_back(s);
                break;
            case '3':
                s.setBuffer(soundMap->at("three"));
                numberSounds.push_back(s);
                break;
            case '4':
                s.setBuffer(soundMap->at("four"));
                numberSounds.push_back(s);
                break;
            case '5':
                s.setBuffer(soundMap->at("five"));
                numberSounds.push_back(s);
                break;
            case '6':
                s.setBuffer(soundMap->at("six"));
                numberSounds.push_back(s);
                break;
            case '7':
                s.setBuffer(soundMap->at("seven"));
                numberSounds.push_back(s);
                break;
            case '8':
                s.setBuffer(soundMap->at("eight"));
                numberSounds.push_back(s);
                break;
            case '9':
                s.setBuffer(soundMap->at("nine"));
                numberSounds.push_back(s);
                break;
            default:
                break;
            }
        }

        // Tens again
        if (numberOfDigits > 1) {
            switch (numStr[numStr.size()-2])
            {
            case '2':
                s.setBuffer(soundMap->at("twenty"));
                numberSounds.push_back(s);
                break;
            case '3':
                s.setBuffer(soundMap->at("thirty"));
                numberSounds.push_back(s);
                break;
            case '4':
                s.setBuffer(soundMap->at("forty"));
                numberSounds.push_back(s);
                break;
            case '5':
                s.setBuffer(soundMap->at("fifty"));
                numberSounds.push_back(s);
                break;
            case '6':
                s.setBuffer(soundMap->at("sixty"));
                numberSounds.push_back(s);
                break;
            case '7':
                s.setBuffer(soundMap->at("seventy"));
                numberSounds.push_back(s);
                break;
            case '8':
                s.setBuffer(soundMap->at("eighty"));
                numberSounds.push_back(s);
                break;
            case '9':
                s.setBuffer(soundMap->at("ninety"));
                numberSounds.push_back(s);
                break;
            
            default:
                break;
            }
        }
        
        // Hundreds
        if (useHundred) {
            digit = numStr[numStr.size()-3];
            if (digit != '0') {
                s.setBuffer(soundMap->at("hundred"));
                numberSounds.push_back(s);
            }
            
            std::cout << "Hundreds: " << digit << "\n";

            switch (digit)
            {
            case '1':
                s.setBuffer(soundMap->at("one"));
                numberSounds.push_back(s);
                break;
            case '2':
                s.setBuffer(soundMap->at("two"));
                numberSounds.push_back(s);
                break;
            case '3':
                s.setBuffer(soundMap->at("three"));
                numberSounds.push_back(s);
                break;
            case '4':
                s.setBuffer(soundMap->at("four"));
                numberSounds.push_back(s);
                break;
            case '5':
                s.setBuffer(soundMap->at("five"));
                numberSounds.push_back(s);
                break;
            case '6':
                s.setBuffer(soundMap->at("six"));
                numberSounds.push_back(s);
                break;
            case '7':
                s.setBuffer(soundMap->at("seven"));
                numberSounds.push_back(s);
                break;
            case '8':
                s.setBuffer(soundMap->at("eight"));
                numberSounds.push_back(s);
                break;
            case '9':
                s.setBuffer(soundMap->at("nine"));
                numberSounds.push_back(s);
                break;
            default:
                break;
            }
        }

        // Thousands
        if (useThousand) {
            s.setBuffer(soundMap->at("thousand"));
            numberSounds.push_back(s);
            digit = numStr[numStr.size()-4];
            std::cout << "Hundreds: " << digit << "\n";

            switch (digit)
            {
            case '1':
                s.setBuffer(soundMap->at("one"));
                numberSounds.push_back(s);
                break;
            case '2':
                s.setBuffer(soundMap->at("two"));
                numberSounds.push_back(s);
                break;
            case '3':
                s.setBuffer(soundMap->at("three"));
                numberSounds.push_back(s);
                break;
            case '4':
                s.setBuffer(soundMap->at("four"));
                numberSounds.push_back(s);
                break;
            case '5':
                s.setBuffer(soundMap->at("five"));
                numberSounds.push_back(s);
                break;
            case '6':
                s.setBuffer(soundMap->at("six"));
                numberSounds.push_back(s);
                break;
            case '7':
                s.setBuffer(soundMap->at("seven"));
                numberSounds.push_back(s);
                break;
            case '8':
                s.setBuffer(soundMap->at("eight"));
                numberSounds.push_back(s);
                break;
            case '9':
                s.setBuffer(soundMap->at("nine"));
                numberSounds.push_back(s);
                break;
            default:
                break;
            }
        }

        /**/
        sf::Sound dnotice1;
        dnotice1.setBuffer(soundMap->at("dnotice1"));
        sf::Sound dnotice2;
        dnotice2.setBuffer(soundMap->at("dnotice2"));

        dnotice1.play();
        while (dnotice1.getStatus() == sf::SoundSource::Status::Playing) {
            
        }
        /**/

        for (uint32_t i = numberSounds.size()-1; i < -1; i--) {
            numberSounds.at(i).play();
            while (numberSounds.at(i).getStatus() == sf::SoundSource::Status::Playing) {

            }
        }

        /**/
        dnotice2.play();
        while (dnotice2.getStatus() == sf::SoundSource::Status::Playing) {
            
        }
        /**/
    }

    std::thread* t;
    void SayTotalScore(CESoundMap* soundMap, uint32_t number)
    {
        if (t != nullptr) {
            if (t->joinable())
	        {
                t->join();
            }
            delete t;
        }

        t = new std::thread(&CurserSoundPlayer::SayNumber, this, soundMap, number);
    }
};

#endif // CURSER_SOUND_HPP