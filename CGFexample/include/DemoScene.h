#ifndef DEMOSCENE_H
#define DEMOSCENE_H

#include "CGFscene.h"
#include "CGFshader.h"
#include "XMLScene.h"
#include "Appearance.h"
#include "interface.h"
#include "Model.h"
#include "Board.h"
#include "Connection.h"
#include "Play.h"

//Game Mode definition. 0 -> Login | 1 -> Free Camera | 2 -> Play Mode | 3 -> Insert Mode | 4 -> WIN
#define LOGIN 0
#define FREE 1
#define PLAY 2
#define INSERT 3
#define WIN 4

//Player definitions. 1 -> Player 1 | 2 -> Player 2
#define PLAYER1 1
#define PLAYER2 2

class DemoScene : public CGFscene {
    friend class interface;

public:
    void init();
    void display();
    void display_select();
    void update(long t);
    void activateCamera(int i);
    void renderstring3d(char string[], float r, float g, float b, float x, float y, float z);
    string getEntireString(Model* model, House* picked);
    DemoScene(char* nome);
    ~DemoScene();
    int lz[8];
    int nr;
    int number;
    int nr_cams;
    int mode;


private:
    CGFobject* obj;
    CGFappearance* materialAppearance;
    CGFappearance* textureAppearance;
    Appearance* argonathFront;
    Plane* skyboxFront;
    CGFshader* shader;
    XMLScene* lsf;
    CGFcamera* def;
    CGFcamera* active;
    vector<CGFcamera*> vec_cameras;
    char nome[40];
    Sphere* coiso;
    Model* cloud;
    Board* board;
    Connection* connection;
    Rectangle* login;
    Rectangle* pickingArea;
    int player;
    int moves1;
    int moves2;
    Play* plays;
    stack<Board*> boardsMovie;
    bool movie;
    int ambient;
    Rectangle * ambi;
    CGFappearance* environtments[4];
    char m1[2];
    char m2[2];
};

#endif
