/******************************************************************************************************************
FFFFFFFFF   LLL              A        PPPPPPPP     PPPPPPPP     YY     YY   ░░░░░░░░░░░░░░░░░░░░
FFFFFFFF    LLL             AAA       PPPP  PPP    PPPP  PPP     YY   YY    ░░▄▀██▄░░░░░░░░░░░░░   
FFF         LLL            AA AA      PPP   PPP    PPPP  PPP      YY YY     ░▀██████████▄▄███▀▀░   
FFFFFF      LLL           AAAAAAA     PPPPPPPP     PPPPPPPP        YYY      ░░░▀██████████▀▀░░░░   
FFFF        LLL          AAA   AAA    PPP          ppp             YYY      ░░░░░▀██▀▀█▀░░░░░░░░   
FFF         LLLLLLLL    AAAA   AAAA   PPP          ppp             YYY      ▓▓▓▓▓▐▐▓▓▌▌▌▓▓▓▓▓▓▓▓   

IMPORTANTE
    Para comenzar el juego es necesario pulsar ENTER y seguir con SPACE para que el pato vuele

******************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "include/OpenGL.h"
#include "include/Duck.h"
#include "include/Pipe.h"
#include "include/Watermelon.h"

using namespace std;

int pos = 999;

static void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
    {
        pos = 0;
    }
    else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    {
        pos = 1;
    }
}

int main(void)
{
    cout << endl;
    cout << "FFFFFFFFF  LLL            A       PPPPPPPP   PPPPPPPP   YY     YY  ░░░░░░░░░░░░░░░░░░░░" << endl;
    cout << "FFFFFFFF   LLL           AAA      PPPP  PPP  PPPP  PPP   YY   YY   ░░▄▀██▄░░░░░░░░░░░░░" << endl;
    cout << "FFF        LLL          AA AA     PPP   PPP  PPPP  PPP    YY YY    ░▀██████████▄▄███▀▀░" << endl;
    cout << "FFFFFF     LLL         AAAAAAA    PPPPPPPP   PPPPPPPP      YYY     ░░░▀██████████▀▀░░░░" << endl;
    cout << "FFFF       LLL        AAA   AAA   PPP        ppp           YYY     ░░░░░▀██▀▀█▀░░░░░░░░" << endl;
    cout << "FFF        LLLLLLLL  AAAA   AAAA  PPP        ppp           YYY     ▓▓▓▓▓▐▐▓▓▌▌▌▓▓▓▓▓▓▓▓" << endl;
    cout << endl;
    cout << "Preciona ENTER para comenzar e inmediatamente SPACE para volar" <<endl;


    OpenGL gl = OpenGL();

    GLFWwindow *window = gl.createWindow(1300, 768, "Flappy Duck");
    if (window == NULL) 
        return -1;

    glfwMakeContextCurrent(window);
    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glfwSetKeyCallback(window, keyboard);

    // Handling Variables
    bool isPaused = true;

    // Duck Variables
    Duck duck;

    // Pipe Variables
    Pipe pipe1(true, 1.0);
    Pipe pipe2(false, 2.0);
    Pipe pipe3(true, 3.0);
    Pipe pipe4(false, 4.0);

    // Watermelon Variables
    const double watermelonTiempoDeEspera = 3.0;
    double watermelonTimer = 0.0;
    int watermelonCounter = 0;
    double watermelonLastTime = glfwGetTime();
    bool watermelonCollected = false;
    Watermelon watermelon(gl.getProgramID());
    cout << endl;
    do
    {
        if (pos == 0)
        {
            isPaused = !isPaused;
            duck.fly();
            pipe1.move();
            pipe2.move();
            pipe3.move();
            pipe4.move();
            watermelon.move();
            pos = 999;
        }

        if (!isPaused)
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // DuckHandling---------------------------------------------------------------------
            if (!duck.hasPipeCollided(pipe1.getBox()) && !duck.hasPipeCollided(pipe2.getBox()) && !duck.hasPipeCollided(pipe3.getBox()) && !duck.hasPipeCollided(pipe4.getBox()))
            {
                if (pos == 1)
                {
                    duck.fly();
                    pos = 999;
                } pos = 999;
                
            }

            // PipeHandling---------------------------------------------------------------------
            pipe1.draw(gl.getProgramID());
            pipe2.draw(gl.getProgramID());
            pipe3.draw(gl.getProgramID());
            pipe4.draw(gl.getProgramID());

            // WatermelonHandling---------------------------------------------------------------
            double watermelonCurrentTime = glfwGetTime();
            double watermelonDeltaTime = watermelonCurrentTime - watermelonLastTime;
            watermelonLastTime = watermelonCurrentTime;
            watermelonTimer += watermelonDeltaTime;
            if (duck.hasWatermelonCollided(watermelon.getBox()))
            {
                watermelonCounter++;
                cout << watermelonCounter << ": Sandia agarrada gg " << endl;
                watermelonCollected = true;
                watermelonTimer = 0.0;
            }
            if (watermelonCollected && watermelonTimer < watermelonTiempoDeEspera)
            {
                watermelon.hide();
            }
            if (watermelonTimer >= watermelonTiempoDeEspera)
            {
                watermelon.show();
                watermelonCollected = false;
            }
            watermelon.draw();

            // Duck------------------------------------------------------------------------------
            duck.draw(gl.getProgramID());
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
             glfwWindowShouldClose(window) == 0);

    return 0;
}    

