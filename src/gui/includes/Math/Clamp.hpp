/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Math clamper
*/

#ifndef clamp
    #define clamp

namespace Math
{
    class Clamp
    {
        public:

        /**
         * @brief Clamp function.
         * 
         * @param value 
         * @param min 
         * @param max 
         */
            static void function(float &value, float min, float max);
    };
} // namespace Math


#endif /* !clamp */
