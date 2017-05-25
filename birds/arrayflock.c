#include "birds.h"

bird *flock;
int   size_of_flock, hawks, doves;

void flock_plays(){
    for (int i=0; i< size_of_flock; i++)
        if (flock[i].id >= 0)
            bird_plays(&(flock[i]), NULL); }

void add_to_flock(bird* b){
    size_of_flock       = b->id;
    flock               = realloc(flock, sizeof(bird)*(size_of_flock+1));
    memcpy(&(flock[b->id]), b, sizeof(bird));
    free(b); }

void free_bird(bird* b){ b->id = -1; }

bird * find_opponent(int n){
    if (flock[n].id >= 0)
        return &(flock[n]);
    else return NULL; }

int flock_size(){ return size_of_flock; }

int flock_wealth(){
  int i, total =0;
    for (i=0; i< size_of_flock; i++)
        if (flock[i].id >= 0)
            total   += flock[i].wealth;
    return total; }

double count(int period){
  int   i, tw   = flock_wealth();
    hawks   = doves   = 0;
    for(i=0; i< size_of_flock; i++)
        if (flock[i].id>=0)
            birth_or_death(&(flock[i]), &tw);
    for(i=0; i< size_of_flock; i++)
        if (flock[i].id>=0){
            if (flock[i].type == 'h')
                hawks ++;
            else doves ++;
        }
    printf("%i\t%i\t%i\n", period, hawks, doves); 
    return (doves+0.0)/hawks;}

void flock_init(){
  flock         = NULL;
  size_of_flock = 0; }
