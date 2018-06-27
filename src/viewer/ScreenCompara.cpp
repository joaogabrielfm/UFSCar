#include "ScreenCompara.hpp"
#include "Config.hpp"
#include "MusicManager.hpp"
#include "TextureManager.hpp"

#include <iostream>

ScreenCompara::ScreenCompara( GameRef& gameRef, Fila* modeloFila, Fila* minhaFila )
    : Screen( gameRef ) {
    this->modeloFila   = modeloFila;
    this->minhaFila    = minhaFila;
    this->remover      = true;
    this->lancheModelo = nullptr;
    this->lancheMeu    = nullptr;

    loadAssets();
}

void ScreenCompara::loadAssets() {
    TextureManager::add( "backgroundJogo", "jogo.jpg" );
    background.setTexture( TextureManager::get( "backgroundJogo" ) );

    MusicManager::add( "musicJogar", "background.ogg" );
    music = &MusicManager::get( "musicJogar" );
}
void ScreenCompara::draw() {
    window->clear();

    window->draw( background );
    if( lancheMeu != nullptr ) {
        window->draw( *lancheMeu );
    }

    if( lancheModelo != nullptr ) {
        window->draw( *lancheModelo );
    }

    window->display();
}
void ScreenCompara::update() {
    if( *isAudioOn && music->getStatus() != sf::SoundSource::Status::Playing ) {
        music->play();
    }

    if( remover ) {
        if( modeloFila->Vazia() ) {
            std::cout << "terminou" << std::endl;
            music->stop();
            *nextScreen = GANHOU;
        } else {
            std::cout << "Nao vazia" << std::endl;
            lancheModelo = modeloFila->Retira();
            lancheModelo->setPosition( -100, 150 );

            lancheMeu = minhaFila->Retira();
            lancheMeu->setPosition( -100, 250 );
            remover = false;
        }
    }

    while( window->pollEvent( *event ) ) {
        if( event->type == sf::Event::Closed ) {
            music->stop();
            window->close();
        }
    }

    draw();
    if( lancheMeu != nullptr ) {
        if( lancheMeu->getPosotion().x < ( WINDOW_WIDTH / 2 - 50 ) ) {
            lancheMeu->move( 3, 0 );
            lancheModelo->move( 3, 0 );
        } else {
            std::cout << "Entrou" << std::endl;
            while( !lancheMeu->isVazia() && !lancheModelo->isVazia() ) {
                Food* foodModelo = lancheModelo->remover();
                Food* foodMeu    = lancheMeu->remover();

                std::cout << "AAA:"
                          << ( foodMeu->getAlias().compare( foodModelo->getAlias() ) != 0 )
                          << std::endl;

                if( foodMeu->getAlias().compare( foodModelo->getAlias() ) != 0 ) {
                    // TODO remover todos elementos
                    music->stop();
                    *nextScreen = PERDEU;

                    break;
                } else {
                    delete foodMeu;
                    delete foodModelo;
                }
            }
            std::cout << "Saiuu" << std::endl;

            lancheMeu    = nullptr;
            lancheModelo = nullptr;

            remover = true;
        }
    }
}