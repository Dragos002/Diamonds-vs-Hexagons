#include "lab_m1/lab3/lab3.h"
#include "lab_m1/lab2/lab2.h"

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "lab_m1/lab3/transform2D.h"
#include "lab_m1/lab3/object2D.h"
#include "Tema1.h"
#include "core/engine.h"
#include "utils/gl_utils.h"


using namespace std;
using namespace m1;


Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}





void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    hexagon = nullptr;
    starcollect = nullptr;
    starcollect2 = nullptr;
    starcollect3 = nullptr;
    l = 125; // latura unui patrat din gridul de 9
    // se calucleaza centrele fiecarui patrat din grid
    cx[0] = 193;
    cy[0] = 377;
    for (int i = 1; i < 9; i++) {
        cx[i] = cx[i - 1] + 200;
        cy[i] = cy[i - 1];
        if (i == 3) {
            cx[i] = cx[0];
            cy[i] -= 150;
        }
        if (i == 6) {
            cx[i] = cx[0];
            cy[i] -= 150;
        }
    }
    
   // coordonate pentru translatii
    x = -900;
    y = 350;
    x2 = -900;
    x3 = -900;
    sx2 = 1;
    sx3 = 1;
    sx = 1;
    // timer hexagoane si stele(ammo)
    timer = 0.0f;
    resourcetimer = 0.0f;
    rendertime = 8.0f;
    starrendertime = 3.0f;

    // coordonate grid (3X3)
    gamematrix[0] = 150;
    gamematrixy[0] = 0;
    // drag & drop
    orangegrab = false;
    bluegrab = false;
    yellowgrab = false;
    purplegrab = false;
    
    for (int i = 0; i < 9; i++) {
        isocupied[i] = false;
        starx[i] = 0;
        angle[i] = 0;
        scaleremove[i] = 1;
        isremoved[i] = false;
        ishit[i] = false;
        meshrender[i] = 0;
        meshrender2[i] = 0;
        meshrender3[i] = 0;
        meshrender4[i] = 0;
    }
    for (int i = 1; i < 9; i++) {
        gamematrix[i] = gamematrix[i - 1] + 200;
        gamematrixy[i] = gamematrixy[i-1];
     
        if (i == 3) {
            gamematrix[i] = 150;
            gamematrixy[i] += 150;
           
        }
        if (i == 6) {
            gamematrix[i] = 150;
            gamematrixy[i] += 150;
           
        }
        
    }
    // grid joc 
    Mesh* square1 = object2D::CreateSquare("square1", glm::vec3(0, 0, 0), 125, glm::vec3(0, 1, 0), true);
    AddMeshToList(square1);
    Mesh* rectangle = object2D::CreateRectangle("rectangle", glm::vec3(0, 0, 0),100,425, glm::vec3(1, 0, 0), true);
    AddMeshToList(rectangle);


    Mesh* bluegun = object2D::CreateRhombusWithRectangle("bluegun", glm::vec3(285, 600, 1), 70, 60, 25, glm::vec3(0, 0, 1), true);
    AddMeshToList(bluegun);
    Mesh* yellowgun = object2D::CreateRhombusWithRectangle("yellowgun", glm::vec3(485, 600, 1), 70, 60, 25, glm::vec3(1, 1, 0), true);
    AddMeshToList(yellowgun);
    Mesh* orangegun = object2D::CreateRhombusWithRectangle("orangegun", glm::vec3(85, 600, 1), 70, 60, 25, glm::vec3(1, 0.64f, 0), true);
    AddMeshToList(orangegun);
    Mesh* purplegun = object2D::CreateRhombusWithRectangle("purplegun", glm::vec3(685, 600, 1), 70, 60, 25, glm::vec3(0.5f, 0, 0.8f), true);
    AddMeshToList(purplegun);


    Mesh* health = object2D::CreateSquare("health", glm::vec3(835, 550, 0), 115, glm::vec3(1, 0, 0), true);
    AddMeshToList(health);


    Mesh* orangeenemy = object2D::CreateHexagon("orangeenemy", glm::vec3(0,0,1), 50, glm::vec3(1, 0.64f, 0), true);
    AddMeshToList(orangeenemy);
    Mesh* blueenemy = object2D::CreateHexagon("blueenemy", glm::vec3(0, 0, 1), 50, glm::vec3(0, 0, 1), true);
    AddMeshToList(blueenemy);
    Mesh* yellowenemy = object2D::CreateHexagon("yellowenemy", glm::vec3(0, 0, 1), 50, glm::vec3(1, 1, 0), true);
    AddMeshToList(yellowenemy);
    Mesh* purpleenemy = object2D::CreateHexagon("purpleenemy", glm::vec3(0, 0, 1), 50, glm::vec3(0.5f, 0, 0.8f), true);
    AddMeshToList(purpleenemy);
    Mesh* innerhexagon = object2D::CreateHexagon("innerhexagon", glm::vec3(0, 0, 2), 35, glm::vec3(0.4f, 1, 0.69f), true);
    AddMeshToList(innerhexagon);


    Mesh* star = object2D::CreateStar("star", glm::vec3(0, 0, 1), 25, glm::vec3(0.5f, 0.5f, 0.5f), true);
    AddMeshToList(star);
    Mesh* starc = object2D::CreateStar("starc", glm::vec3(0, 0, 3), 25, glm::vec3(1, 1, 1), true);
    AddMeshToList(starc);
    Mesh* orangestar = object2D::CreateStar("orangestar", glm::vec3(0, 0, 1), 25, glm::vec3(1, 0.6f, 0), true);
    AddMeshToList(orangestar);
    Mesh* bluestar = object2D::CreateStar("bluestar", glm::vec3(0, 0, 1), 25, glm::vec3(0, 0, 1), true);
    AddMeshToList(bluestar);
    Mesh* yellowstar = object2D::CreateStar("yellowstar", glm::vec3(0, 0, 1), 25, glm::vec3(1, 1, 0), true);
    AddMeshToList(yellowstar);
    Mesh* purplestar = object2D::CreateStar("purplestar", glm::vec3(0, 0, 1), 25, glm::vec3(0.5f, 0, 0.5f), true);
    AddMeshToList(purplestar);


    Mesh* frame = object2D::CreateSquare("frame", glm::vec3(40, 537.5f, 0), 125, glm::vec3(0.5f, 0.5f, 0.5f), false);
    AddMeshToList(frame);
}   

void Tema1::FrameStart()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{
    if (hp == 0) {
        exit(1);
    }

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(800, 500);
    modelMatrix *= transform2D::Rotate(M_PI);
    // generare contro de resurse
    for (int i = 0; i < resource; i++) {
        modelMatrix *= transform2D::Translate(-55, 0);
       
        RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

    }
 
    // gird
    for (int i = 0; i < 9; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(gamematrix[i], gamematrixy[i]);
        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
    }
    // above GUI
    modelMatrix = glm::mat3(1);
    RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix);
    
    RenderMesh2D(meshes["orangegun"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["frame"], shaders["VertexColor"], modelMatrix);

    
    modelMatrix *= transform2D::Translate(200, 0);
    RenderMesh2D(meshes["frame"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat3(1);
    RenderMesh2D(meshes["bluegun"], shaders["VertexColor"], modelMatrix);
    
    modelMatrix *= transform2D::Translate(400, 0);
    RenderMesh2D(meshes["frame"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat3(1);
    RenderMesh2D(meshes["yellowgun"], shaders["VertexColor"], modelMatrix);

    modelMatrix *= transform2D::Translate(600, 0);
    RenderMesh2D(meshes["frame"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat3(1);
    RenderMesh2D(meshes["purplegun"], shaders["VertexColor"], modelMatrix);

    if ( hp >= 1)
    {
        RenderMesh2D(meshes["health"], shaders["VertexColor"], modelMatrix);
    }
    modelMatrix = glm::mat3(1);
    if (hp >= 2)
    {
        modelMatrix *= transform2D::Translate(150, 0);
        RenderMesh2D(meshes["health"], shaders["VertexColor"], modelMatrix);
    }
    if (hp == 3)
    {
        modelMatrix *= transform2D::Translate(150, 0);
        RenderMesh2D(meshes["health"], shaders["VertexColor"], modelMatrix);
    }


    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(60, 500);
    modelMatrix *= transform2D::Rotate(M_PI);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(260, 500);
    modelMatrix *= transform2D::Rotate(M_PI);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(315, 500);
    modelMatrix *= transform2D::Rotate(M_PI);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(460, 500);
    modelMatrix *= transform2D::Rotate(M_PI);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(515, 500);
    modelMatrix *= transform2D::Rotate(M_PI);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(660, 500);
    modelMatrix *= transform2D::Rotate(M_PI);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(715, 500);
    modelMatrix *= transform2D::Rotate(M_PI);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(765, 500);
    modelMatrix *= transform2D::Rotate(M_PI);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

    // enemy
    modelMatrix = glm::mat3(1);
    timer += deltaTimeSeconds;
    if (timer >= rendertime && hexagon == nullptr) {
        timer = 0.0f;
        Enemy* hexagon = new Enemy();
        hexagon->color = rand() % 4;
        hexagon->x = 1275;
        int line = rand() % 3;
        switch (line) {
        case 0:
            hexagon->y = cy[1];
            break;
        case 1:
            hexagon->y = cy[4];
            break;
        case 2:
            hexagon->y = cy[7];
            break;
        }
        
        hexagons.push_back(*hexagon);
        rendertime = 5.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / (10.0f - 5.0f));
        
    }
    for (int i = 0; i < hexagons.size(); i++) {
        modelMatrix = glm::mat3(1);
         if (hexagons[i].hp <= 0) {
            hexagons[i].scale -= deltaTimeSeconds;
            if (hexagons[i].scale <= 0)
            {
                
                hexagons.erase(hexagons.begin() + i);
                break;
            }
            
          }

        hexagons[i].xtranslate -= 60 * deltaTimeSeconds;
        modelMatrix *= transform2D::Translate(hexagons[i].x, hexagons[i].y);
        modelMatrix *= transform2D::Translate(hexagons[i].xtranslate, 0);
        modelMatrix *= transform2D::Scale(hexagons[i].scale, hexagons[i].scale);

        
        if (hexagons[i].xtranslate + 1275 <= 1) {
            hexagons.erase(hexagons.begin() + i);
            hp--;
            break;
        }
       
      //  cout << hexagons[i].hp << endl;
        
        
        switch (hexagons[i].color)
        {
        case 0:
            RenderMesh2D(meshes["orangeenemy"], shaders["VertexColor"], modelMatrix);
            RenderMesh2D(meshes["innerhexagon"], shaders["VertexColor"], modelMatrix);
            hexagons[i].isrendered = true;
            break;
        case 1:
            RenderMesh2D(meshes["blueenemy"], shaders["VertexColor"], modelMatrix);
            RenderMesh2D(meshes["innerhexagon"], shaders["VertexColor"], modelMatrix);
            hexagons[i].isrendered = true;
            break;
        case 2:
            RenderMesh2D(meshes["yellowenemy"], shaders["VertexColor"], modelMatrix);
            RenderMesh2D(meshes["innerhexagon"], shaders["VertexColor"], modelMatrix);
            hexagons[i].isrendered = true;
            break;
        case 3:
            RenderMesh2D(meshes["purpleenemy"], shaders["VertexColor"], modelMatrix);
            RenderMesh2D(meshes["innerhexagon"], shaders["VertexColor"], modelMatrix);
            hexagons[i].isrendered = true;
            break;
        }
        
        for (int j = 0; j < 9; j++)
        {

            if (hexagons[i].y == cy[j]) {
                if (hexagons[i].xtranslate + 1275 - 25 <= cx[j] + 70 && hexagons[i].xtranslate + 1275 >= cx[j] - 20 && isocupied[j] == true) {
                    isremoved[j] = true;
                    break;
                }
                if (isocupied[j] && hexagons[i].y == cy[j] && hexagons[i].isrendered == true) {
                    if (hexagons[i].color == 0 && isorange[j]== true && hexagons[i].xtranslate + 1275 - 25 > cx[j] && hexagons[i].hp >0)
                    {
                        meshrender[j] = 1;
                        if (hexagons[i].xtranslate + 1275 - 25 <= starx[j] + cx[j] + 25 && ishit[j] == false ) {
                            ishit[j] = true;
                            hexagons[i].hp--;
                            if (hexagons[i].hp <= 0) {
                                meshrender[j] = 0;
                                starx[j] = 0;
                                ishit[j] = false;
                            }
                           
                            

                        }

                    }
                    if (hexagons[i].color == 1 && isblue[j] == true && hexagons[i].xtranslate + 1275 - 25 > cx[j] && hexagons[i].hp > 0) {
                        meshrender2[j] = 1;
                        if (hexagons[i].xtranslate + 1275 - 25 <= starx[j] + cx[j] + 25 && ishit[j] == false) {
                            ishit[j] = true;
                            hexagons[i].hp--;
                            if (hexagons[i].hp <= 0) {
                                meshrender2[j] = 0;
                                starx[j] = 0;
                                ishit[j] = false;
                            }
                            
                            
                        }
                    }
                    if (hexagons[i].color == 2 && isyellow[j] == true && hexagons[i].xtranslate + 1275 - 25 > cx[j] && hexagons[i].hp > 0) {
                        meshrender3[j] = 1;
                        if (hexagons[i].xtranslate + 1275 - 25 <= starx[j] + cx[j] + 25 && ishit[j] == false ) {
                            ishit[j] = true;
                            hexagons[i].hp--;
                            if (hexagons[i].hp <= 0) {
                                meshrender3[j] = 0;
                                starx[j] = 0;
                                ishit[j] = false;
                            }
                       

                        }
                    }
                    if (hexagons[i].color == 3 && ispurple[j] == true && hexagons[i].xtranslate + 1275 - 25 > cx[j] && hexagons[i].hp > 0) {
                        meshrender4[j] = 1;
                        if (hexagons[i].xtranslate + 1275 - 25 <= starx[j] + cx[j] + 25 && ishit[j] == false ) {
                            ishit[j] = true;
                            hexagons[i].hp--;
                            if (hexagons[i].hp <= 0) {
                                meshrender4[j] = 0;
                                starx[j] = 0;
                                ishit[j] = false;
                            }
                            

                        }
                        
                    }
                    if (meshrender[j] == 1 && hexagons[i].hp <= 0) {
                        meshrender[j] = 0;
                        starx[j] = 0;
                    }
                    if (meshrender2[j] == 1 && hexagons[i].hp <= 0) {
                        meshrender2[j] = 0;
                        starx[j] = 0;
                    }
                    if (meshrender3[j] == 1 && hexagons[i].hp <= 0) {
                        meshrender3[j] = 0;
                        starx[j] = 0;
                    }
                    if (meshrender4[j] == 1 && hexagons[i].hp <= 0) {
                        meshrender4[j] = 0;
                        starx[j] = 0;
                    }

                    
                }
            }
        }
    }
    





    // ammo
    resourcetimer += deltaTimeSeconds;
    if (resourcetimer >= starrendertime && starcollect== nullptr)
    {
        resourcetimer = 0.0f;
        Resource* starcollect = new Resource();
        Resource* starcollect2 = new Resource();
        Resource* starcollect3 = new Resource();
        starcollect->xs = rand() % 900 + 1;
        starcollect->ys = rand() % 449 + 1;
        starcollect2->xs = rand() % 900 + 1;
        starcollect2->ys = rand() % 449 + 1;
        starcollect3->xs = rand() % 900 + 1;
        starcollect3->ys = rand() % 449 + 1;
        resources.push_back(*starcollect);
        resources.push_back(*starcollect2);
        resources.push_back(*starcollect3);
        starrendertime = 10.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / (10.0f - 7.0f));
    }
    
    for (int i = 0; i < resources.size(); i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(resources[i].xs, resources[i].ys);
        modelMatrix *= transform2D::Rotate(M_PI);
        RenderMesh2D(meshes["starc"], shaders["VertexColor"], modelMatrix);
        if (resources[i].isclicked == true) {
            resources.erase(resources.begin() + i);
            break;
        }
    }





    // drag & drop render
    modelMatrix = glm::mat3(1);
    if (orangegrab == true) {
        modelMatrix *= transform2D::Translate(xmouse - 80, ymouse - 600);
        RenderMesh2D(meshes["orangegun"], shaders["VertexColor"], modelMatrix);
    }
    if (bluegrab == true) {
        modelMatrix *= transform2D::Translate(xmouse - 280, ymouse - 600);
        RenderMesh2D(meshes["bluegun"], shaders["VertexColor"], modelMatrix);
    }
    if (yellowgrab == true) {
        modelMatrix *= transform2D::Translate(xmouse - 480, ymouse - 600);
        RenderMesh2D(meshes["yellowgun"], shaders["VertexColor"], modelMatrix);
    }
    if (purplegrab == true) {
        modelMatrix *= transform2D::Translate(xmouse - 680, ymouse - 600);
        RenderMesh2D(meshes["purplegun"], shaders["VertexColor"], modelMatrix);
    }
    for (int i = 0; i < 9; i++) {
      
        if (isocupied[i] == true) {
            modelMatrix = glm::mat3(1);
           
           



            if (isorange[i] == true) {
                
                modelMatrix = glm::mat3(1);
                if (isremoved[i] == true) {
                    if (scaleremove[i] > 0) {
                        scaleremove[i] -= deltaTimeSeconds;
                    }
                    if (scaleremove[i] <= 0)
                    {
                        isorange[i] = false;
                        isocupied[i] = false;
                        isremoved[i] = false;
                        starx[i] = 0;
                    }
                }
                else {
                    scaleremove[i] = 1;

                }
                modelMatrix *= transform2D::Translate(cx[i] , cy[i] );
                modelMatrix *= transform2D::Scale(scaleremove[i], scaleremove[i]);
                modelMatrix *= transform2D::Translate(-85, -600);
                RenderMesh2D(meshes["orangegun"], shaders["VertexColor"], modelMatrix);
                modelMatrix = glm::mat3(1);
               
                if (meshrender[i] == 1)
                {

                    starx[i] += 420 * deltaTimeSeconds;
                    angle[i] -= M_PI * deltaTimeSeconds;
                    if (starx[i] >= 1270) {
                        starx[i] = 0;
                        ishit[i] = false;
                    }

                    modelMatrix *= transform2D::Translate(cx[i], cy[i]);
                    modelMatrix *= transform2D::Translate(starx[i], 0);
                    modelMatrix *= transform2D::Rotate(angle[i]);
                    if (ishit[i] == false)
                    {
                        RenderMesh2D(meshes["orangestar"], shaders["VertexColor"], modelMatrix);
                    }
                }
            }
            if (isblue[i] == true) {
                modelMatrix = glm::mat3(1);
                if (isremoved[i] == true) {
                    if (scaleremove[i] > 0) {
                        scaleremove[i] -= deltaTimeSeconds;
                    }
                    if (scaleremove[i] <= 0)
                    {
                        isblue[i] = false;
                        isocupied[i] = false;
                        isremoved[i] = false;
                        starx[i] = 0;
                    }
                }
                else {
                    scaleremove[i] = 1;

                }
                modelMatrix *= transform2D::Translate(cx[i], cy[i]);
                modelMatrix *= transform2D::Scale(scaleremove[i], scaleremove[i]);
                modelMatrix *= transform2D::Translate(-285, -600);
                RenderMesh2D(meshes["bluegun"], shaders["VertexColor"], modelMatrix);
                modelMatrix = glm::mat3(1);
                
                if (meshrender2[i] == 1)
                {
                    starx[i] += 420 * deltaTimeSeconds;
                    angle[i] -= M_PI * deltaTimeSeconds;
                    if (starx[i] >= 1270) {
                        starx[i] = 0;
                        ishit[i] = false;

                    }
                    modelMatrix *= transform2D::Translate(cx[i], cy[i]);
                    modelMatrix *= transform2D::Translate(starx[i], 0);
                    modelMatrix *= transform2D::Rotate(angle[i]);
                    if (ishit[i] == false)
                    {
                        RenderMesh2D(meshes["bluestar"], shaders["VertexColor"], modelMatrix);
                    }
                }
            }
            if (isyellow[i] == true) {
                modelMatrix = glm::mat3(1);
                if (isremoved[i] == true) {
                    if (scaleremove[i] > 0) {
                        scaleremove[i] -= deltaTimeSeconds;
                    }
                    if (scaleremove[i] <= 0)
                    {
                        isyellow[i] = false;
                        isocupied[i] = false;
                        isremoved[i] = false;
                        starx[i] = 0;
                    }
                }
                else {
                    scaleremove[i] = 1;

                }
                modelMatrix *= transform2D::Translate(cx[i], cy[i]);
                modelMatrix *= transform2D::Scale(scaleremove[i], scaleremove[i]);
                modelMatrix *= transform2D::Translate(-485, -600);
                RenderMesh2D(meshes["yellowgun"], shaders["VertexColor"], modelMatrix);
                modelMatrix = glm::mat3(1);
                
                if (meshrender3[i] == 1)
                {
                    starx[i] += 420 * deltaTimeSeconds;
                    angle[i] -= M_PI * deltaTimeSeconds;
                    if (starx[i] >= 1270) {
                        starx[i] = 0;
                        ishit[i] = false;
                    }
                    modelMatrix *= transform2D::Translate(cx[i], cy[i]);
                    modelMatrix *= transform2D::Translate(starx[i], 0);
                    modelMatrix *= transform2D::Rotate(angle[i]);
                    if (ishit[i] == false)
                    {
                        RenderMesh2D(meshes["yellowstar"], shaders["VertexColor"], modelMatrix);
                    }
                }

            }
            if (ispurple[i] == true) {
                modelMatrix = glm::mat3(1);
                if (isremoved[i] == true) {
                    if (scaleremove[i] > 0) {
                        scaleremove[i] -= deltaTimeSeconds;
                    }
                    if (scaleremove[i] <= 0)
                    {
                        ispurple[i] = false;
                        isocupied[i] = false;
                        isremoved[i] = false;
                        starx[i] = 0;
                    }
                }
                else {
                    scaleremove[i] = 1;

                }
                modelMatrix *= transform2D::Translate(cx[i], cy[i]);
                modelMatrix *= transform2D::Scale(scaleremove[i], scaleremove[i]);
                modelMatrix *= transform2D::Translate(-685, -600);
                RenderMesh2D(meshes["purplegun"], shaders["VertexColor"], modelMatrix);
                modelMatrix = glm::mat3(1);
                
                if (meshrender4[i] == 1)
                {
                    starx[i] += 420 * deltaTimeSeconds;
                    angle[i] -= M_PI * deltaTimeSeconds;
                    if (starx[i] >= 1270) {
                        starx[i] = 0;
                        ishit[i] = false;
                    }
                    modelMatrix *= transform2D::Translate(cx[i], cy[i]);
                    modelMatrix *= transform2D::Translate(starx[i], 0);
                    modelMatrix *= transform2D::Rotate(angle[i]);
                    if (ishit[i] == false)
                    {
                        RenderMesh2D(meshes["purplestar"], shaders["VertexColor"], modelMatrix);
                    }
                }
            }
        }
    }
}

void Tema1::FrameEnd()
{
}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}

void Tema1::OnKeyPress(int key, int mods)
{
}

void Tema1::OnKeyRelease(int key, int mods)
{
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{

    xmouse = mouseX;
    ymouse = 720 - mouseY;
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    if (button == 1) {
        // orange gun
        if (mouseX >= 40 && mouseX <= 161 && mouseY >= 62 && mouseY <= 182) {
            orangegrab = true;
        }
        if (mouseX >= 243 && mouseX <= 360 && mouseY >= 62 && mouseY <= 182) {
            bluegrab = true;
        }
        if (mouseX >= 444 && mouseX <= 561 && mouseY >= 62 && mouseY <= 182) {
            yellowgrab = true;
        }
        if (mouseX >= 642 && mouseX <= 760 && mouseY >= 62 && mouseY <= 182) {
            purplegrab = true;
        }
        for (int i = 0; i < resources.size(); i++) {
            if (mouseX >= resources[i].xs - 25 && mouseX <= resources[i].xs + 25 && mouseY >= 720 - resources[i].ys - 25 && mouseY <= 720 - resources[i].ys + 25) {
                resource++;
                resources[i].isclicked = true;
            }
        }
    }
  
    if (button == 2) {
        if (mouseX >= 148 && mouseX <= 273 && mouseY >= 291 && mouseY <= 419) {
            isremoved[0] = true;
           
        } else
        if (mouseX >= 350 && mouseX <= 474 && mouseY >= 291 && mouseY <= 419) {
           
            isremoved[1] = true;
        } else
        if (mouseX >= 550 && mouseX <= 673 && mouseY >= 291 && mouseY <= 419) {
          
            isremoved[2] = true;
        }
        else
        if (mouseX >= 148 && mouseX <= 273 && mouseY >= 442 && mouseY <= 569) {
           
            isremoved[3] = true;
        } else
        if (mouseX >= 350 && mouseX <= 474 && mouseY >= 442 && mouseY <= 569) {
           
            isremoved[4] = true;
        } else
        if (mouseX >= 550 && mouseX <= 673 && mouseY >= 442 && mouseY <= 569) {
            isremoved[5] = true;
        }
        else
        if (mouseX >= 148 && mouseX <= 273 && mouseY >= 594 && mouseY <= 714) {
            isremoved[6] = true;
        } else
        if (mouseX >= 350 && mouseX <= 474 && mouseY >= 594 && mouseY <= 714) {
            isremoved[7] = true;
        } else
        if (mouseX >= 550 && mouseX <= 673 && mouseY >= 594 && mouseY <= 714) {
            isremoved[8] = true;
        }
        
        
    }
    
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    if (button == 1) {
        if (mouseX >= 148 && mouseX <= 273 && mouseY >= 291 && mouseY <= 419 && isocupied[0] == false) {
            if (orangegrab == true && resource >= 1) {
                isocupied[0] = true;
                orangegrab = false;
                isorange[0] = true;
                resource--;
            } else
            if (bluegrab == true && resource >= 2) {
                isocupied[0] = true;
                bluegrab = false;
                isblue[0] = true;
                resource -= 2;
            } else
            if (yellowgrab == true && resource >= 2) {
                isocupied[0] = true;
                yellowgrab = false;
                isyellow[0] = true;
                resource -= 2;
            } else
            if (purplegrab == true && resource >= 3) {
                isocupied[0] = true;
                purplegrab = false;
                ispurple[0] = true;
                resource -= 3;
            }
            else {
                orangegrab = false;
                bluegrab = false;
                yellowgrab = false;
                purplegrab = false;
            }
        } else
        if (mouseX >= 350 && mouseX <= 474 && mouseY >= 291 && mouseY <= 419 && isocupied[1] == false) {
           
            if (orangegrab == true && resource >= 1) {
                 isocupied[1] = true;
                orangegrab = false;
                isorange[1] = true;
                resource--;
            } else
            if (bluegrab == true && resource >=2) {
                isocupied[1] = true;
                bluegrab = false;
                isblue[1] = true;
                resource -= 2;
            } else
            if (yellowgrab == true && resource >= 2) {
                isocupied[1] = true;
                yellowgrab = false;
                isyellow[1] = true;
                resource -= 2;
            } else
            if (purplegrab == true && resource >=3) {
                isocupied[1] = true;
                purplegrab = false;
                ispurple[1] = true;
                resource -= 3;
            }
            else {
                orangegrab = false;
                bluegrab = false;
                yellowgrab = false;
                purplegrab = false;
            }
        } else
        if (mouseX >= 550 && mouseX <= 673 && mouseY >= 291 && mouseY <= 419 && isocupied[2] == false) {
          
            if (orangegrab == true && resource>=1) {
                  isocupied[2] = true;
                orangegrab = false;
                isorange[2] = true;
                resource--;
            } else
            if (bluegrab == true && resource >=2) {
                isocupied[2] = true;
                bluegrab = false;
                isblue[2] = true;
                resource -= 2;
            } else
            if (yellowgrab == true && resource >= 2) {
                isocupied[2] = true;
                yellowgrab = false;
                isyellow[2] = true;
                resource -= 2;
            } else
            if (purplegrab == true && resource >= 3) {
                isocupied[2] = true;
                purplegrab = false;
                ispurple[2] = true;
                resource -= 3;
            }
            else {
                orangegrab = false;
                bluegrab = false;
                yellowgrab = false;
                purplegrab = false;
            }
        }
        else
        if (mouseX >= 148 && mouseX <= 273 && mouseY >= 442 && mouseY <= 569 && isocupied[3] == false) {
           
            if (orangegrab == true && resource >= 1) {
                 isocupied[3] = true;
                orangegrab = false;
                isorange[3] = true;
                resource--;
            } else
            if (bluegrab == true && resource >=2) {
                isocupied[3] = true;
                bluegrab = false;
                isblue[3] = true;
                resource -= 2;
            } else
            if (yellowgrab == true && resource >= 2) {
                isocupied[3] = true;
                yellowgrab = false;
                isyellow[3] = true;
                resource -= 2;
            } else
            if (purplegrab == true && resource >=3) {
                isocupied[3] = true;
                purplegrab = false;
                ispurple[3] = true;
                resource -= 3;
            }
            else {
                orangegrab = false;
                bluegrab = false;
                yellowgrab = false;
                purplegrab = false;
            }
        } else
        if (mouseX >= 350 && mouseX <= 474 && mouseY >= 442 && mouseY <= 569 && isocupied[4] == false) {
           
            if (orangegrab == true && resource >=1) {
                isocupied[4] = true;
                orangegrab = false;
                isorange[4] = true;
                resource--;

            } else
            if (bluegrab == true && resource >=2) {
                isocupied[4] = true;
                bluegrab = false;
                isblue[4] = true;
                resource -= 2;
            } else
            if (yellowgrab == true && resource >=2) {
                isocupied[4] = true;
                yellowgrab = false;
                isyellow[4] = true;
                resource -= 2;
            } else
            if (purplegrab == true && resource >=3) {
                isocupied[4] = true;
                purplegrab = false;
                ispurple[4] = true;
                resource -= 3;
            }
            else {
                orangegrab = false;
                bluegrab = false;
                yellowgrab = false;
                purplegrab = false;
            }
        } else
        if (mouseX >= 550 && mouseX <= 673 && mouseY >= 442 && mouseY <= 569 && isocupied[5] == false) {
            
            if (orangegrab == true && resource >=1) {
               isocupied[5] = true;
                orangegrab = false;
                isorange[5] = true;
                resource--;

            } else
            if (bluegrab == true && resource >= 2) {
                isocupied[5] = true;
                bluegrab = false;
                isblue[5] = true;
                resource -= 2;
            } else
            if (yellowgrab == true && resource >=2) {
                isocupied[5] = true;
                yellowgrab = false;
                isyellow[5] = true;
                resource -= 2;
            } else
            if (purplegrab == true && resource >= 3) {
                isocupied[5] = true;
                purplegrab = false;
                ispurple[5] = true;
                resource -= 3;
            }
            else {
                orangegrab = false;
                bluegrab = false;
                yellowgrab = false;
                purplegrab = false;
            }
        }
        else
        if (mouseX >= 148 && mouseX <= 273 && mouseY >= 594 && mouseY <= 714 && isocupied[6] == false) {
            
            if (orangegrab == true && resource >= 1) {
               isocupied[6] = true;
                orangegrab = false;
                isorange[6] = true;
                resource--;

            }else
            if (bluegrab == true && resource >=2) {
                isocupied[6] = true;
                bluegrab = false;
                isblue[6] = true;
                resource -= 2;
            } else
            if (yellowgrab == true && resource >=2) {
                isocupied[6] = true;
                yellowgrab = false;
                isyellow[6] = true;
                resource -= 2;
            } else
            if (purplegrab == true && resource >= 3) {
                isocupied[6] = true;
                purplegrab = false;
                ispurple[6] = true;
                resource -= 3;
            }
            else {
                orangegrab = false;
                bluegrab = false;
                yellowgrab = false;
                purplegrab = false;
            }
        } else
        if (mouseX >= 350 && mouseX <= 474 && mouseY >= 594 && mouseY <= 714 && isocupied[7] == false) {
           
            if (orangegrab == true && resource >= 1) {
                isocupied[7] = true;
                orangegrab = false;
                isorange[7] = true;
                resource--;
            } else
            if (bluegrab == true && resource >=2) {
                isocupied[7] = true;
                bluegrab = false;
                isblue[7] = true;
                resource -= 2;
            } else
            if (yellowgrab == true && resource >= 2) {
                isocupied[7] = true;
                yellowgrab = false;
                isyellow[7] = true;
                resource -= 2;
            } else
            if (purplegrab == true && resource >=3) {
                isocupied[7] = true;
                purplegrab = false;
                ispurple[7] = true;
                resource -= 3;
            }
            else {
                orangegrab = false;
                bluegrab = false;
                yellowgrab = false;
                purplegrab = false;
            }
        } else
        if (mouseX >= 550 && mouseX <= 673 && mouseY >= 594 && mouseY <= 714 && isocupied[8] == false) {
            
            if (orangegrab == true && resource >=1) {
               isocupied[8] = true;
                orangegrab = false;
                isorange[8] = true;
                resource--;

            }else
            if (bluegrab == true && resource >= 2) {
                isocupied[8] = true;
                bluegrab = false;
                isblue[8] = true;
                resource -= 2;
            } else
            if (yellowgrab == true && resource >= 2) {
                isocupied[8] = true;
                yellowgrab = false;
                isyellow[8] = true;
                resource -= 2;
            } else
            if (purplegrab == true && resource >= 3) {
                isocupied[8] = true;
                purplegrab = false;
                ispurple[8] = true;
                resource -= 3;
            }
            else {
                orangegrab = false;
                bluegrab = false;
                yellowgrab = false;
                purplegrab = false;
            }
        }
        else {
            orangegrab = false;
            bluegrab = false;
            yellowgrab = false;
            purplegrab = false;
        }
        
    }
    

}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}
