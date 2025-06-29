#pragma once

#include "components/simple_scene.h"

namespace m1
{
    class MiniBullet {
    public:
        glm::vec3 posMini;
        float angleMini;
        float speedMini;

    public:MiniBullet(const glm::vec3& posMini, const float angleMini, const float speedMini) {
        this->posMini = posMini;
        this->angleMini = angleMini;
        this->speedMini = speedMini;
    }
          MiniBullet() {

          };
    };

    class Bullet {
    public:
        glm::vec3 pos;
        float angle;
        float speed;

    public:Bullet(const glm::vec3& pos, const float angle, const float speed) {
        this->pos = pos;
        this->angle = angle;
        this->speed = speed;
    }
          Bullet() {

          };
    };

    class MiniObstacle {
    public:
        glm::vec3 posObsMini;

    public:MiniObstacle(const glm::vec3& posObsMini) {
        this->posObsMini = posObsMini;
    }
          MiniObstacle() {

          };
    };

    class Obstacle {
    public:
        glm::vec3 posObs;

    public:Obstacle(const glm::vec3& posObs) {
        this->posObs = posObs;
    }
          Obstacle() {

          };
    };

    class Enemy {
    public:
        glm::vec3 posEnemy;
        float enemyAngle;
        float enemySpeed;
    
    public:Enemy(const glm::vec3& posEnemy, const float enemyAngle, const float enemySpeed) {
            this->posEnemy = posEnemy;
            this->enemyAngle = enemyAngle;
            this->enemySpeed = enemySpeed;
    }
          Enemy() {

          };
    };


    class Tema1 : public gfxc::SimpleScene
    {
     public:
         struct ViewportSpace
         {
             ViewportSpace() : x(0), y(0), width(1), height(1) {}
             ViewportSpace(int x, int y, int width, int height)
                 : x(x), y(y), width(width), height(height) {}
             int x;
             int y;
             int width;
             int height;
         };

         struct LogicSpace
         {
             LogicSpace() : x(0), y(0), width(1), height(1) {}
             LogicSpace(float x, float y, float width, float height)
                 : x(x), y(y), width(width), height(height) {}
             float x;
             float y;
             float width;
             float height;
         };

         Tema1();
        ~Tema1();

        void Init() override;

     private:
        Mesh *CreateSquare(const std::string& name, glm::vec3 center, float length, glm::vec3 color, bool fill);
        Mesh* CreateCircle(const std::string& name, glm::vec3 center, float length, int div, glm::vec3 color, bool fill);
        Mesh* CreateRectangle(const std::string& name, glm::vec3 center, float length, glm::vec3 color, bool fill);
        Mesh* CreateRectangleMap(const std::string& name, glm::vec3 center, float length, glm::vec3 color, bool fill);
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
        void PlayerEnemyAngle();
        bool CheckCollision(const float posX, const float posY, const glm::vec3& posEnemy, const float length, const float radius);
        bool CheckCollisionCircle(const float posX, const float posY, const float posX1, const float posY1, const float radius1, const float radius2);
        bool CheckCollisionMap(const float posX, const float posY, const float radius);
        void EnemySpawn();
        void DrawMinimap(glm::mat3 modelMatrix);
        void Health();
 
        glm::mat3 VisualizationTransf2D(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);
        glm::mat3 VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);
        void SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor = glm::vec3(0), bool clear = true);

     protected:
        glm::mat3 modelMatrix;
        float angularStep;
        float posX, posY, posX1, posY1, posX2, posY2;
        float rotateAngle;
        float angle;
        bool fired;
        std::vector<Bullet> bullets;
        std::vector<MiniBullet> minibullets;
        ViewportSpace viewSpace;
        LogicSpace logicSpace;
        glm::mat3 visMatrix;
        float middleScreenX, middleScreenY;
        int n;
        Obstacle obstacle[100];
        float positionxObstacle[100];
        float positionyObstacle[100];
        float positionxMiniObstacle[100];
        float positionyMiniObstacle[100];
        std::vector<Enemy> enemy;
        float positionxEnemy[100];
        float positionyEnemy[100];
        float enemyspeed[100];
        float rotateAngle1;
        float cornersSide;
        float contorLife;
        float score;
        float fireRate;
        float enemySpawnRate;
        glm::mat3 vis_matrix;
        float minimapX, minimapY;
        float kills;
        float doubleSpeed;
        int contorKills;
    };
} 
