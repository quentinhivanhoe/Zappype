/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** Network
*/

#ifndef NETWORK_HPP_
    #define NETWORK_HPP_
    #include <memory>
namespace Zappy 
{
    class GUI;
    class Network
    {
        private:
            std::shared_ptr<GUI> _gui;
            /*manque les attirubut du serv*/
        public:
            Network(/* args */);
            ~Network();
            inline void updateGUi() {};
            inline void init() {};
            inline void fetchData() {};
    };
}

#endif /* !NETWORK_HPP_ */
