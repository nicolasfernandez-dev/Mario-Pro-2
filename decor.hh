#ifndef DECOR_HH
#define DECOR_HH

#include <iostream>
#include <vector>
#include "window.hh"

/**
 * @class Decor
 * @brief Representa un element decoratiu de l'escenari, com núvols, pedres o canonades.
 */
class Decor {
public:
    /**
     * @brief Constructor de la classe Decor.
     * @param pos Posició on es dibuixa el decorat.
     * @param sprite Referència al sprite que representa el decorat.
     */
    Decor(pro2::Pt pos, const std::vector<std::vector<int>>& sprite);

    /**
     * @brief Dibuixa el decorat a la finestra.
     * @param window Referència a la finestra on es dibuixa.
     */
    void paint(pro2::Window& window) const;

    /**
     * @brief Retorna el rectangle que ocupa el decorat (per col·lisions o posicionament).
     * @return Rectangle que ocupa el decorat.
     */
    pro2::Rect get_rect() const;

    /**
     * @brief Indica si el decorat és una canonada.
     * @return true si és una canonada, false en cas contrari.
     */
    bool es_tuberia() const;

    /**
     * @brief Sprite dels núvols.
     */
    static const std::vector<std::vector<int>> nubes_;

    /**
     * @brief Sprite de les pedres.
     */
    static const std::vector<std::vector<int>> piedras_;

    /**
     * @brief Sprite de la canonada.
     */
    static const std::vector<std::vector<int>> tuberia_;

private:
    pro2::Pt pos_; ///< Posició del decorat.
    const std::vector<std::vector<int>>& sprite_; ///< Referència al sprite del decorat.
};

#endif