#include "birds.h"
#include <glib.h>

GTree *flock  = NULL;
int hawks, doves;

static gint compare_keys(const void *L, const void *R){
  const int *Lb  = L;
  const int *Rb  = R;
    return *Lb - *Rb;
}

static gboolean tree_bird_plays(void *key, void *in, void *v){
    bird_plays(in, NULL);
    return 0;
}

void flock_plays(){ g_tree_foreach(flock, tree_bird_plays, NULL); }

void add_to_flock(bird* b){ g_tree_insert(flock, &(b->id), b); }

bird * find_opponent(int n){return g_tree_lookup(flock, &n);}

int flock_size(){ return g_tree_nnodes(flock); }

static gboolean wealth_foreach(void *key, void *in, void *t){
  int *total = t;
    *total   += ((bird*)in)->wealth;
    return 0; }

int flock_wealth(){
  int   total   = 0;
    g_tree_foreach(flock, wealth_foreach, &total);
    return total; }

static gboolean tree_bird_count(void *key, void *in, void *v){
    if (((bird *)in)->type == 'h')
        hawks   ++;
    else doves   ++;
    return 0; }

GList *dying_birds;

void free_bird(bird* b){dying_birds = g_list_prepend(dying_birds, b);}

static gboolean tree_birth_or_death(void *key, void *in, void *t){
    birth_or_death(in, t);
    return 0; }

static void cull_foreach(void *b, void *v){
  bird*    a_bird = b;
    g_tree_remove(flock, &(a_bird->id));
    free(a_bird); }

double count(int period){
  int   total_wealth    =flock_wealth();
    hawks   = doves = 0;
    dying_birds     = NULL;
    g_tree_foreach(flock, tree_birth_or_death, &total_wealth);
    g_list_foreach(dying_birds, cull_foreach, NULL);
    g_list_free(dying_birds);
    g_tree_foreach(flock, tree_bird_count, NULL);
    printf("%i\t%i\t%i\n", period, hawks, doves); 
    return (doves+0.0)/hawks;}

void flock_init(){ flock   = g_tree_new(compare_keys); }
