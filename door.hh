#ifndef DOOR_HH
#define DOOR_HH

#include "window.hh"
#include <vector>

/**
 * @class Door
 * @brief Representa una porta al joc, que pot estar oberta o tancada.
 */
class Door {
private:
    pro2::Pt pos_; ///< Posició de la porta.
    bool abierta_ = false; ///< Indica si la porta està oberta.
    static const std::vector<std::vector<int>> door_sprite_; ///< Sprite de la porta tancada.
    static const std::vector<std::vector<int>> door_sprite_open_; ///< Sprite de la porta oberta.

public:
    /**
     * @brief Constructor de la classe Door.
     * @param pos Posició inicial de la porta.
     */
    Door(pro2::Pt pos);

    /**
     * @brief Obre la porta.
     */
    void abrir();

    /**
     * @brief Tanca la porta.
     */
    void cerrar();

    /**
     * @brief Indica si la porta està oberta.
     * @return true si la porta està oberta, false altrament.
     */
    bool is_abierta() const;

    /**
     * @brief Retorna la posició de la porta.
     * @return Posició actual de la porta.
     */
    pro2::Pt get_pos() const;

    /**
     * @brief Retorna el rectangle que ocupa la porta (per col·lisions).
     * @return Rectangle de la porta.
     */
    pro2::Rect get_rect() const;

    /**
     * @brief Dibuixa la porta a la finestra.
     * @param window Referència a la finestra on es dibuixa.
     */
    void paint(pro2::Window& window) const;
};

#endif