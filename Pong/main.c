
    /* Copyright (C) 2016 Marcelo Serrano Zanetti - All Rights Reserved

     * Licensed under the GNU GPL V3.0 license. All conditions apply.

     * Powered by Allegro: http://liballeg.org/license.html

     */




    #include <stdio.h>

    #include <allegro5/allegro.h>

    #include <allegro5/allegro_image.h>
    #include <allegro5/allegro_font.h>
    #include <allegro5/allegro_ttf.h>
    #include <allegro5/allegro_primitives.h>
    #include <stdlib.h>
    #include <stdbool.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
    #include <time.h>

void shuffle(char **array, size_t n);
bool isflush(char **array, size_t n);
int ismultiple(char **array, size_t n);
bool issequence(char **array, size_t n);
int comparador(const void *a, const void *b);
void numerar_baralho(char **array, size_t n, int* a);
//declaração de todas as funções utilizadas
    const float FPS = 90;

    const int SCREEN_W = 1024;

    const int SCREEN_H = 768;


    const int BARALHO_LARGURA = 257;

    const int BARALHO_ALTURA = 506;

    const int BOTAO_LARGURA = 257;

    const int BOTAO_ALTURA = 124;
//declaração de largura e altura de dois objetos no jogo, a fim de utilizar eles para alguns parametros de distancia



    int main(int argc, char **argv){
        al_init_font_addon();
    al_init_ttf_addon();

        ALLEGRO_DISPLAY *display = NULL;

        ALLEGRO_EVENT_QUEUE *event_queue = NULL;

        ALLEGRO_TIMER *timer = NULL;



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

        ALLEGRO_FONT *font = al_load_ttf_font("./fontebalatro.ttf", 20, 0);
        // Credito para a fonte: https://managore.itch.io/m6x11
        //declaração de uso de fonte personalizada
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

        if(!al_install_audio())

        {

            fprintf(stderr, "failed to initialize the install audio!\n");

            return -1;

        }

   if(!al_init_acodec_addon())

        {

            fprintf(stderr, "failed to initialize the acordec addon!\n");

            return -1;

        }


            al_reserve_samples(1);
//aqui é feitos as funções pra tocar a musica, sendo primeiro reservado a sample no allegro, tendo apenas um audio
    ALLEGRO_SAMPLE* music = al_load_sample("./audios/OST.ogg");
    //Aqui é declarado que a musica está no diretorio "./audios/OST.ogg" da pasta
    ALLEGRO_SAMPLE_INSTANCE* music_instance = al_create_sample_instance(music);
    //cria a instancia da musica
    al_set_sample_instance_playmode(music_instance, ALLEGRO_PLAYMODE_LOOP);
    //aqui é declarado que a musica estará sempre em loop
    al_attach_sample_instance_to_mixer(music_instance, al_get_default_mixer());
    al_play_sample_instance(music_instance);
    //aqui a musica começa a ser tocada
    bool music_muted = false;
//aqui é usada uma booleana pra declarar quando a musica pode ser tocada ou não
        ALLEGRO_BITMAP *background = NULL;

        ALLEGRO_BITMAP *baralho = NULL;

        ALLEGRO_BITMAP *botjog = NULL;

        ALLEGRO_BITMAP *botdisc = NULL;

        ALLEGRO_BITMAP *carta[7] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL};

        ALLEGRO_BITMAP *menu = NULL;


//declaração dos bitmaps usados pelo allegro


        float baralho_pos_x = SCREEN_W - BARALHO_LARGURA;

        float baralho_pos_y = SCREEN_H/1.5 /  - BARALHO_ALTURA  / 2.0 ;

        float botjog_pos_x = SCREEN_W/2 - BOTAO_LARGURA - 10;

        float botjog_pos_y = SCREEN_H/3 + BARALHO_ALTURA/2.5 ;


      float botdisc_pos_x = SCREEN_W/2 + 10;

        float botdisc_pos_y = SCREEN_H/3 + BARALHO_ALTURA/2.5 ;


      float menu_pos_x = SCREEN_W/4;

        float menu_pos_y = SCREEN_H/4 ;

        float carta_pos_x[7];
        float carta_pos_y[7];
   int a;
        for(a=0;a<7;a++){
                carta_pos_x[a] = SCREEN_W/2 - BARALHO_LARGURA*1.5+ 100*a ;
           carta_pos_y[a] = SCREEN_H*2  - BARALHO_ALTURA*2 ;
        }
//aqui são todos os valores de posições dos objetos


        int click=0;

        int savebvx;

        int savebvy;


        background        = al_load_bitmap("imagens/campo.png");

        baralho=al_load_bitmap("imagens/baralho.png");

        botjog=al_load_bitmap("imagens/negbotao_jogarmao.png");

        botdisc=al_load_bitmap("imagens/negbotao_discartarmao.png");


        menu=al_load_bitmap("imagens/menu.png");
        //Credito para o sprite do menu: https://managore.itch.io/m6x11
// Aqui é declarado os sprites usados para cada objeto
         char *cartas[] = {
 "AO", "AE", "AC", "AP", "2O", "2E", "2C", "2P","3O", "3E", "3C", "3P","4O", "4E", "4C", "4P","5O", "5E", "5C", "5P","6O", "6E", "6C", "6P","7O", "7E", "7C", "7P","8O", "8E", "8C", "8P","9O", "9E", "9C", "9P","0O", "0E", "0C", "0P","JO", "JE", "JC", "JP","QO", "QE", "QC", "QP","KO", "KE", "KC", "KP"
};
//aqui é declarado as cartas utilizadas num vetor de strings, sendo elas representadas com 'numero/letra''letra do naipe da carta', por exemplo 5 de copas é mostrada como "5C"
int mao_num[5];

    int size = sizeof(cartas) / sizeof(cartas[0]);


    srand(time(NULL));
        shuffle(cartas,size);
        //aqui é declarado o tamando do vetor, e em seguida usa a função shuffle para embaralhar o vetor
int nmrcartatopo=0, disc_ind=0,cartamaos=0, total=0,cont_selec=0,jogadas=4,descartes=3;

char *mao[7], *discarte[52],  image_path[50],texto[50],val_mao[20];
bool carta_click[7]={false,false,false,false,false,false,false},gameover=false, apagaprimeiramensagem=false;
 //declaração de todas as variaveis importantes usadas no jogo



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


                               if(!menu)

        {

            fprintf(stderr, "falhou ao criar o menu bitmap!\n");

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
https://managore.itch.io/m6x11


        al_clear_to_color(al_map_rgb(0,0,0));



        al_flip_display();



        al_start_timer(timer);



 while(1)

        {

if(jogadas==0)
    gameover=true;


            ALLEGRO_EVENT ev;

            al_wait_for_event(event_queue, &ev);




            if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && !gameover && apagaprimeiramensagem)

            {

                switch(ev.mouse.button)

                {

                case 1:

                    printf("x:%d y:%d\n",ev.mouse.x, ev.mouse.y);

char *maoselec[5];

   int fichas,mult;


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
  }
                        }
                    for(a=0;a<7;a++){
        if(carta_click[a]&& cont_selec < 5){
            maoselec[cont_selec]=mao[a];
            cont_selec++;

        }



}

                 bool flush=false,sequencia=false;
                 if(cont_selec==5){
   flush=isflush(maoselec, cont_selec);
   sequencia=issequence(maoselec, cont_selec);

}
   int multiplos=ismultiple(maoselec, cont_selec);if(flush && sequencia){
       strcpy(val_mao, "straight flush");
       fichas = 100;
       mult=8;
   }
    else if(multiplos==4){
       strcpy(val_mao, "Quadra");
       fichas = 60;
       mult=7;
   }
    else if(multiplos==7){
       strcpy(val_mao, "Full house");
       fichas = 40;
       mult=4;
   }
    else if(flush){
       strcpy(val_mao, "Flush");
       fichas = 35;
       mult=4;

   }else if(sequencia){
       strcpy(val_mao, "straight");
       fichas = 30;
       mult=4;

   }
    else if(multiplos==3){
       strcpy(val_mao, "Trinca");
       fichas = 30;
       mult=3;
   }
    else if(multiplos==6){
       strcpy(val_mao, "Dois pares");
       fichas = 20;
       mult=2;
   }
    else if(multiplos==2){
       strcpy(val_mao, "par");
       fichas = 10;
       mult=2;
   }
   else{
       strcpy(val_mao, "carta alta");
       fichas = 5;
       mult=1;
   }


   printf("\n");

int cont_res=cont_selec;
   cont_selec=0;



                    if(ev.mouse.x >= baralho_pos_x &&
        ev.mouse.x <= baralho_pos_x + al_get_bitmap_width(baralho) &&
        ev.mouse.y >= baralho_pos_y &&
        ev.mouse.y <= baralho_pos_y +  al_get_bitmap_height(baralho)){
                        printf("baralho tocado");
                        music_muted=!music_muted;
                         if (music_muted)
                {
                    al_set_sample_instance_gain(music_instance, 0.0);
                } else {
                    al_set_sample_instance_gain(music_instance, 1.0);
                }
                    }

                    if(ev.mouse.x >= botjog_pos_x &&
        ev.mouse.x <= botjog_pos_x + al_get_bitmap_width(botjog) &&
        ev.mouse.y >= botjog_pos_y &&
        ev.mouse.y <= botjog_pos_y+  al_get_bitmap_height(botjog)){
                        printf("botao compra tocado");





for(a=0;a< cont_res  ;a++){



            printf("\n %s",maoselec[a]);



}

   numerar_baralho(maoselec, cont_res, mao_num);
for(a=0;a<cont_res;a++){
    fichas+=mao_num[a];
printf("%d\n",mao_num[a]);
}
    total+=fichas*mult;
printf("\nSua pontuacao e: %d e seu mult e %d dando um total de %d:",fichas,mult,total);
jogadas--;





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
        ev.mouse.y <= botdisc_pos_y+  al_get_bitmap_height(botdisc)&&descartes!=0&&cartamaos!=0){
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
descartes--;

        }



        if (cartamaos == 0 || descartes == 0) {
    botdisc = al_load_bitmap("imagens/negbotao_discartarmao.png");
} else {
    botdisc = al_load_bitmap("imagens/botao_discartarmao.png");
}

if (cartamaos == 0) {
    botjog = al_load_bitmap("imagens/negbotao_jogarmao.png");
} else {
    botjog = al_load_bitmap("imagens/botao_jogarmao.png");
}

redraw = true;



                }

            }else if(ev.type == ALLEGRO_EVENT_TIMER)

            {

                redraw=true;



            }else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)

            {

                switch(ev.keyboard.keycode)

                {





                case ALLEGRO_KEY_SPACE:
if(gameover)
                    return 0;

                    break;
                case ALLEGRO_KEY_M:
 apagaprimeiramensagem=!apagaprimeiramensagem;

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
    sprintf(texto, "%s",val_mao);
    al_draw_text(font, al_map_rgb(255, 255, 255), 20, 40, ALLEGRO_ALIGN_LEFT, texto);

      sprintf(texto, "%d/7",cartamaos);
    al_draw_text(font, al_map_rgb(255, 255, 255), 440, 640, ALLEGRO_ALIGN_LEFT, texto);
          sprintf(texto, "%d/%d",size-nmrcartatopo,size);
    al_draw_text(font, al_map_rgb(255, 255, 255), 800, 200, ALLEGRO_ALIGN_LEFT, texto);

          sprintf(texto, "Maos: %d",jogadas);
    al_draw_text(font, al_map_rgb(255, 255, 255), 800, 525, ALLEGRO_ALIGN_LEFT, texto);
          sprintf(texto, "Descartes: %d",descartes);
    al_draw_text(font, al_map_rgb(255, 255, 255), 800, 575, ALLEGRO_ALIGN_LEFT, texto);

if(gameover){
          sprintf(texto, "Voce perdeu, com uma pontuacao de: %d fichas.",total);
    al_draw_text(font, al_map_rgb(255, 255, 255), menu_pos_x+50, menu_pos_y+50, ALLEGRO_ALIGN_LEFT, texto);
    al_draw_text(font, al_map_rgb(255, 255, 255), menu_pos_x+50, menu_pos_y+70, ALLEGRO_ALIGN_LEFT, "Aperte espaco para fechar");
}

if(!apagaprimeiramensagem){
    al_draw_text(font, al_map_rgb(255, 255, 255), menu_pos_x+50, menu_pos_y+50, ALLEGRO_ALIGN_LEFT, "Bem vindo ao Baluistro!, aqui estao as regras:");
    al_draw_text(font, al_map_rgb(255, 255, 255), menu_pos_x+50, menu_pos_y+70, ALLEGRO_ALIGN_LEFT, "Jogue maos de poker, voce tem direito a jogar elas 4 vezes");
    al_draw_text(font, al_map_rgb(255, 255, 255), menu_pos_x+50, menu_pos_y+90, ALLEGRO_ALIGN_LEFT, "com 3 descartes, cada mao possui um valor, sendo eles a");
    al_draw_text(font, al_map_rgb(255, 255, 255), menu_pos_x+50, menu_pos_y+110, ALLEGRO_ALIGN_LEFT, "quantidade de pontos base, e o multiplicador");
    al_draw_text(font, al_map_rgb(255, 255, 255), menu_pos_x+50, menu_pos_y+130, ALLEGRO_ALIGN_LEFT, "cada carta adicionada na sua mao adiciona seu");
    al_draw_text(font, al_map_rgb(255, 255, 255), menu_pos_x+50, menu_pos_y+150, ALLEGRO_ALIGN_LEFT, "valor na pontuacao base.");
    al_draw_text(font, al_map_rgb(255, 255, 255), menu_pos_x+50, menu_pos_y+170, ALLEGRO_ALIGN_LEFT, "Por exemplo: Voce joga a mao de um par");
    al_draw_text(font, al_map_rgb(255, 255, 255), menu_pos_x+50, menu_pos_y+190, ALLEGRO_ALIGN_LEFT, "com as cartas A de copas e um A de espadas");
    al_draw_text(font, al_map_rgb(255, 255, 255), menu_pos_x+50, menu_pos_y+210, ALLEGRO_ALIGN_LEFT, "o par possui pontuacao base 10 e mult 2, cada A vale 14");
    al_draw_text(font, al_map_rgb(255, 255, 255), menu_pos_x+50, menu_pos_y+230, ALLEGRO_ALIGN_LEFT, "adicionando 28 dos dois As na pontuacao base da 38");
    al_draw_text(font, al_map_rgb(255, 255, 255), menu_pos_x+50, menu_pos_y+250, ALLEGRO_ALIGN_LEFT, "multiplicado por 2 da uma pontuacao de 76 ");
    al_draw_text(font, al_map_rgb(255, 255, 255), menu_pos_x+50, menu_pos_y+270, ALLEGRO_ALIGN_LEFT, "Aperte M pra comecar a apostar!");
    al_draw_text(font, al_map_rgb(255, 255, 255), menu_pos_x+50, menu_pos_y+290, ALLEGRO_ALIGN_LEFT, "(Dica: aperte M pra abrir e fechar essa aba enquanto joga!)");




}
        al_flip_display();

                redraw = false;



                al_clear_to_color(al_map_rgb(0,100,0));



               al_draw_scaled_bitmap(
        background,
        0, 0,
        al_get_bitmap_width(background),
        al_get_bitmap_height(background),
        0, 0,
        SCREEN_W, SCREEN_H,
        0
    );



                al_draw_bitmap(baralho, baralho_pos_x, baralho_pos_y, 0);

                al_draw_bitmap(botjog, botjog_pos_x, botjog_pos_y, 0);

                al_draw_bitmap(botdisc, botdisc_pos_x, botdisc_pos_y, 0);
                for( a=0;a<7;a++){
if(carta[a]!=NULL){
                al_draw_bitmap(carta[a], carta_pos_x[a], carta_pos_y[a], 0);
                }}
if(gameover||!apagaprimeiramensagem)
                al_draw_bitmap(menu, menu_pos_x, menu_pos_y, 0);


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

//aqui dois arrays são criados, um para chars e outros pra contadores, sendo eles pra representar partes do vetor iguais
bool encontrado,par=false,dpares=false,trinca=false,fullhouse=false;


int k,j;
for ( k = 0; k < n; k++) {
ra = array[k][0];
encontrado = false;
ir = -1;

for ( j = 0; j < nmrd; j++) {
 if (charr[j] == ra) {
encontrado = true;
ir = j;
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

//aqui um for é iniciado percorrendo todo o vetor, que guarda o valor dele no inicio, e em seguida olha todo o vetor novamente pelo valor nmrd, pra quando ele "olhar" o array, não pegar valor antes dele
//caso seja encontrado um numero que ja tenha sido encontrado anteriormente ele é salvo no charr e no contador, e em seguida ele continua a procura
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
//Nesta função é usado dois arrays, um de strings, e outro de inteiros, a função analisa o primeiro caracter da string, caso seja um '0', que representa o 10, é dado o valor de 10 pro array numerico, caso sejam letras ele dá um valor que representa o valor delas no jogo no array de numeros, caso sejam algum outro numero no array de char, é dado um -'0' pra demonstrar que não é mais um carater, mas sim um numero.
