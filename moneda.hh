#ifndef MONEDA_HH
#define MONEDA_HH

#include <iostream>
#include "window.hh"

/**
 * @class Moneda
 * @brief Representa una moneda col·leccionable al joc.
 */
class Moneda{
 private:
    bool recogida_ = false; ///< Indica si la moneda ha estat recollida.
    pro2::Pt pos_; ///< Posició de la moneda.
    static const std::vector<std::vector<std::vector<int>>> moneda_sprites_; ///< Sprites de la moneda.
    int current_sprite_ = 0; ///< Índex de l'sprite actual per a l'animació.

 public:
    /**
     * @brief Constructor de la moneda.
     * @param pos Posició inicial de la moneda.
     */
    Moneda(pro2::Pt pos) : pos_(pos) {};

    /**
     * @brief Dibuixa la moneda a la finestra.
     * @param window Finestra on es dibuixa.
     */
    void paint(pro2::Window& window) const;

    /**
     * @brief Retorna la posició de la moneda.
     * @return Posició actual de la moneda.
     */
    pro2::Pt pos() const { return pos_; }

    /**
     * @brief Indica si la moneda ha estat recollida.
     * @return true si ha estat recollida, false en cas contrari.
     */
    bool is_recogida() const;

    /**
     * @brief Marca la moneda com a recollida.
     */
    void recoger();

    /**
     * @brief Actualitza l'animació de la moneda.
     * @param window Finestra per obtenir el frame actual.
     */
    void update_animation(const pro2::Window& window);

    /**
     * @brief Retorna el rectangle que ocupa la moneda (per col·lisions).
     * @return Rectangle de la moneda.
     */
    pro2::Rect get_rect() const {
        return {pos_.x - 6, pos_.y - 15, pos_.x + 6, pos_.y + 1};
    }
};

#endif