/*
Author: Ugonna Nwankwo
Class: ECE4122
Last Date Modified: 10/27/2021

Description:

    Welcome to Buzzy's Revenge!! In this game, the user launches buzzy across the field attempting to hit the evil mascots from 
    other universities, while avoiding the cute woodland creatures. Do you have what it takes to defeat the evil mascots???
*/

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <ctime>
#include <cmath>
#include <stdio.h> 
#include <stdlib.h>
#include <iostream>
using namespace std;
int position;

struct creatures
{
    sf::Sprite property;
    int id;
};

void sort(vector<creatures> &animals)
{
    int mascot;
    bool mascotNoColumn = true;

    while (mascotNoColumn)
    {
        random_shuffle(animals.begin(), animals.end());
        mascot = 0;
        for (int i = 0; i < 5; i++)
        {
            if (animals[i].id == 7 || animals[i].id == 6)
            {
                mascot++;
            }
        }

        if (mascot == 1)
        {
            mascotNoColumn = false;
        }
    }

    for (int i = 0; i < 5; i++)
    {
        // Get a rectangle of image bounds
        sf::FloatRect imgRect = animals[i].property.getLocalBounds();

        // Calcuate Origin
        animals[i].property.setOrigin(imgRect.left + imgRect.width / 2.0f,
            imgRect.top + imgRect.height / 2.0f);

        animals[i].property.setPosition(1585, 405 + (float)i * 140);
    }

    for (int i = 5; i < animals.size(); i++)
    {
        // Get a rectangle of image bounds
        sf::FloatRect imgRect = animals[i].property.getLocalBounds();

        // Calcuate Origin
        animals[i].property.setOrigin(imgRect.left + imgRect.width / 2.0f,
            imgRect.top + imgRect.height / 2.0f);

        animals[i].property.setPosition(1805, 405 + (float)(i - 5) * 140);
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Buzzy's Revenge");
    int scoreCounter = 99;

    // Declare and load a font
    sf::Font font;
    font.loadFromFile("KOMIKAP_.ttf");

    // Create a text
    sf::Text title("Buzzy's Revenge", font);
    title.setCharacterSize(80);
    title.setStyle(sf::Text::Regular);
    title.setFillColor(sf::Color::Red);
    title.setPosition(570, 140);

    sf::Text instructOne("Press Enter to Restart Game", font);
    instructOne.setCharacterSize(58);
    instructOne.setStyle(sf::Text::Regular);
    instructOne.setFillColor(sf::Color::White);
    instructOne.setPosition(470, 320);

    sf::Text instructTwo("Press Esc to exit", font);
    instructTwo.setCharacterSize(58);
    instructTwo.setStyle(sf::Text::Regular);
    instructTwo.setFillColor(sf::Color::White);
    instructTwo.setPosition(660, 400);

    sf::Text instructThree("Press Space to Powerup", font);
    instructThree.setCharacterSize(58);
    instructThree.setStyle(sf::Text::Regular);
    instructThree.setFillColor(sf::Color::White);
    instructThree.setPosition(552, 476);

    sf::Text instructFour("Press up/down arrow to aim", font);
    instructFour.setCharacterSize(58);
    instructFour.setStyle(sf::Text::Regular);
    instructFour.setFillColor(sf::Color::White);
    instructFour.setPosition(490, 554);

    sf::Text create("created by", font);
    create.setCharacterSize(30);
    create.setStyle(sf::Text::Regular);
    create.setFillColor(sf::Color::White);
    create.setPosition(800, 726);

    sf::Text name("Ugonna Nwankwo", font);
    name.setCharacterSize(30);
    name.setStyle(sf::Text::Regular);
    name.setFillColor(sf::Color::White);
    name.setPosition(800, 766);

    sf::Text live("Lives", font);
    live.setCharacterSize(38);
    live.setStyle(sf::Text::Regular);
    live.setFillColor(sf::Color::White);
    live.setPosition(25, 34);

    sf::Text power("Power", font);
    power.setCharacterSize(38);
    power.setStyle(sf::Text::Regular);
    power.setFillColor(sf::Color::White);
    power.setPosition(40, 970);

    sf::Text score("Score: ", font);
    score.setCharacterSize(38);
    score.setStyle(sf::Text::Regular);
    score.setFillColor(sf::Color::White);
    score.setPosition(1700, 8);

    sf::Text scoreCount(to_string(scoreCounter), font);
    scoreCount.setCharacterSize(38);
    scoreCount.setStyle(sf::Text::Regular);
    scoreCount.setFillColor(sf::Color::White);
    scoreCount.setPosition(1850, 8);

    sf::RectangleShape powerBarOutline;
    powerBarOutline.setSize(sf::Vector2f(470, 60));
    powerBarOutline.setOutlineColor(sf::Color::Black);
    powerBarOutline.setFillColor(sf::Color::Transparent);
    powerBarOutline.setOutlineThickness(5);
    powerBarOutline.setPosition(190, 970);

    sf::RectangleShape powerBar;
    powerBar.setFillColor(sf::Color::Red);
    powerBar.setSize(sf::Vector2f(0, 60));
    powerBar.setPosition(190, 970);

    // Load a texture from a file
    sf::Texture textureBack;
    if (!textureBack.loadFromFile("Background.png"))
        return -1;

    sf::Texture textureBuzz;
    if (!textureBuzz.loadFromFile("smallbuzzy.png"))
        return -1;

    sf::Texture textureChick;
    if (!textureChick.loadFromFile("chicken.png"))
        return -1;

    sf::Texture textureMouse;
    if (!textureMouse.loadFromFile("mouse.png"))
        return -1;

    sf::Texture texturePig;
    if (!texturePig.loadFromFile("pig.png"))
        return -1;

    sf::Texture textureTiger;
    if (!textureTiger.loadFromFile("tiger.png"))
        return -1;

    sf::Texture textureBull;
    if (!textureBull.loadFromFile("Georgia_Bulldogs_logo_dog_g.png"))
        return -1;

    sf::Texture textureDog;
    if (!textureDog.loadFromFile("dog.png"))
        return -1;

    sf::Texture textureFrog;
    if (!textureFrog.loadFromFile("frog.png"))
        return -1;

    sf::Texture textureBunny;
    if (!textureBunny.loadFromFile("bunny.png"))
        return -1;

    sf::Texture textureUnicorn;
    if (!textureUnicorn.loadFromFile("angry_unicorn.png"))
        return -1;

    sf::Texture textureSheep;
    if (!textureSheep.loadFromFile("sheep.png"))
        return -1;

    sf::Texture textureInsect;
    if (!textureInsect.loadFromFile("insect.png"))
        return -1;

    sf::Texture textureLife;
    if (!textureLife.loadFromFile("buzzy life.png"))
        return -1;

    // Assign it to a sprite
    sf::Sprite background;
    background.setTexture(textureBack);

    sf::Sprite buzz;
    buzz.setTexture(textureBuzz);
    buzz.setScale(1.5, 1.5);
    buzz.setOrigin(169, 55);
    buzz.setPosition(120, 600);
    buzz.rotate(330);

    sf::Sprite chickenSprite;
    chickenSprite.setTexture(textureChick);
    chickenSprite.setScale(1.5, 1.5);

    sf::Sprite mouseSprite;
    mouseSprite.setTexture(textureMouse);
    mouseSprite.setScale(1.5, 1.5);

    sf::Sprite pigSprite;
    pigSprite.setTexture(texturePig);
    pigSprite.setScale(1.5, 1.5);

    sf::Sprite tigerSprite;
    tigerSprite.setTexture(textureTiger);
    tigerSprite.setScale(0.15, 0.15);

    sf::Sprite bullSprite;
    bullSprite.setTexture(textureBull);
    bullSprite.setScale(1.5, 1.5);

    sf::Sprite dogSprite;
    dogSprite.setTexture(textureDog);
    dogSprite.setScale(1.5, 1.5);

    sf::Sprite frogSprite;
    frogSprite.setTexture(textureFrog);
    frogSprite.setScale(1.5, 1.5);

    sf::Sprite bunnySprite;
    bunnySprite.setTexture(textureBunny);
    bunnySprite.setScale(1.5, 1.5);

    sf::Sprite unicornSprite;
    unicornSprite.setTexture(textureUnicorn);
    unicornSprite.setScale(1.5, 1.5);

    sf::Sprite sheepSprite;
    sheepSprite.setTexture(textureSheep);
    sheepSprite.setScale(1.5, 1.5);

    sf::Sprite lifeOne;
    lifeOne.setTexture(textureLife);
    lifeOne.setScale(0.62, 0.62);
    lifeOne.setPosition(130, 20);

    sf::Sprite lifeTwo;
    lifeTwo.setTexture(textureLife);
    lifeTwo.setScale(0.62, 0.62);
    lifeTwo.setPosition(202, 20);

    sf::Sprite lifeThree;
    lifeThree.setTexture(textureLife);
    lifeThree.setScale(0.62, 0.62);
    lifeThree.setPosition(274, 20);

    sf::Sprite lifeFour;
    lifeFour.setTexture(textureLife);
    lifeFour.setScale(0.62, 0.62);
    lifeFour.setPosition(346, 20);

    sf::Sprite lifeFive;
    lifeFive.setTexture(textureLife);
    lifeFive.setScale(0.62, 0.62);
    lifeFive.setPosition(418, 20);

    //create a creatures class for each sprite
    creatures chicken =
    {
        chickenSprite,
        10
    };

    creatures mouse =
    {
        mouseSprite,
        9
    };

    creatures pig =
    {
        pigSprite,
        8
    };

    creatures tiger =
    {
        tigerSprite,
        7
    };

    creatures bull =
    {
        bullSprite,
        6
    };

    creatures dog =
    {
        dogSprite,
        5
    };

    creatures frog =
    {
        frogSprite,
        4
    };

    creatures bunny =
    {
        bunnySprite,
        3
    };

    creatures unicorn =
    {
        unicornSprite,
        2
    };

    creatures sheep =
    {
        sheepSprite,
        1
    };

    sf::Sprite insect;
    insect.setTexture(textureInsect);
    insect.setScale(-2, 2.2);
    insect.setPosition(1678, 124);

    // Load a music to play
    sf::Music music;
    if (!music.openFromFile("Wii Sports - Wii Sports Theme.wav"))
        return EXIT_FAILURE;
    music.setVolume(20);
    // Play the music
    music.play();


    sf::SoundBuffer buffer;
    buffer.loadFromFile("Problems.wav");
    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.setVolume(25);

    vector<sf::Sprite> lives;
    lives.push_back(lifeOne);
    lives.push_back(lifeTwo);
    lives.push_back(lifeThree);
    lives.push_back(lifeFour);
    lives.push_back(lifeFive);
    

    vector<creatures> animals;
    animals.push_back(unicorn);
    animals.push_back(frog);
    animals.push_back(bull);
    animals.push_back(pig);
    animals.push_back(chicken);
    animals.push_back(mouse);
    animals.push_back(tiger);
    animals.push_back(dog);
    animals.push_back(bunny);
    animals.push_back(sheep);

    int noText = 0;
    bool gameStart = false;
    bool buzzLaunch = false;
    float horizontalVelocity;
    float maxInitialVelocity = 1920;
    float minInitialVelocity = 1920 / 4;
    float initialVelocity;
    float verticalVelocity;
    float xfinal;
    float yfinal;
    float dy;
    float dx;
    float angle;
    int insectDirection;
    bool spaceBarPressed;
    bool unicornHit = false;
    bool hitInsect = false;
    bool insectMove = false;
    float dt = 0;
    int mascotCount = 0;
    int lostLives = 5;
    srand(time(NULL));
    sort(animals);
   
    sf::Clock clock;
    sf::Time elapsed1;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //starts the game
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            noText = 1;
            gameStart = true;
            scoreCounter = 0;
            insectMove = true;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }

        if (gameStart == true)
        {
            scoreCount.setString(to_string(scoreCounter));
            //increases the powerbar size
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && powerBar.getSize().x <= 470)
            {
                powerBar.setSize(sf::Vector2f(powerBar.getSize().x + 2, powerBar.getSize().y));
                spaceBarPressed = true;
            }
            //checks to see if spacebar is released to launch buzz
            if (powerBar.getSize().x > 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space) != true && spaceBarPressed == true)
            {
                buzzLaunch = true;
                spaceBarPressed = false;
                initialVelocity = ((powerBar.getSize().x) / 470) * (maxInitialVelocity - minInitialVelocity) + minInitialVelocity + 10;
                horizontalVelocity = initialVelocity * (cos((360 - (double)buzz.getRotation()) * (acos(0.0) / 90)));
                verticalVelocity = initialVelocity * (sin((360 - (double)buzz.getRotation()) * (acos(0.0) / 90)));
                powerBar.setSize(sf::Vector2f(0, powerBar.getSize().y));
                sound.play();
                clock.restart();
            }
            //rotate buzz using up and down keys
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && buzzLaunch != true)
            {
                buzz.setRotation(buzz.getRotation() - 1);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && buzzLaunch != true)
            {
                buzz.setRotation(buzz.getRotation() + 1);
            }
            //move buzz using projectile motion equations
            if (buzzLaunch)
            {
                elapsed1 = clock.getElapsedTime();
                xfinal = 120 + (horizontalVelocity * elapsed1.asSeconds());
                yfinal = 600 - (verticalVelocity * elapsed1.asSeconds()) + (0.5 * (2200) * ((double)elapsed1.asSeconds() * (double)elapsed1.asSeconds()));
                dx = xfinal - buzz.getPosition().x;
                dy = buzz.getPosition().y - yfinal;
                angle = atan2(dy, dx);
                buzz.setPosition(xfinal, yfinal);
                buzz.setRotation( 360 - (angle * (90 / acos(0.0))));
            }
            //check if buzz is out of the screen
            if (buzz.getPosition().x > 1910 || buzz.getPosition().x <= 5 || buzz.getPosition().y > 1075 || buzz.getPosition().y <= 5)
            {
                lostLives--;
                buzzLaunch = false;
                buzz.setPosition(120, 600);
            }

            //move the insect randomly
            insectDirection = rand() % 2;
            if (insect.getPosition().x != 0 && insectMove == true)
            {
                if (insectDirection == 0)
                {
                    insect.move(-4, 2);
                }
                else if (insectDirection == 1)
                {
                    insect.move(-4, -2);
                }
                    
            }
            //check if insect is hit
            if (buzz.getPosition().x  >= (insect.getPosition().x - 60) && buzz.getPosition().x  <= (insect.getPosition().x + 60) && buzz.getPosition().y  >= (insect.getPosition().y - 60)  && buzz.getPosition().y <= (insect.getPosition().y + 60) )
            {
                scoreCounter += 75;
                scoreCount.setString(to_string(scoreCounter));
                insect.setPosition(-10, -10);
                hitInsect = true;
            }

            for (int i = 0; i < animals.size(); i++)
            {
                if (buzz.getPosition().x >= (animals[i].property.getPosition().x - 70) && buzz.getPosition().x <= (animals[i].property.getPosition().x + 70) && buzz.getPosition().y >= (animals[i].property.getPosition().y - 70) && buzz.getPosition().y <= (animals[i].property.getPosition().y + 70))
                {
                    //checks if a mascot is hit
                    if (animals[i].id == 6 || animals[i].id == 7)
                    {
                        scoreCounter += 25;
                        scoreCount.setString(to_string(scoreCounter));
                        buzz.setPosition(120, 600);
                        buzzLaunch = false;
                        sound.stop();
                        mascotCount++;
                        if (unicornHit == true)
                        {
                            animals.erase(animals.begin(), animals.begin() + 4);
                        }
                        else
                        {
                            animals.erase(animals.begin(), animals.begin() + 5);
                        }

                        break;
                    }
                    //checks to see if unicorn is hit
                    else if (animals[i].id == 2 && lostLives < 5)
                    {
                        lostLives++;
                        unicornHit = true;
                        animals.erase(animals.begin() + i);
                        for (int j = 0; j < i; j++)
                        {
                            animals[j].property.setPosition(animals[j].property.getPosition().x, animals[j].property.getPosition().y + 140);
                        }
                        buzz.setPosition(120, 600);
                        buzzLaunch = false;
                        break;
                        
                    }
                    //checks if a woodland creature is hit
                    else
                    {
                        lostLives--;
                        buzz.setPosition(120, 600);
                        buzzLaunch = false;
                        break;
                    }
                }
            }
            //places a life
            for (int i = 0; i < lostLives; i++)
            {
                lives[i].setColor(sf::Color(4294967295));
            }
            //removes a life
            for (int i = lostLives; i < lives.size(); i++)
            {
                lives[i].setColor(sf::Color(0));
            }

            //sets the insect back to its initial position
            if (insect.getPosition().x <= 0 && hitInsect == false)
            {
                insect.setPosition(1678, 124);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
            }
            
        }
        //generates the next level
        if (mascotCount == 2)
        {
            animals.clear();
            animals.push_back(unicorn);
            animals.push_back(frog);
            animals.push_back(bull);
            animals.push_back(pig);
            animals.push_back(chicken);
            animals.push_back(mouse);
            animals.push_back(tiger);
            animals.push_back(dog);
            animals.push_back(bunny);
            animals.push_back(sheep);
            buzz.setPosition(120, 600);
            sort(animals);
            insect.setPosition(1678, 124);
            insectMove = true;
            hitInsect = false;
            mascotCount = 0;
        }
        //ends the game
        if (lostLives == 0)
        {
            animals.clear();
            animals.push_back(unicorn);
            animals.push_back(frog);
            animals.push_back(bull);
            animals.push_back(pig);
            animals.push_back(chicken);
            animals.push_back(mouse);
            animals.push_back(tiger);
            animals.push_back(dog);
            animals.push_back(bunny);
            animals.push_back(sheep);
            buzz.setPosition(120, 600);
            sort(animals);
            noText = 0;
            insect.setPosition(1678, 124);
            scoreCounter = 0;
            scoreCount.setString(to_string(scoreCounter));
            insectMove = false;
            lostLives = 5;
        }
        

        window.clear();
        window.draw(background);
        //draws characters and titles on the screen.
        if (noText == 0)
        {
            window.draw(title);
            window.draw(instructOne);
            window.draw(instructTwo);
            window.draw(instructThree);
            window.draw(instructFour);
            window.draw(create);
            window.draw(name);
        }
        window.draw(live);
        window.draw(power);
        window.draw(powerBar);
        window.draw(powerBarOutline);
        window.draw(score);
        window.draw(scoreCount);
        window.draw(buzz);
        window.draw(insect);

        for (int i = 0; i < animals.size(); i++)
        {
            window.draw(animals[i].property);
        }
        
        for (int i = 0; i < lives.size(); i++)
        {
            window.draw(lives[i]);
        }

        window.display();
    }

    return 0;
}