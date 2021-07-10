MLFQ:
first 4 queues in mlfq follow FCFS and last one follow round robin.
first four queues.
struct proc*
readyproc(int priority)
{
  struct proc *p,*minP=0;
  int found = 0;
  for(p = ptable.proc;p < &ptable.proc[NPROC]; p++)
  {
    if(p->qno!=priority || p->state != RUNNABLE)continue;
    if(p->qno == priority && found==0){
      found = 1;
      minP = p;
    }
    if(p->ctime < minP->ctime)minP = p;
  }
  return minP;
}
This is for finding least creation time process in queues.
if qno = 4. ie all other queues are empty.
    if(p->qno == 4)
    {
      for(exp = ptable.proc;exp < &ptable.proc[NPROC]; exp++)
      {
        if(exp->state != RUNNABLE)
         continue;

      // Switch to chosen process.  It is the process's job
      // to release ptable.lock and then reacquire it
      // before jumping back to us.
        c->proc = exp;
        switchuvm(exp);
        exp->state = RUNNING;

        swtch(&(c->scheduler), exp->context);
        p->qtime[p->qno]++;
        p->n_run++;
        switchkvm();

        // Process is done running for now.
        // It should have changed its p->state before coming back.
        c->proc = 0;
        p->execgap = ticks;
        foundone = 0;
        for(exp = ptable.proc;exp < &ptable.proc[NPROC]; exp++)
        { 
          if(exp->qno !=0 && (ticks - exp->execgap) > 20){
            exp->qno--;
            exp->execgap=ticks;
            foundone = 1;   
          }
        }
        if(foundone==1)break;
      }
this is round robin for fifth queue which will be iterating until a process enters other queues. 

Runtime observations:

RR 5840
FCFS 8354
PBS 5957
MLFQ 7086

observed for benchmark
so order is (best is first)
RR > PBS ~ MLFQ > FCFS

FCFS(without preemption):
FCFS scheduling algorithm finds process with minimum creation time and executes that without preemption,

      if(p->pid > 1)
      {
        if (minProc != 0){
        // here I find the process with the lowest creation time (the first one that was created)
        if(p->ctime < minProc->ctime)minProc = p;
        }
      else minProc = p;
      // If I found the process which I created first and it is runnable I run it
      //(in the real FCFS I should not check if it is runnable, but for testing purposes I have to make this control, otherwise every time I launch
      // a process which does I/0 operation (every simple command) everything will be blocked
      if(minProc != 0 && minProc->state == RUNNABLE)p = minProc;
      }
This finds minimum in the for loop of processes.
then it will be executed.
For getting rid of preemtion conitions are used as shown below.
    #ifndef FCFS
    yield();
    #endif
because yield makes the preemtion.

PBS:
PBS searches for the minimum priority value(high priority) in all processes and executes that with preemption until other high priority process enter or
until it exits.
Here processes with same priority are following round robin.

    for(p = ptable.proc; p < &ptable.proc[NPROC]; p++)
    {
      if((p->priority < minpriority) && (p->state == RUNNABLE))
      {
        minpriority = p->priority;
      }
    }
This is for getting minimum priority value.
    for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
      if((p->state == RUNNABLE) && (p->priority == minpriority))
      {

        // Switch to chosen process.  It is the process's job
        // to release ptable.lock and then reacquire it
        // before jumping back to us.
        c->proc = p;
        switchuvm(p);
        p->state = RUNNING;
        p->n_run++;
        swtch(&(c->scheduler), p->context);
        switchkvm();

        // Process is done running for now.
        // It should have changed its p->state before coming back.
        c->proc = 0;
      }
      struct proc *dupp;
      for(dupp = ptable.proc;dupp < &ptable.proc[NPROC]; dupp++)
      {
        if(dupp->priority < minpriority) break;
      }
    }
THis is for executing the processes having priority value as minpriority in a round robin and after every preemption it will check for processes where priority value is changed to
less than present minpriority.

Graph:
for graph execution
Command:
make qemu PRIORITY=MLFQ GRAPH=YES
//garbage should be deleted
python graph.py