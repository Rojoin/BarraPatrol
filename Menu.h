#pragma once
#include <string>
#include "raylib.h"

struct MenuUI
{
    int fontSize;
    float xPosition;
    float yPosition;
    float xRepos;
    float yRepos;
};

class Menu
{
public:
    Menu();

    enum class MenuInterface
    {
        menu,
        play1Player,
        play2Player,
        options,
        rules,
        credits,
        exit
    };

private:
    void MainMenu();
    void DrawMainMenu(MenuUI menuUI) const;
    void OptionsMenu();
    void DrawOptions(Rectangle backBackRec, Rectangle screenSizeA, Rectangle screenSizeB, Rectangle bgMusic,
                     Rectangle soundRec) const;
    void RulesMenu();
    void DrawRules(Rectangle backRulesRec) const;
    void CreditsMenu();
    void DrawCredits(Rectangle backCreditsRec) const;
    static MenuUI InitMenuUI();
    void DrawBackgroundMenu() const;

    int screenWidth;
    int screenHeight;
    float height;
    float width1;
    bool music = true;
    bool sound = true;
    bool debugMode = false;
    bool fullscreen = false;
    Texture2D backgroundTexture;
    MenuInterface menuOptions;
    static constexpr Color NEONCYAN = CLITERAL(Color){4, 217, 255, 255};
    static constexpr Color DIFDARKGRAY = CLITERAL(Color){245, 245, 245, 60};
    Image logo;
    std::string credits[6];
    Rectangle linkedinRec;
    Rectangle itchioRec;
    Rectangle creditsRec[6];
    Rectangle menuRectangles[7];
};
