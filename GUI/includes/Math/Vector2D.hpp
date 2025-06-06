/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** Vector2D
*/

#ifndef VECTOR2D_HPP_
    #define VECTOR2D_HPP_
class Vector2D
{
private:
    double x;
    double y;
public:
    Vector2D(double x = 0.0, double y = 0.0);
    ~Vector2D();
    double getX() const {return this->x;};
    double getY() const {return this->y;};
    void setX(double x) {this->x = x;};
    void setY(double y) {this->y = y;};
};
#endif /* !VECTOR2D_HPP_ */
