/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** broadcast_command
*/
#include "../includes/server.h"
#include "../includes/ia.h"

static int compute_broadcast_direction(trn_t *sender, trn_t *receiver)
{
    int dx = (int)sender->pos.x - (int)receiver->pos.x;
    int dy = (int)sender->pos.y - (int)receiver->pos.y;
    int width = my_server()->params.width;
    int height = my_server()->params.height;
    int raw_dir = 0;
    int rotated;
    int rotated_index;

    // Calcule pour prendre en compte la map torique
    if (dx > width / 2)
        dx -= width;
    if (dx < -width / 2)
        dx += width;
    if (dy > height / 2)
        dy -= height;
    if (dy < -height / 2)
        dy += height;
    if (dx == 0 && dy == 0)
        return 0;
    // Détermine la direction relative brute (avant rotation)
    if (dy < 0 && dx == 0) // Le sender est au-dessus du receiver, sur la même colonne
        raw_dir = 1; // donc direction = Nord
    if (dy < 0 && dx > 0) // Le sender est au-dessus et à droite du receiver
        raw_dir = 2; // donc direction = Nord-Est
    if (dx > 0 && dy == 0) // Le sender est sur la même ligne mais à droite du receiver
        raw_dir = 3; // donc direction = Est
    if (dx > 0 && dy > 0) // Le sender est en bas et à droite du receiver
        raw_dir = 4; // donc direction = Sud-Est
    if (dy > 0 && dx == 0) // Le sender est en dessous du receiver, sur la même colonne
        raw_dir = 5; // donc direction = Sud
    if (dx < 0 && dy > 0) // Le sender est en dessous et à gauche du receiver
        raw_dir = 6; // donc direction = Sud-Ouest
    if (dx < 0 && dy == 0) // Le sender est sur la même ligne mais à gauche du receiver
        raw_dir = 7; // donc direction = Ouest
    if (dx < 0 && dy < 0) // Le sender est au-dessus et à gauche du receiver
        raw_dir = 8; // donc direction = Nord-Ouest

    // Rotation en fonction de la direction du receveur

    //TO DO:
    // On veut ajuster la direction brute du message (raw_dir) pour qu’elle soit
    // relative à la direction du receveur (receiver->pos.dir).
    //
    // Exemple : si le message arrive du nord (raw_dir = 1), mais que le receveur
    // regarde vers l’est (dir = 3), alors pour lui, le nord est à sa gauche, donc
    // la direction perçue sera différente.
    rotated_index = (raw_dir - 1 - (receiver->pos.dir - 1) * 2 + 8) % 8;
    rotated = rotated_index + 1;
    // Le calcul :
    // - (raw_dir - 1) pour passer de [1-8] à [0-7] (C'est pour l'utilisation du modulo plus simplement)
    // - (receiver->pos.dir - 1) * 2 : car chaque direction (N, E, S, W) décale
    //    l’angle de 90°, soit 2 crans dans le repère circulaire à 8 directions
    // - on fait la soustraction et on ajoute 8 pour éviter les valeurs négatives
    // - le modulo 8 permet de tourner dans le cercle
    return rotated;
}