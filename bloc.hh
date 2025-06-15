#ifndef BLOC_HH
#define BLOC_HH

#include <iostream>
#include <vector>
#include "window.hh"
#include "utils.hh"

/**
 * @class Bloc
 * @brief Representa un bloc de l'escenari.
 */
class Bloc {
    pro2::Pt pos_; ///< Posició del bloc.
    bool destruido_ = false; ///< Indica si el bloc ha estat destruït.
public:
    static const std::vector<std::vector<int>> bloc_sprite_; ///< Sprite del bloc.

    /**
     * @brief Constructor del bloc.
     * @param pos Posició inicial del bloc.
     */
    Bloc(pro2::Pt pos);

    /**
     * @brief Retorna la posició del bloc.
     * @return Posició actual.
     */
    pro2::Pt pos() const;

    /**
     * @brief Indica si el bloc ha estat destruït.
     * @return true si està destruït, false en cas contrari.
     */
    bool destruido() const;

    /**
     * @brief Marca el bloc com a destruït.
     */
    void destruir();

    /**
     * @brief Retorna el rectangle que ocupa el bloc (per col·lisions).
     * @return Rectangle del bloc.
     */
    pro2::Rect get_rect() const;

    /**
     * @brief Dibuixa el bloc a la finestra.
     * @param window Finestra on es dibuixa.
     */
    void paint(pro2::Window& window) const;
};

#endif