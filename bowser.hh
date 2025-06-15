#ifndef BOWSER_HH
#define BOWSER_HH

#include <vector>
#include "window.hh"
#include "utils.hh"
#include "geometry.hh"

/**
 * @struct Fireball
 * @brief Representa una bola de foc llançada per Bowser.
 */
struct Fireball {
    pro2::Pt pos; ///< Posició actual de la bola de foc.
    pro2::Pt speed; ///< Velocitat de la bola de foc.
    bool active = true; ///< Indica si la bola de foc està activa.
    int frame = 0; ///< Frame actual de l'animació.
    int base_y = 0; ///< Alçada base per al moviment sinusoidal.
    static const std::vector<std::vector<int>> fireball_sprite_; ///< Sprite de la bola de foc.

    /**
     * @brief Constructor de Fireball.
     * @param p Posició inicial.
     * @param s Velocitat inicial.
     */
    Fireball(pro2::Pt p, pro2::Pt s)
        : pos(p), speed(s), base_y(p.y) {}

    /**
     * @brief Actualitza la posició i animació de la bola de foc.
     */
    void update() {
        frame++;
        pos.x += speed.x;
        pos.y = base_y + int(10 * std::sin(frame / 8.0)) + speed.y;
    }

    /**
     * @brief Dibuixa la bola de foc a la finestra.
     * @param window Finestra on es dibuixa.
     */
    void paint(pro2::Window& window) const {
        if (active)
            paint_sprite(window, {pos.x-4, pos.y-4}, fireball_sprite_, false);
    }
};

/**
 * @class Bowser
 * @brief Representa el cap Bowser al joc.
 */
class Bowser {
private:
    pro2::Pt pos_; ///< Posició de Bowser.
    bool alive_ = true; ///< Indica si Bowser està viu.
    int frame_offset_ = 0; ///< Offset d'animació.
    int vidas_ = 3; ///< Vides actuals de Bowser.
    int vidas_max_ = 3; ///< Vides màximes de Bowser.
    std::vector<Fireball> fireballs_; ///< Bolas de foc actives.
    int fireball_cooldown_ = 0; ///< Cooldown per llançar boles de foc.
    static const std::vector<std::vector<int>> bowser_sprite_; ///< Sprite de Bowser viu.
    static const std::vector<std::vector<int>> bowser_dead; ///< Sprite de Bowser mort.

    int parpadeo_frames_ = 0; ///< Frames de parpelleig després de rebre dany.
    int parpadeos_totales_ = 0; ///< Total de parpelleigs realitzats.
    static constexpr int PARPADEOS_MAX_ = 8; ///< Màxim de frames de parpelleig.
    int frame_bowser_muerto_ = -1; ///< Frame en què Bowser ha mort.

public:
    /**
     * @brief Constructor de Bowser.
     * @param pos Posició inicial de Bowser.
     */
    Bowser(pro2::Pt pos);

    /**
     * @brief Dibuixa Bowser i la seva barra de vida a la finestra.
     * @param window Finestra on es dibuixa.
     */
    void paint(pro2::Window& window) const;

    /**
     * @brief Actualitza l'estat de Bowser i les seves boles de foc.
     * @param mario_pos Posició actual de Mario.
     */
    void update(const pro2::Pt& mario_pos);

    /**
     * @brief Llança una bola de foc cap a la posició de Mario.
     * @param mario_pos Posició de Mario.
     */
    void lanzar_bola(const pro2::Pt& mario_pos);

    /**
     * @brief Bowser rep dany i pot morir si es queda sense vides.
     * @param window Finestra per obtenir el frame actual.
     */
    void recibir_danio(pro2::Window& window);

    /**
     * @brief Retorna el nombre màxim de vides de Bowser.
     * @return Vides màximes.
     */
    int vidas_max() const;

    /**
     * @brief Retorna el nombre actual de vides de Bowser.
     * @return Vides actuals.
     */
    int vidas() const;

    /**
     * @brief Indica si Bowser està viu.
     * @return true si està viu, false si està mort.
     */
    bool is_alive() const;

    /**
     * @brief Retorna la posició actual de Bowser.
     * @return Posició de Bowser.
     */
    pro2::Pt pos() const;

    /**
     * @brief Retorna el rectangle que ocupa Bowser (per col·lisions).
     * @return Rectangle de Bowser.
     */
    pro2::Rect get_rect() const;

    /**
     * @brief Retorna el vector de boles de foc actives.
     * @return Referència al vector de boles de foc.
     */
    std::vector<Fireball>& fireballs();

    /**
     * @brief Mata Bowser instantàniament.
     */
    void kill();
};

#endif