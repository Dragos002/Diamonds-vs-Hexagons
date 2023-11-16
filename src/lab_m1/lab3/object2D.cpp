#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateRectangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float width,
    float height,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(width, 0, 0), color),
        VertexFormat(corner + glm::vec3(width, height, 0), color),
        VertexFormat(corner + glm::vec3(0, height, 0), color)
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices;

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
        indices = { 0, 1, 2, 3 };
    }
    else {
        indices = { 0, 1, 2, 0, 2, 3 };
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh* object2D::CreateRhombusWithRectangle(
    const std::string& name,
    glm::vec3 rhombusCenter,
    float rhombusSideLength,
    float rectangleWidth,
    float rectangleHeight,
    glm::vec3 colorRhombus,
    bool fill)
{
    float halfSide = rhombusSideLength / 2.0f;

    // Rhombus vertices
    std::vector<VertexFormat> rhombusVertices =
    {
        VertexFormat(rhombusCenter + glm::vec3(0, -halfSide, 0), colorRhombus),  // Bottom
        VertexFormat(rhombusCenter + glm::vec3(halfSide, 0, 0), colorRhombus),   // Right
        VertexFormat(rhombusCenter + glm::vec3(0, halfSide, 0), colorRhombus),   // Top
        VertexFormat(rhombusCenter + glm::vec3(-halfSide, 0, 0), colorRhombus)   // Left
    };

    // Calculate the starting position for the rectangle
    glm::vec3 rectangleStart = rhombusCenter + glm::vec3(0, -rectangleHeight / 2.0f, 0);

    // Rectangle vertices
    std::vector<VertexFormat> rectangleVertices =
    {
        VertexFormat(rectangleStart, colorRhombus),
        VertexFormat(rectangleStart + glm::vec3(rectangleWidth, 0, 0), colorRhombus),
        VertexFormat(rectangleStart + glm::vec3(rectangleWidth, rectangleHeight, 0), colorRhombus),
        VertexFormat(rectangleStart + glm::vec3(0, rectangleHeight, 0), colorRhombus)
    };

    Mesh* combinedShape = new Mesh(name);
    std::vector<unsigned int> indices;

    if (!fill) {
        combinedShape->SetDrawMode(GL_LINE_LOOP);
        indices = { 0, 1, 2, 3, 4, 5, 6, 7 };
    }
    else {
        indices = { 0, 1, 2, 0, 2, 3, 4, 5, 6, 4, 6, 7 };
    }

    // Combine the vertices and indices
    std::vector<VertexFormat> allVertices(rhombusVertices);
    allVertices.insert(allVertices.end(), rectangleVertices.begin(), rectangleVertices.end());

    combinedShape->InitFromData(allVertices, indices);
    return combinedShape;
}

Mesh* object2D::CreateHexagon(
    const std::string& name,
    glm::vec3 center,
    float sideLength,
    glm::vec3 color,
    bool fill)
{
    std::vector<VertexFormat> vertices;

    for (int i = 0; i < 6; ++i) {
        float angle = (M_PI / 3.0) * i;
        vertices.push_back(VertexFormat(
            center + glm::vec3(sideLength * cos(angle), sideLength * sin(angle), 0), color)
        );
    }

    Mesh* hexagon = new Mesh(name);
    std::vector<unsigned int> indices;

    if (!fill) {
        hexagon->SetDrawMode(GL_LINE_LOOP);
        for (unsigned int i = 0; i < 6; ++i) {
            indices.push_back(i);
        }
    }
    else {
        for (unsigned int i = 0; i < 4; ++i) {
            indices.push_back(0);
            indices.push_back(i + 1);
            indices.push_back(i + 2);
        }
    }

    hexagon->InitFromData(vertices, indices);
    return hexagon;
}

Mesh* object2D::CreateStar(
    const std::string& name,
    glm::vec3 center,
    float radius,
    glm::vec3 color,
    bool fill)
{
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    const int points = 5;
    const float angleIncrement = 2.0f * M_PI / points;
    float angle = -M_PI / 2; // Starting angle

    for (int i = 0; i < points * 2; ++i) {
        float currentRadius = (i % 2 == 0) ? radius : 0;
        float x = center.x + currentRadius * cos(angle);
        float y = center.y + currentRadius * sin(angle);

        vertices.push_back(VertexFormat(glm::vec3(x, y,center.z), color));
        angle += angleIncrement;

        indices.push_back(i);
    }

    // Close the shape
    indices.push_back(0);
    indices.push_back(1);

    Mesh* star = new Mesh(name);

    if (fill) {
        star->InitFromData(vertices, indices);
        star->SetDrawMode(GL_TRIANGLE_STRIP);
    }
    else {
        star->InitFromData(vertices, indices);
        star->SetDrawMode(GL_LINE_LOOP);
    }

    return star;
}



