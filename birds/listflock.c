#include "birds.h"
#include <glib.h>

GList *flock;
int hawks, doves;

void flock_plays(){ g_list_foreach(flock, bird_plays, NULL); }

void add_to_flock(bird* b){ flock = g_list_prepend(flock, b); }

void free_bird(bird* b){
    flock   = g_list_remove(flock, b);
    free(b); }

bird * find_opponent(int n){ return g_list_nth_data(flock, n); }

void wealth_foreach(void *in, void *total){
    *((int*)total)   += ((bird*)in)->wealth;  }

int flock_wealth(){
  int   total   = 0;
    g_list_foreach(flock, wealth_foreach, &total);
    return total; }

int flock_size(){ return g_list_length(flock); }

void bird_count(void *in, void *v){
  bird *b   = in;
    if (b->type == 'h')
        hawks   ++;
    else doves   ++;
}

double count(int period){
  int   total_wealth    =flock_wealth();
    hawks   = doves   = 0;
    g_list_foreach(flock, birth_or_death, &total_wealth);
    g_list_foreach(flock, bird_count, NULL);
    printf("%i\t%i\t%i\n", period, hawks, doves);
    return (doves+0.0)/hawks;}

void flock_init(){ flock  = NULL; }
