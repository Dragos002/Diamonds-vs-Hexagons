#pragma once

#include "components/simple_scene.h"
#include <vector>

namespace m1
{
    class Enemy {
    public:
        int hp = 3;
        float x, y, scale = 1;
        int color;
        float xtranslate = x;
        bool hit = false;
        bool isrendered = false;
    };
    class Resource {
    public:
        float xs, ys;
        bool isclicked = false;
    };
    class Bullet {
    public:
        float sx, sy;
        float sxtranslate = sx;
    };
   


    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        void CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices);


    protected:
        glm::mat3 modelMatrix;
        int gamematrix[9];
        int gamematrixy[9];
        float x, y,sx,sy,x2,x3,sx2,sx3;
        float angle[9], timer, timerS;
        bool scaleCompleted;
        bool orangegrab, isorange[9];
        bool bluegrab, isblue[9];
        bool yellowgrab, isyellow[9];
        bool purplegrab, ispurple[9];
        float xmouse, ymouse, mxmouse, mymouse;
        bool isocupied[9];
        float cx[9], cy[9];
        float l;
        float rendertime, rendertimeS;
        bool isremoved[9];
        float scaleremove[9];
        float starx[9];
        float hpscale[3];
        Enemy* hexagon;
        std::vector<Enemy> hexagons;
        Resource* starcollect;
        Resource* starcollect2;
        Resource* starcollect3;
        std::vector<Resource> resources;
        std::vector<Bullet> bullets;
        int hp = 3;
        float starrendertime, resourcetimer;
        float xstar = 965;
        int resource = 0;
        bool ishit[9];
        int meshrender[9];
        int meshrender2[9];
        int meshrender3[9];
        int meshrender4[9];

    };
    
}   // namespace m1
