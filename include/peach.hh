#ifndef PEACH_HH
#define PEACH_HH

#include "window.hh"
#include "utils.hh"
#include <vector>

/**
 * @class Peach
 * @brief Representa la princesa Peach al joc.
 */
class Peach {
public:
    /**
     * @enum Estado
     * @brief Estats possibles de Peach.
     */
    enum Estado { LLORANDO, FELIZ, OCULTA };

private:
    pro2::Pt pos_; ///< Posició de Peach.
    Estado estado_ = LLORANDO; ///< Estat actual de Peach.
    static const std::vector<std::vector<int>> peach_llorando_sprite_; ///< Sprite de Peach plorant.
    static const std::vector<std::vector<int>> peach_feliz_sprite_;    ///< Sprite de Peach feliç.

public:
    /**
     * @brief Constructor de Peach.
     * @param pos Posició inicial de Peach.
     */
    Peach(pro2::Pt pos);

    /**
     * @brief Canvia l'estat de Peach.
     * @param e Nou estat.
     */
    void set_estado(Estado e);

    /**
     * @brief Retorna l'estat actual de Peach.
     * @return Estat actual.
     */
    Estado estado() const;

    /**
     * @brief Retorna la posició de Peach.
     * @return Posició actual.
     */
    pro2::Pt pos() const;

    /**
     * @brief Dibuixa Peach a la finestra.
     * @param window Finestra on es dibuixa.
     */
    void paint(pro2::Window& window) const;
};

#endif