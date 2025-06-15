#ifndef KEY_HH
#define KEY_HH

#include<iostream>
#include "window.hh"

/**
 * @class Key
 * @brief Representa una clau col·leccionable al joc.
 */
class Key{
private:
    pro2::Pt pos; ///< Posició de la clau.
    int base_y; ///< Alçada base per a l'animació.
    bool recogida_ = false; ///< Indica si la clau ha estat recollida.

public:
    static const std::vector<std::vector<int>> key_sprite_; ///< Sprite de la clau.
    static const std::vector<std::vector<int>> key_sprite_black_; ///< Sprite alternatiu de la clau.

    /**
     * @brief Constructor de la clau.
     * @param pos Posició inicial de la clau.
     */
    Key(pro2::Pt pos) : pos(pos), base_y(pos.y) {};

    /**
     * @brief Dibuixa la clau a la finestra.
     * @param window Finestra on es dibuixa.
     */
    void paint(pro2::Window& window) const;

    /**
     * @brief Retorna la posició de la clau.
     * @return Posició actual de la clau.
     */
    pro2::Pt get_pos() const { return pos; }

    /**
     * @brief Indica si la clau ha estat recollida.
     * @return true si ha estat recollida, false en cas contrari.
     */
    bool is_recogida() const;

    /**
     * @brief Marca la clau com a recollida.
     */
    void recoger();

    /**
     * @brief Retorna el rectangle que ocupa la clau (per col·lisions).
     * @return Rectangle de la clau.
     */
    pro2::Rect get_rect() const {
        return {pos.x - 6, pos.y - 15, pos.x + 6, pos.y + 1};
    }

    /**
     * @brief Estableix la posició de la clau.
     * @param pos Nova posició.
     */
    void set_pos(const pro2::Pt& pos);

    /**
     * @brief Actualitza l'animació de la clau.
     * @param window Finestra per obtenir el frame actual.
     */
    void update_animation(const pro2::Window& window);
};

#endif