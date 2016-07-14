#include <BarraProgreso.h>
#include <CajaListas.h>
#include <Dibujar.h>
#include <Diagrama.h>
#include <iostream>

using namespace std;

const string audio_file("C:/Users/Miguel/Music/AOMdialog/ajax103.wav");

int main()
{
    BarraProgreso bp;
    bp.show();
    CajaListas cl;
    cl.show();
    //Dibujar dj;
    //dj.show();
    nana::audio::player reproductor_audio(audio_file);
    reproductor_audio.play();

    cout << "fasterr" << endl;
    nana::exec(); //bloquea

    return 0;
}
