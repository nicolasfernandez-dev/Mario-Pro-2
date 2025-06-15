#ifndef GOOMBA_HH
#define GOOMBA_HH

#include <iostream>
#include "window.hh"
#include "platform.hh"

/**
 * @class Goomba
 * @brief Representa un enemic Goomba que es mou sobre una plataforma.
 */
class Goomba{
private:
    int extrem_esquer_ = 0; ///< Extrem esquerre de la plataforma.
    int extrem_dret_ = 0;   ///< Extrem dret de la plataforma.
    pro2::Pt pos_;          ///< Posició del Goomba.
    int speed_ = 1;         ///< Velocitat del Goomba.
    bool looking_left_ = true; ///< Direcció en què mira el Goomba.
    static const std::vector<std::vector<int>> goomba_sprite_; ///< Sprite del Goomba.
    bool eliminat = false;  ///< Indica si el Goomba ha estat eliminat.

public:
    /**
     * @brief Constructor del Goomba.
     * @param pos Posició inicial del Goomba.
     */
    Goomba(pro2::Pt pos) : pos_(pos) {};

    /**
     * @brief Estableix els extrems de la plataforma sobre la qual es mou el Goomba.
     * @param esq Extrem esquerre.
     * @param dre Extrem dret.
     */
    void set_extrems(int esq, int dre) {
        extrem_esquer_ = esq;
        extrem_dret_ = dre;
    }

    /**
     * @brief Dibuixa el Goomba a la finestra.
     * @param window Finestra on es dibuixa.
     */
    void paint(pro2::Window& window) const;

    /**
     * @brief Retorna la posició del Goomba.
     * @return Posició actual del Goomba.
     */
    pro2::Pt pos() const { return pos_; }

    /**
     * @brief Actualitza l'animació del Goomba.
     * @param window Finestra per obtenir el frame actual.
     * @param platforms Vector de plataformes per al moviment.
     */
    void update_animation(const pro2::Window& window, const std::vector<Platform>& platforms);

    /**
     * @brief Mou el Goomba sobre la plataforma.
     * @param platforms Vector de plataformes.
     */
    void move(const std::vector<Platform>& platforms);

    /**
     * @brief Indica si el Goomba ha estat eliminat.
     * @return true si ha estat eliminat, false en cas contrari.
     */
    bool is_eliminat() const;

    /**
     * @brief Elimina el Goomba.
     */
    void eliminar();

    /**
     * @brief Retorna el rectangle que ocupa el Goomba (per col·lisions).
     * @return Rectangle del Goomba.
     */
    pro2::Rect get_rect() const {
        return {pos_.x - 6, pos_.y - 15, pos_.x + 6, pos_.y + 1};
    }
};

#endif





