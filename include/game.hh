#ifndef GAME_HH
#define GAME_HH

#include <vector>
#include "mario.hh"
#include "platform.hh"
#include "window.hh"
#include "moneda.hh"
#include "finder.hh"
#include "goomba.hh"
#include "key.hh"
#include "decor.hh"
#include "bloc.hh"
#include "planta.hh"
#include "door.hh"
#include "bowser.hh"
#include "peach.hh"
#include "flor.hh"

/**
 * @class Game
 * @brief Classe principal que gestiona l'estat i la lògica del joc.
 */
class Game {
    // --- Personatges i objectes principals ---
    Mario   mario_;                  ///< El jugador principal
    Planta  carnivora_;              ///< Planta carnívora animada
    Bloc    bloc_{pro2::Pt{300, 84}};      ///< Bloc per la clau
    Bloc    bloc_flor_{pro2::Pt{0, 0}};    ///< Bloc per la flor
    Door    puerta_{pro2::Pt{1125, 149}};  ///< Porta de sortida
    Bowser  bowser_{pro2::Pt{1300, 150-39}}; ///< Cap final Bowser
    Peach   peach_{pro2::Pt{1350, 150-32}};  ///< Princesa Peach

    // --- Estat de la clau i porta ---
    bool llave_animando_ = false;    ///< Si la clau està animant-se (apareixent)
    int  llave_anim_frame_ = 0;      ///< Frame actual de l'animació de la clau
    int  llave_anim_max_frames_ = 20;///< Durada màxima de l'animació de la clau
    int  llave_y_inicial_ = 100;     ///< Y inicial de la clau per animació
    int  llave_y_animada_ = 100;     ///< Y animat de la clau
    bool llave_oculta_ = true;       ///< Si la clau està oculta
    bool puerta_visible_ = false;    ///< Si la porta és visible
    bool esperando_transicion_puerta_ = false; ///< Esperant transició de porta

    // --- Estat del mapa i transicions ---
    bool en_nuevo_mapa_ = false;         ///< Si estem al segon mapa
    bool nuevo_mapa_inicializado_ = false; ///< Si el segon mapa ja s'ha inicialitzat
    int  frame_entrada_nuevo_mapa_ = -1; ///< Frame d'entrada al nou mapa

    // --- Estat de Peach i flor especial ---
    bool peach_rescatada_ = false;       ///< Si la princesa ha estat rescatada
    int  frame_peach_rescatada_ = -1;    ///< Frame en què s'ha rescatat Peach
    bool flor_visible_ = false;          ///< Si la flor especial és visible
    bool flor_recogida_ = false;         ///< Si la flor ha estat recollida
    bool flor_animando_ = false;         ///< Si la flor està animant-se
    int  flor_anim_frame_ = 0;           ///< Frame actual de l'animació de la flor
    const int flor_anim_max_frames_ = 20;///< Durada màxima de l'animació de la flor
    int  flor_y_inicial_ = 0;            ///< Y inicial de la flor per animació
    double flor_y_animada_ = 0;          ///< Y animat de la flor
    int  flor_base_y_ = 0;               ///< Y base de la flor
    pro2::Pt flor_pos_ = {1200, 170};    ///< Posició de la flor
    int  frame_flor_aparece_ = -1;       ///< Frame en què apareix la flor

    // --- Estat de transició de mapa ---
    bool transicion_nuevo_mapa_ = false; ///< Si estem en transició al nou mapa
    int  frame_transicion_ = -1;         ///< Frame de la transició

    // --- Vectors d'objectes del joc ---
    std::vector<Goomba>    goombas_;     ///< Enemics Goomba
    std::vector<Platform>  platforms_;   ///< Plataformes del mapa principal
    std::vector<Moneda>    monedas_;     ///< Monedes col·leccionables
    std::vector<Key>       keys_;        ///< Claus col·leccionables
    std::vector<Decor>     decoracions_; ///< Elements decoratius
    std::vector<Platform>  plataformas_nuevo_mapa_; ///< Plataformes del segon mapa
    std::vector<Iceball>   iceballs_;    ///< Bolas de gel llançades per Mario
    std::vector<pro2::Pt>  estrellas_;   ///< Estrelles de fons

    // --- Finders per optimitzar col·lisions i visibilitat ---
    Finder<Platform> platforms_finder_;      ///< Finder per plataformes
    Finder<Moneda>   monedas_finder_;        ///< Finder per monedes
    Finder<Goomba>   goombas_finder_;        ///< Finder per goombas
    Finder<Decor>    decoracions_finder_;    ///< Finder per decoracions

    // --- Estat general del joc ---
    bool finished_;                      ///< Indica si el joc ha acabat
    int  frame_mort = -1;                ///< Frame en què Mario ha mort
    int  monedas_recogidas_ = 0;         ///< Comptador de monedes recollides

    // --- Mètodes privats de gestió interna ---
    void process_keys(pro2::Window& window);      ///< Processa l'entrada de teclat
    void update_objects(pro2::Window& window);    ///< Actualitza tots els objectes del joc
    void update_camera(pro2::Window& window);     ///< Actualitza la càmera

public:
    /**
     * @brief Constructor del joc.
     * @param width Amplada de la finestra.
     * @param height Alçada de la finestra.
     */
    Game(int width, int height);

    /**
     * @brief Actualitza l'estat del joc (objectes, càmera, etc).
     * @param window Finestra del joc.
     */
    void update(pro2::Window& window);

    /**
     * @brief Pinta tot el joc a la finestra.
     * @param window Finestra del joc.
     */
    void paint(pro2::Window& window);

    /**
     * @brief Pinta el fons d'estrelles.
     * @param window Finestra del joc.
     */
    void paint_stars_background(pro2::Window& window) const;

    /**
     * @brief Indica si el joc ha acabat.
     * @return true si el joc ha acabat, false altrament.
     */
    bool is_finished() const {
        return finished_;
    }

private:
    static constexpr int sky_blue = 0x5c94fc; ///< Color de fons del cel
};

#endif