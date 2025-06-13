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
    #include <time.h>
void shuffle(char **array, size_t n);
bool isflush(char **array, size_t n);
int ismultiple(char **array, size_t n);
bool issequence(char **array, size_t n);
int comparador(const void *a, const void *b);

    const float FPS = 90;

    const int SCREEN_W = 1024;

    const int SCREEN_H = 768;

    const int BOLA_TAMANHO = 77;

    const int REBATEDOR_LARGURA = 257;

    const int REBATEDOR_ALTURA = 506;

    const int BARALHO_LARGURA = 257;

    const int BARALHO_ALTURA = 506;

    const int BOTAOJOG_LARGURA = 257;

    const int BOTAOJOG_ALTURA = 124;



    int main(int argc, char **argv)

    {al_init_font_addon();
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

        ALLEGRO_FONT *font = al_create_builtin_font();
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

        ALLEGRO_BITMAP *bola = NULL;

        ALLEGRO_BITMAP *rebatedorEsquerda = NULL;

        ALLEGRO_BITMAP *rebatedorDireita = NULL;

        ALLEGRO_BITMAP *background = NULL;

        ALLEGRO_BITMAP *baralho = NULL;

        ALLEGRO_BITMAP *botjog = NULL;

        ALLEGRO_BITMAP *carta[7] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL};



        float bola_pos_x = SCREEN_W / 2.0 - BOLA_TAMANHO / 2.0;

        float bola_pos_y = SCREEN_H / 2.0 - BOLA_TAMANHO / 2.0;

        float bola_vx = -4;

        float bola_vy = -4;



        float rebatedorEsquerda_pos_x = 0;

        float rebatedorEsquerda_pos_y = SCREEN_H / 2.0 - REBATEDOR_ALTURA / 2.0;

        float rebatedorEsquerda_vy = 0;



        float rebatedorDireita_pos_x = SCREEN_W - REBATEDOR_LARGURA;

        float rebatedorDireita_pos_y = SCREEN_H / 2.0 - REBATEDOR_ALTURA / 2.0;

        float rebatedorDireita_vy = 0;


        float baralho_pos_x = SCREEN_W - BARALHO_LARGURA;

        float baralho_pos_y = SCREEN_H/1.5 /  - BOLA_TAMANHO / 2.0 ;

        float botjog_pos_x = SCREEN_W/2 -BARALHO_LARGURA/2;

        float botjog_pos_y = SCREEN_H/3 + BARALHO_ALTURA/2.5 ;

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



        bola              =  al_load_bitmap("imagens/bola.png");

        rebatedorEsquerda = al_load_bitmap("imagens/maradona.png");

        rebatedorDireita  = al_load_bitmap("imagens/pele.png");

        background        = al_load_bitmap("imagens/campo.png");

        baralho=al_load_bitmap("imagens/baralho.png");

        botjog=al_load_bitmap("imagens/botao_jogarmao.png");

         char *cartas[] = {
 "AO", "AE", "AC", "AP", "2O", "2E", "2C", "2P","3O", "3E", "3C", "3P","4O", "4E", "4C", "4P","5O", "5E", "5C", "5P","6O", "6E", "6C", "6P","7O", "7E", "7C", "7P","8O", "8E", "8C", "8P","9O", "9E", "9C", "9P","0O", "0E", "0C", "0P","JO", "JE", "JC", "JP","QO", "QE", "QC", "QP","KO", "KE", "KC", "KP"
};

    int size = sizeof(cartas) / sizeof(cartas[0]);


    srand(time(NULL));
        shuffle(cartas,size);
int nmrcartatopo=0;
char *mao[7];
char *discarte[52];
int disc_ind=0;
char image_path[50];
bool carta_click[7]={false,false,false,false,false,false,false};
int cartamaos=1;

int possel=0;


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

        if(!bola)

        {

            fprintf(stderr, "falhou ao criar a bola bitmap!\n");

            al_destroy_display(display);

            al_destroy_timer(timer);

            return -1;

        }

        if(!rebatedorEsquerda)

        {

            fprintf(stderr, "falhou ao criar o rebatedoresquerda bitmap!\n");

            al_destroy_display(display);

            al_destroy_timer(timer);

            al_destroy_bitmap(bola);

            return -1;

        }

        if(!rebatedorDireita)

        {

            fprintf(stderr, "falhou ao criar o rebatedordireita bitmap!\n");

            al_destroy_display(display);

            al_destroy_timer(timer);

            al_destroy_bitmap(bola);

            al_destroy_bitmap(rebatedorEsquerda);

            return -1;

        }

        if(!background)

        {

            fprintf(stderr, "falhou ao criar o background bitmap!\n");

            al_destroy_display(display);

            al_destroy_timer(timer);

            al_destroy_bitmap(bola);

            al_destroy_bitmap(rebatedorEsquerda);

            al_destroy_bitmap(rebatedorDireita);

            return -1;

        }


        if(!baralho)

        {

            fprintf(stderr, "falhou ao criar o baralho bitmap!\n");

            al_destroy_display(display);

            al_destroy_timer(timer);

            al_destroy_bitmap(bola);

            al_destroy_bitmap(rebatedorEsquerda);

            al_destroy_bitmap(rebatedorDireita);

            return -1;

        }

                if(!botjog)

        {

            fprintf(stderr, "falhou ao criar o botao de jogar carta bitmap!\n");

            al_destroy_display(display);

            al_destroy_timer(timer);

            al_destroy_bitmap(bola);

            al_destroy_bitmap(rebatedorEsquerda);

            al_destroy_bitmap(rebatedorDireita);

            return -1;

        }
        if(!carta[0])

        {

            fprintf(stderr, "falhou ao criar a carta bitmap!\n");

            al_destroy_display(display);

            al_destroy_timer(timer);

            al_destroy_bitmap(bola);

            al_destroy_bitmap(rebatedorEsquerda);

            al_destroy_bitmap(rebatedorDireita);

            return -1;

        }

        al_set_target_bitmap(al_get_backbuffer(display));



        event_queue = al_create_event_queue();

        if(!event_queue)

        {

            fprintf(stderr, "failed to create event_queue!\n");

            al_destroy_bitmap(bola);

            al_destroy_bitmap(rebatedorEsquerda);

            al_destroy_bitmap(rebatedorDireita);

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



        while(1)

        {

            ALLEGRO_EVENT ev;

            al_wait_for_event(event_queue, &ev);



            if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)

            {

                switch(ev.mouse.button)

                {

                case 1:

                    printf("x:%d y:%d\n",ev.mouse.x, ev.mouse.y);

                    if(click==0)

                    {

                        savebvx=bola_vx;

                        savebvy=bola_vy;

                        bola_vx=0;

                        bola_vy=0;

                        click=1;

                    }

                    else

                    {

                        bola_vx=savebvx;

                        bola_vy=savebvy;

                        click=0;

                    }


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
                        printf("botao tocado");
char *maoselec[5];
int cont_selec=0;

for(a=0;a<7;a++){
        if(carta_click[a]){
            maoselec[cont_selec]=mao[a];
            cont_selec++;

        }



}

for(a=0;a<cont_selec;a++){



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

printf("\nSua pontuacao e: %d e seu mult e %d dando um total de %d:",fichas,mult,fichas*mult);

for(a=0;a<7;a++){
        if(carta_click[a]){
              carta_click[a] =false;
            discarte[disc_ind]=maoselec[a];
            disc_ind++;
             al_destroy_bitmap(carta[a]);
mao[a]=cartas[nmrcartatopo];
nmrcartatopo++;
    sprintf(image_path, "imagens/%s.png", mao[a]);
    printf("\n%s",image_path);
        carta[a] = al_load_bitmap(image_path);
if (!carta[a]) {
    fprintf(stderr, "Failed to load image for carta %d e %s\n", a, mao[a]);
    exit(-1);
}
        }



}


                    }



                        for(a=0;a<7;a++){
       if(ev.mouse.x >= carta_pos_x[a] &&
        ev.mouse.x <= carta_pos_x[a] + al_get_bitmap_width(carta[a]) &&
        ev.mouse.y >= carta_pos_y[a] &&
        ev.mouse.y <= carta_pos_y[a] +  al_get_bitmap_height(carta[a])){


                       if(carta_click[a]==false && cartamaos<=5){
                        cartamaos++;
                       carta_pos_y[a]-=200;
                       carta_click[a]=true;
                       possel++;
                       printf("carta %s selecionada", mao[a]);
        }

                    else if(carta_click[a]==true){

                       carta_pos_y[a]+=200;
                       carta_click[a]=false;
                       possel--;
                       cartamaos--;
                       printf("carta %s deselecionada", mao[a]);
                    }

                        }

                }



            }}else if(ev.type == ALLEGRO_EVENT_TIMER)

            {

                if(bola_pos_y < 0 || bola_pos_y > SCREEN_H - BOLA_TAMANHO)

                {

                    bola_vy = -bola_vy;

                }



                if(bola_pos_x < 0 || bola_pos_x > SCREEN_W - BOLA_TAMANHO)

                {

                    bola_pos_x = SCREEN_W / 2.0 - BOLA_TAMANHO / 2.0;

                    bola_pos_y = SCREEN_H / 2.0 - BOLA_TAMANHO / 2.0;

                    bola_vx = -4, bola_vy = -4;

                }



                if(bola_pos_x <= rebatedorEsquerda_pos_x + REBATEDOR_LARGURA)

                    if(bola_pos_y+BOLA_TAMANHO>=rebatedorEsquerda_pos_y)

                        if(bola_pos_y-BOLA_TAMANHO<=rebatedorEsquerda_pos_y+REBATEDOR_ALTURA)

                            bola_vx = -bola_vx;



                if(bola_pos_x + BOLA_TAMANHO >= rebatedorDireita_pos_x )

                    if(bola_pos_y+BOLA_TAMANHO>=rebatedorDireita_pos_y)

                        if(bola_pos_y-BOLA_TAMANHO<=rebatedorDireita_pos_y+REBATEDOR_ALTURA)

                            bola_vx = -bola_vx;



                bola_pos_x              += bola_vx;

                bola_pos_y              += bola_vy;

                rebatedorEsquerda_pos_y += rebatedorEsquerda_vy;

                rebatedorDireita_pos_y  += rebatedorDireita_vy;

                redraw = true;

            }

            else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)

            {

                switch(ev.keyboard.keycode)

                {

                case ALLEGRO_KEY_UP:

                    rebatedorDireita_vy=-4;

                    break;



                case ALLEGRO_KEY_DOWN:

                    rebatedorDireita_vy=4;

                    break;



                case ALLEGRO_KEY_W:

                    rebatedorEsquerda_vy=-4;

                    break;

                case ALLEGRO_KEY_S:

                    rebatedorEsquerda_vy=4;

                    break;





                case ALLEGRO_KEY_ESCAPE:

                    return 0;

                    break;

                }

            }

            else if(ev.type == ALLEGRO_EVENT_KEY_UP)

            {

                switch(ev.keyboard.keycode)

                {

                case ALLEGRO_KEY_UP:

                case ALLEGRO_KEY_DOWN:

                    rebatedorDireita_vy=0;

                    break;



                case ALLEGRO_KEY_W:

                case ALLEGRO_KEY_S:

                    rebatedorEsquerda_vy=0;

                    break;

                }

            }

            else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)

            {

                break;

            }



            if(redraw && al_is_event_queue_empty(event_queue))

            {

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

                al_draw_bitmap(rebatedorEsquerda,rebatedorEsquerda_pos_x, rebatedorEsquerda_pos_y, 0);

                al_draw_bitmap(rebatedorDireita,rebatedorDireita_pos_x, rebatedorDireita_pos_y, 0);

                al_draw_bitmap(bola, bola_pos_x, bola_pos_y, 0);

                al_draw_bitmap(baralho, baralho_pos_x, baralho_pos_y, 0);
                al_draw_bitmap(botjog, botjog_pos_x, botjog_pos_y, 0);
                for( a=0;a<7;a++){

                al_draw_bitmap(carta[a], carta_pos_x[a], carta_pos_y[a], 0);
                }
    char texto[50];
    sprintf(texto, "x:%.1f y:%.1f",rebatedorEsquerda_pos_y, rebatedorDireita_pos_y);
    al_draw_text(font, al_map_rgb(255, 255, 255), 20, 20, ALLEGRO_ALIGN_LEFT, texto);
                al_flip_display();

            }

        }



        al_destroy_bitmap(bola);

        al_destroy_bitmap(rebatedorEsquerda);

        al_destroy_bitmap(rebatedorDireita);

        al_destroy_timer(timer);

        al_destroy_display(display);

        al_destroy_event_queue(event_queue);



        return 0;

    }

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

}

int ismultiple(char **array, size_t n) {

char charr[5] = {0},ra;

int count[5] = {0},ir, nmrd = 0;

bool encontrado,par=false,dpares=false,trinca=false,fullhouse=false;


int i,j,k;
for ( i = 0; i < n; i++) {
ra = array[i][0];
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
if (nmrd < 5) {
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
}


bool issequence(char **array, size_t n){
    int mao[5];
    numerar_baralho(array, 5,mao);
    bool sequencia=true;


qsort(mao, n, sizeof(int), comparador);
int k;
     	for( k = 0; k < n-1; k++) {
if(mao[k]+1!=mao[k+1]){
    sequencia=false;
    break;
}

}

    return sequencia;
}




int comparador(const void *a, const void *b) {
   return ( *(int*)a - *(int*)b );
}




void numerar_baralho(char **array, size_t n, int* maonumerada){
int i;
    for( i=0;i<n;i++){
    if(array[i][0]=='0')
       maonumerada[i]=10;
    else if(array[i][0]=='V')
        maonumerada[i]=11;
    else if(array[i][0]=='D')
        maonumerada[i]=12;
    else if(array[i][0]=='R')
        maonumerada[i]=13;
    else if(array[i][0]=='A')
        maonumerada[i]=14;

    else{
        maonumerada[i]=array[i][0]  - '0';
    }
    }
}
