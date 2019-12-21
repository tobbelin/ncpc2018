/* Quadratic solution to the altruisticfrogs problem in NCPC2018 by Andreas Björklund*/
#include <stdio.h>
#include <stdlib.h>

#define MAXW (50000)
#define MAXF (100000)
#define MIN(a,b) ((a)<(b)?(a):(b))

int d, n;

struct frog {
  int l,w,h;
};

struct frog frogs[MAXF];

int cmp(const void *a, const void *b)
{
  int ia = ((struct frog*)a)->w;
  int ib = ((struct frog*)b)->w;
  int ja = ((struct frog*)a)->h;
  int jb = ((struct frog*)b)->h;
  if (ia == ib)
    return jb-ja;
  return ib-ia;
}

struct frog q[MAXW];
int nw;

int main()
{
  int i, j;
  int esc = 0;
  scanf("%d %d",&n,&d);
  
  for (i = 0; i < n; i++) {
    scanf("%d %d %d", &frogs[i].l, &frogs[i].w, &frogs[i].h);
  }
  
  qsort(frogs, n, sizeof(struct frog), cmp);

  nw = 1;
  q[0].w = 1000000000;
  q[0].h = 0;
  int oldw = 0;
  int posw = 0;
  int qstart = 0;
  for (i = 0; i < n; i++) {
    int nnw = nw;
    if (frogs[i].w != oldw) {
      j=qstart;
      while (j < nw && 2*frogs[i].w <= q[j].w) j++;
      q[nnw].w = frogs[i].w;
      q[nnw++].h = q[j-1].h + frogs[i].h;

      while (j < nw && (q[j].w > frogs[i].w)) {
            q[nnw].w = q[j].w - frogs[i].w;
            q[nnw++].h = MIN(100000000, q[j].h + frogs[i].h);
            j++;
      }
      posw = j-1;
    
      if (nnw > j)
        qsort(&q[j], nnw - j, sizeof(struct frog), cmp);
    
      j = qstart; 
      while (j < nnw && q[j].w >= 2*frogs[i].w) j++;
      qstart = j-1;
      int r = j;
      for (j = qstart+1; j < nnw; j++) 
        if (q[j].h > q[r-1].h) 
          q[r++] = q[j];
      nw = r;
      oldw = frogs[i].w;
    } 
    if (q[posw].h + frogs[i].l > d) esc++;
  } 
  printf("%d\n",esc);
  return 0;
}

 