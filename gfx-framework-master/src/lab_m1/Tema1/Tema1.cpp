#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>
#include <math.h>

#include "lab_m1/Tema1/transform2D.h"

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

    logicSpace.x = 0;       // logic x
    logicSpace.y = 0;       // logic y
    logicSpace.width = 6;   // logic width
    logicSpace.height = 4;  // logic height

    float squareSide = 1;
    cornersSide = 0.5;
    posX = logicSpace.width / 2;
    posY = logicSpace.height / 2;
    middleScreenX = logicSpace.width / 2;
    middleScreenY = logicSpace.height / 2;
    contorLife = 1;
    score = 0;
    fireRate = 0.3;
    enemySpawnRate = 5;
    kills = 0;
    doubleSpeed = 5;

    positionxObstacle[0] = -4;
    positionyObstacle[0] = 4;
    positionxObstacle[1] = 5;
    positionyObstacle[1] = 3;
    positionxObstacle[2] = -2;
    positionyObstacle[2] = 8;
    positionxObstacle[3] = 9;
    positionyObstacle[3] = -3;
    positionxObstacle[4] = 3;
    positionyObstacle[4] = -5;
    positionxObstacle[5] = 10;
    positionyObstacle[5] = 1;
    positionxObstacle[6] = -4;
    positionyObstacle[6] = -4;
    positionxObstacle[7] = 10;
    positionyObstacle[7] = 9;
    positionxObstacle[8] = 2;
    positionyObstacle[8] = -3;
    positionxObstacle[9] = 4;
    positionyObstacle[9] = 1;
    positionxObstacle[10] = 9;
    positionyObstacle[10] = 5;
    positionxObstacle[11] = 3;
    positionyObstacle[11] = 8;
    positionxObstacle[12] = -5;
    positionyObstacle[12] = 8;
    positionxObstacle[13] = -5;
    positionyObstacle[13] = 0;
    positionxObstacle[14] = -1;
    positionyObstacle[14] = 4;
    positionxObstacle[15] = 6;
    positionyObstacle[15] = -2;

    for (int i = 0; i < 16; i++) {
        obstacle[i] = Obstacle({ positionxObstacle[i], positionyObstacle[i], 0 });
    }

    fired = false;

    AddMeshToList(CreateCircle("blackCircle", { 0, 0, 0 }, 60, 100, { 0, 0, 0 }, true));
    AddMeshToList(CreateCircle("yellowCircle", { 0, 0, 1 }, 56, 100, { 0.956, 0.858, 0.364 }, true));
    AddMeshToList(CreateCircle("blackCircle1", { 0, 0, 2 }, 60, 100, { 0, 0, 0 }, true));
    AddMeshToList(CreateCircle("yellowCircle1", { 0, 0, 3 }, 56, 100, { 0.956, 0.858, 0.364 }, true));
    AddMeshToList(CreateCircle("orangeCircle", { 0, 0, 3 }, 20, 100, { 0.925, 0.356, 0.094 }, true));
    AddMeshToList(CreateCircle("blackCircle2", { 0, 0, 1 }, 50, 100, { 0.113, 0.109, 0.105 }, true));
    AddMeshToList(CreateCircle("blackCircle3", { 0, 0, 8 }, 60, 100, { 0, 0, 0 }, true));
    AddMeshToList(CreateCircle("greenCircle", { 0, 0, 9 }, 60, 100, { 0.470, 0.827, 0.211 }, true));

    AddMeshToList(CreateRectangle("rec1", { 0, 0, 4 }, squareSide / 2, { 0, 0, 0 }, true));
    AddMeshToList(CreateRectangle("rec2", { 0, 0, 5 }, squareSide / 2, { 0.925, 0.356, 0.094 }, true));
    AddMeshToList(CreateRectangleMap("rectangleMap", { 0, 0, 0 }, 2, { 0.658824, 0.658824, 0.658824 }, true));
    AddMeshToList(CreateRectangle("cornersForMap", { 0, 0, 2 }, cornersSide, { 0.509, 0.870, 0.8 }, true));
    AddMeshToList(CreateRectangle("healthbar", { 0, 0, 12 }, cornersSide, { 1, 0, 0 }, true));


    AddMeshToList(CreateSquare("blackSquare", { 0, 0, 1 }, 2.5, { 0, 0, 0 }, true));
    AddMeshToList(CreateSquare("greenSquare", { 0, 0, 3 }, 2.5, { 0.470, 0.827, 0.211 }, true));
    AddMeshToList(CreateSquare("blackSquare1", { 0, 0, 5 }, 2.5, { 0, 0, 0 }, true));
    AddMeshToList(CreateSquare("greenSquare2", { 0, 0, 9 }, 2.5, { 0.470, 0.827, 0.211 }, true));
    AddMeshToList(CreateSquare("squareMap", { 0, 0, 0 }, 2, { 0.658824, 0.658824, 0.658824 }, true));

    AddMeshToList(CreateSquare("blackSquareMinimap", { 0, 0, 10 }, 2, { 0, 0, 0 }, true));
    AddMeshToList(CreateSquare("squareMinimap", { 0, 0, 11 }, 2, { 0.658824, 0.658824, 0.658824 }, true));
    AddMeshToList(CreateCircle("blackCircleMini", { 0, 0, 12 }, 60, 100, { 0, 0, 0 }, true));
    AddMeshToList(CreateCircle("yellowCircleMini", { 0, 0, 13 }, 56, 100, { 0.956, 0.858, 0.364 }, true));
    AddMeshToList(CreateRectangle("rec1Mini", { 0, 0, 14 }, squareSide / 2, { 0, 0, 0 }, true));
    AddMeshToList(CreateRectangle("rec2Mini", { 0, 0, 15 }, squareSide / 2, { 0.925, 0.356, 0.094 }, true));
    AddMeshToList(CreateSquare("greenSquareMini", { 0, 0, 3 }, 2.5, { 0.470, 0.827, 0.211 }, true));
}

void Tema1::EnemySpawn() {
        for (int i = 0; i < 5; i++) {
            positionxEnemy[i] = rand() % 15 + (1.8 * cornersSide - 2);
            positionyEnemy[i] = rand() % 9 + (2 * cornersSide - 1.5);
            enemyspeed[i] = rand() % 4 + 1;
            enemy.push_back(Enemy({ positionxEnemy[i], positionyEnemy[i], 0 }, 0, enemyspeed[i]));
        }
}

bool Tema1::CheckCollision(const float posX, const float posY, const glm::vec3& posEnemy, const float length, const float radius) // AABB - Circle collision
{ 
    glm::vec2 center(posX, posY);
    glm::vec2 aabb_half_extents(length / 2, length / 2);
    glm::vec2 aabb_center(
        posEnemy.x, posEnemy.y
    );
    glm::vec2 difference = center - aabb_center;
    glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
    glm::vec2 closest = aabb_center + clamped;
    difference = closest - center;
    return glm::length(difference) < radius;
}

bool Tema1::CheckCollisionMap(const float posX, const float posY, const float radius) {
    if (posX - radius < -2.2 * middleScreenX)
        return true;
    if (posX + radius > 4.21 * middleScreenX)
        return true;
    if (posY - radius < -3.78 * middleScreenY)
        return true;
    if (posY + radius > 5.8 * middleScreenY)
        return true;

    return false;
}

bool Tema1::CheckCollisionCircle(const float posX, const float posY, const float posX1, const float posY1, const float radius1, const float radius2)
{
    return (pow(posX - posX1, 2) + pow(posY - posY1, 2) <= pow(radius1 + radius2, 2));
}

glm::mat3 Tema1::VisualizationTransf2D(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
    float sx, sy, tx, ty;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    tx = viewSpace.x - sx * logicSpace.x;
    ty = viewSpace.y - sy * logicSpace.y;

    return glm::transpose(glm::mat3(
        sx, 0.0f, tx,
        0.0f, sy, ty,
        0.0f, 0.0f, 1.0f));
}

glm::mat3 Tema1::VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
    float sx, sy, tx, ty, smin;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    if (sx < sy)
        smin = sx;
    else
        smin = sy;
    tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
    ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;

    return glm::transpose(glm::mat3(
        smin, 0.0f, tx,
        0.0f, smin, ty,
        0.0f, 0.0f, 1.0f));
}

void Tema1::SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor, bool clear)
{
    glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    glEnable(GL_SCISSOR_TEST);
    glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
    GetSceneCamera()->Update();
}

Mesh* Tema1::CreateSquare(const std::string& name, glm::vec3 center, float length, glm::vec3 color, bool fill)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center + glm::vec3(-length / 2, -length / 2, 0),  color),
        VertexFormat(center + glm::vec3(-length / 2, length / 2, 0), color),
        VertexFormat(center + glm::vec3(length / 2, length / 2, 0), color),
        VertexFormat(center + glm::vec3(length / 2, -length / 2, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* Tema1::CreateRectangle(const std::string& name, glm::vec3 center, float length, glm::vec3 color, bool fill)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center + glm::vec3(-length / 2, -length, 0),  color),
        VertexFormat(center + glm::vec3(-length / 2, length, 0), color),
        VertexFormat(center + glm::vec3(length / 2, length, 0), color),
        VertexFormat(center + glm::vec3(length / 2, -length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* Tema1::CreateRectangleMap(const std::string& name, glm::vec3 center, float length, glm::vec3 color, bool fill)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center + glm::vec3(-length / 2, -length / 4, 0),  color),
        VertexFormat(center + glm::vec3(-length / 2, length / 4, 0), color),
        VertexFormat(center + glm::vec3(length / 2, length / 4, 0), color),
        VertexFormat(center + glm::vec3(length / 2, -length / 4, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* Tema1::CreateCircle(const std::string& name, glm::vec3 center, float length, int div, glm::vec3 color, bool fill)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center + glm::vec3(length, 0, 0),  color),
    };

    Mesh* circle = new Mesh(name);

    std::vector<unsigned int> indices = { 0 };
    float angularStep = 2 * glm::pi<float>() / div;

    for (int i = 1; i <= div; i++) {
        float angle = i * angularStep;
        glm::vec3 vertex = center + glm::vec3(length * cos(angle), length * sin(angle), 0);

        vertices.push_back(VertexFormat(vertex, color));
        indices.push_back(i);
    }

    if (!fill) {
        circle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        circle->SetDrawMode(GL_TRIANGLE_FAN);
    }

    circle->InitFromData(vertices, indices);
    return circle;
}

void Tema1::PlayerEnemyAngle() {

    for (int i = 0; i < enemy.size(); i++) {
        float getAngle = asin(sqrt(pow(enemy[i].posEnemy.x - posX, 2)) / (sqrt(pow(enemy[i].posEnemy.x - posX, 2) + pow(enemy[i].posEnemy.y - posY, 2))));

        if (enemy[i].posEnemy.x < posX && enemy[i].posEnemy.y < posY)
            getAngle = M_PI - getAngle;
        else {
            if (enemy[i].posEnemy.x > posX && enemy[i].posEnemy.y < posY)
                getAngle = getAngle + M_PI;
            else
                if (enemy[i].posEnemy.x > posX && enemy[i].posEnemy.y > posY) {
                    getAngle = 2 * M_PI - getAngle;
                }
        }

        rotateAngle1 = getAngle;

        enemy[i].enemyAngle = rotateAngle1;
    }
}

void Tema1::FrameStart()
{
    glClearColor(0, 0, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Tema1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->GetResolution();

    viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
    SetViewportArea(viewSpace, glm::vec3(0, 0, 0), true);

    visMatrix = glm::mat3(1);
    visMatrix *= VisualizationTransf2D(logicSpace, viewSpace);
    
    vis_matrix = glm::mat3(1);
    LogicSpace logic_space = LogicSpace(2, 2, 3, 3);
    ViewportSpace view_space = ViewportSpace(1135, 115, 280, 220);
    vis_matrix *= VisualizationTransf2D(logic_space, view_space);
    minimapX = logic_space.width / 2;
    minimapY = logic_space.height / 2;
    DrawMinimap(vis_matrix);
    
    fireRate += 0.5 * deltaTimeSeconds;
    enemySpawnRate += deltaTimeSeconds;

    if (enemySpawnRate >= 5) {
        EnemySpawn();
        enemySpawnRate = 0;
    }

    if (kills >= 5) {
        doubleSpeed -= deltaTimeSeconds;
        if (doubleSpeed <= 0) {
            doubleSpeed = 5;
            kills = 0;
        }
    }
  
    // create player
    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(posX, posY);
    modelMatrix *= transform2D::Rotate(rotateAngle);
    modelMatrix *= transform2D::Scale(0.0035, 0.0035);
    RenderMesh2D(meshes["blackCircle"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(posX, posY);
    modelMatrix *= transform2D::Rotate(rotateAngle);
    modelMatrix *= transform2D::Scale(0.0035, 0.0035);
    RenderMesh2D(meshes["yellowCircle"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(posX, posY);
    modelMatrix *= transform2D::Rotate(rotateAngle);
    modelMatrix *= transform2D::Translate(-0.10, 0.18);
    modelMatrix *= transform2D::Scale(0.0010, 0.0010);
    RenderMesh2D(meshes["blackCircle1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(posX, posY);
    modelMatrix *= transform2D::Rotate(rotateAngle);
    modelMatrix *= transform2D::Translate(-0.10, 0.18);
    modelMatrix *= transform2D::Scale(0.0009, 0.0009);
    RenderMesh2D(meshes["yellowCircle1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(posX, posY);
    modelMatrix *= transform2D::Rotate(rotateAngle);
    modelMatrix *= transform2D::Translate(0.10, 0.18);
    modelMatrix *= transform2D::Scale(0.0010, 0.0010);
    RenderMesh2D(meshes["blackCircle1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(posX, posY);
    modelMatrix *= transform2D::Rotate(rotateAngle);
    modelMatrix *= transform2D::Translate(0.10, 0.18);
    modelMatrix *= transform2D::Scale(0.0009, 0.0009);
    RenderMesh2D(meshes["yellowCircle1"], shaders["VertexColor"], modelMatrix);

    // create bullet
    if (fired == true) {
        for (int i = 0; i < bullets.size(); i++) {
            bullets[i].pos.x += bullets[i].speed * deltaTimeSeconds * cos(bullets[i].angle + M_PI / 2);
            bullets[i].pos.y += bullets[i].speed * deltaTimeSeconds * sin(bullets[i].angle + M_PI / 2);

            bool enemyHit = false;
            for (int j = 0; j < enemy.size(); j++) {
                if (CheckCollisionCircle(bullets[i].pos.x, bullets[i].pos.y, enemy[j].posEnemy.x, enemy[j].posEnemy.y, 0.5 * 0.1, 2.5 * 0.15)) {
                    enemyHit = true;
                    score = score + 10;
                    kills++;
                    cout << "Your score is : " << score << endl;
                    enemy.erase(enemy.begin() + j);
                    break;
                }
            }

            if (enemyHit == true) {
                bullets.erase(bullets.begin() + i);
                continue;
            }

            if (CheckCollisionMap(bullets[i].pos.x, bullets[i].pos.y, 0.5 * 0.10)) {
                bullets.erase(bullets.begin() + i);
                continue;
             }
         
            bool obstacleHit = false;
            for (int j = 0; j < 16; j++) {
                if (CheckCollision(bullets[i].pos.x, bullets[i].pos.y, obstacle[j].posObs, 2.5 * 0.75, 0.5 * 0.10)) {
                    obstacleHit = true;
                    bullets.erase(bullets.begin() + i);
                    break;
                }
            }

            if (obstacleHit == true)
                continue;

            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(bullets[i].pos.x, bullets[i].pos.y);
            modelMatrix *= transform2D::Rotate(bullets[i].angle);
            modelMatrix *= transform2D::Translate(0, 0.4);
            modelMatrix *= transform2D::Scale(0.10, 0.10);
            RenderMesh2D(meshes["rec1"], shaders["VertexColor"], modelMatrix);

            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(bullets[i].pos.x, bullets[i].pos.y);
            modelMatrix *= transform2D::Rotate(bullets[i].angle);
            modelMatrix *= transform2D::Translate(0, 0.4);
            modelMatrix *= transform2D::Scale(0.084, 0.084);
            RenderMesh2D(meshes["rec2"], shaders["VertexColor"], modelMatrix);

            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(bullets[i].pos.x, bullets[i].pos.y);
            modelMatrix *= transform2D::Rotate(bullets[i].angle);
            modelMatrix *= transform2D::Translate(0, 0.4);
            modelMatrix *= transform2D::Translate(0, 0.050);
            modelMatrix *= transform2D::Scale(0.00050, 0.00050);
            RenderMesh2D(meshes["blackCircle2"], shaders["VertexColor"], modelMatrix);

            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(bullets[i].pos.x, bullets[i].pos.y);
            modelMatrix *= transform2D::Rotate(bullets[i].angle);
            modelMatrix *= transform2D::Translate(0, 0.4);
            modelMatrix *= transform2D::Translate(0, 0.050);
            modelMatrix *= transform2D::Scale(0.00084, 0.00084);
            RenderMesh2D(meshes["orangeCircle"], shaders["VertexColor"], modelMatrix);
        }
    }

    //create map
    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(middleScreenX, middleScreenY);
    modelMatrix *= transform2D::Scale(10, 10);
    RenderMesh2D(meshes["squareMap"], shaders["VertexColor"], modelMatrix);

    // create obstacles
    for (int i = 0; i < 16; i++) {
         modelMatrix = visMatrix;
         modelMatrix *= transform2D::Translate(positionxObstacle[i], positionyObstacle[i]);
         modelMatrix *= transform2D::Scale(0.5, 0.5);
         RenderMesh2D(meshes["greenSquare"], shaders["VertexColor"], modelMatrix);

         modelMatrix = visMatrix;
         modelMatrix *= transform2D::Translate(positionxObstacle[i], positionyObstacle[i]);
         modelMatrix *= transform2D::Scale(0.5, 0.5);
         RenderMesh2D(meshes["greenSquare"], shaders["VertexColor"], modelMatrix);

         modelMatrix = visMatrix;
         modelMatrix *= transform2D::Translate(positionxObstacle[i], positionyObstacle[i]);
         modelMatrix *= transform2D::Scale(0.5, 0.5);
         RenderMesh2D(meshes["greenSquare"], shaders["VertexColor"], modelMatrix);

         modelMatrix = visMatrix;
         modelMatrix *= transform2D::Translate(positionxObstacle[i], positionyObstacle[i]);
         modelMatrix *= transform2D::Scale(0.5, 0.5);
         RenderMesh2D(meshes["greenSquare"], shaders["VertexColor"], modelMatrix);

         modelMatrix = visMatrix;
         modelMatrix *= transform2D::Translate(positionxObstacle[i], positionyObstacle[i]);
         modelMatrix *= transform2D::Scale(0.5, 0.5);
         RenderMesh2D(meshes["greenSquare"], shaders["VertexColor"], modelMatrix);

         modelMatrix = visMatrix;
         modelMatrix *= transform2D::Translate(positionxObstacle[i], positionyObstacle[i]);
         modelMatrix *= transform2D::Scale(0.5, 0.5);
         RenderMesh2D(meshes["greenSquare"], shaders["VertexColor"], modelMatrix);

         modelMatrix = visMatrix;
         modelMatrix *= transform2D::Translate(positionxObstacle[i], positionyObstacle[i]);
         modelMatrix *= transform2D::Scale(0.5, 0.5);
         RenderMesh2D(meshes["greenSquare"], shaders["VertexColor"], modelMatrix);

         modelMatrix = visMatrix;
         modelMatrix *= transform2D::Translate(positionxObstacle[i], positionyObstacle[i]);
         modelMatrix *= transform2D::Scale(0.5, 0.5);
         RenderMesh2D(meshes["greenSquare"], shaders["VertexColor"], modelMatrix);

         modelMatrix = visMatrix;
         modelMatrix *= transform2D::Translate(positionxObstacle[i], positionyObstacle[i]);
         modelMatrix *= transform2D::Scale(0.5, 0.5);
         RenderMesh2D(meshes["greenSquare"], shaders["VertexColor"], modelMatrix);

         modelMatrix = visMatrix;
         modelMatrix *= transform2D::Translate(positionxObstacle[i], positionyObstacle[i]);
         modelMatrix *= transform2D::Scale(0.5, 0.5);
         RenderMesh2D(meshes["greenSquare"], shaders["VertexColor"], modelMatrix);

         modelMatrix = visMatrix;
         modelMatrix *= transform2D::Translate(positionxObstacle[i], positionyObstacle[i]);
         modelMatrix *= transform2D::Scale(0.5, 0.5);
         RenderMesh2D(meshes["greenSquare"], shaders["VertexColor"], modelMatrix);

         modelMatrix = visMatrix;
         modelMatrix *= transform2D::Translate(positionxObstacle[i], positionyObstacle[i]);
         modelMatrix *= transform2D::Scale(0.5, 0.5);
         RenderMesh2D(meshes["greenSquare"], shaders["VertexColor"], modelMatrix);

         modelMatrix = visMatrix;
         modelMatrix *= transform2D::Translate(positionxObstacle[i], positionyObstacle[i]);
         modelMatrix *= transform2D::Scale(0.5, 0.5);
         RenderMesh2D(meshes["greenSquare"], shaders["VertexColor"], modelMatrix);

         modelMatrix = visMatrix;
         modelMatrix *= transform2D::Translate(positionxObstacle[i], positionyObstacle[i]);
         modelMatrix *= transform2D::Scale(0.5, 0.5);
         RenderMesh2D(meshes["greenSquare"], shaders["VertexColor"], modelMatrix);

         modelMatrix = visMatrix;
         modelMatrix *= transform2D::Translate(positionxObstacle[i], positionyObstacle[i]);
         modelMatrix *= transform2D::Scale(0.5, 0.5);
         RenderMesh2D(meshes["greenSquare"], shaders["VertexColor"], modelMatrix);

         modelMatrix = visMatrix;
         modelMatrix *= transform2D::Translate(positionxObstacle[i], positionyObstacle[i]);
         modelMatrix *= transform2D::Scale(0.5, 0.5);
         RenderMesh2D(meshes["greenSquare"], shaders["VertexColor"], modelMatrix);
    }
    // create enemy
    for (int i = 0; i < enemy.size(); i++) {
        PlayerEnemyAngle();
        if (enemy[i].enemyAngle != 0) {
            enemy[i].posEnemy.x += enemy[i].enemySpeed * deltaTimeSeconds * cos(enemy[i].enemyAngle - M_PI / 2);
            enemy[i].posEnemy.y += enemy[i].enemySpeed * deltaTimeSeconds * sin(enemy[i].enemyAngle - M_PI / 2);
        }

        if (CheckCollisionCircle(posX, posY, enemy[i].posEnemy.x, enemy[i].posEnemy.y, 60 * 0.0035, 2.5 * 0.10)) {
            enemy.erase(enemy.begin() + i);
            contorLife = contorLife - 0.25;
            score = score + 10;
            cout << "Your score is : " << score << endl;
            if (contorLife == 0) {
                window->Close();
                cout << "Game over.Your score is : " << score << endl;
            }
            continue;
        }

        if (CheckCollisionMap(enemy[i].posEnemy.x, enemy[i].posEnemy.y, 2.5 * 0.10)) {
            enemy.erase(enemy.begin() + i);
            continue;
        }

        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(enemy[i].posEnemy.x, enemy[i].posEnemy.y);
        modelMatrix *= transform2D::Rotate(enemy[i].enemyAngle);
        modelMatrix *= transform2D::Scale(0.15, 0.15);
        RenderMesh2D(meshes["blackSquare"], shaders["VertexColor"], modelMatrix);

        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(enemy[i].posEnemy.x, enemy[i].posEnemy.y);
        modelMatrix *= transform2D::Rotate(enemy[i].enemyAngle);
        modelMatrix *= transform2D::Scale(0.14, 0.14);
        RenderMesh2D(meshes["greenSquare"], shaders["VertexColor"], modelMatrix);

        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(enemy[i].posEnemy.x - 0.1, enemy[i].posEnemy.y + 0.05);
        modelMatrix *= transform2D::Rotate(enemy[i].enemyAngle);
        modelMatrix *= transform2D::Scale(0.03, 0.03);
        RenderMesh2D(meshes["blackSquare1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(enemy[i].posEnemy.x + 0.1, enemy[i].posEnemy.y + 0.05);
        modelMatrix *= transform2D::Rotate(enemy[i].enemyAngle);
        modelMatrix *= transform2D::Scale(0.03, 0.03);
        RenderMesh2D(meshes["blackSquare1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(enemy[i].posEnemy.x, enemy[i].posEnemy.y - 0.05);
        modelMatrix *= transform2D::Rotate(enemy[i].enemyAngle);
        modelMatrix *= transform2D::Scale(0.001, 0.001);
        RenderMesh2D(meshes["blackCircle3"], shaders["VertexColor"], modelMatrix);

        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(enemy[i].posEnemy.x - 0.1, enemy[i].posEnemy.y + 0.05);
        modelMatrix *= transform2D::Rotate(enemy[i].enemyAngle);
        modelMatrix *= transform2D::Scale(0.02, 0.02);
        RenderMesh2D(meshes["greenSquare2"], shaders["VertexColor"], modelMatrix);

        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(enemy[i].posEnemy.x + 0.1, enemy[i].posEnemy.y + 0.05);
        modelMatrix *= transform2D::Rotate(enemy[i].enemyAngle);
        modelMatrix *= transform2D::Scale(0.02, 0.02);
        RenderMesh2D(meshes["greenSquare2"], shaders["VertexColor"], modelMatrix);

        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(enemy[i].posEnemy.x, enemy[i].posEnemy.y - 0.05);
        modelMatrix *= transform2D::Rotate(enemy[i].enemyAngle);
        modelMatrix *= transform2D::Scale(0.0008, 0.0008);
        RenderMesh2D(meshes["greenCircle"], shaders["VertexColor"], modelMatrix);    
    }

    // create healthbar
    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(posX, posY + 0.35);
    modelMatrix *= transform2D::Scale(1, 0.15);
    if (contorLife != 0)
        modelMatrix *= transform2D::Scale(contorLife, 1);
    if (contorLife == 0)
        modelMatrix *= transform2D::Scale(0, 0);
    RenderMesh2D(meshes["healthbar"], shaders["VertexColor"], modelMatrix);
}

void Tema1::DrawMinimap(glm::mat3 modelMatrix) {
    //create minimap
    modelMatrix = vis_matrix;
    modelMatrix *= transform2D::Translate(minimapX, minimapY);
    modelMatrix *= transform2D::Scale(2, 1);
    RenderMesh2D(meshes["blackSquareMinimap"], shaders["VertexColor"], modelMatrix);

    modelMatrix = vis_matrix;
    modelMatrix *= transform2D::Translate(minimapX, minimapY);
    modelMatrix *= transform2D::Scale(1.9, 0.9);
    RenderMesh2D(meshes["squareMinimap"], shaders["VertexColor"], modelMatrix);

    // create miniplayer
    modelMatrix = vis_matrix;
    modelMatrix *= transform2D::Translate(minimapX, minimapY);
    modelMatrix *= transform2D::Rotate(rotateAngle);
    modelMatrix *= transform2D::Scale(0.0015, 0.0015);
    RenderMesh2D(meshes["blackCircleMini"], shaders["VertexColor"], modelMatrix);

    modelMatrix = vis_matrix;
    modelMatrix *= transform2D::Translate(minimapX, minimapY);
    modelMatrix *= transform2D::Rotate(rotateAngle);
    modelMatrix *= transform2D::Scale(0.0015, 0.0015);
    RenderMesh2D(meshes["yellowCircleMini"], shaders["VertexColor"], modelMatrix);

    // create minibullet
    for (int i = 0; i < minibullets.size(); i++) {
        modelMatrix = vis_matrix;
        modelMatrix *= transform2D::Translate(minibullets[i].posMini.x, minibullets[i].posMini.y);
        modelMatrix *= transform2D::Rotate(minibullets[i].angleMini);
        modelMatrix *= transform2D::Translate(0, 0.4);
        modelMatrix *= transform2D::Scale(0.10, 0.10);
        RenderMesh2D(meshes["rec1Mini"], shaders["VertexColor"], modelMatrix);

        modelMatrix = vis_matrix;
        modelMatrix *= transform2D::Translate(minibullets[i].posMini.x, minibullets[i].posMini.y);
        modelMatrix *= transform2D::Rotate(minibullets[i].angleMini);
        modelMatrix *= transform2D::Translate(0, 0.4);
        modelMatrix *= transform2D::Scale(0.084, 0.084);
        RenderMesh2D(meshes["rec2Mini"], shaders["VertexColor"], modelMatrix);
    }  
}

void Tema1::FrameEnd()
{
}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
    deltaTime += deltaTime;

    if (kills >= 5) {
        if (doubleSpeed > 0) {
            deltaTime += 2 * deltaTime;
        }
    }

    if (window->KeyHold(GLFW_KEY_A) && posX > -2.2 * middleScreenX){
        bool flag = 0;
        for (int i = 0; i < 16; i++) {
            if (CheckCollision(posX - deltaTime, posY, obstacle[i].posObs, 2.5 * 0.5, 60 * 0.0035)) {
                flag = 1;
            }
        }

        if (flag == 0) {
            posX -= deltaTime;
            logicSpace.x -= deltaTime;
            minimapX -= deltaTime;       
        }
    }

    if (window->KeyHold(GLFW_KEY_D) && posX < 4.21 * middleScreenX) {
        bool flag = 0;
        for (int i = 0; i < 16; i++) {
            if (CheckCollision(posX + deltaTime, posY, obstacle[i].posObs, 2.5 * 0.5, 60 * 0.0035)) {
                flag = 1;
            }
        }

        if (flag == 0) {
            posX += deltaTime;
            logicSpace.x += deltaTime;
            minimapX += deltaTime;
        }
    }

    if (window->KeyHold(GLFW_KEY_S) && posY > - 3.78 * middleScreenY) {
        bool flag = 0;
        for (int i = 0; i < 16; i++) {
            if (CheckCollision(posX, posY - deltaTime, obstacle[i].posObs, 2.5 * 0.5, 60 * 0.0035)) {
                flag = 1;
            }
        }

        if (flag == 0) {
            posY -= deltaTime;
            logicSpace.y -= deltaTime;
            minimapY -= deltaTime;
        }
    }

    if (window->KeyHold(GLFW_KEY_W) && posY < middleScreenY * 5.8) {
        bool flag = 0;
        for (int i = 0; i < 16; i++) {
            if (CheckCollision(posX, posY + deltaTime, obstacle[i].posObs, 2.5 * 0.5, 60 * 0.0035)) {
                flag = 1;
            }
        }

        if (flag == 0) {
            posY += deltaTime;
            logicSpace.y += deltaTime;
            minimapY += deltaTime;
        }
    }

    if (window->KeyHold(GLFW_KEY_X)) {
        logicSpace.x += deltaTime;
        logicSpace.y += deltaTime;
        logicSpace.height -= 2 * deltaTime;
        logicSpace.width -= 2 * deltaTime;

    }
    if (window->KeyHold(GLFW_KEY_Z)) {
        logicSpace.x -= deltaTime;
        logicSpace.y -= deltaTime;
        logicSpace.height += 2 * deltaTime;
        logicSpace.width += 2 * deltaTime;
    }
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    float getAngle = asin(sqrt(pow(mouseX - window->GetResolution().x / 2
        , 2)) / (sqrt(pow(mouseX - window->GetResolution().x / 2, 2) + pow((window->GetResolution().y - mouseY) - window->GetResolution().y / 2, 2))));

    if (mouseX < window->GetResolution().x / 2 && window->GetResolution().y - mouseY < window->GetResolution().y / 2)
        getAngle = M_PI - getAngle;
    else {
        if (mouseX > window->GetResolution().x / 2 && window->GetResolution().y - mouseY < window->GetResolution().y / 2)
            getAngle = getAngle + M_PI;
        else
            if (mouseX > window->GetResolution().x / 2 && window->GetResolution().y - mouseY > window->GetResolution().y / 2) {
                getAngle = 2 * M_PI - getAngle;

            }
    }

    rotateAngle = getAngle;
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        float getAngle = asin(sqrt(pow(mouseX - window->GetResolution().x / 2
            , 2)) / (sqrt(pow(mouseX - window->GetResolution().x / 2, 2) + pow((window->GetResolution().y - mouseY) - window->GetResolution().y / 2, 2))));

        if (mouseX < window->GetResolution().x / 2 && window->GetResolution().y - mouseY < window->GetResolution().y / 2)
            getAngle = M_PI - getAngle;
        else {
            if (mouseX > window->GetResolution().x / 2 && window->GetResolution().y - mouseY < window->GetResolution().y / 2)
                getAngle = getAngle + M_PI;
            else
                if (mouseX > window->GetResolution().x / 2 && window->GetResolution().y - mouseY > window->GetResolution().y / 2) {
                    getAngle = 2 * M_PI - getAngle;
                }
        }

        rotateAngle = getAngle;
    

        if (fireRate >= 0.3) {
            bullets.push_back(Bullet({ posX, posY, 0 }, rotateAngle, 2));
            minibullets.push_back(MiniBullet({ minimapX, minimapY, 0 }, rotateAngle, 2));
            fireRate = 0;
        }

        fired = true;
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}