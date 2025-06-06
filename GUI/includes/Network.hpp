/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** Network
*/

#ifndef NETWORK_HPP_
    #define NETWORK_HPP_
    #include "GUI.hpp"
namespace Zappy 
{
    class Network
    {
    private:
        GUI *_gui;
        /*manque les attirubut du serv*/
    public:
        Network(/* args */);
        ~Network();
        void updateGUi();
        void init();
        void fetchData();
    };
}

#endif /* !NETWORK_HPP_ */
