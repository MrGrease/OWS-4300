#include <imgui.h>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <imgui-SFML.h>
#include <iostream>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Config/ConfigManager.h"
#include "Actors/ShapeActor.h"
#include "Actors/Circle.h"
#include "Actors/Rectangle.h"

//read config file
//store shit
//draw to screen

int main() {

    ConfigManager* conf = new ConfigManager();
    conf->ReadConfigFile("config.txt");

    // create a new window of size w*h pixels
    // top-left of window is (0,0) and bottom-right is (w,h)
    // you will have to read these from the config file

    ConfigWindowSize& winConf = conf->GetWindowConfig();

    const unsigned int wWidth = winConf.width;
    const unsigned int wHeight = winConf.height;

    sf::RenderWindow window(sf::VideoMode({ wWidth, wHeight }), "SFML WORKS!");
    window.setFramerateLimit(60);


    if (!ImGui::SFML::Init(window))
    {
        std::cout << "Could not init window \n";
        std::exit(-1);
    }
    sf::Clock deltaClock;

    // scale the imgui ui and text size by 2
    ImGui::GetStyle().ScaleAllSizes(2.0f);
    ImGui::GetIO().FontGlobalScale = 2.0f;

    // the imgui color {r,g,b} wheel requires floats from 0-1
    // sfml will require instead of uint8_t from 0-255
    // this is the only really annoying conversion between sfml and imgui
    float c[3] = { 0.0f, 1.0f, 1.0f };

    // let's make a shape that we will draw to the screen
    float circleRadius = 50; // radius to draw the circle
    float shapeScale = 1;
    int circleSegmentsGlobal = 32; // number of segments to draw the circle with
    float circleSpeedX = 1.0f; // we will use this to move the circle later
    float circleSpeedY = 0.5f; // you will read these values from the file
    float speedx = 1;
    float speedy = 1;
    bool drawCircle = true; //whether or not to draw the circle
    bool drawText = true; //whether or not to draw the text
    bool drawShape = true; //whether or not to draw the shape
    // create the sfml circle shape based on our parameters
    //sf::CircleShape circle(circleRadius, circleSegmentsGlobal);//create the circle shape
    //circle.setPosition({ 10.0f, 10.0f });

    ConfigFont& fontConf = conf->GetFontConfig();
    sf::Font myFont;
    std::cout << "Working directory: " << std::filesystem::current_path() << "\n";
    for (auto& p : std::filesystem::directory_iterator("fonts/"))
    {
        std::cout << p.path() << "\n";
    }

    // attempt to load the font from a file
    //if (!myFont.openFromFile("C:\\Windows\\Fonts\\arial.ttf"))
    if (!myFont.openFromFile(fontConf.path))
    {
        // if we can't load the font, print an error to the console and exit
        std::cout << "Could not load font! \n";
        std::exit(-1);
    }


    sf::Text text(myFont, "Sample Text", fontConf.size);

    text.setFillColor(sf::Color(fontConf.r, fontConf.g, fontConf.b));

    text.setPosition({ 0, wHeight - (float)text.getCharacterSize() });

    char displayString[255] = "";


    //Generate All shapes
    std::vector<Simulation::ShapeActor*> actors;

    std::vector<std::string> actorRegister;

    for (int i = 0; i<conf->GetCircleConfigLength();i++)
    {
        ConfigCircle tempConfig = conf->GetCircleConfig(i);
        Simulation::Circle* tempCircle = new Simulation::Circle(circleSegmentsGlobal, tempConfig.radius,tempConfig.xpos, tempConfig.ypos, tempConfig.xspeed, tempConfig.yspeed, tempConfig.r, tempConfig.g, tempConfig.b, tempConfig.name,myFont, fontConf.size);
        actors.push_back(tempCircle);
        actorRegister.push_back(tempConfig.name);
    }

    for (int i = 0; i<conf->GetRectangleConfigLength(); i++)
    {
        ConfigRectangle tempConfig = conf->GetRectangleConfig(i);
        Simulation::Rectangle* tempRect = new Simulation::Rectangle(tempConfig.width, tempConfig.height, tempConfig.xpos, tempConfig.ypos, tempConfig.xspeed, tempConfig.yspeed, tempConfig.r, tempConfig.g, tempConfig.b, tempConfig.name, myFont, fontConf.size);
        actors.push_back(tempRect);
        actorRegister.push_back(tempConfig.name);
    }
    
    static int currentItem = 0;

    drawShape = actors[0]->GetDraw();
    shapeScale = actors[0]->GetScale();
    speedx = actors[0]->GetSpeedX();
    speedy = actors[0]->GetSpeedY();
    //displayString = actors[i]->GetActorText()->getString().toAnsiString().c_str();//TODO GET STRING
    memset(displayString, 0, sizeof(displayString));
    for (int j = 0; j < actors[0]->GetActorText()->getString().getSize(); j++)
    {
        displayString[j] = actors[0]->GetActorText()->getString().getData()[j];
    }

    while (window.isOpen()) {

        while (const auto event = window.pollEvent()) {
            ImGui::SFML::ProcessEvent(window, *event);

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {

                // print the key that was pressed to the console
                std::printf("Key pressed with code = {}\n", int(keyPressed->scancode));

                if (keyPressed->scancode == sf::Keyboard::Scancode::X)
                {
                    circleSpeedX *= -1.0f;
                }
            }
        }

        // update imgui for this frame with the time that the last frame took
        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Shape Properties");

        const char* preview = actorRegister[currentItem].c_str();

        if (ImGui::BeginCombo("Shape", preview))
        {
            for (int i = 0; i < actorRegister.size(); i++)
            {
                bool isSelected = (currentItem == i);

                if (ImGui::Selectable(actorRegister[i].c_str(), isSelected))
                {
                    currentItem = i;
                    drawShape = actors[i]->GetDraw();
                    shapeScale = actors[i]->GetScale();
                    speedx = actors[i]->GetSpeedX();
                    speedy = actors[i]->GetSpeedY();
                    //displayString = actors[i]->GetActorText()->getString().toAnsiString().c_str();//TODO GET STRING
                    memset(displayString, 0, sizeof(displayString));
                    for (int j = 0; j < actors[i]->GetActorText()->getString().getSize(); j++)
                    {
                        displayString[j] = actors[i]->GetActorText()->getString().getData()[j];
                    }
                }

                if (isSelected)
                {
                    ImGui::SetItemDefaultFocus();

                }
            }
            ImGui::EndCombo();
        }
        if(ImGui::Checkbox("Draw Shape", &drawShape))
        {
            actors[currentItem]->SetDraw(drawShape);
        }
        
        //ImGui::Checkbox("Draw Circle", &drawCircle);
        //ImGui::SameLine();
        //ImGui::Checkbox("DrawText", &drawText);
        if(ImGui::SliderFloat("Scale", &shapeScale, 0.1f, 300.0f))
        {
            actors[currentItem]->SetScale(shapeScale);
        }
        //ImGui::SliderFloat("Radius", &circleRadius, 0.0f, 300.0f);
        ImGui::SetNextItemWidth(120.0f);
        if (ImGui::SliderFloat("##", &speedx, 0.1f, 10.0f))
        {
            actors[currentItem]->SetSpeedX(speedx);
        }
        ImGui::SameLine();
        ImGui::SetNextItemWidth(120.0f);
        if (ImGui::SliderFloat("Velocity", &speedy, 0.1f, 10.0f))
        {
            actors[currentItem]->SetSpeedY(speedy);
        }
        //ImGui::SliderInt("Sides", &speedx, 3, 64);
        if (ImGui::ColorEdit3("Color", c))
        {
            actors[currentItem]->SetFillColor(c[0],c[1],c[2]);
        }
        if (ImGui::InputText("Name", displayString, 255))
        {
            actors[currentItem]->SetActorText(displayString);
        }

        /*if (ImGui::Button("Set Text"))
        {
            text.setString(displayString);
        }
        ImGui::SameLine();
        if (ImGui::Button("Reset Circle"))
        {
            //circle.setPosition({ 0,0 });
        }*/
        ImGui::End();

        //set the circle properties, because they may have been updated with the ui
        //circle.setPointCount(circleSegmentsGlobal);
        //circle.setRadius(circleRadius);

        // imgui uses 0-1 float for colors, sfml uses 0-255 for colors
        // we must convert from the ui floats to sfml uint8
        //circle.setFillColor(sf::Color(uint8_t(c[0] * 255), uint8_t(c[1] * 255), uint8_t(c[2] * 255)));

        //circle.setPosition({ circle.getPosition().x + circleSpeedX, circle.getPosition().y + circleSpeedY });

        window.clear();

        /*if (drawCircle)
        {
            //window.draw(circle);
        }
        if (drawText)
        {
            window.draw(text);
        }*/


        for (Simulation::ShapeActor* actor : actors)
        {
            actor->Tick();
            actor->Draw(window);
        }



        ImGui::SFML::Render(window);
        window.display();
    }


    for (Simulation::ShapeActor* actor : actors)
    {
        delete actor;
    }

    ImGui::SFML::Shutdown();


    delete conf;

    return 0;
}