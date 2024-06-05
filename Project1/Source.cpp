#include <iostream>
#include <SFML/Graphics.hpp>
#include "windows.h"
using namespace std;
using namespace sf;

const int LY = 23; // ������ ��������� �� ���������
const int LX = 28; // ������ ��������� �� �����������
const int sprSize = 24; // ������ ������� � ��������
const int dashboardSprSize = 48; // ������ �������� �������������� ���������
const int spritesCount = 9; //���������� ��������


int maze[LY][LX] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {2,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,4,0,0,0,4,0,0,0,0,0,0,0,0,0,1,4,0,8,0,0,0,4,1,1},
    {1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,1},
    {1,0,0,7,1,4,0,0,1,8,0,4,0,0,1,0,0,0,1,0,1,5,1,0,1,0,1,1},
    {1,0,1,1,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,0,1,1},
    {1,0,4,0,0,0,1,0,1,6,1,0,1,4,1,0,1,4,0,0,0,0,0,0,1,0,1,1},
    {1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,4,1,1},
    {2,0,1,0,1,4,1,0,0,0,0,4,0,0,1,0,0,0,1,4,0,0,1,0,0,0,1,1},
    {1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1},
    {1,4,1,4,0,0,1,6,1,4,0,0,1,4,0,0,0,7,0,0,0,5,1,0,1,6,1,1},
    {1,0,1,0,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,0,1,1,1,0,1,0,1,1},
    {1,8,0,0,1,4,0,0,0,0,0,0,4,0,1,0,0,0,1,0,0,0,1,8,1,0,1,1},
    {1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,0,1,0,1,0,1,1},
    {1,4,0,0,0,0,0,0,1,0,0,0,1,0,1,4,1,0,0,0,1,0,0,0,0,0,1,1},
    {1,1,1,0,1,0,1,0,1,1,1,0,1,4,1,1,1,1,1,0,1,1,1,1,1,1,1,1},
    {1,4,1,5,1,6,1,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,1,0,1,4,1,1},
    {1,0,1,1,1,1,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1},
    {1,7,1,0,0,0,0,5,1,0,1,5,1,0,1,7,1,4,1,0,1,0,1,0,1,0,1,1},
    {1,0,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,0,1,0,1,0,1,1},
    {1,4,0,0,0,0,4,0,0,0,4,0,0,0,0,4,0,0,0,0,1,0,4,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};
// ���������� �� ���������� ������ ����
int score = 0; // ���� ����
int value = 0;


int gameState = 0; // 0 - ���� ������������, 1 - �������, 2 - ����������� �����
sf::Time timeLimit = sf::milliseconds(20000); // ����� ���� � �������������
sf::Time gameTime; // ���������� �����
sf::Time elapsedTime; // ������� ���������� �������
sf::Clock gameClock; // ������

sf::Vector2f scoreTextPosition, timeTextPosition; // ������� ������ ��� ����� � ������ ��� �������

struct PlayerPosition // ���������, � ������� ������ ������� ������
{
    int x, y; // ���������� � � � ������
};

PlayerPosition playerPos{ 25, 21 }; // ��������� ����������, ������� ����� ������� ������� ������
// ��� ��������� PlayerPosition � ������ � � �
// � ���� �������� ���� ����� ������� �� ������ ���
// ������� ������������� ��� ������ ���������. �� ��� ������ ������ ���������

// ��������� ����, � ������� ������������ ����. ������ ������, ������� ������� ������� � ��������� ����
sf::RenderWindow window(sf::VideoMode(800, 688), "SFML maze game");

// ������� ����
sf::Texture textures[spritesCount];    // ��� ������ ��� �������� �������
sf::Sprite sprites[spritesCount];      // ��� ������ ��� ��������, ��� ���� ������� ������� ������� � ������� ������������� ��������� � ������� maze

std::string textureNames[spritesCount]{  // ��������� ������ ����� ��� �������� ���� ������, ������� ������ ��������
    "assets\\bitmaps\\empty.bmp",
    "assets\\bitmaps\\wall.bmp",
    "assets\\bitmaps\\door.bmp",
    "assets\\bitmaps\\man.png",
    "assets\\bitmaps\\money.png",
    "assets\\bitmaps\\diamond.png",
    "assets\\bitmaps\\time.png",
    "assets\\bitmaps\\mine.png",
    "assets\\bitmaps\\mine.png"
};

// ������� �������� �����������
sf::Texture backgroundTexture;
sf::Sprite backgroundSprite;
string backgroundImage = "assets\\background\\background.jpg";

// ������ "����"
sf::Texture scoreTexture;
sf::Sprite scoreSprite;
string scoreImage = "assets\\bitmaps\\score.png";

// ������ "������"
sf::Texture timerTexture;
sf::Sprite timerSprite;
string timerImage = "assets\\bitmaps\\timer.png";

// ����� �������� ����
sf::Text headerText;
sf::Font headerFont;
string headerTextFile = "assets\\fonts\\Novartis-Deco.ttf";

// ����� ����������� ����
sf::Text dashboardText;
sf::Font dashboardFont;
string dashboardTextFile = "assets\\fonts\\Grotesque-Bourgeoisie.ttf";

void UpdateScore(int score)
{
    dashboardText.setString(to_string(score)); // ������������� ����� ��� ������ to_string ��������� ����� � ��������� �������������
    dashboardText.setPosition(scoreTextPosition); // ������������� ������� ������ ��� �����
    dashboardText.setFillColor(sf::Color(255, 255, 35));
    window.draw(dashboardText); // ������������ ����� � ������ �����
}

// ������� ��������� ���������� ����� �� ��������� ����
void UpdateClock(sf::Time elapsed)
{
    gameTime = timeLimit - elapsed; /* ��������� ���������� ����� � ��������
                    timeLimit - ����� �������, elapsed - ��������� ����� � ������� ������ ����*/
    if (gameTime.asSeconds() < 0) // ���������, ����������� �� �����
        // gameTime.asSeconds() - ���������� ����� �� ������� Time � �������
    {
        gameState = 2; // ���� ��, �� ��������� ������ ���� �� 2 - ����� ��������
    }
    else
    {   // ���� ����� ��������
        dashboardText.setPosition(timeTextPosition); // ������������� ������� ������ ��� �����
        // ������������� ����� ��� ������ to_string ��������� ����� � ��������� �������������
        // ��� ��������� ������� � �������� ���������� ������� asSeconds. ��� ���������� float
        // ������� ���� ����������� �� � int, ����� �������� ���������� ����� ��� ������ ����������� �������
        dashboardText.setString(to_string((int)gameTime.asSeconds()));
        // ������������ ����� � ������ �����
        int u = value % 10;
        if (gameTime > milliseconds(15000)) {
            dashboardText.setFillColor(sf::Color(152, 251, 152));
            window.draw(dashboardText);
            window.draw(timerSprite);
        }
        else {
            dashboardText.setFillColor(sf::Color::Red);
            window.draw(dashboardText);
            if (u < 5)
            {
                window.draw(timerSprite);
            }
        }
    }
}

//������� ���������� �������� �������
void PrepareBackgroundImage(string imageFileName)
{
    backgroundTexture.loadFromFile(imageFileName); // ��������� ������� ��������
    backgroundSprite.setTexture(backgroundTexture); // ���������� �� �� ������
    backgroundSprite.setColor(sf::Color(255, 255, 255, 100)); // ������������� ������������ �������� �������
}

//������� �������� �������� ����������� ����
void PrepareDashboardImage(string scoreImageFileName, string timerImageFileName)
{
    scoreTexture.loadFromFile(scoreImageFileName); // ��������� ��������
    scoreSprite.setTexture(scoreTexture); // ���������� �� �� ������

    timerTexture.loadFromFile(timerImageFileName); // ��������� ��������
    timerSprite.setTexture(timerTexture); // ���������� �� �� ������

    // �������������. �������� ������� ���� ����
    sf::Vector2u wSize = window.getSize();
    // ��������� ���������� ������������ ������
    unsigned int scoreXPos = wSize.x / 2 - 8 * sprSize;
    unsigned int scoreYPos = wSize.y - dashboardSprSize - 10; // 48 ������ ������� ������, 10 - ������ ����� ����
    unsigned int timerXPos = wSize.x / 2 + 3 * sprSize;
    // ������������� ������� ��������
    scoreSprite.setPosition(sf::Vector2f(scoreXPos, scoreYPos));
    timerSprite.setPosition(sf::Vector2f(timerXPos, scoreYPos));
    // ��������� ������� ������ ��� ����� ���� = ��������_������� + ������ ������� + ������
    scoreTextPosition.x = scoreXPos + dashboardSprSize + 10;
    scoreTextPosition.y = scoreYPos - 15;
    // ��������� ������� ������ ��� ������� ���� = ��������_������� + ������ ������� + ������
    timeTextPosition.x = timerXPos + dashboardSprSize + 10;
    timeTextPosition.y = scoreYPos - 15;
}

// ������� �������� �������
void PrepareFonts(string headerFontName, string dashboardFontName)
{
    // ��������� ��������� ����
    headerFont.loadFromFile(headerFontName); // ��������� �����
    headerText.setFont(headerFont); // ������������� ����� ��� ������
    headerText.setCharacterSize(45); // ������������� ������ ��������
    headerText.setString("MAZE GAME");  // ������ ������ ������ ��� �����������
    headerText.setFillColor(sf::Color(255, 0, 0, 200)); // ������������� ���� ������� � ������������
    headerText.setStyle(sf::Text::Bold);  // ������ ����� ������
    // ��������� ������ ����������� ����
    dashboardFont.loadFromFile(dashboardFontName); // ��������� �����
    dashboardText.setFont(dashboardFont);// ������������� ����� ��� ������
    dashboardText.setCharacterSize(45);// ������������� ������ ��������
    dashboardText.setString("0");// ������ ������ ������ ��� �����������
    dashboardText.setFillColor(sf::Color(255, 255, 35)); // ������������� ������-������ ���� ������
    dashboardText.setStyle(sf::Text::Bold | sf::Text::Italic);// ������ ����� ������ � ��������, ��������� ������� �
    // ������������� ���������. �������� ������� ���� ����
    sf::Vector2u wSize = window.getSize();
    // �������� ������� ��������� ������ ���������. textBounds.width - ������ ������ � ��������
    sf::FloatRect textBounds = headerText.getLocalBounds();
    float x = wSize.x / 2 - textBounds.width / 2;
    headerText.setPosition(sf::Vector2f(x, 5));  // ������������� ���������
}

// �������, ���������������� ����� ���������. ������������ ������ PrintMaze
void RedrawMaze(int maze[LY][LX], int width, int height)
{
    // ������� "����������" �������� �� ������� ����, ��� ����� ����� ��������� ����������
    // �������� ������ ���� ���������. ��� ����� ������� �������� ������� ���� ����
    sf::Vector2u wSize = window.getSize();
    // ��� ����� ������� � �������� ������ ���� ��������� ������ ����?
    // ���� ������ ���� �������� �� 2 � ������� �� ����������� �������� �������� ������ ���������
    unsigned int xMaze = wSize.x / 2 - LX * sprSize / 2;
    // ���������� ��������� � �
    unsigned int yMaze = wSize.y / 2 - LY * sprSize / 2;
    // ����� ���������� ��� ���������� � �������� ������� ����� ��� ������ ���������

    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            // �������� �� ������� ��������� ��� ��������������� �������
            int index = maze[j][i];
            // ������ ������� ������� � ����. ������� ����� �� � - ������ �������� �������
            // ����������� �� ������ ������� �� �����������. �� � - ������ ������, �����������
            // �� ������ ������� �� ���������
            sprites[index].setPosition(sf::Vector2f(xMaze + i * sprSize, yMaze + j * sprSize));
            // ������������ ������
            if (index > 0) window.draw(sprites[index]);
        }
    }
}

// �������� ������� � ������������� ��������
void PrepareSpriteTexture(std::string names[spritesCount], int count = spritesCount)
{
    for (int i = 0; i < count; i++) // ���� �������� ������� � ������������� ��������
    {
        textures[i].loadFromFile(names[i]); // ������ �������� �� �����
        textures[i].setSmooth(true); // ��������� ���������� �������� ��� ���������� ������� ������������
        textures[i].setRepeated(false); // ��������� ����������� ���������� ������� ���������
        sprites[i].setTexture(textures[i]); // ���������� �������� �� ������
    }
}

// ���������� ������ �� ������� ������� �� dx ������ �� �����������
// � dy ������ �� ���������
void Move(int dx, int dy)
{
    if (playerPos.y + dy >= 0 && playerPos.y + dy < LY && // ��������� �� ����� �� ������� �����
        playerPos.x + dx >= 0 && playerPos.x + dx < LX)
    {
        if (maze[playerPos.y + dy][playerPos.x + dx] != 1) // ���������, ���� �� � ������� �����������
        {                                                  // ������, � ���� ��� - ������������
            maze[playerPos.y][playerPos.x] = 0; // ������� ������ �� ��������� � ������� �������
            playerPos.x += dx; // �������� ����������
            playerPos.y += dy; // ������
            switch (maze[playerPos.y][playerPos.x]) //��������� ���������� ������ ���������, ������� ������ �����
            {
            case 2: // ���� ����� - ���� 500 ������� � ������ ������ ���� �� �������
                score += 500; // ����������� ������
                gameState = 1;
                break;
            case 4: // ���� ������ - ��������� 100 �������
                score += 100; // ����������� ������
                break;
            case 5: // ���� ����� - ��������� 300 �������
                score += 300; // ����������� ������
                break;
            case 6: 
                timeLimit += milliseconds(10000);
                break;
            case 7: 
                score -= 200; 
                break;
            case 8:
                timeLimit -= milliseconds(8000);
                break;
            }
            maze[playerPos.y][playerPos.x] = 3; // ���������� ������ � ����� ������� ���������
        }
    }
}

void HandleKeyboardEvents() // ������������ ������� ����������
{
    // ������� isKeyPressed ������������ ��� �������� - ���� �� ������ ������������ �������.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) // ������ ������� �����?
    {
        Move(-1, 0); // ���� �����
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))// ������ ������� ������?
    {
        Move(1, 0);// ���� ������
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))  // �����
    {
        Move(0, -1);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) // ����
    {
        Move(0, 1);
    }
}


void RenderScene()
{
        window.draw(backgroundSprite);  // ������������ ������ � ������� ������������ � ������ �����
        RedrawMaze(maze, LX, LY); // ��������� ���������
        window.draw(headerText); // ������� ��������� ����
        window.draw(scoreSprite);
        UpdateScore(score); // ��������� ����� �����
        UpdateClock(gameClock.getElapsedTime()); // ��������� ���������� ����� ����
        value += 1;
}

void ShowMessageWindow(string text, Vector2f(size), Color textcolor, Color framecolor, Color backgroundColor) {
    RectangleShape messageWindow(size);
    sf::Vector2u wSize = window.getSize();
    messageWindow.move(window.getSize().x / 2 - 300.f, window.getSize().y / 2 - 150.f);
    messageWindow.setFillColor(backgroundColor);
    messageWindow.setOutlineThickness(5.f);
    messageWindow.setOutlineColor(framecolor);
    window.draw(messageWindow);
 
    dashboardText.setFillColor(textcolor); 
    dashboardText.setString(text); 
    sf::FloatRect textBounds = dashboardText.getLocalBounds();
    dashboardText.setPosition(wSize.x / 2 - textBounds.width / 2, wSize.y / 2);
    window.draw(dashboardText);
}

bool FindPlayerStartPosition(int maze[LY][LX], int sizeX, int sizeY, int& x, int& y) 
       {
        int k = 0, flag = 0;
        for (int i = 0; i < sizeY; i++)  
        {
            for (int j = 0; j < sizeX; j++) 
            {
                if (maze[i][j] == 3)    
                {                       
                    k += 1;
                    playerPos.x = j;             
                    playerPos.y = i;            
                    break;             
                }
                if (maze[i][j] == 2)
                    flag = 1;
            }
        }
        if (k == 1 and flag == 1)
            return true;
        else return false;
}

/*if (FindPlayerStartPosition(maze, LX, LY, playerPos.x, playerPos.y) == false) {
ShowMessageWindow("The labirint is invalid!!!", Vector2f(600.f, 300.f), Color::Yellow, Color::Yellow, Color::Red);
    }
    else {
    */

int main()
{
    PrepareSpriteTexture(textureNames, 9); // �������������� ������� ���������
    PrepareBackgroundImage(backgroundImage); // ������� ������ ����
    PrepareDashboardImage(scoreImage, timerImage); // ������� ������� ����������� ����
    PrepareFonts(headerTextFile, dashboardTextFile); // ������� ����� ��� ������ ������� � �����
    gameClock.restart(); // ��������� ������ � ����
        while (window.isOpen()) // ���� ��������� �������, ���� ���� ��������� �� �������
        {
            sf::Event event; // ��������� ������ �������
            while (window.pollEvent(event)) // �������� ������� �� �������
            {

                if (event.type == sf::Event::Closed) // ���������, ���� ��� �������� ����, �� ��������� ����
                    window.close();
            }
            window.clear(); // ������� ����
            HandleKeyboardEvents(); // ��������� ������� ����������
            RenderScene(); // ��������� (��������) �����
            if (gameState == 1) {
                ShowMessageWindow("Congratulations! You Won!!!", Vector2f(600.f, 300.f), Color::White, Color::White, Color::Blue);
            }
            else if (gameState == 2) {
                ShowMessageWindow("Time is over! You lost!!!", Vector2f(600.f, 300.f), Color::Yellow, Color::Yellow, Color::Red);
            }

            window.display();  // ��������� ������ ������ � ����
            Sleep(100); // ����� 100��

        }
   }
    
