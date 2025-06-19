/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** clamp class
*/

#include "../../includes/Math/Clamp.hpp"

void Math::Clamp::function(float *value, float min, float max)
{
    if (*value < min)
        *value = min;
    if (*value > max)
        *value = max;
}
