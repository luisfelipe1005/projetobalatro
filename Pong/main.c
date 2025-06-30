
    /* Copyright (C) 2016 Marcelo Serrano Zanetti - All Rights Reserved

     * Licensed under the GNU GPL V3.0 license. All conditions apply.

     * Powered by Allegro: http://liballeg.org/license.html

     */



     /*Sistema de audios baseado no tutorial de allegro:
     https://github.com/liballeg/allegro5/blob/c870f466638b345639b46628e4d421443aacff71/examples/ex_audio_simple.c#L33
     */

    #include <stdio.h>

    #include <allegro5/allegro.h>

    #include <allegro5/allegro_image.h>
    #include <allegro5/allegro_font.h>
    #include <allegro5/allegro_ttf.h>
    #include <allegro5/allegro_primitives.h>
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"
    #include <stdlib.h>
    #include <stdbool.h>
    #include <time.h>
#define RESERVED_SAMPLES   16
#define MAX_SAMPLE_DATA    10
void shuffle(char **array, size_t n);
bool isflush(char **array, size_t n);
int ismultiple(char **array, size_t n);
bool issequence(char **array, size_t n);
int comparador(const void *a, const void *b);
void numerar_baralho(char **array, size_t n, int* a);

    const float FPS = 90;

    const int SCREEN_W = 1024;

    const int SCREEN_H = 768;


    const int BARALHO_LARGURA = 257;

    const int BARALHO_ALTURA = 506;

    const int BOTAO_LARGURA = 257;

    const int BOTAO_ALTURA = 124;

const char *default_files[] = {NULL, "audios/button.ogg",
         "audios/cancel.ogg", "audios/card1.ogg",
         };


    int main(int argc, char **argv){
        al_init_font_addon();
    al_init_ttf_addon();

        ALLEGRO_DISPLAY *display = NULL;

        ALLEGRO_EVENT_QUEUE *event_queue = NULL;

        ALLEGRO_TIMER *timer = NULL;

   ALLEGRO_SAMPLE *sample_data[MAX_SAMPLE_DATA] = {NULL};
   ALLEGRO_EVENT event;
   ALLEGRO_SAMPLE_ID sample_id;
   bool sample_id_valid = false;
   ALLEGRO_AUDIO_STREAM *music = NULL;
   int i;
   bool panning = false;

        if(!al_init())

        {

            fprintf(stderr, "failed to initialize allegro!\n");

            return -1;

        }

        timer = al_create_timer(1.0 / FPS);

        if(!timer)

        {

            fprintf(stderr, "failed to create timer!\n");

            return -1;

        }

        ALLEGRO_FONT *font = al_create_builtin_font();



   if (argc < 2) {
      printf("This example can be run from the command line.\nUsage: %s {audio_files}\n", argv[0]);
      argv = default_files;
      argc = 10;
   }
   argc--;
   argv++;

    if (!font) {
        fprintf(stderr, "Erro ao criar fonte builtin!\n");
        return -1;
    }

        bool redraw = true;

      al_set_new_display_flags(ALLEGRO_WINDOWED);

        display = al_create_display(SCREEN_W, SCREEN_H);

        if(!display)

        {

            fprintf(stderr, "failed to create display!\n");

            al_destroy_timer(timer);

            return -1;

        }

        if(!al_install_keyboard())

        {

            fprintf(stderr, "failed to initialize the keyboard!\n");

            return -1;

        }

        if(!al_install_mouse())

        {

            fprintf(stderr, "failed to initialize the mouse!\n");

            return -1;

        }

        if(!al_init_image_addon())

        {

            fprintf(stderr, "failed to initialize the image addon!\n");

            return -1;

        }

        ALLEGRO_BITMAP *background = NULL;

        ALLEGRO_BITMAP *baralho = NULL;

        ALLEGRO_BITMAP *botjog = NULL;

        ALLEGRO_BITMAP *botdisc = NULL;

        ALLEGRO_BITMAP *carta[7] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL};




        float baralho_pos_x = SCREEN_W - BARALHO_LARGURA;

        float baralho_pos_y = SCREEN_H/1.5 /  - BARALHO_ALTURA  / 2.0 ;

        float botjog_pos_x = SCREEN_W/2 - BOTAO_LARGURA - 10;

        float botjog_pos_y = SCREEN_H/3 + BARALHO_ALTURA/2.5 ;


      float botdisc_pos_x = SCREEN_W/2 + 10;

        float botdisc_pos_y = SCREEN_H/3 + BARALHO_ALTURA/2.5 ;

        float carta_pos_x[7];
        float carta_pos_y[7];
   int a;
        for(a=0;a<7;a++){
                carta_pos_x[a] = SCREEN_W/2 - BARALHO_LARGURA*1.5+ 100*a ;
           carta_pos_y[a] = SCREEN_H*2  - BARALHO_ALTURA*2 ;
        }



        int click=0;

        int savebvx;

        int savebvy;


        background        = al_load_bitmap("imagens/campo.png");

        baralho=al_load_bitmap("imagens/baralho.png");

        botjog=al_load_bitmap("imagens/negbotao_jogarmao.png");

        botdisc=al_load_bitmap("imagens/negbotao_discartarmao.png");

         char *cartas[] = {
 "AO", "AE", "AC", "AP", "2O", "2E", "2C", "2P","3O", "3E", "3C", "3P","4O", "4E", "4C", "4P","5O", "5E", "5C", "5P","6O", "6E", "6C", "6P","7O", "7E", "7C", "7P","8O", "8E", "8C", "8P","9O", "9E", "9C", "9P","0O", "0E", "0C", "0P","JO", "JE", "JC", "JP","QO", "QE", "QC", "QP","KO", "KE", "KC", "KP"
};
int mao_num[5];
    int size = sizeof(cartas) / sizeof(cartas[0]);


    srand(time(NULL));
        shuffle(cartas,size);
int nmrcartatopo=0;
char *mao[7];
char *discarte[52];
int disc_ind=0;
char image_path[50];
bool carta_click[7]={false,false,false,false,false,false,false};
int cartamaos=0;
char texto[50];
int total=0;
int cont_selec=0;
int jogs=4,discs=3;


for (a = 0; a < 7; a++) {
mao[a]=cartas[nmrcartatopo];
nmrcartatopo++;
    sprintf(image_path, "imagens/%s.png", mao[a]);
        carta[a] = al_load_bitmap(image_path);
if (!carta[a]) {
    fprintf(stderr, "Failed to load image for carta %d e %s\n", a, mao[a]);
    exit(-1);
}

    }





        if(!background)

        {

            fprintf(stderr, "falhou ao criar o background bitmap!\n");

            al_destroy_display(display);

            al_destroy_timer(timer);


            return -1;

        }


        if(!baralho)

        {

            fprintf(stderr, "falhou ao criar o baralho bitmap!\n");

            al_destroy_display(display);

            al_destroy_timer(timer);


            return -1;

        }

                if(!botjog)

        {

            fprintf(stderr, "falhou ao criar o botao de jogar carta bitmap!\n");

            al_destroy_display(display);

            al_destroy_timer(timer);

            return -1;

        }
                       if(!botdisc)

        {

            fprintf(stderr, "falhou ao criar o botao de descartar carta bitmap!\n");

            al_destroy_display(display);

            al_destroy_timer(timer);

            return -1;

        }
        for(a=0;a<7;a++){
        if(!carta[a])

        {

            fprintf(stderr, "falhou ao criar a carta bitmap!\n");

            al_destroy_display(display);

            al_destroy_timer(timer);


            return -1;

        }}

        al_set_target_bitmap(al_get_backbuffer(display));



        event_queue = al_create_event_queue();

        if(!event_queue)

        {

            fprintf(stderr, "failed to create event_queue!\n");


            al_destroy_bitmap(background);

            al_destroy_display(display);

            al_destroy_timer(timer);

            return -1;

        }



        al_register_event_source(event_queue, al_get_display_event_source(display));

        al_register_event_source(event_queue, al_get_timer_event_source(timer));

        al_register_event_source(event_queue, al_get_keyboard_event_source());

        al_register_event_source(event_queue, al_get_mouse_event_source());



        al_clear_to_color(al_map_rgb(0,0,0));



        al_flip_display();



        al_start_timer(timer);

Restart:

   if (!al_install_audio()) {
                fprintf(stderr, "failed to create event_queue!\n");
 return -1;

   }

   if (!al_reserve_samples(RESERVED_SAMPLES)) {
                     fprintf(stderr, "Could not set up voice and mixer.\n");
 return -1;
   }

   memset(sample_data, 0, sizeof(sample_data));
   for (i = 0; i < argc && i < MAX_SAMPLE_DATA; i++) {
      const char *filename = argv[i];

      /* Load the entire sound file from disk. */
      sample_data[i] = al_load_sample(argv[i]);
      if (!sample_data[i]) {
        fprintf(stderr, "Could not load sample from '%s'!\n", filename);
 return -1;
      }
   }

   printf(
      "Press digits to play sounds.\n"
      "Space to stop sounds.\n"
      "Add Alt to play sounds repeatedly.\n"
      "'p' to pan the last played sound.\n"
      "Escape to quit.\n");

 while(1)

        {
      al_wait_for_event(event_queue, &event);
      if (event.type == ALLEGRO_EVENT_KEY_CHAR) {
         if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
            break;
         }
         if (event.keyboard.unichar == ' ') {
            printf("Stopping all sounds\n");
            al_stop_samples();
            if (music) {
               al_set_audio_stream_playing(music, false);
            }
         }

         if (event.keyboard.keycode >= ALLEGRO_KEY_0 && event.keyboard.keycode <= ALLEGRO_KEY_9) {
            bool loop = event.keyboard.modifiers & ALLEGRO_KEYMOD_ALT;
            bool bidir = event.keyboard.modifiers & ALLEGRO_KEYMOD_CTRL;
            bool reversed = event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
            i = (event.keyboard.keycode - ALLEGRO_KEY_0 + 9) % 10;
            if (sample_data[i]) {
               ALLEGRO_SAMPLE_ID new_sample_id;
               ALLEGRO_PLAYMODE playmode;
               const char* playmode_str;
               if (loop) {
                  playmode = ALLEGRO_PLAYMODE_LOOP;
                  playmode_str = "on a loop";
               }
               else if (bidir) {
                  playmode = ALLEGRO_PLAYMODE_BIDIR;
                  playmode_str = "on a bidirectional loop";
               }
               else {
                  playmode = ALLEGRO_PLAYMODE_ONCE;
                  playmode_str = "once";
               }
               bool ret = al_play_sample(sample_data[i], 1.0, 0.0, 1.0,
                  playmode, &new_sample_id);
               if (reversed) {
                  ALLEGRO_SAMPLE_INSTANCE* inst = al_lock_sample_id(&new_sample_id);
                  al_set_sample_instance_position(inst, al_get_sample_instance_length(inst) - 1);
                  al_set_sample_instance_speed(inst, -1);
                  al_unlock_sample_id(&new_sample_id);
               }
               if (ret) {
                  printf("Playing %d %s\n", i, playmode_str);
               }
               else {
                  printf(
                     "al_play_sample_data failed, perhaps too many sounds\n");
               }
               if (!panning) {
                  if (ret) {
                     sample_id = new_sample_id;
                     sample_id_valid = true;
                  }
               }
            }
         }

         if (event.keyboard.unichar == 'p') {
            if (sample_id_valid) {
               panning = !panning;
               if (panning) {
                  printf("Panning\n");
               }
               else {
                  printf("Not panning\n");
               }
            }
         }

         if (event.keyboard.unichar == 'm') {
            music = al_play_audio_stream("../demos/cosmic_protector/data/sfx/title_music.ogg");
         }

         /* Hidden feature: restart audio subsystem.
          * For debugging race conditions on shutting down the audio.
          */
         if (event.keyboard.unichar == 'r') {
            for (i = 0; i < argc && i < MAX_SAMPLE_DATA; i++) {
               if (sample_data[i])
                  al_destroy_sample(sample_data[i]);
            }
            al_uninstall_audio();
            goto Restart;
         }
      }
      else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      }
      else if (event.type == ALLEGRO_EVENT_TIMER) {
         int y = 12;
         int dy = 12;
         if (panning && sample_id_valid) {
            ALLEGRO_SAMPLE_INSTANCE* instance = al_lock_sample_id(&sample_id);
            if (instance) {
               al_set_sample_instance_pan(instance, sin(al_get_time()));
            }
            al_unlock_sample_id(&sample_id);
         }
         al_clear_to_color(al_map_rgb_f(0., 0., 0.));
         al_draw_text(font, al_map_rgb_f(1., 0.5, 0.5), 12, y,
            ALLEGRO_ALIGN_LEFT, "CONTROLS");
         y += dy;
         al_draw_text(font, al_map_rgb_f(1., 0.5, 0.5), 12, y,
            ALLEGRO_ALIGN_LEFT, "1-9 - play the sounds");
         y += dy;
         al_draw_text(font, al_map_rgb_f(1., 0.5, 0.5), 12, y,
            ALLEGRO_ALIGN_LEFT, "SPACE - stop all sounds");
         y += dy;
         al_draw_text(font, al_map_rgb_f(1., 0.5, 0.5), 12, y,
            ALLEGRO_ALIGN_LEFT, "Ctrl 1-9 - play sounds with bidirectional looping");
         y += dy;
         al_draw_text(font, al_map_rgb_f(1., 0.5, 0.5), 12, y,
            ALLEGRO_ALIGN_LEFT, "Alt 1-9 - play sounds with regular looping");
         y += dy;
         al_draw_text(font, al_map_rgb_f(1., 0.5, 0.5), 12, y,
            ALLEGRO_ALIGN_LEFT, "Shift 1-9 - play sounds reversed");
         y += dy;
         al_draw_text(font, al_map_rgb_f(1., 0.5, 0.5), 12, y,
            ALLEGRO_ALIGN_LEFT, "p - pan the last played sound");
         y += dy;
         al_draw_text(font, al_map_rgb_f(1., 0.5, 0.5), 12, y,
            ALLEGRO_ALIGN_LEFT, "m - play music");
         y += 2 * dy;
         al_draw_text(font, al_map_rgb_f(0.5, 1., 0.5), 12, y,
            ALLEGRO_ALIGN_LEFT, "SOUNDS");
         y += dy;
         for (i = 0; i < argc && i < MAX_SAMPLE_DATA; i++) {
            al_draw_textf(font, al_map_rgb_f(0.5, 1., 0.5), 12, y,
               ALLEGRO_ALIGN_LEFT, "%d - %s", i + 1, argv[i]);
            y += dy;
         }
         al_flip_display();
      }


   for (i = 0; i < argc && i < MAX_SAMPLE_DATA; i++) {
      if (sample_data[i])
         al_destroy_sample(sample_data[i]);
   }
            ALLEGRO_EVENT ev;

            al_wait_for_event(event_queue, &ev);




            if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)

            {

                switch(ev.mouse.button)

                {

                case 1:

                    printf("x:%d y:%d\n",ev.mouse.x, ev.mouse.y);




                    if(ev.mouse.x >= baralho_pos_x &&
        ev.mouse.x <= baralho_pos_x + al_get_bitmap_width(baralho) &&
        ev.mouse.y >= baralho_pos_y &&
        ev.mouse.y <= baralho_pos_y +  al_get_bitmap_height(baralho)){
                        printf("baralho tocado");
                    }

                    if(ev.mouse.x >= botjog_pos_x &&
        ev.mouse.x <= botjog_pos_x + al_get_bitmap_width(botjog) &&
        ev.mouse.y >= botjog_pos_y &&
        ev.mouse.y <= botjog_pos_y+  al_get_bitmap_height(botjog)){
                        printf("botao compra tocado");
char *maoselec[5];

for(a=0;a<7;a++){
        if(carta_click[a]&& cont_selec < 5){
            maoselec[cont_selec]=mao[a];
            cont_selec++;

        }



}



for(a=0;a< cont_selec  ;a++){



            printf("\n %s",maoselec[a]);



}
bool flush=false,sequencia=false;

if(cont_selec==5){
   flush=isflush(maoselec, cont_selec);
   sequencia=issequence(maoselec, cont_selec);

}
   int multiplos=ismultiple(maoselec, cont_selec);

   int fichas,mult;
   printf("\n");

    if(flush && sequencia){
       printf("straight flush");
       fichas = 100;
       mult=8;
   }
    else if(multiplos==4){
       printf("Quadra");
       fichas = 60;
       mult=7;
   }
    else if(multiplos==7){
       printf("Full house");
       fichas = 40;
       mult=4;
   }
    else if(flush){
       printf("Flush");
       fichas = 35;
       mult=4;

   }else if(sequencia){
       printf("straight");
       fichas = 30;
       mult=4;

   }
    else if(multiplos==3){
       printf("Trinca");
       fichas = 30;
       mult=3;
   }
    else if(multiplos==6){
       printf("Dois pares");
       fichas = 20;
       mult=2;
   }
    else if(multiplos==2){
       printf("par");
       fichas = 10;
       mult=2;
   }
   else{
       printf("carta alta");
       fichas = 5;
       mult=1;
   }
   numerar_baralho(maoselec, cont_selec, mao_num);
for(a=0;a<cont_selec;a++)
    fichas+=mao_num[a];

    total+=fichas*mult;
printf("\nSua pontuacao e: %d e seu mult e %d dando um total de %d:",fichas,mult,total);





for(a=0;a<7;a++){

         if(carta_click[a]){
                 redraw = true;
              carta_click[a] =false;
            discarte[disc_ind]=mao[a];
             al_destroy_bitmap(carta[a]);
 carta[a] = NULL;

    if (nmrcartatopo < size) {
printf("pode comprar");


            disc_ind++;
mao[a]=cartas[nmrcartatopo];
nmrcartatopo++;
    sprintf(image_path, "imagens/%s.png", mao[a]);
    printf("\n%s",image_path);
        carta[a] = al_load_bitmap(image_path);
if (!carta[a]) {
    fprintf(stderr, "Failed to load image for carta %d e %s\n", a, mao[a]);
    exit(-1);
}

carta_pos_y[a] = SCREEN_H * 2 - BARALHO_ALTURA * 2;
        }else
        printf("nao pode comprar");
        }


}
cartamaos = 0;
printf("Cartas no discarte:\n");
for(a=0;a<disc_ind;a++)
    printf("%s\n",discarte[a]);
                    }





                    if(ev.mouse.x >= botdisc_pos_x &&
        ev.mouse.x <= botdisc_pos_x + al_get_bitmap_width(botdisc) &&
        ev.mouse.y >= botdisc_pos_y &&
        ev.mouse.y <= botdisc_pos_y+  al_get_bitmap_height(botdisc)){
                        printf("botao descarte tocado");

for(a=0;a<7;a++){
        if(carta_click[a]){
              carta_click[a] =false;
            discarte[disc_ind]=mao[a];
             al_destroy_bitmap(carta[a]);
 carta[a] = NULL;
  if (nmrcartatopo < size) {



            disc_ind++;
mao[a]=cartas[nmrcartatopo];
nmrcartatopo++;
    sprintf(image_path, "imagens/%s.png", mao[a]);
    printf("\n%s",image_path);
        carta[a] = al_load_bitmap(image_path);
if (!carta[a]) {
    fprintf(stderr, "Failed to load image for carta %d e %s\n", a, mao[a]);
    exit(-1);
}
carta_pos_y[a] = SCREEN_H * 2 - BARALHO_ALTURA * 2;

        }}



}
cartamaos = 0;
printf("Cartas no discarte:\n");
for(a=0;a<disc_ind;a++)
    printf("%s\n",discarte[a]);


        }



                        for(a=0;a<7;a++){
                                   if (carta[a] != NULL) {
       if(ev.mouse.x >= carta_pos_x[a] &&
        ev.mouse.x <= carta_pos_x[a] + al_get_bitmap_width(carta[a]) &&
        ev.mouse.y >= carta_pos_y[a] &&
        ev.mouse.y <= carta_pos_y[a] +  al_get_bitmap_height(carta[a])){


                       if(carta_click[a]==false && cartamaos<5){
                        cartamaos++;
                       carta_pos_y[a]-=200;
                       carta_click[a]=true;
                       printf("carta %s selecionada", mao[a]);
        }

                    else if(carta_click[a]==true){

                       carta_pos_y[a]+=200;
                       carta_click[a]=false;
                       cartamaos--;
                       printf("carta %s deselecionada", mao[a]);
                    }
break;
                        }

                }}
                  if(cartamaos==0){
                 redraw = true;
        botdisc=al_load_bitmap("imagens/negbotao_discartarmao.png");
        botjog = al_load_bitmap("imagens/negbotao_jogarmao.png");
            }
            else{
                 redraw = true;
        botdisc=al_load_bitmap("imagens/botao_discartarmao.png");
        botjog = al_load_bitmap("imagens/botao_jogarmao.png");
            }


                }

            }else if(ev.type == ALLEGRO_EVENT_TIMER)

            {

                redraw=true;



            }else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)

            {

                switch(ev.keyboard.keycode)

                {





                case ALLEGRO_KEY_ESCAPE:

                    return 0;

                    break;

                }

            }



            else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)

            {

                break;

            }



            if(redraw && al_is_event_queue_empty(event_queue))

            {


  sprintf(texto, "fichas: %d",total);
    al_draw_text(font, al_map_rgb(255, 255, 255), 20, 20, ALLEGRO_ALIGN_LEFT, texto);
      sprintf(texto, "%d/7",cartamaos);
    al_draw_text(font, al_map_rgb(255, 255, 255), 440, 640, ALLEGRO_ALIGN_LEFT, texto);
          sprintf(texto, "%d/%d",size-nmrcartatopo,size);
    al_draw_text(font, al_map_rgb(255, 255, 255), 800, 200, ALLEGRO_ALIGN_LEFT, texto);
              sprintf(texto, "%d/%d",size-nmrcartatopo,size);
    al_draw_text(font, al_map_rgb(255, 255, 255), 800, 200, ALLEGRO_ALIGN_LEFT, texto);
              sprintf(texto, "%d/%d",size-nmrcartatopo,size);
    al_draw_text(font, al_map_rgb(255, 255, 255), 800, 200, ALLEGRO_ALIGN_LEFT, texto);


        al_flip_display();

                redraw = false;



                al_clear_to_color(al_map_rgb(0,100,0));



               al_draw_scaled_bitmap(
        background,
        0, 0,                                  // origem da imagem (canto superior esquerdo)
        al_get_bitmap_width(background),       // largura da imagem original
        al_get_bitmap_height(background),      // altura da imagem original
        0, 0,                                  // onde desenhar na tela (canto superior esquerdo)
        SCREEN_W, SCREEN_H,                    // nova largura e altura (tamanho da tela)
        0                                      // flags
    );



                al_draw_bitmap(baralho, baralho_pos_x, baralho_pos_y, 0);

                al_draw_bitmap(botjog, botjog_pos_x, botjog_pos_y, 0);

                al_draw_bitmap(botdisc, botdisc_pos_x, botdisc_pos_y, 0);
                for( a=0;a<7;a++){
if(carta[a]!=NULL){
                al_draw_bitmap(carta[a], carta_pos_x[a], carta_pos_y[a], 0);
                }}


            }

        }
        al_destroy_timer(timer);

        al_destroy_display(display);

        al_destroy_event_queue(event_queue);



        return 0;

    }

/* Sistema de embaralhar um array pego de " Asmodiel's link to Ben Pfaff's Writings"
https://benpfaff.org/writings/clc/shuffle.html
*/
void shuffle(char **array, size_t n)
{
    if (n > 1)
    {
        size_t i;
        for (i = 0; i < n - 1; i++)
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          char *t =  array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}




bool isflush(char **array, size_t n){
    int i;
for(i=1; i<n;i++){
    if(array[i-1][1] != array[i][1]){
        return false;
    }
}

    return true;
    //Nesta função um for percorre todo o array, pelo jeito que as cartas são escritas(rei de copas sendo por exemplo:RC), a função verifica se todos os segundos digitos do array são iguais, se não ele para de percorrer e retorna negativo, do contrario irá percorrer todo o array e retornar positivo

}

int ismultiple(char **array, size_t n) {

char charr[5] = {0,0,0,0,0},ra;

int count[5] = {0,0,0,0,0},ir, nmrd = 0;

bool encontrado,par=false,dpares=false,trinca=false,fullhouse=false;


int k;
for ( k = 0; k < n; k++) {
ra = array[k][0];
encontrado = false;
ir = -1;

for ( k = 0; k < nmrd; k++) {
 if (charr[k] == ra) {
encontrado = true;
ir = k;
break;
}
}

if (encontrado) {
count[ir]++;
} else {
if (nmrd < n) {
charr[nmrd] = ra;
count[nmrd] = 1;
nmrd++;
}
}

}


int maior=1;

for( k = 0; k < nmrd; k++) {
    if(count[k] > maior) {
        maior = count[k];
    }
    if(count[k] == 2 && par==false) {
        par=true;
    }
    else if(count[k] == 2 && par==true) {
        dpares=true;
    }
    else if (count[k] == 3) {
        trinca=true;
    }
    if(trinca==true&&par==true){
        fullhouse=true;
    }

//nesse encadeamento de if, é criado uma variavel maior, sendo ela igual o contador de repetições, tambem é verificado se existe pares e trincas, para verificar se existe um fullhouse, que é quando uma mão possui um par e uma trinca
}

if(fullhouse && maior <4){
return 7; //7 é o codigo para fullhouse
}
else if(dpares){
return 6; //6 é o codigo para dois pares
}
else{
return maior;
}
//aqui é usado codigos para verificar o tipo de mão e retornar, 1 sendo carta, alta, 
}


bool issequence(char **array, size_t n){
    int mao[5];
    numerar_baralho(array, 5,mao);
    
    /*Nessas duas linhas eu crio um array de inteiros, pra simbolizar a versão do baralho usando apenas seus numeros para a comparação    */
    bool sequencia=true;


qsort(mao, n, sizeof(int), comparador);
//Aqui eu uso a função qsort da biblioteca stdlib  para ordenar o baralho de menor para maior
int k;

     	for( k = 0; k < n-1; k++) {
if(mao[k]+1!=mao[k+1]){
    sequencia=false;
    break;
}

}

    return sequencia;
    //neste conjunto de funções eu uso o array ordenado do baralho e percorre ele, caso encontre algum elemento que pule mais de um valor(ou seja, a mão não terá uma sequencia), ele ira parar a execução do for que percorre todo o baralho, retornando falso, caso o contrario ele apenas percorre todo array e retorna verdadeiro   
}



/*Sistema de comparador para o qsort pego do tutorial: https://www.tutorialspoint.com/c_standard_library/c_function_qsort.htm 
*/
int comparador(const void *a, const void *b) {
   return ( *(int*)a - *(int*)b );
}




void numerar_baralho(char **array, size_t n, int* maonumerada){
int i;
    for( i=0;i<n;i++){
    if(array[i][0]=='0')
       maonumerada[i]=10;
    else if(array[i][0]=='J')
        maonumerada[i]=11;
    else if(array[i][0]=='Q')
        maonumerada[i]=12;
    else if(array[i][0]=='K')
        maonumerada[i]=13;
    else if(array[i][0]=='A')
        maonumerada[i]=14;

    else{
        maonumerada[i]=array[i][0]  - '0';
    }
    }
}
