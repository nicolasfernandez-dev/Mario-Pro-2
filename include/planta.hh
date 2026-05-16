#ifndef PLANTA_HH
#define PLANTA_HH

#include <vector>
#include "window.hh"

/**
 * @class Planta
 * @brief Representa una planta carnívora animada al joc.
 */
class Planta{
public:
    /**
     * @brief Constructor de la classe Planta.
     * @param pos Posició inicial de la planta.
     * @param base_y Alçada base de la planta.
     * @param recorregut Recorregut vertical de l'animació.
     */
    Planta(pro2::Pt pos, int base_y, int recorregut);

    /**
     * @brief Actualitza l'animació de la planta.
     * @param window Finestra per obtenir el frame actual.
     */
    void update_animation(const pro2::Window& window);

    /**
     * @brief Dibuixa la planta a la finestra.
     * @param window Finestra on es dibuixa.
     */
    void paint(pro2::Window& window) const;

    /**
     * @brief Retorna el rectangle que ocupa la planta (per col·lisions).
     * @return Rectangle de la planta.
     */
    pro2::Rect get_rect() const;

private:
    pro2::Pt pos_; ///< Posició de la planta.
    int base_y_; ///< Alçada base de la planta.
    int recorregut_; ///< Recorregut vertical de l'animació.
    int frame_offset_; ///< Desfase d'animació.
    static const std::vector<std::vector<int>> planta_carnivora_sprite_; ///< Sprite de la planta.
};

#endif