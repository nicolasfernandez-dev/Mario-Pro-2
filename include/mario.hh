#ifndef MARIO_HH
#define MARIO_HH

#include <iostream>
#include <vector>
#include "platform.hh"
#include "window.hh"
#include "utils.hh"

/**
 * @struct Iceball
 * @brief Projectil de gel que pot llençar Mario amb la flor especial.
 */
struct Iceball {
    pro2::Pt pos;    ///< Posició actual de la bola de gel
    pro2::Pt speed;  ///< Velocitat de la bola de gel
    bool active = true; ///< Indica si la bola està activa
    int frame = 0;      ///< Comptador de frames per animació
    int base_y = 0;     ///< Y base per a l'animació sinusoidal
    static const std::vector<std::vector<int>> iceball_sprite_; ///< Sprite de la bola de gel

    Iceball(pro2::Pt p, pro2::Pt s)
        : pos(p), speed(s), base_y(p.y) {}

    void update() {
        frame++;
        pos.x += speed.x;
        pos.y = base_y + int(10 * std::sin(frame / 8.0)) + speed.y;
    }

    void paint(pro2::Window& window) const {
        if (active)
            paint_sprite(window, {pos.x-4, pos.y-4}, iceball_sprite_, false);
    }
};

/**
 * @class Mario
 * @brief Classe que representa el personatge principal, Mario.
 */
class Mario {
 private:
    pro2::Pt pos_, last_pos_;      ///< Posició actual i anterior de Mario
    pro2::Pt speed_ = {0, 0};      ///< Velocitat actual de Mario
    pro2::Pt accel_ = {0, 0};      ///< Acceleració temporal (per salt)
    int      accel_time_ = 0;      ///< Temps restant d'acceleració

    bool grounded_ = false;        ///< Indica si Mario està a terra
    bool looking_left_ = false;    ///< Indica si Mario mira a l'esquerra
    bool dead = false;             ///< Indica si Mario ha mort

    void apply_physics_();

 public:
    /**
     * @brief Constructor de Mario.
     * @param pos Posició inicial.
     */
    Mario(pro2::Pt pos) : pos_(pos), last_pos_(pos) {}

    /**
     * @brief Dibuixa Mario a la finestra.
     * @param window Finestra on es dibuixa.
     * @param dead_sprite Si true, es dibuixa Mario mort.
     * @param flor_recogida Si true, es dibuixa Mario amb el sprite de gel.
     */
    void paint(pro2::Window& window, bool dead_sprite = false, bool flor_recogida = false) const;

    /**
     * @brief Retorna la posició actual de Mario.
     */
    pro2::Pt pos() const { return pos_; }

    /**
     * @brief Retorna la darrera posició de Mario.
     */
    pro2::Pt last_pos() const { return last_pos_; }

    /**
     * @brief Estableix la coordenada Y de Mario.
     */
    void set_y(int y) { pos_.y = y; }

    /**
     * @brief Retorna si Mario està a terra.
     */
    bool is_grounded() const { return grounded_; }

    /**
     * @brief Estableix si Mario està a terra.
     */
    void set_grounded(bool grounded) {
        grounded_ = grounded;
        if (grounded_) {
            speed_.y = 0;
        }
    }

    /**
     * @brief Canvia l'estat de grounded.
     */
    void toggle_grounded() { set_grounded(!grounded_); }

    /**
     * @brief Fa saltar Mario si està a terra.
     */
    void jump();

    /**
     * @brief Fa rebotar Mario cap amunt (després de matar un enemic).
     */
    void bounce();

    /**
     * @brief Fa rebotar Mario cap avall (després de trencar un bloc).
     */
    void bounce_down();

    /**
     * @brief Retorna si Mario mira a l'esquerra.
     */
    bool is_looking_left() const { return looking_left_; }

    /**
     * @brief Actualitza l'estat de Mario: moviment, física i col·lisions amb plataformes.
     * @param window Finestra per llegir les tecles.
     * @param platforms Vector de plataformes per comprovar col·lisions.
     */
    void update(pro2::Window& window, const std::vector<Platform>& platforms);

    /**
     * @brief Mata Mario (estableix l'estat de mort).
     */
    void matar();

    /**
     * @brief Retorna si Mario està mort.
     */
    bool is_dead() const;

    /**
     * @brief Retorna la velocitat actual de Mario.
     */
    pro2::Pt speed() const { return speed_; }

 private:
    static const std::vector<std::vector<int>> mario_sprite_normal_; ///< Sprite normal de Mario
    static const std::vector<std::vector<int>> mario_sprite_dead_;   ///< Sprite de Mario mort
    static const std::vector<std::vector<int>> mario_sprite_hielo_;  ///< Sprite de Mario amb flor de gel
};

#endif