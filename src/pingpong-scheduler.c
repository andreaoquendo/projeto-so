// PingPongOS - PingPong Operating System
// Prof. Carlos A. Maziero, DINF UFPR
// Versão 1.1 -- Julho de 2016

// Teste do escalonador por prioridades dinâmicas

#include <stdio.h>
#include <stdlib.h>
#include "ppos.h"

task_t Pang, Peng, Ping, Pong, Pung ;

// corpo das threads
void Body (void * arg)
{
  int i ;

  printf ("%s: inicio (prioridade %d)\n", (char *) arg, task_getprio(NULL)) ;

  for (i=0; i<10; i++)
  {
    printf ("%s: %d\n", (char *) arg, i) ;
    task_yield ();
  }
  printf ("%s: fim\n", (char *) arg) ;
  task_exit (0) ;
}

int main (int argc, char *argv[])
{
  printf ("main: inicio\n");

  ppos_init () ;

  task_create (&Pang, Body, "task A") ;
  task_setprio (&Pang, 0);
  task_set_eet(&Pang, 10);

  task_create (&Peng, Body, "task B") ;
  task_setprio (&Peng, 2);
  task_set_eet(&Peng, 35);

  task_create (&Ping, Body, "task C") ;
  task_setprio (&Ping, 4);
  task_set_eet(&Ping, 30);

  task_create (&Pong, Body, "task D") ;
  task_setprio (&Pong, 6);
  task_set_eet(&Pong, 40);

  task_create (&Pung, Body, "task E") ;
  task_setprio (&Pung, 8);
  task_set_eet(&Pung, 15);

  task_join(&Pang);
  task_join(&Peng);
  task_join(&Ping);
  task_join(&Pong);
  task_join(&Pung);

  printf ("main: fim\n");

  while(1);
  exit (0) ;
}
