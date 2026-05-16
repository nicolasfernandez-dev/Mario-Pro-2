#ifndef FINDER_HH
#define FINDER_HH

#include <map>
#include <set>
#include "geometry.hh"

/**
 * @class Finder
 * @brief Classe genèrica per optimitzar la cerca d'objectes dins d'una àrea rectangular.
 * @tparam T Tipus d'objecte que ha d'implementar get_rect().
 */
template <typename T>
class Finder {
 private:
    std::map<std::pair<int, int>, const T*> objects_; ///< Mapatge de posicions a objectes.

 public:
    /**
     * @brief Constructor per defecte.
     */
    Finder() {}

    /**
     * @brief Afegeix un objecte al Finder.
     * @param t Punter a l'objecte a afegir.
     */
    void add(const T *t) {
        auto r = t->get_rect();
        objects_[{r.left, r.top}] = t;
    }

    /**
     * @brief Actualitza la posició d'un objecte al Finder.
     * @param t Punter a l'objecte a actualitzar.
     */
    void update(const T *t) {
        remove(t);
        add(t);
    }

    /**
     * @brief Elimina un objecte del Finder.
     * @param t Punter a l'objecte a eliminar.
     */
    void remove(const T *t) {
        auto r = t->get_rect();
        objects_.erase({r.left, r.top});
    }

    /**
     * @brief Retorna un conjunt d'objectes que es troben dins d'un rectangle donat.
     * @param rect Rectangle de cerca.
     * @return Conjunt de punters als objectes dins del rectangle.
     */
    std::set<const T *> query(pro2::Rect rect) const {
        std::set<const T *> result;
        for (const auto& [key, obj] : objects_) {
            auto r = obj->get_rect();
            if (!(r.right < rect.left or r.left > rect.right or r.bottom < rect.top or r.top > rect.bottom)) {
                result.insert(obj);
            }
        }
        return result;
    }
};

#endif