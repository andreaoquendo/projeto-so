#include "ppos.h"
#include "ppos-core-globals.h"

/*
    Código modificado pela aluna
    Andrea Alexandra Sánez Oquendo
    RA:2126524
*/

// ****************************************************************************
// Coloque aqui as suas modificações, p.ex. includes, defines variáveis, 
// estruturas e funções
#define PROJECT_SECONDS_CLOCK                2
#define PROJECT_MILISSECONDS_CLOCK           0
#define TASK_TICKS                           20

struct sigaction action ;
struct itimerval timer ;
int quantum;
int system_lock = 0; // 0 - para quando está bloqueado, 1 = para quando nao esta bloqueado

void tratador_timer(int signum);

task_t* scheduler_srtf();
void task_set_eet (task_t *task, int et);
int task_get_eet(task_t *task);
int task_get_ret(task_t *task);
void task_set_type(task_t *task);
void configure_timer();

// ************************* 



void before_ppos_init () { 
    system_lock = 0;
#ifdef DEBUG
    printf("\ninit - BEFORE");
#endif
}

void after_ppos_init () {

    configure_timer();
    systemTime = 0;
    quantum = TASK_TICKS;
    system_lock = 1;
#ifdef DEBUG
    printf("\ninit - AFTER");
#endif
}

void before_task_create (task_t *task ) {
    system_lock = 0;
#ifdef DEBUG
    printf("\ntask_create - BEFORE - [%d]", task->id);
#endif
}

void after_task_create (task_t *task ) {

    task->create_time = systemTime;
    task_set_type(task);
    task_set_eet(task, 99999); 
    task->running_time = 0;
    task->activations = 1;
    system_lock = 1;

#ifdef DEBUG
    printf("\ntask_create - AFTER - [%d]", task->id);
#endif
}

void before_task_exit () {
    system_lock = 0;
#ifdef DEBUG
    printf("\ntask_exit - BEFORE - [%d]", taskExec->id);
#endif
}

void after_task_exit () {
    
    printf("\nTask %d exit: execution time %4d ms, processor time %4d ms, %4d activations\n\n", taskExec->id, (systime() - taskExec->create_time), taskExec->running_time, taskExec->activations);
    system_lock = 1;
#ifdef DEBUG
    printf("\ntask_exit - AFTER- [%d]", taskExec->id);
#endif
}

void before_task_switch ( task_t *task ) {
    system_lock = 0;
#ifdef DEBUG
    printf("\ntask_switch - BEFORE - [%d -> %d]", taskExec->id, task->id);
#endif
}

void after_task_switch ( task_t *task ) {
    system_lock = 1;
#ifdef DEBUG
    printf("\ntask_switch - AFTER - [%d -> %d]", taskExec->id, task->id);
#endif
}

void before_task_yield () {
    taskExec->activations++;
    system_lock = 0;
#ifdef DEBUG
    printf("\ntask_yield - BEFORE - [%d]", taskExec->id);
#endif
}

void after_task_yield () {
    system_lock = 1;
    quantum = TASK_TICKS;
#ifdef DEBUG
    printf("\ntask_yield - AFTER - [%d]", taskExec->id);
#endif
}

void before_task_suspend( task_t *task ) {
    system_lock = 0;

#ifdef DEBUG
    printf("\ntask_suspend - BEFORE - [%d]", task->id);
#endif
}

void after_task_suspend( task_t *task ) {
    system_lock = 1;
#ifdef DEBUG
    printf("\ntask_suspend - AFTER - [%d]", task->id);
#endif
}

void before_task_resume(task_t *task) {
    system_lock = 0;
#ifdef DEBUG
    printf("\ntask_resume - BEFORE - [%d]", task->id);
#endif
}

void after_task_resume(task_t *task) {
    system_lock = 1;
#ifdef DEBUG
    printf("\ntask_resume - AFTER - [%d]", task->id);
#endif
}

void before_task_sleep () {
    system_lock = 0;
#ifdef DEBUG
    printf("\ntask_sleep - BEFORE - [%d]", taskExec->id);
#endif
}

void after_task_sleep () {
    system_lock = 1;

#ifdef DEBUG
    printf("\ntask_sleep - AFTER - [%d]", taskExec->id);
#endif
}

int before_task_join (task_t *task) {
    system_lock = 0;

#ifdef DEBUG
    printf("\ntask_join - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_task_join (task_t *task) {
    system_lock = 1;

#ifdef DEBUG
    printf("\ntask_join - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}


int before_sem_create (semaphore_t *s, int value) {
#ifdef DEBUG
    printf("\nsem_create - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_sem_create (semaphore_t *s, int value) {
#ifdef DEBUG
    printf("\nsem_create - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_sem_down (semaphore_t *s) {
#ifdef DEBUG
    printf("\nsem_down - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_sem_down (semaphore_t *s) {
#ifdef DEBUG
    printf("\nsem_down - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_sem_up (semaphore_t *s) {
#ifdef DEBUG
    printf("\nsem_up - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_sem_up (semaphore_t *s) {
#ifdef DEBUG
    printf("\nsem_up - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_sem_destroy (semaphore_t *s) {
#ifdef DEBUG
    printf("\nsem_destroy - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_sem_destroy (semaphore_t *s) {
#ifdef DEBUG
    printf("\nsem_destroy - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_mutex_create (mutex_t *m) {
#ifdef DEBUG
    printf("\nmutex_create - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_mutex_create (mutex_t *m) {
#ifdef DEBUG
    printf("\nmutex_create - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_mutex_lock (mutex_t *m) {
#ifdef DEBUG
    printf("\nmutex_lock - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_mutex_lock (mutex_t *m) {
#ifdef DEBUG
    printf("\nmutex_lock - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_mutex_unlock (mutex_t *m) {
#ifdef DEBUG
    printf("\nmutex_unlock - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_mutex_unlock (mutex_t *m) {
#ifdef DEBUG
    printf("\nmutex_unlock - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_mutex_destroy (mutex_t *m) {
#ifdef DEBUG
    printf("\nmutex_destroy - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_mutex_destroy (mutex_t *m) {
#ifdef DEBUG
    printf("\nmutex_destroy - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_barrier_create (barrier_t *b, int N) {
#ifdef DEBUG
    printf("\nbarrier_create - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_barrier_create (barrier_t *b, int N) {
#ifdef DEBUG
    printf("\nbarrier_create - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_barrier_join (barrier_t *b) {
#ifdef DEBUG
    printf("\nbarrier_join - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_barrier_join (barrier_t *b) {
#ifdef DEBUG
    printf("\nbarrier_join - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_barrier_destroy (barrier_t *b) {
#ifdef DEBUG
    printf("\nbarrier_destroy - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_barrier_destroy (barrier_t *b) {
#ifdef DEBUG
    printf("\nbarrier_destroy - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_mqueue_create (mqueue_t *queue, int max, int size) {
#ifdef DEBUG
    printf("\nmqueue_create - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_mqueue_create (mqueue_t *queue, int max, int size) {
#ifdef DEBUG
    printf("\nmqueue_create - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_mqueue_send (mqueue_t *queue, void *msg) {
#ifdef DEBUG
    printf("\nmqueue_send - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_mqueue_send (mqueue_t *queue, void *msg) {
#ifdef DEBUG
    printf("\nmqueue_send - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_mqueue_recv (mqueue_t *queue, void *msg) {
#ifdef DEBUG
    printf("\nmqueue_recv - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_mqueue_recv (mqueue_t *queue, void *msg) {
#ifdef DEBUG
    printf("\nmqueue_recv - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_mqueue_destroy (mqueue_t *queue) {
#ifdef DEBUG
    printf("\nmqueue_destroy - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_mqueue_destroy (mqueue_t *queue) {
#ifdef DEBUG
    printf("\nmqueue_destroy - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_mqueue_msgs (mqueue_t *queue) {
#ifdef DEBUG
    printf("\nmqueue_msgs - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_mqueue_msgs (mqueue_t *queue) {
#ifdef DEBUG
    printf("\nmqueue_msgs - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

 /*
    Uma função scheduler que analisa a fila de tarefas prontas, devolvendo um ponteiro para a próxima tarefa a receber o processador
*/
task_t * scheduler() {
    system_lock = 0;
    task_t* selectedTask = NULL;

    if ( readyQueue != NULL ) {
        task_t* currTask = readyQueue;
        selectedTask = readyQueue;

        while(currTask->next != readyQueue){  
            currTask = currTask->next;

            if(task_get_ret(currTask) < task_get_ret(selectedTask)){
                selectedTask = currTask;
            }
        } 
        
        system_lock = 1;
        return selectedTask;

    }
    printf("\nrREADY QUEUE IS EMPTY");
    system_lock = 1;
    return NULL;
   
}

/*
    Esta função ajusta a prioridade com base no tempo de execução total estimado para da tarefa. Caso task seja nulo, ajusta a prioridade da tarefa atual. Quando a tarefa já está eexecução, essa função deve sobrescrever tanto o valor estimado do tempo deexecução como também o valor do tempo que ainda resta para a tarefa terminarsua execução
*/
void task_set_eet (task_t *task, int et){ // [TAREFA 1.2.1]

    system_lock = 0;
    if(task == NULL){
        task = taskExec;
    }
    task->eet = et;
    system_lock = 1;

}

/*
    Esta função devolve o valor do tempo estimado de execução da tarefa task (ou da tarefa corrente, se task fornulo).
*/
int task_get_eet(task_t *task){
    
    if(task == NULL){ return taskExec-> eet; }

    return task->eet;
}

int task_get_ret(task_t *task){
    /*
    Esta função devolve o valor do tempo restante para terminar a execução da tarefa task (ou da tarefa corrente,se task for nulo)
    */
    int remaining_time;
    
    if (task == NULL) {
        // Se task for nulo, use a tarefa em execução atual
        task = taskExec;
    }

    remaining_time = task->eet - task->running_time;
    
    // Verifique se o tempo restante é não negativo
    if (remaining_time < 0) {
        remaining_time = 9999; // Tempo restante não pode ser negativo
    }

    return remaining_time;
}

void task_setprio (task_t *task, int prio){

    if(task == NULL){
        task = taskExec;
    }

    task->prio = prio;
}

int task_getprio (task_t *task){

    if(task == NULL){
        task = taskExec;
    }

    return task->prio;
}

void tratador_timer(int signum){
    systemTime++;
    quantum--;
    taskExec->running_time++;

    if(system_lock == 0){ return; }
    if(quantum <= 0){
        task_yield();
    } 

}

void configure_timer(){
    
    system_lock = 0;
    action.sa_handler = tratador_timer ;
    sigemptyset (&action.sa_mask) ;
    action.sa_flags = 0 ;
    if (sigaction (SIGALRM, &action, 0) < 0)
    {
        perror ("Erro em sigaction: ") ;
        exit (1) ;
    }

    // ajusta valores do temporizador
    timer.it_value.tv_usec = 1 ;      // primeiro disparo, em micro-segundos
    timer.it_value.tv_sec  = 0 ;      // primeiro disparo, em segundos

    timer.it_interval.tv_usec = 1000 ;   // disparos subsequentes, em micro-segundos
    timer.it_interval.tv_sec  = 0 ;   // disparos subsequentes, em segundos

    // arma o temporizador ITIMER_REAL (vide man setitimer)
    if (setitimer (ITIMER_REAL, &timer, 0) < 0)
    {
        perror ("Erro em setitimer: ") ;
        exit (1) ;
    }

    quantum = TASK_TICKS;
    system_lock = 1;
}

void task_set_type(task_t *task){
    system_lock = 0;
    if(task == taskDisp){
        task->type = 0;
    } else {
        task->type = 1;
    }
    system_lock = 1;
}