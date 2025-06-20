/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Trantor buttons
*/

#ifndef TRANTOR_BUTTON_H
    #define TRANTOR_BUTTON_H
    #include <memory>
    #include "Trantor.hpp"
    #include "Buttons.hpp"
    #include "GUI.hpp"

namespace Zappy
{
    class Trantorian;
    class GUI;
    class TrantorButtons : public Buttons
    {
        private:
            std::shared_ptr<Trantorian> _targetTrantorian = nullptr;
            GUI *_gui = nullptr;
        public:
            TrantorButtons(GUI *gui = nullptr, std::shared_ptr<Trantorian> trantorian = nullptr);
            inline ~TrantorButtons() = default;
            inline std::shared_ptr<Trantorian> operator()() { return this->_targetTrantorian; };
            inline std::shared_ptr<Trantorian> function() { return this->_targetTrantorian; };
            void update(MouseStatus mouse);
    };
} // namespace Zappy

#endif /* !TRANTOR_BUTTON_H */
