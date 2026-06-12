#include<SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <SFML/Audio.hpp>
#include <iomanip>
#include <ctime>
using namespace std;
using namespace sf;

void start();
void update();
void draw();

void MENUSCREEN();
void LEVEL1();
void LEVEL2TEXT();
void LEVEL2();
void GAMEOVER();
void VICCTORY();
void resetGame();
void CREDITS();
void CLEARLEGS();


RenderWindow window(VideoMode(1200, 800), "Chicken Invaders");
Music menuMusic, gamemusic;
SoundBuffer  clickBKAK, loseSOUND, VICTORYSOUND, explodSOUND, eatingSOUND, eggCrackSOUND, click;
Sound BKAK, gameover, victorySound, explosion, eating, eggCrack, CLICK;
Texture menuBG, player1Texture, BulletTexture, chickenTexture, eggTexture, bossTexture, bossEggTexture, giftTexture, logoTexture, chickLeg, brokenEggT, playT, playSelectT, creditsT, creditsSelectT
, exitT, exitSelectT, menuIconT, creditsPhotoT, thxPhotoT;
Sprite  menuBackGround, player1, bullet, egg, boss, bossEgg, gift, logo, brokenEggS, brokenBossEggS, playS, creditsS, exitS, playSelectS, exitSelectS, creditsSelectS, menuIconS, creditsPhotoS, thxPhotoS;
float playerSpeed = 500.f, bulletSpeed = 900.f, chickenSpeed = 100.f, eggSpeed = 250.f, bossEggSpeed = 400.f, giftSpeed = 200.f, bossSpeed = 150.f, legSpeed = 300.f;

const int MAX_CHICKENS = 30;
Sprite chickens[MAX_CHICKENS];

const int MAX_LEGS = 30;
Sprite legs[MAX_LEGS];

bool bulletActive = false,
chickensMoveRight = true,
eggActive = false,
bossActive = false,
bossMoveRight = true,
bossEggActive = false,
giftActive = false,
gameOver = false,
victory = false,
inGame = false
, level2Start = false
, legActive[MAX_LEGS], brokenEGG = false, brokenBossEggB = false;

bool MenuScreen = true
, Level1Screen = false
, Level2TextScreen = false
, Level2Screen = false
, GameOverScreen = false
, VictoryScreen = false
, CreditsScreen = false
, playerMoving = false;


IntRect playerRect(0, 0, 45, 37);
IntRect chickenRect(0, 0, 306, 203);
IntRect bossRect(0, 0, 354, 235);


int bossHealth = 100, bulletDamage = 2, giftCounter = 0, level = 1, lives = 3, score = 0, playerFrame = 0, chickenFrame = 0, bossFrame = 0, showScore = 0;
Clock eggClock, bossEggClock, giftClock, chickenMoveClock, Gclock, brokenEggClock, brokenBossEggC, playerMoveC, chickMoveC, bossMoveC, scoreCountC;
Font font;
int chickenFrameNum[MAX_CHICKENS];





Text playText("PLAY", font, 32), exitText("EXIT", font, 32), livesText, bossHealthText, victoryText, gameOverText, pressEnterText, level2Text, Entertorestart, scoreText;
int  menunumber = 0;




void MENUSCREEN() {
    MenuScreen = true;
    Level1Screen = Level2TextScreen = Level2Screen = GameOverScreen = VictoryScreen = false;
}

void LEVEL1() {
    Level1Screen = true;
    MenuScreen = Level2TextScreen = Level2Screen = GameOverScreen = VictoryScreen = false;
}

void  LEVEL2TEXT() {
    Level2TextScreen = true;
    MenuScreen = Level1Screen = Level2Screen = GameOverScreen = VictoryScreen = false;
}

void  LEVEL2() {
    Level2Screen = true;
    MenuScreen = Level1Screen = Level2TextScreen = GameOverScreen = VictoryScreen = false;
}

void GAMEOVER() {
    GameOverScreen = true;
    MenuScreen = Level1Screen = Level2TextScreen = Level2Screen = VictoryScreen = false;
}

void VICCTORY() {
    VictoryScreen = true;
    MenuScreen = Level1Screen = Level2TextScreen = Level2Screen = GameOverScreen = false;
}

void CLEARLEGS()
{
    for (int i = 0; i < MAX_LEGS; i++)
    {
        legActive[i] = false;
    }
}
void CREDITS() {
    CreditsScreen = true;
    MenuScreen = Level1Screen = Level2TextScreen = Level2Screen = GameOverScreen = VictoryScreen = false;
}

void start() {
    window.setFramerateLimit(60);


    menuMusic.openFromFile("assets/MENU.MUSIC.ogg");
    menuMusic.setLoop(true);
    menuMusic.play();

    gamemusic.openFromFile("assets/GAMEMUSIC.ogg");
    gamemusic.setLoop(true);
    gamemusic.setVolume(30);

    clickBKAK.loadFromFile("assets/chickenscream.ogg");
    BKAK.setBuffer(clickBKAK);

    loseSOUND.loadFromFile("assets/LOSESOUND.ogg");
    gameover.setBuffer(loseSOUND);

    explodSOUND.loadFromFile("assets/explodingSOUND.ogg");
    explosion.setBuffer(explodSOUND);
    explosion.setVolume(100);

    VICTORYSOUND.loadFromFile("assets/VICTORYSOUND.ogg");
    victorySound.setBuffer(VICTORYSOUND);

    eatingSOUND.loadFromFile("assets/eating.ogg");
    eating.setBuffer(eatingSOUND);
    eating.setVolume(60);


    eggCrackSOUND.loadFromFile("assets/eggCRASH.ogg");
    eggCrack.setBuffer(eggCrackSOUND);

    click.loadFromFile("assets/CLICKK.ogg");
    CLICK.setBuffer(click);

    player1Texture.loadFromFile("assets/player.png");
    player1.setTexture(player1Texture);
    player1.setTextureRect(playerRect);
    player1.setScale(3, 3);
    player1.setOrigin(
        45.f / 2,
        37.f / 2
    );

    player1.setPosition(500, 725);

    menuBG.loadFromFile("assets/BG.jpg");
    menuBackGround.setTexture(menuBG);
    menuBackGround.setScale(1200.f / 800, 1);

    BulletTexture.loadFromFile("assets/BULLET.png");
    bullet.setTexture(BulletTexture);
    bullet.setOrigin(bullet.getLocalBounds().width / 2, bullet.getLocalBounds().height / 2);
    bullet.setScale(0.06f, 0.06f);

    brokenEggT.loadFromFile("assets/brokenEGG.png");
    brokenEggS.setTexture(brokenEggT);
    brokenEggS.setScale(0.05f, 0.05f);

    brokenBossEggS.setTexture(brokenEggT);
    brokenBossEggS.setScale(0.12f, 0.12f);

    chickenTexture.loadFromFile("assets/chicken.png");
    for (int i = 0; i < 30; i++)
    {
        chickens[i].setTexture(chickenTexture);

        chickenFrameNum[i] = rand() % 4;

        IntRect rect = chickenRect;
        rect.left = chickenFrameNum[i] * 306;

        chickens[i].setTextureRect(rect);

        chickens[i].setScale(0.8f, 0.8f);

        chickens[i].setOrigin(
            306.f / 2,
            203.f / 2
        );

        chickens[i].setPosition(150 + (i % 10) * 100, 100 + (i / 10) * 90);

    }

    chickLeg.loadFromFile("assets/chickLEG.png");

    for (int i = 0; i < MAX_LEGS; i++)
    {
        legs[i].setTexture(chickLeg);
        legs[i].setScale(0.08f, 0.08f);
        legs[i].setOrigin(
            legs[i].getLocalBounds().width / 2, legs[i].getLocalBounds().height / 2);
        legActive[i] = false;

    }

    eggTexture.loadFromFile("assets/EGG.png");
    egg.setTexture(eggTexture);
    egg.setScale(0.04f, 0.04f);

    bossTexture.loadFromFile("assets/chickBOSS.png");
    boss.setTexture(bossTexture);
    boss.setTextureRect(bossRect);

    boss.setScale(1.70f, 1.7f);

    boss.setOrigin(
        354.f / 2,
        235.f / 2
    );

    bossEggTexture.loadFromFile("assets/BIGBOSSEGG.png");
    bossEgg.setTexture(bossEggTexture);
    bossEgg.setScale(0.06f, 0.06f);

    giftTexture.loadFromFile("assets/GIFT.png");
    gift.setTexture(giftTexture);
    gift.setScale(0.05f, 0.05f);

    logoTexture.loadFromFile("assets/LOGO.png");
    logo.setTexture(logoTexture);
    logo.setScale(0.9f, 0.7f);
    logo.setPosition(130, 80);

    font.loadFromFile("assets/ARCADECLASSIC.ttf");



    livesText.setFont(font);
    livesText.setCharacterSize(24);
    livesText.setPosition(20, 20);

    playT.loadFromFile("assets/play1.png");
    playSelectT.loadFromFile("assets/play2.png");

    creditsT.loadFromFile("assets/credits1.png");
    creditsSelectT.loadFromFile("assets/credits2.png");

    exitT.loadFromFile("assets/exit1.png");
    exitSelectT.loadFromFile("assets/exit2.png");

    playS.setTexture(playT);
    creditsS.setTexture(creditsT);
    exitS.setTexture(exitT);
    playSelectS.setTexture(playSelectT);
    exitSelectS.setTexture(exitSelectT);
    creditsSelectS.setTexture(creditsSelectT);

    playS.setPosition(190, 380);
    playSelectS.setPosition(190, 380);
    creditsS.setPosition(520, 470);
    creditsSelectS.setPosition(520, 470);
    exitS.setPosition(740, 380);
    exitSelectS.setPosition(740, 380);

    playS.setScale(0.6f, 0.6f);
    playSelectS.setScale(0.7f, 0.7f);
    creditsS.setScale(0.5f, 0.5f);
    creditsSelectS.setScale(0.6f, 0.6f);
    exitS.setScale(0.5f, 0.5f);
    exitSelectS.setScale(0.6f, 0.6f);
    livesText.setFont(font);
    livesText.setCharacterSize(24);
    livesText.setFillColor(Color::White);
    livesText.setPosition(20, 20);

    bossHealthText.setFont(font);
    bossHealthText.setCharacterSize(24);
    bossHealthText.setFillColor(Color::Red);
    bossHealthText.setPosition(20, 50);

    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(1000, 20);
    scoreText.setString("SCORE 0");

    level2Text.setFont(font);
    level2Text.setCharacterSize(100);
    level2Text.setOrigin(50, 50);
    level2Text.setFillColor(Color::Yellow);
    level2Text.setString("LEVEL 2");
    level2Text.setPosition(430, 300);


    pressEnterText.setFont(font);
    pressEnterText.setCharacterSize(50);
    pressEnterText.setOrigin(50, 50);
    pressEnterText.setFillColor(Color::White);
    pressEnterText.setString("Press   Enter  to   Start");
    pressEnterText.setPosition(380, 450);


    Entertorestart.setFont(font);
    Entertorestart.setCharacterSize(100);
    Entertorestart.setOrigin(50, 50);
    Entertorestart.setFillColor(Color::White);
    Entertorestart.setString("Press   Enter ");
    Entertorestart.setPosition(380, 450);

    victoryText.setFont(font);
    victoryText.setCharacterSize(100);
    victoryText.setOrigin(50, 50);
    victoryText.setFillColor(Color::Green);
    victoryText.setString("VICTORY");
    victoryText.setPosition(483, 350);

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(100);
    gameOverText.setOrigin(50, 50);
    gameOverText.setFillColor(Color::Red);
    gameOverText.setString("GAME   OVER");
    gameOverText.setPosition(400, 350);

    menuIconT.loadFromFile("assets/menu icon.png");
    menuIconS.setTexture(menuIconT);

    menuIconS.setScale(0.2f, 0.2f);

    creditsPhotoT.loadFromFile("assets/credits.png");
    creditsPhotoS.setTexture(creditsPhotoT);
    creditsPhotoS.setOrigin(306, 204);
    creditsPhotoS.setPosition(600, 400);
    creditsPhotoS.setScale(1.8f, 1.8f);

    thxPhotoT.loadFromFile("assets/thxphoto.png");
    thxPhotoS.setTexture(thxPhotoT);
    thxPhotoS.setOrigin(1200, 800);
    thxPhotoS.setPosition(600, 380);
    thxPhotoS.setScale(0.5f, 0.5f);
}

void update()
{
    float dt = Gclock.restart().asSeconds();
    Event event;

    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
            window.close();

        if (CreditsScreen && event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
        {
            CLICK.play();
            CreditsScreen = false;
            MENUSCREEN();
        }

        if (Level2TextScreen && event.type == Event::KeyPressed && event.key.code == Keyboard::Enter)
        {
            LEVEL2();
            bossActive = true;
            inGame = true;
            eggActive = false;
            brokenEGG = false;

            Level2TextScreen = false;
            player1.setPosition((1200 - player1.getGlobalBounds().width) / 2,
                850 - player1.getGlobalBounds().height - 20);
            boss.setPosition(600, 200);
        }


        if (MenuScreen && event.type == Event::KeyPressed)
        {
            if (event.key.code == Keyboard::Up || event.key.code == Keyboard::Left) {
                menunumber--;
                CLICK.play();
                if (menunumber < 0) menunumber = 2;
            }
            if (event.key.code == Keyboard::Down || event.key.code == Keyboard::Right) {
                menunumber++;
                CLICK.play();
                if (menunumber > 2) menunumber = 0;
            }
            if (event.key.code == Keyboard::Space || event.key.code == Keyboard::Enter) {
                CLICK.play();
                if (menunumber == 0) {
                    LEVEL1();
                    inGame = true;
                    menuMusic.stop();
                    gamemusic.play();
                }
                else if (menunumber == 1) {
                    CREDITS();
                }
                else if (menunumber == 2) {
                    window.close();
                }
            }
        }

        playS.setTexture(playT);
        creditsS.setTexture(creditsT);
        exitS.setTexture(exitT);


        if (menunumber == 0)
            playS.setTexture(playSelectT);

        else if (menunumber == 1)

            creditsS.setTexture(creditsSelectT);

        else if (menunumber == 2)
            exitS.setTexture(exitSelectT);


        if ((GameOverScreen || VictoryScreen) && event.type == Event::KeyPressed)
        {
            if (event.key.code == Keyboard::Enter)
            {
                resetGame();
                MENUSCREEN();
            }
        }
    }


    if (inGame)
    {

        if (Level1Screen || Level2Screen)
        {
            playerMoving = false;


            if (Keyboard::isKeyPressed(Keyboard::Right) &&
                player1.getPosition().x + player1.getGlobalBounds().width / 2 < 1200)
            {
                player1.move(playerSpeed * dt, 0);
                player1.setScale(3, 3);
                playerMoving = true;
            }


            if (Keyboard::isKeyPressed(Keyboard::Left) &&
                player1.getPosition().x - player1.getGlobalBounds().width / 2 > 0)
            {
                player1.move(-playerSpeed * dt, 0);
                player1.setScale(-3, 3);
                playerMoving = true;
            }
        }

        if (playerMoving)
        {
            if (playerMoveC.getElapsedTime().asSeconds() > 0.1f)
            {


                if (playerFrame < 3)
                    playerFrame++;

                playerRect.left = playerFrame * 45;
                player1.setTextureRect(playerRect);

                playerMoveC.restart();

            }
        }
        else {
            playerFrame = 0;
            playerRect.left = 0;
            player1.setTextureRect(playerRect);
        }

        if ((Level1Screen || Level2Screen) && !bulletActive)
        {
            if (Keyboard::isKeyPressed(Keyboard::Space))
            {
                bulletActive = true;
                bullet.setPosition(player1.getPosition().x, player1.getPosition().y);
            }
        }
        if (Level1Screen)
        {
            bool moveEnd = false;

            for (int i = 0; i < MAX_CHICKENS; i++)
            {
                if (chickens[i].getPosition().x < -500)
                    continue;

                if (chickensMoveRight &&
                    chickens[i].getPosition().x + chickens[i].getGlobalBounds().width / 2 >= 1200)
                {
                    moveEnd = true;
                    break;
                }

                if (!chickensMoveRight &&
                    chickens[i].getPosition().x - chickens[i].getGlobalBounds().width / 2 <= 0)
                {
                    moveEnd = true;
                    break;
                }
            }

            if (moveEnd)
            {
                chickensMoveRight = !chickensMoveRight;
            }

            for (int i = 0; i < MAX_CHICKENS; i++)
            {
                if (chickens[i].getPosition().x > -500)
                {
                    if (chickensMoveRight)
                        chickens[i].move(chickenSpeed * dt, 0);
                    else
                        chickens[i].move(-chickenSpeed * dt, 0);
                }
            }

            if (chickMoveC.getElapsedTime().asSeconds() > 0.10f)
            {
                chickenFrame++;

                if (chickenFrame >= 4)
                    chickenFrame = 0;

                for (int i = 0; i < MAX_CHICKENS; i++)
                {
                    int frame = (chickenFrame + chickenFrameNum[i]) % 4;

                    IntRect rect = chickenRect;
                    rect.left = frame * 306;

                    chickens[i].setTextureRect(rect);
                }

                chickMoveC.restart();
            }

        }
        if (Level1Screen && !eggActive && eggClock.getElapsedTime().asSeconds() >= 0.8f)
        {
            int randomChicken = rand() % MAX_CHICKENS;
            while (chickens[randomChicken].getPosition().x < -500)
            {
                randomChicken = rand() % MAX_CHICKENS;
            }
            egg.setPosition(
                chickens[randomChicken].getPosition().x -
                egg.getGlobalBounds().width / 2,
                chickens[randomChicken].getPosition().y +
                chickens[randomChicken].getGlobalBounds().height / 2
            );
            eggActive = true;
            eggClock.restart();
        }
        if (eggActive)
        {

            egg.move(0, eggSpeed * dt);


            if (egg.getPosition().y + egg.getGlobalBounds().height > 800) {
                eggActive = false;
                brokenEggS.setPosition(
                    egg.getPosition().x,
                    800 - brokenEggS.getGlobalBounds().height
                );

                brokenEGG = true;
                eggCrack.play();
                brokenEggClock.restart();
            }

            if (egg.getGlobalBounds().intersects(player1.getGlobalBounds()))
            {
                eggActive = false;
                lives--;
                explosion.play();

                if (lives <= 0 && !gameOver)
                {
                    lives = 0;
                    gameOver = true;
                    GAMEOVER();
                    inGame = false;
                    gamemusic.stop();
                    gameover.play();
                }

            }
        }
        if (brokenEGG)
        {
            if (brokenEggClock.getElapsedTime().asSeconds() > 1.0f)
            {
                brokenEGG = false;
            }
        }

        if (!giftActive && giftClock.getElapsedTime().asSeconds() >= 8.f)
        {
            float xPos = rand() % (1200 - (int)gift.getGlobalBounds().width);
            gift.setPosition(xPos, -50);
            giftActive = true;
            giftClock.restart();
        }
        if (giftActive)
        {
            gift.move(0, giftSpeed * dt);
            if (gift.getPosition().y > 850)
                giftActive = false;

            if (gift.getGlobalBounds().intersects(player1.getGlobalBounds()))
            {
                giftActive = false;
                giftCounter++;
                bulletDamage = giftCounter * 2;

                score += 2;
                scoreText.setString("SCORE " + to_string(score));

            }
        }
    }

    if (Level2Screen && bossActive)
    {

        if (bossMoveC.getElapsedTime().asSeconds() > 0.15f)
        {
            bossFrame++;

            if (bossFrame >= 3)
                bossFrame = 0;

            bossRect.left = bossFrame * 354;
            boss.setTextureRect(bossRect);

            bossMoveC.restart();
        }

        if (bossMoveRight)
            boss.move(bossSpeed * dt, 0);
        else
            boss.move(-bossSpeed * dt, 0);

        if (boss.getPosition().x - boss.getGlobalBounds().width / 2 <= 0)
            bossMoveRight = true;

        if (boss.getPosition().x + boss.getGlobalBounds().width / 2 >= 1200)
            bossMoveRight = false;

        if (!bossEggActive && bossEggClock.getElapsedTime().asSeconds() >= 2.f)
        {
            bossEgg.setPosition(
                boss.getPosition().x - bossEgg.getGlobalBounds().width / 2,
                boss.getPosition().y + boss.getGlobalBounds().height / 2
            );
            bossEggActive = true;
            bossEggClock.restart();
        }
        if (bossEggActive)
        {
            bossEgg.move(0, bossEggSpeed * dt);

            if (bossEgg.getPosition().y + bossEgg.getGlobalBounds().height > 800)
            {
                bossEggActive = false;

                brokenBossEggS.setPosition(
                    bossEgg.getPosition().x - 50,
                    800 - brokenBossEggS.getGlobalBounds().height
                );

                brokenBossEggB = true;
                eggCrack.play();
                brokenBossEggC.restart();
            }

            if (bossEgg.getGlobalBounds().intersects(player1.getGlobalBounds()))
            {
                bossEggActive = false;
                lives--;
                explosion.play();

                if (lives <= 0 && !gameOver)
                {
                    lives = 0;
                    gameOver = true;

                    brokenEGG = false;
                    brokenBossEggB = false;

                    GAMEOVER();
                    inGame = false;
                    bossActive = false;
                    gamemusic.stop();
                    gameover.play();
                }
            }
        }
        if (brokenBossEggB)
        {
            if (brokenBossEggC.getElapsedTime().asSeconds() > 1.0f)
            {
                brokenBossEggB = false;
            }
        }



        if (bossActive && bulletActive && bullet.getGlobalBounds().intersects(boss.getGlobalBounds()))
        {
            bulletActive = false;
            BKAK.play();
            bossHealth -= bulletDamage;

            if (bossHealth <= 0)
            {
                bossActive = false;
                brokenEGG = false;
                brokenBossEggB = false;
                VICCTORY();
                boss.setPosition(-1000, -1000);
                explosion.play();
                victory = true;
                gamemusic.stop();
                victorySound.play();
            }
        }
    }

    if (Level1Screen && level == 1)
    {
        bool allDead = true;
        for (int i = 0; i < MAX_CHICKENS; i++)
        {
            if (chickens[i].getPosition().x > -500)
            {
                allDead = false;
                break;
            }
        }
        if (allDead)
        {
            level = 2;
            CLEARLEGS();


            brokenEGG = false;
            brokenBossEggB = false;

            LEVEL2TEXT();
            inGame = false;
        }
    }

    if (bulletActive)
    {
        bullet.move(0, -bulletSpeed * dt);
        if (bullet.getPosition().y < 0)
            bulletActive = false;
    }

    for (int i = 0; i < MAX_LEGS; i++)
    {
        if (legActive[i])
        {
            legs[i].move(0, legSpeed * dt);


            if (legs[i].getPosition().y > 850)
            {
                legActive[i] = false;
            }


            if (legs[i].getGlobalBounds().intersects(player1.getGlobalBounds()))
            {
                legActive[i] = false;
                eating.play();
                score += 3;
                scoreText.setString("SCORE " + to_string(score));
                BKAK.play();
            }
        }
    }
    if (Level1Screen) {
        for (int i = 0; i < MAX_CHICKENS; i++)
        {
            if (bulletActive &&
                bullet.getGlobalBounds().intersects(chickens[i].getGlobalBounds()))
            {
                bulletActive = false;
                float x = chickens[i].getPosition().x;
                float y = chickens[i].getPosition().y;
                legs[i].setPosition(
                    chickens[i].getPosition().x + chickens[i].getGlobalBounds().width / 2,
                    chickens[i].getPosition().y + chickens[i].getGlobalBounds().height / 2
                );
                legActive[i] = true;

                chickens[i].setPosition(-1000, -1000);
                BKAK.play();
                score += 1;
                scoreText.setString("SCORE " + to_string(score));

                break;
            }
        }
    }
    if (VictoryScreen || GameOverScreen)
    {
        if (scoreCountC.getElapsedTime().asSeconds() > 0.03f)
        {
            if (showScore < score)
            {
                showScore++;
            }

            scoreText.setString("SCORE " + to_string(showScore));
            scoreCountC.restart();
        }
    }

}



void draw()
{
    window.clear();
    window.draw(menuBackGround);

    if (MenuScreen)
    {
        window.draw(menuBackGround);
        window.draw(logo);


        if (menunumber == 0)
        {
            window.draw(playSelectS);
            window.draw(exitS);
            window.draw(creditsS);
            menuIconS.setPosition(250, 430);
        }
        else if (menunumber == 1)
        {
            window.draw(playS);
            window.draw(exitS);
            window.draw(creditsSelectS);
            menuIconS.setPosition(500, 500);
        }
        else if (menunumber == 2)
        {
            window.draw(playS);
            window.draw(exitSelectS);
            window.draw(creditsS);
            menuIconS.setPosition(770, 400);
        }
        window.draw(menuIconS);

    }


    else if (Level1Screen || Level2Screen)
    {
        window.draw(player1);
        if (Level1Screen)
        {
            for (int i = 0; i < MAX_CHICKENS; i++) {
                if (chickens[i].getPosition().x > -500)
                    window.draw(chickens[i]);
            }

            for (int i = 0; i < MAX_LEGS; i++)
            {
                if (legActive[i])
                    window.draw(legs[i]);
            }
        }
        if (bulletActive) window.draw(bullet);
        if (eggActive) window.draw(egg);
        if (giftActive) window.draw(gift);

        if (bossActive)
        {
            window.draw(boss);
            if (bossEggActive) window.draw(bossEgg);
            bossHealthText.setString("Boss HP  " + to_string(bossHealth));
            window.draw(bossHealthText);
        }

        if (lives == 3) livesText.setString("Lives  3");
        else if (lives == 2) livesText.setString("Lives  2");
        else if (lives == 1) livesText.setString("Lives  1");
        else livesText.setString("Lives  0");

        window.draw(livesText);
    }

    if (Level1Screen || Level2Screen)
    {
        if (brokenEGG)
            window.draw(brokenEggS);

        if (brokenBossEggB)
            window.draw(brokenBossEggS);
    }

    if (Level1Screen || Level2Screen)
    {
        scoreText.setFillColor(Color::White);
        scoreText.setCharacterSize(24);
        scoreText.setPosition(1070, 20);
        window.draw(scoreText);
    }

    if (Level2TextScreen)
    {
        window.draw(level2Text);
        window.draw(pressEnterText);
    }

    if (GameOverScreen) {
        scoreText.setFillColor(Color::Yellow);
        scoreText.setCharacterSize(100);

        scoreText.setPosition(370, 220);
        window.draw(scoreText);

        window.draw(gameOverText);
        window.draw(Entertorestart);
    }

    if (VictoryScreen) {
        scoreText.setFillColor(Color::Yellow);
        scoreText.setCharacterSize(100);
        scoreText.setPosition(370, 220);
        window.draw(scoreText);

        window.draw(victoryText);
        window.draw(Entertorestart);

    }
    if (CreditsScreen)
    {

        window.draw(creditsPhotoS);
        window.draw(thxPhotoS);
    }
    window.display();
}

void resetGame()
{
    lives = 3;
    bossHealth = 100;
    bulletActive = false;
    eggActive = false;
    bossActive = false;
    bossEggActive = false;
    giftActive = false;
    gameOver = false;
    victory = false;
    inGame = false;
    level = 1;
    giftCounter = 0;
    bulletDamage = 2;
    level2Start = false;

    brokenEGG = false;
    brokenBossEggB = false;
    showScore = 0;
    score = 0;
    scoreText.setString("SCORE 0");

    player1.setPosition(500, 725);

    for (int i = 0; i < MAX_CHICKENS; i++) {
        chickens[i].setPosition(150 + (i % 10) * 100, 100 + (i / 10) * 90);
    }
    CLEARLEGS();

    chickensMoveRight = true;
    chickenMoveClock.restart();
    menuMusic.play();
    gamemusic.stop();



}
int main() {

    srand(time(0));
    start();

    while (window.isOpen())
    {
        update();
        draw();
    }
}