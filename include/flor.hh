#ifndef FLOR_HH
#define FLOR_HH

#include "window.hh"
#include <vector>

/**
 * @class Flor
 * @brief Representa la flor de gel del joc.
 */
class Flor {
public:
    /**
     * @brief Constructor de la classe Flor.
     * @param pos Posició inicial de la flor.
     */
    Flor(pro2::Pt pos);

    /**
     * @brief Dibuixa la flor a la finestra si no ha estat recollida
     * @param window Referencia a la ventana on es dibuixa.
     */
    void paint(pro2::Window& window) const;

    /**
     * @brief Retorne la posició de la flor.
     * @return Posició actual de la flor.
     */
    pro2::Pt pos() const;

    /**
     * @brief Indica si la flor ha estat recollida.
     * @return true si ha estat recollida, false en cas contrari.
     */
    bool is_recogida() const;

    /**
     * @brief Marca la flor com recollida.
     */
    void recoger();

    /**
     * @brief Sprite de la flor.
     */
    static const std::vector<std::vector<int>> flor_sprite_;

private:
    pro2::Pt pos_;      ///< Posició de la flor.
    bool recogida_ = false; ///< Indica si la flor ha estat recollida.
};

#endif