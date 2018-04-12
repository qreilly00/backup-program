#include "../inc/common.h"
#include "../inc/textBox.h"


class window
{

private:

    sf::Vector2f mousePos;
    sf::Vector2f rectInputPos;
    sf::Vector2f rectInputSize;

    sf::RenderWindow window1;

    sf::Color clrButton1;
    sf::Color clrButton2;
    sf::Color clrTextBack1;
    sf::Color clrTextBack2;

    std::string fontLocation;

    sf::Font fnt1;

    sf::Text txtWelcome1;
    sf::Text txtButton1;
    sf::Text txtButton2;
    sf::Text txtInput1;

    sf::RectangleShape rectButton1;
    sf::RectangleShape rectButton2;
    sf::RectangleShape rectText;

    sf::FloatRect box1;
    sf::FloatRect box2;
    sf::FloatRect windowSize;
    
    bool inputOpen = 0;

public:

    window();

    sf::Vector2f getTextBoxPos();

    void update();
    void windowLoop();

};

window::window()
{

    windowSize = sf::FloatRect(0, 0, 1024, 576);
    mousePos.x = sf::Mouse::getPosition().x;
    mousePos.y = sf::Mouse::getPosition().y;
    rectInputSize =
    (
        sf::Vector2f(windowSize.width - 40, 45)
    );
    rectInputPos =
    (
        sf::Vector2f(((window1.getSize().x / 2) - (rectText.getSize().x / 2)),
        (rectText.getSize().y + rectText.getPosition().y + 40))
    );

    window1.create(sf::VideoMode(windowSize.width, windowSize.height), "backup your files", sf::Style::Titlebar | sf::Style::Close);

    clrButton1.r = 171;
    clrButton2.r = 230;
    clrTextBack1.r = 225;
    clrTextBack2.r = 190;

    clrButton1.g = 177;
    clrButton2.g = 236;
    clrTextBack1.g = 232;
    clrTextBack2.g = 204;

    clrButton1.b = 188;
    clrButton2.b = 247;
    clrTextBack1.b = 244;
    clrTextBack2.b = 226;

    fontLocation = "../fnt/Georgia.ttf";

    if(!(fnt1.loadFromFile(fontLocation)))
        std::cout << std::endl << "ERROR: Could not load 'Georgia.ttf' from folder fnt." << std::endl;

    txtWelcome1.setFont(fnt1);
    txtButton1.setFont(fnt1);
    txtButton2.setFont(fnt1);

    txtWelcome1.setCharacterSize(15);
    txtButton1.setCharacterSize(15);
    txtButton2.setCharacterSize(15);
    txtInput1.setCharacterSize(45);

    txtWelcome1.setString("Welcome to the backup program. To choose files to backup, write into the text file named 'backup locations' the following things: file/folder locaiton space new folder name. If you write the same folder name for a different backup, they will be put into the same folder. When making more than one file/folder backup, you must write them on seperate lines. The backups will be made to the location of the program.");
    txtButton1.setString("generate 'backup locations' file");
    txtButton2.setString("start backup");

    rectButton1.setSize(sf::Vector2f(150, 75));
    rectButton2.setSize(sf::Vector2f(150, 75));
    rectText.setSize(sf::Vector2f(windowSize.width - 40, windowSize.height - 240));

    rectText.setFillColor(clrTextBack1);

    rectButton1.setPosition
    (
        ((window1.getSize().x / 2) - (rectButton1.getSize().x / 2) - (rectButton1.getSize().x / 2) - 5),
        (window1.getSize().y - 85)
    );
    rectButton2.setPosition
    (
        ((window1.getSize().x / 2) - (rectButton2.getSize().x / 2) + (rectButton1.getSize().x / 2) + 5),
        (window1.getSize().y - 85)
    );
    rectText.setPosition
    (
        ((window1.getSize().x / 2) - (rectText.getSize().x / 2)),
        (/*window1.getSize().y -*/ 20)
    );

    box1 = rectButton1.getGlobalBounds();
    box2 = rectButton2.getGlobalBounds();


}

void window::update()
{

    box1 = rectButton1.getGlobalBounds();
    box2 = rectButton2.getGlobalBounds();

    mousePos.x = sf::Mouse::getPosition(window1).x;
    mousePos.y = sf::Mouse::getPosition(window1).y;

}

void window::windowLoop()
{

    //window1.create(sf::VideoMode(500, 500), "title", sf::Style::Titlebar | sf::Style::Close);

    window1.setPosition
    (
        sf::Vector2i(((sf::VideoMode::getDesktopMode().width / 2) - (window1.getSize().x / 2)),
        ((sf::VideoMode::getDesktopMode().height / 2) - (window1.getSize().y / 2)))
    );

    textBox txtBx(clrButton1, clrButton2, rectInputPos, rectInputSize, windowSize, fontLocation);

    while(window1.isOpen())
    {

        sf::Event event;

        while(window1.pollEvent(event))
        {
            
            if(event.type == sf::Event::Closed)
                window1.close();

            if(box1.contains(mousePos))
            {

                rectButton1.setFillColor(clrButton2);

            }
            else if(! (box1.contains(mousePos)))
            {

                rectButton1.setFillColor(clrButton1);

            }

            if(box2.contains(mousePos))
            {

                rectButton2.setFillColor(clrButton2);

            }
            else if(! (box2.contains(mousePos)))
            {

                rectButton2.setFillColor(clrButton1);

            }
            
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(txtBx.isTextBoxClicked(mousePos) == 1)
                {

                    txtBx.changeTextBox(1);
                    inputOpen = 1;

                }
                else if(txtBx.isTextBoxClicked(mousePos) == 0)
                {

                    txtBx.changeTextBox(0);
                    inputOpen = 0;

                }
            }
            
            if(inputOpen == 1 /*&& sf::Keyboard::isKeyPressed()*/)
            {
                
                txtBx.userInput(event);
                
            }
            
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                
                std::cout << "W";
                
            }
            
            /*if(textEvent.type == sf::Event::TextEntered)
            {
                if (textEvent.text.unicode == 8)
                {

                }

            }*/

        }
        
        update();
        //txtBx.update();
        
        window1.clear(sf::Color::White);
        window1.draw(rectButton1);
        window1.draw(rectButton2);
        window1.draw(rectText);
        window1.draw(txtBx.getRectInput());
        window1.display();

    }

}

class readFile
{

private:

    std::vector <std::string> vectReadLocation;
    std::vector <std::string> vectReadFoldername;

    std::ifstream infile;

    std::string fileName;

public:

    readFile(std::string fileNameInput);

    void fileIn();

};

readFile::readFile(std::string fileNameInput)
{

    fileName = fileNameInput;

}

void readFile::fileIn()
{



}

window mainw;
//readFile rf("hello")

int main()
{
    //std::string input;

    //std::cout << "Hello world";

    mainw.windowLoop();

    //std::cin >> input;

    return 0;
}
