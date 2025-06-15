#include "game.hh"
#include "utils.hh"
#include "mario.hh"
using namespace pro2;

// SPRITES GLOBALS
const int r = pro2::red;  //vermell
const int w = pro2::white; //blanc
const int _ = -1; //espai en blanc
const std::vector<std::vector<int>> game_over_sprite = {
        {_, _, r, r, r, r, r, _, _, _, r, r, r, _, _, _, r, r, _, _, _, r, r, _, r, r, r, r, r, r, r},
        {_, r, r, _, _, _, _, _, _, r, r, _, r, r, _, _, r, r, r, _, r, r, r, _, r, r, _, _, _, _, _},
        {r, r, _, _, _, _, _, _, r, r, _, _, _, r, r, _, r, r, r, r, r, r, r, _, r, r, _, _, _, _, _},
        {r, r, _, _, r, r, r, _, r, r, _, _, _, r, r, _, r, r, r, r, r, r, r, _, r, r, r, r, r, _, _},
        {r, r, _, _, _, r, r, _, r, r, r, r, r, r, r, _, r, r, _, r, _, r, r, _, r, r, _, _, _, _, _},
        {_, r, r, _, _, r, r, _, r, r, _, _, _, r, r, _, r, r, _, _, _, r, r, _, r, r, _, _, _, _, _},
        {_, _, r, r, r, r, r, _, r, r, _, _, _, r, r, _, r, r, _, _, _, r, r, _, r, r, r, r, r, r, r},
        
        {_, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
        {_, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
        
        {_, r, r, r, r, r, _, _, r, r, _, _, _, r, r, _, r, r, r, r, r, r, r, _, r, r, r, r, r, r, _},
        {r, r, _, _, _, r, r, _, r, r, _, _, _, r, r, _, r, r, _, _, _, _, _, _, r, r, _, _, _, r, r},
        {r, r, _, _, _, r, r, _, r, r, _, _, _, r, r, _, r, r, _, _, _, _, _, _, r, r, _, _, _, r, r},
        {r, r, _, _, _, r, r, _, r, r, r, _, r, r, r, _, r, r, r, r, r, _, _, _, r, r, _, _, r, r, r},
        {r, r, _, _, _, r, r, _, _, r, r, r, r, r, _, _, r, r, _, _, _, _, _, _, r, r, r, r, r, _, _},
        {r, r, _, _, _, r, r, _, _, _, r, r, r, _, _, _, r, r, _, _, _, _, _, _, r, r, _, r, r, r, _},
        {_, r, r, r ,r, r, _, _, _, _, _, r, _, _, _, _, r, r, r, r, r, r, r, _, r, r, _, _, r, r, r},
    };

const std::vector<std::vector<int>> loading_sprite = {
    {w, w, _, _, _, _, w, w, w, w, _, _, _, _, w, w, w, _, _, _, w, w, w, _, _, _, w, w, _, w, w, _, _, _, w, w, _, _, _, w, w, w, w, w},
    {w, w, _, _, _, w, w, _, _, w, w, _, _, w, w, _, w, w, _, _, w, _, _, w, _, _, w, w, _, w, w, w, _, _, w, w, _, _, w, w,},
    {w, w, _, _, _, w, w, _, _, w, w, _, w, w, _, _, _, w, w, _, w, _, _, _, w, _, _, _, _, w, w, w, w, _, w, w, _, w, w},
    {w, w, _, _, _, w, w, _, _, w, w, _, w, w, _, _, _, w, w, _, w, _, _, _, w, _, w, w, _, w, w, w, w, _, w, w, _, w, w, _, _, w, w, w},
    {w, w, _, _, _, w, w, _, _, w, w, _, w, w, w, w, w, w, w, _, w, _, _, _, w, _, w, w, _, w, w, _, w, w, w, w, _, w, w, _, _, _, w, w},
    {w, w, w, w, _, w, w, _, _, w, w, _, w, w, _, _, _, w, w, _, w, _, _, w, w, _, w, w, _, w, w, _, _, w, w, w, _, _, w, w, _, _, w, w},
    {w, w, w, w, _, _, w, w, w, w, _, _, w, w, _, _, _, w, w, _, w, w, w, w, _, _, w, w, _, w, w, _, _, _, w, w, _, _, _, w, w, w, w, w}, 
};

const std::vector <std::vector<int>> game_won_sprite = {

    {_, _, w, w, w, w, w, _, w, w, w, w, w, w, _, _, _, _, w, w, w, _, _, _, w, w, w, w, w, w, _, w, w, _, _, _, w, w, w, _, _, _, _, _, w, w, w, w},
    {_, w, w, _, _, _, _, _, w, w, _, _, _, w, w, _, _, w, w, _, w, w, _, _, w, w, w, w, w, w, _, w, w, _, _, w, w, _, w, w, _, _, _, w, w, w, w, w, w},
    {w, w, _, _, _, _, _, _, w, w, _, _, _, w, w, _, w, w, _, _, _, w, w, _, w, w, _, _, _, _, _, _, _, _, w, w, _, _, _, w, w, _, w, w, w, w},
    {w, w, _, _, w, w, w, _, w, w, _, _, w, w, w, _, w, w, _, _, _, w, w, _, w, w, _, _, _, _, _, w, w, _, w, w, _, _, _, w, w, _, _, w, w, w, w, w, w},
    {w, w, _, _, _, w, w, _, w, w, w, w, w, _, _, _, w, w, w, w, w, w, w, _, w, w, _, _, _, _, _, w, w, _, w, w, w, w, w, w, w, _, _, _, _, _, _, w, w},
    {_, w, w, _, _, w, w, _, w, w, _, w, w, w, _, _, w, w, _, _, _, w, w, _, w, w, w, w, w, w, _, w, w, _, w, w, _, _, _, w, w, _, _, w, w, w, w, w, w},
    {_, _, w, w, w, w, w, _, w, w, _, _, w, w, w, _, w, w, _, _, _, w, w, _, w, w, w, w, w, w, _, w, w, _, w, w, _, _, _, w, w, _, _, _, w, w, w, w}

};

   // --- CONSTRUCTOR ---
// Inicialitza tots els objectes i vectors del joc
Game::Game(int width, int height)
    : mario_({width / 2, 150}),
      keys_{
          Key({-50, 100}),
          Key({1040, -60}),
          Key({300, 100}),
      },
      goombas_{
          Goomba({100, 250}),
          Goomba({150, 250}),
          Goomba({970, -10}),
      },
      monedas_{
          Moneda({50, 250}),
          Moneda({150, 250}),
          Moneda({300, 150}),
          Moneda({350, 150}),
          Moneda({400, 150}),
          Moneda({450, 150}),
          Moneda({500, 150}),
          Moneda({550, 150}),
      },
      platforms_{
          Platform(150, 300, 200, 211),
          Platform(40, 200, 250, 800),
          Platform(250, 400, 150, 161),
          Platform(-100, 5, 200, 800),
          Platform(730, 790, 90, 100),
          Platform(800, 860, 70, 80),
          Platform(870, 930, 30, 40),
          Platform(940, 1000, -10, 0),
          Platform(1010, 1070, -50, -40),
      },
      carnivora_({-50, 50}, 135, 100),
      finished_(false)
{
    // --- Inicialització d'estrelles de fons ---
    int estrellas_count = 400;
    int left = 500, right = 3000, top = 0, bottom = 300;
    srand(42);
    for (int i = 0; i < estrellas_count; ++i) {
        int x = left + rand() % (right - left);
        int y = top + rand() % (bottom - top);
        estrellas_.push_back({x, y});
    }

    // --- Inicialització de plataformes, goombas i monedes addicionals ---
    for (int i = 1; i < 1000; i++) {
        platforms_.push_back(Platform(250 + i * 200, 400 + i * 200, 150, 700));
    }
    for (int i = 1; i < 1000; i++) {
        goombas_.push_back(Goomba({150 + i * 200, 150}));
    }
    for (int i = 1; i < 1000; i++) {
        monedas_.push_back(Moneda({325 + i * 200, 125}));
        monedas_.push_back(Moneda({275 + i * 200, 125}));
        monedas_.push_back(Moneda({375 + i * 200, 125}));
    }

    // --- Assignació d'extrems a cada Goomba segons la plataforma on està ---
    for (Goomba& goomba : goombas_) {
        for (const Platform& plat : platforms_) {
            pro2::Rect r = plat.get_rect();
            if (goomba.pos().x >= r.left && goomba.pos().x <= r.right && goomba.pos().y == r.top) { // Si el Goomba està sobre la plataforma 
                goomba.set_extrems(r.left, r.right);    // Assigna els extrems de la plataforma al Goomba
                break;
            }
        }
        goombas_finder_.add(&goomba);   // Afegeix el Goomba al finder per optimitzar col·lisions
    }

    // --- Decoració: núvols i tuberies ---
    for (int i = 1; i < 1000; i++) {
        decoracions_.emplace_back(pro2::Pt{325 + i * 200, -30}, Decor::nubes_);
        decoracions_.emplace_back(pro2::Pt{275 + i * 200, 10}, Decor::nubes_);
        decoracions_.emplace_back(pro2::Pt{400 + i * 200, 0}, Decor::nubes_);
    }
    decoracions_.emplace_back(pro2::Pt{-52, 166}, Decor::tuberia_);
    pro2::Rect tubo_rect = decoracions_.back().get_rect();
    platforms_.push_back(Platform(tubo_rect.left, tubo_rect.right, tubo_rect.top, tubo_rect.bottom));

    // --- Decoració: pedres aleatòries sobre plataformes ---
    for (const Platform& plat : platforms_) {
        if (rand() % 2 == 0) {
            pro2::Rect r = plat.get_rect();
            int ancho = r.right - r.left;
            if (ancho > 20) {
                int piedra1_x = r.left + rand() % (ancho - 10) + 5;
                int piedra_y = r.top - 3;
                decoracions_.emplace_back(pro2::Pt{piedra1_x, piedra_y}, Decor::piedras_);
                int piedra2_x = r.left + rand() % (ancho - 10) + 5;
                decoracions_.emplace_back(pro2::Pt{piedra2_x, piedra_y}, Decor::piedras_);
            }
        }
    }

    // --- Afegim objectes als finders per optimitzar col·lisions i visibilitat ---
    for (size_t i = 0; i < platforms_.size() - 1; ++i) {
        platforms_finder_.add(&platforms_[i]);
    }
    for (const Moneda& m : monedas_) {
        monedas_finder_.add(&m);
    }
    for (const Decor& decor : decoracions_) {
        decoracions_finder_.add(&decor);
    }
}

// --- GESTIÓ DE TECLAT ---
// Processa l'entrada de teclat per accions globals (sortida, etc)
void Game::process_keys(pro2::Window& window) {
    if (window.is_key_down(Keys::Escape)) {
        finished_ = true;
        return;
    }
}

// --- ACTUALITZACIÓ D'OBJECTES ---
// Actualitza tots els objectes i gestiona col·lisions, animacions i transicions de mapa
void Game::update_objects(pro2::Window& window) {
    // --- Transició a nou mapa ---
    if (transicion_nuevo_mapa_) {   // Si estem en transició a un nou mapa
        if (window.frame_count() - frame_transicion_ > 48) {    // Si han passat més de 48 frames
            transicion_nuevo_mapa_ = false;
            en_nuevo_mapa_ = true;
            frame_entrada_nuevo_mapa_ = window.frame_count();
            if (!nuevo_mapa_inicializado_) {    // Si el nou mapa no està inicialitzat
                platforms_.clear();     // Neteja les plataformes del mapa antic
                goombas_.clear();       // Neteja els goombas del mapa antic
                monedas_.clear();       // Neteja les monedes del mapa antic
                decoracions_.clear();   // Neteja les decoracions del mapa antic
                plataformas_nuevo_mapa_.clear();    // Neteja les plataformes del nou mapa

                int plataforma_top = window.height() * 3 / 4;   
                plataformas_nuevo_mapa_.emplace_back(500, 3000, plataforma_top, 700);   // Plataforma base del nou mapa

                puerta_ = Door({1125, plataforma_top - 2});     // Porta per accedir al nou mapa
                bowser_ = Bowser({1700, plataforma_top - 39});  // Bowser al nou mapa
                peach_ = Peach({1750, plataforma_top - 10});    // Princesa Peach al nou mapa
                bloc_flor_ = Bloc({1200, 180});         // Bloc de la flor especial al nou mapa

                flor_visible_ = false;
                flor_recogida_ = false;
                nuevo_mapa_inicializado_ = true;
                flor_pos_ = {1200, 185};
                mario_.set_y(plataforma_top - 26);
                mario_.set_grounded(true);
            }
        }
        return; // No actualitzem més si estem en transició
    }

    // --- Bloc de la flor (segon mapa) ---
    if (!bloc_flor_.destruido() && en_nuevo_mapa_) {
        pro2::Rect bloque_rect = bloc_flor_.get_rect();
        pro2::Pt mario_pos = mario_.pos();
        pro2::Pt mario_last_pos = mario_.last_pos();
        /*
        Si Mario ha saltat per sota del bloc de la flor i co.lisiona amb ell,
        el bloc es trenca i la flor apareix a la posició del bloc, fent un efecte
        com si la flor sortís del bloc.
        */
        if (mario_last_pos.y > bloque_rect.bottom && mario_pos.y <= bloque_rect.bottom &&       
            mario_pos.x + 8 > bloque_rect.left && mario_pos.x - 8 < bloque_rect.right) {
            bloc_flor_.destruir();
            mario_.bounce_down();
            flor_visible_ = true;
            flor_animando_ = true;
            flor_anim_frame_ = 0;
            flor_base_y_ = flor_pos_.y;
            frame_flor_aparece_ = window.frame_count();
        }
    }

    // --- Col·lisió Mario amb la flor especial ---
    if (flor_visible_ && !flor_recogida_) {
        if (window.frame_count() - frame_flor_aparece_ > 48) {
            pro2::Rect mario_head = {
                mario_.pos().x - 8, mario_.pos().y - 26,
                mario_.pos().x + 8, mario_.pos().y - 10
            };
            pro2::Rect flor_rect = {
                flor_pos_.x - 8, flor_pos_.y - 16,
                flor_pos_.x + 8, flor_pos_.y + 8
            };
            // Si Mario col·lisiona amb la flor, la recull
            if (!(mario_head.right < flor_rect.left ||
                  mario_head.left > flor_rect.right ||
                  mario_head.bottom < flor_rect.top ||
                  mario_head.top > flor_rect.bottom)) {
                flor_recogida_ = true;
                flor_visible_ = false;
            }
        }
    }

    // --- Actualització de Mario i Bowser ---
    if (!mario_.is_dead()) {
        if (en_nuevo_mapa_) {
            mario_.update(window, plataformas_nuevo_mapa_);
            bowser_.update(mario_.pos());
        } else {
            mario_.update(window, platforms_);
        }
    }

    // --- Bloc de la clau (primer mapa) ---
    if (!bloc_.destruido() && llave_oculta_) {
        pro2::Rect bloque_rect = bloc_.get_rect();
        pro2::Pt mario_pos = mario_.pos();
        pro2::Pt mario_last_pos = mario_.last_pos();

        /*
        Si Mario ha saltat per sota del bloc de la clau i col·lisiona amb ell,
        el bloc es trenca, la clau apareix a la posició del bloc 
        i Mario rebotarà cap avall.
        */
        if (mario_last_pos.y > bloque_rect.bottom && mario_pos.y <= bloque_rect.bottom &&
            mario_pos.x + 8 > bloque_rect.left && mario_pos.x - 8 < bloque_rect.right) {
            bloc_.destruir();
            llave_oculta_ = false;
            mario_.bounce_down();
            llave_animando_ = true;
            llave_anim_frame_ = 0;
            llave_y_inicial_ = 100;
            llave_y_animada_ = 100;
        }
    }

    // --- Animació de la clau ---
    if (llave_animando_) {
        llave_anim_frame_++;
        llave_y_animada_ = llave_y_inicial_ - (llave_anim_frame_ < llave_anim_max_frames_ ? llave_anim_frame_ * 1.5 : llave_anim_max_frames_ * 1.5);
        if (llave_anim_frame_ >= llave_anim_max_frames_) {
            llave_animando_ = false;
            llave_y_animada_ = llave_y_inicial_ - llave_anim_max_frames_ * 1.5;
        }
        for (Key& key : keys_) {
            if (key.get_pos().x == 300 && key.get_pos().y == 100) {
                key.set_pos({300, (int)llave_y_animada_});
            }
        }
    }

    // --- Animació de la flor especial ---
    if (flor_animando_) {
        flor_anim_frame_++;
        if (flor_anim_frame_ < flor_anim_max_frames_) {
            flor_pos_.y = flor_base_y_ - flor_anim_frame_ * 1.5;
        } else {
            flor_pos_.y = flor_base_y_ - flor_anim_max_frames_ * 1.5 + int(8 * std::sin((flor_anim_frame_ - flor_anim_max_frames_) / 12.0));
        }
    }

    // --- Col·lisions Mario amb enemics i objectes especials ---
    // Bowser i boles de foc
    if (en_nuevo_mapa_ && bowser_.is_alive()) {
        for (auto& fireball : bowser_.fireballs()) {
            if (fireball.active) {
                pro2::Rect mario_rect = {mario_.pos().x - 8, mario_.pos().y - 26, mario_.pos().x + 8, mario_.pos().y + 1};
                pro2::Rect fire_rect = {fireball.pos.x - 4, fireball.pos.y - 4, fireball.pos.x + 4, fireball.pos.y + 4};
                /*
                Si una bola de foc toca a Mario, aquest mor i
                per tant la bola de foc es desactiva.
                */
                if (!(mario_rect.right < fire_rect.left || mario_rect.left > fire_rect.right ||
                      mario_rect.bottom < fire_rect.top || mario_rect.top > fire_rect.bottom)) {
                    mario_.matar();
                    frame_mort = window.frame_count();
                    fireball.active = false;
                }
            }
        }
        // Iceballs contra Bowser
        pro2::Rect bowser_rect = bowser_.get_rect();
        for (auto& iceball : iceballs_) {
            if (!iceball.active) continue;
            pro2::Rect ice_rect = {iceball.pos.x - 4, iceball.pos.y - 4, iceball.pos.x + 4, iceball.pos.y + 4};
            /*
            Si una bola de gel toca a Bowser, aquest perdrà una vida
            i la bola de gel es desactiva.
            */
            if (!(ice_rect.right < bowser_rect.left || ice_rect.left > bowser_rect.right ||
                  ice_rect.bottom < bowser_rect.top || ice_rect.top > bowser_rect.bottom)) {
                bowser_.recibir_danio(window);
                iceball.active = false;
            }
        }
    }

    // --- Llançament d'iceballs si Mario té la flor especial ---
    if (en_nuevo_mapa_ && !mario_.is_dead() && flor_recogida_) {
        if (window.is_key_down(Keys::Tab)) {
            static int iceball_cooldown = 0;
            if (iceball_cooldown == 0) {
                int dir = mario_.is_looking_left() ? -1 : 1;
                pro2::Pt speed = {6 * dir, 0};
                pro2::Pt iceball_pos = {mario_.pos().x, mario_.pos().y - 13};
                iceballs_.emplace_back(iceball_pos, speed);
                iceball_cooldown = 15; // cooldown de 15 frames
            } else {
                iceball_cooldown--;
            }
        }
    }

    // --- Actualització de totes les iceballs ---
    for (auto& iceball : iceballs_) {
        if (iceball.active) iceball.update();
    }

    // --- Animació i col·lisió de Goombas ---
    pro2::Rect camera = window.camera_rect();
    std::set<const Goomba*> goombas_visibles = goombas_finder_.query(camera);
    for (Goomba& goomba : goombas_) {
        if (goombas_visibles.count(&goomba) && !goomba.is_eliminat()) {
            goomba.update_animation(window, platforms_);
        }
    }

    // --- Animació i recollida de monedes ---
    for (Moneda& moneda : monedas_) {
        if (!moneda.is_recogida()) {
            const pro2::Pt mario_pos = mario_.pos();
            const pro2::Pt moneda_pos = moneda.pos();
            const int collision_distance = 15;
            if (abs(mario_pos.x - moneda_pos.x) < collision_distance && abs(mario_pos.y - moneda_pos.y) < collision_distance) {
                moneda.recoger();
                monedas_recogidas_++;
                std::cout << "\r Monedes: " << monedas_recogidas_ << std::flush;
            }
        }
        moneda.update_animation(window);
    }

    // --- Col·lisió Mario amb Goombas i planta carnívora ---
    if (!mario_.is_dead()) {
        for (Goomba& goomba : goombas_) {
            if (goomba.is_eliminat()) continue;
            const pro2::Pt mario_pos = mario_.pos();
            const pro2::Rect goomba_rect = goomba.get_rect();
            const pro2::Rect planta_rect = carnivora_.get_rect();
            const pro2::Pt mario_last_pos = mario_.last_pos();

            /*
            Si Mario co.lisiona amb el goomba o la planta carnívora,
            hi ha dues possibilitats:
            1. Si Mario salta sobre el goomba, aquest es elimina i Mario rebotarà.
            2. Si Mario toca el goomba o la planta carnívora, morirà.
            */
            if ((mario_pos.x >= goomba_rect.left && mario_pos.x <= goomba_rect.right && mario_pos.y >= goomba_rect.top && mario_pos.y <= goomba_rect.bottom) ||
                (mario_pos.x >= planta_rect.left && mario_pos.x <= planta_rect.right && mario_pos.y >= planta_rect.top && mario_pos.y <= planta_rect.bottom)) {
                if (mario_last_pos.y < goomba_rect.top && mario_pos.y >= goomba_rect.top) {
                    goomba.eliminar();
                    mario_.set_y(goomba_rect.top - 15);
                    mario_.bounce();
                } else {
                    mario_.matar();
                    frame_mort = window.frame_count();
                }
            }
        }
    }

    // --- Col·lisió Mario amb Bowser ---
    if (!mario_.is_dead() && en_nuevo_mapa_ && bowser_.is_alive()) {
        pro2::Rect mario_rect = {mario_.pos().x - 8, mario_.pos().y - 26, mario_.pos().x + 8, mario_.pos().y + 1};
        pro2::Rect bowser_rect = bowser_.get_rect();
        //Si Mario col·lisiona amb Bowser, mor
        if (!(mario_rect.right < bowser_rect.left ||
              mario_rect.left > bowser_rect.right ||
              mario_rect.bottom < bowser_rect.top ||
              mario_rect.top > bowser_rect.bottom)) {
            mario_.matar();
            frame_mort = window.frame_count();
        }
    }

    // --- Col·lisió Mario amb el límit inferior del mapa ---
    const int limit_mapa = 600;
    // Si Mario cau per sota del límit del mapa (el que considerem lava), mor
    if (mario_.pos().y > limit_mapa && !mario_.is_dead()) {
        mario_.matar();
        frame_mort = window.frame_count();
    }

    // --- Animació de la planta carnívora ---
    carnivora_.update_animation(window);

    // --- Col·lisió i animació de claus ---
    for (Key& key : keys_) {
        if (key.get_pos().x == 300 && llave_oculta_) continue;
        if (key.get_pos().x == 300 && llave_animando_) continue;
        if (!key.is_recogida()) {
            const pro2::Pt mario_pos = mario_.pos();
            const pro2::Pt key_pos = key.get_pos();
            const int collision_distance = 15;
            // Si Mario col·lisiona amb una clau, la recull
            if (abs(mario_pos.x - key_pos.x) < collision_distance && abs(mario_pos.y - key_pos.y) < collision_distance) {
                key.recoger();
            }
        }
        key.update_animation(window);
    }

    // --- Comprovació de claus recollides per mostrar la porta ---
    int recogidas = 0;
    for (const Key& key : keys_) {
        if (key.is_recogida()) recogidas++;
    }
    // Si s'han recollit totes les claus, la porta que ens porta al final del joc es fa visible
    if (recogidas == 3) puerta_visible_ = true;

    // --- Col·lisió Mario amb la porta per transició ---
    if (puerta_visible_ && !en_nuevo_mapa_) {
        const pro2::Pt mario_pos = mario_.pos();
        const pro2::Rect puerta_rect = puerta_.get_rect();
        // Si Mario col·lisiona amb la porta i prem la tecla d'entrada, s'obre la porta i es prepara la transició al nou mapa
        if (mario_pos.x >= puerta_rect.left && mario_pos.x <= puerta_rect.right &&
            mario_pos.y >= puerta_rect.top && mario_pos.y <= puerta_rect.bottom) {
            if (window.is_key_down(Keys::Up) && !puerta_.is_abierta()) {
                puerta_.abrir();
                esperando_transicion_puerta_ = true;
                frame_transicion_ = window.frame_count();
            } else if (window.frame_count() - frame_transicion_ >= 24 && esperando_transicion_puerta_) {
                transicion_nuevo_mapa_ = true;
                esperando_transicion_puerta_ = false;
                frame_transicion_ = window.frame_count();
            }
        }
    }

    // --- Rescat de Peach i canvi d'estat ---
    if (en_nuevo_mapa_) {
        if (!peach_rescatada_ && !bowser_.is_alive()) {
            pro2::Rect mario_rect = {mario_.pos().x - 8, mario_.pos().y - 26, mario_.pos().x + 8, mario_.pos().y + 1};
            pro2::Rect peach_rect = {peach_.pos().x - 8, peach_.pos().y - 32, peach_.pos().x + 8, peach_.pos().y + 1};
            // Si Mario col·lisiona amb Peach, la rescata i canvia el seu estat a "llorando" durant 48 frames fins que es converteixi en "feliz" i s'acaba el joc
            if (!(mario_rect.right < peach_rect.left - 5 || mario_rect.bottom < peach_rect.top || mario_rect.top > peach_rect.bottom)) {
                peach_rescatada_ = true;
                frame_peach_rescatada_ = window.frame_count();
                peach_.set_estado(Peach::LLORANDO);
            }
        }
        if (peach_rescatada_ && peach_.estado() == Peach::LLORANDO) {
            if (window.frame_count() - frame_peach_rescatada_ >= 48) {
                peach_.set_estado(Peach::FELIZ);
            }
        }
    }
}

// --- ACTUALITZACIÓ DE LA CÀMERA ---
// Centra la càmera en Mario i ajusta segons el moviment
void Game::update_camera(pro2::Window& window) {
    const Pt pos = mario_.pos();
    const Pt cam = window.camera_center();

    const int left = cam.x - window.width() / 32;
    const int right = cam.x + window.width() / 32;
    const int top = cam.y - window.height() / 4;
    const int bottom = cam.y + window.height() / 4;

    int dx = 0, dy = 0;
    if (pos.x > right) {
        dx = pos.x - right;
    } else if (pos.x < left) {
        dx = pos.x - left;
    }
    if (pos.y < top) {
        dy = pos.y - top;
    } else if (pos.y > bottom) {
        dy = pos.y - bottom;
    }

    window.move_camera({dx, dy});
}

// --- UPDATE PRINCIPAL ---
// Actualitza l'estat global del joc (tecles, objectes, càmera, finalització)
void Game::update(pro2::Window& window) {
    process_keys(window);
    update_objects(window);
    update_camera(window);

    // Si Mario ha mort fa més de 3 segons, acaba el joc
    if (frame_mort != -1 && window.frame_count() - frame_mort > 3 * 48) {
        finished_ = true;
    }
    // Si Peach ha estat rescatada fa més de 4 segons, acaba el joc
    if (peach_rescatada_ && window.frame_count() - frame_peach_rescatada_ > 48 * 4) {
        finished_ = true;
    }
}

// --- FONS D'ESTRELLES ---
// Pinta les estrelles de fons segons la càmera
void Game::paint_stars_background(pro2::Window& window) const {
    pro2::Rect cam = window.camera_rect();
    for (const auto& estrella : estrellas_) {
        if (estrella.x >= cam.left && estrella.x < cam.right &&
            estrella.y >= cam.top && estrella.y < cam.bottom) {
            window.set_pixel(estrella, pro2::white);
        }
    }
}

// --- PINTAT GENERAL DEL JOC ---
// Pinta tot el joc segons l'estat actual (pantalla de càrrega, game over, mapes, etc)
void Game::paint(pro2::Window& window) {
    // --- Pantalla de càrrega ---
    if (transicion_nuevo_mapa_) {
        window.clear(pro2::black);
        window.set_camera_topleft({0, 0});
        pro2::Pt top_left = {
            window.width() / 2 - (int)loading_sprite[0].size() / 2,
            window.height() / 2 - (int)loading_sprite.size() / 2
        };
        paint_sprite(window, top_left, loading_sprite, false);
        return;
    }

    // --- Pantalla de Game Over ---
    int frames_since_death = 0;
    if (mario_.is_dead()) {
        frames_since_death = window.frame_count() - frame_mort;
    }
    if (mario_.is_dead() && frames_since_death >= 48) {
        window.clear(pro2::black);
        window.set_camera_topleft({0, 0});
        pro2::Pt top_left = {
            window.width() / 2 - (int)game_over_sprite[0].size() / 2,
            window.height() / 2 - (int)game_over_sprite.size() / 2
        };
        paint_sprite(window, top_left, game_over_sprite, false);
        return;
    }

    // --- Nou mapa (segon nivell) ---
    if (en_nuevo_mapa_) {
        window.clear(0x222288);
        paint_stars_background(window);
        for (const Platform& p : plataformas_nuevo_mapa_) {
            p.paint(window);
        }
        if (frame_entrada_nuevo_mapa_ != -1 && window.frame_count() - frame_entrada_nuevo_mapa_ < 24) {
            puerta_.abrir();
            puerta_.paint(window);
        } else {
            puerta_.cerrar();
            puerta_.paint(window);
        }
        bowser_.paint(window);
        mario_.paint(window, mario_.is_dead(), flor_recogida_);
        peach_.paint(window);
        bloc_flor_.paint(window);
        if (flor_visible_ && !flor_recogida_) {
            paint_sprite(window, flor_pos_, Flor::flor_sprite_, false);
        }
        for (const auto& iceball : iceballs_) {
            if (iceball.active) iceball.paint(window);
        }
        if (peach_rescatada_ && peach_.estado() == Peach::FELIZ) {
            pro2::Pt peach_pos = peach_.pos();
            int offset_x = 40;
            int offset_y = -32;
            pro2::Pt sprite_pos = {peach_pos.x + offset_x, peach_pos.y + offset_y};
            paint_sprite(window, sprite_pos, game_won_sprite, false);
        }
        return;
    }

    // --- Mapa normal (nivell principal) ---
    window.clear(sky_blue);
    pro2::Rect camera = window.camera_rect();

    // --- Lava al fons ---
    const Color lava = 0xAB2327;
    paint_rect(window, camera.left, std::max(600, camera.top), camera.right - 1, camera.bottom - 1, lava);

    // --- Pintat d'objectes visibles ---
    carnivora_.paint(window);

    std::set<const Decor*> decoracions_visibles = decoracions_finder_.query(camera);
    for (const Decor* decor : decoracions_visibles) {
        decor->paint(window);
    }

    std::set<const Platform*> visibles = platforms_finder_.query(camera);
    for (const Platform* p : visibles) {
        p->paint(window);
    }

    // --- Claus visibles ---
    for (const Key& key_ : keys_) {
        if (key_.get_pos().x == 300 && key_.get_pos().y == 100 && llave_oculta_) continue;
        if (!key_.is_recogida()) {
            key_.paint(window);
        }
    }

    // --- Dibuixa les claus recollides a la UI ---
    int total_llaves = keys_.size();
    int recogidas = 0;
    for (const Key& key : keys_) {
        if (key.is_recogida()) recogidas++;
    }
    if (recogidas == 3) puerta_visible_ = true;

    if (puerta_visible_ && !en_nuevo_mapa_) {
        puerta_.paint(window);
    }

    bloc_.paint(window);
    mario_.paint(window, mario_.is_dead());

    // --- Dibuixa les claus recollides a la cantonada ---
    int margen = 10;
    int separacion = 30;
    pro2::Rect cam = window.camera_rect();
    pro2::Pt cam_topleft = {cam.left, cam.top};
    int x0 = cam_topleft.x + window.width() - margen - separacion * total_llaves;
    int y0 = cam_topleft.y + margen;

    for (int i = 0; i < total_llaves; ++i) {
        pro2::Pt pos = {x0 + i * separacion, y0};
        if (i < recogidas) {
            paint_sprite(window, pos, Key::key_sprite_, false);
        } else {
            paint_sprite(window, pos, Key::key_sprite_black_, false);
        }
    }

    // --- Goombas visibles ---
    std::set<const Goomba*> goombas_visibles = goombas_finder_.query(camera);
    for (const Goomba* goomba : goombas_visibles) {
        if (!goomba->is_eliminat()) {
            goomba->paint(window);
        }
    }

    // --- Monedes visibles ---
    std::set<const Moneda*> monedes_visibles = monedas_finder_.query(camera);
    for (const Moneda* m : monedes_visibles) {
        if (!m->is_recogida()) {
            m->paint(window);
        }
    }
} 
