#include "birds.h"
#include <apophenia/headers.h>

gsl_rng *r;

int     periods             = 300;
int     initial_pop         = 100;
int     id_count            = 0;

void play_pd_game(bird *row, bird *col){
  float     resource    = 2,
            conflict    = 2.01;
  if (row->type == 'd' && col->type == 'h')
        col->wealth += resource;
  else if (row->type == 'h' && col->type == 'd')
        row->wealth += resource;
  else if (row->type == 'd' && col->type == 'd'){
        col->wealth += resource/2;
        row->wealth += resource/2;
        }
  else if (row->type == 'h' && col->type == 'h'){
        col->wealth += (resource-conflict)/2;
        row->wealth += (resource-conflict)/2;
  }
}

void bird_plays(void *in, void *v){
  bird *other;
    while(!(other = find_opponent((int)(gsl_rng_uniform(r)*id_count))));
    if (!(in==other))
        play_pd_game(in, other);
}

bird *new_chick(bird *parent){
  bird  *out    = malloc(sizeof(*out));
    if (parent)
        out->type  = parent->type;
    else{
        if (gsl_rng_uniform(r) > 0.5)
            out->type  = 'd';
        else
            out->type  = 'h';
    }
    out->wealth = 5* gsl_rng_uniform(r);
    out->id     = id_count;
    id_count    ++;
    return out;
}

void birth_or_death(void *in, void *t){
  bird  *b              = in; //cast void to bird;
  int   *total_wealth   = t;
    if (b->wealth*20./ *total_wealth >= gsl_rng_uniform(r))
        add_to_flock(new_chick(b));
    if (b->wealth*800./ *total_wealth <= gsl_rng_uniform(r))
        free_bird(b);
}

void startup(int initial_flock_size){
    flock_init();
    r   = apop_rng_alloc(972);
    for(int i=0; i< initial_flock_size; i++)
        add_to_flock(new_chick(NULL));
}

gsl_vector * run(){
    startup(initial_pop);
    for (int i=0; i< periods; i++){
        flock_plays();
        count(i);
    }
    return 0;
}
