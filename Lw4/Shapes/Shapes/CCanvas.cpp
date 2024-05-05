#include "ICanvas.h"
#include "CCanvas.h"
#include <sstream>
#include <cstdlib>

void HexToRGB(uint32_t color, unsigned int& r, unsigned int& g, unsigned int& b)
{
    r = (color >> 16) & 0xFF;
    g = (color >> 8) & 0xFF;
    b = color & 0xFF;
}

void CCanvas::DrawLine(CPoint startPoint, CPoint endPoint, uint32_t lineColor)
{
    unsigned int r, g, b;

    HexToRGB(lineColor, r, g, b);

    sf::Vertex vertex1(sf::Vector2f(startPoint.m_x, startPoint.m_y), sf::Color(r, g, b));
    sf::Vertex vertex2(sf::Vector2f(endPoint.m_x, endPoint.m_y), sf::Color(r, g, b));

    sf::VertexArray line(sf::Lines, 10);
    line[0] = vertex1;
    line[1] = vertex2;

    m_window->draw(line);
}

void CCanvas::FillPolygon(std::vector<CPoint> points, uint32_t lineColor, uint32_t fillColor)
{
    if (points.empty())
    {
        return;
    }

    unsigned int r, g, b;
    
    sf::ConvexShape polygon;

    polygon.setPointCount(points.size());

    // Задаем позиции вершин полигона на основе переданных точек
    for (size_t i = 0; i < points.size(); ++i)
    {
        polygon.setPoint(i, sf::Vector2f(points[i].m_x, points[i].m_y));
    }

    HexToRGB(fillColor, r, g, b);

    polygon.setFillColor(sf::Color(r, g, b));

    HexToRGB(lineColor, r, g, b);
    polygon.setOutlineColor(sf::Color(r, g, b));
    polygon.setOutlineThickness(2);

    m_window->draw(polygon);
}

void CCanvas::DrawCircle(CPoint center, double radius, uint32_t lineColor)
{
    unsigned int r, g, b;

    sf::CircleShape circle;

    circle.setRadius(static_cast<float>(radius));

    circle.setPosition(static_cast<float>(center.m_x - radius), static_cast<float>(center.m_y - radius));

    HexToRGB(lineColor, r, g, b);

    circle.setOutlineColor(sf::Color(r, g, b));
    circle.setOutlineThickness(2);

    circle.setFillColor(sf::Color::Transparent);

    m_window->draw(circle);
}

void CCanvas::FillCircle(CPoint center, double radius, uint32_t fillColor)
{
    unsigned int r, g, b;
    sf::CircleShape circle;

    circle.setRadius(static_cast<float>(radius));

    circle.setPosition(static_cast<float>(center.m_x - radius), static_cast<float>(center.m_y - radius));

    HexToRGB(fillColor, r, g, b);

    circle.setFillColor(sf::Color(r, g, b));
    circle.setOutlineColor(sf::Color::Transparent);

    m_window->draw(circle);
}