#include <stdio.h>
#include <threads.h>

int counter = 0;
mtx_t mtx;

int func1()
{
  mtx_lock (&mtx);
  printf ("111printing from thread1 + counter: %d \n", counter);
  counter++;
  mtx_unlock (&mtx);
  return 0;

}

int func2()
{
  mtx_lock (&mtx);
  printf ("222printing from twosasfad2:        %d \n", counter);
  counter++;
  mtx_unlock (&mtx);
  return 0;
}

int func3()
{
  mtx_lock (&mtx);
  printf ("333printing from three6sasfyd3:     %d \n", counter);
  counter++;
  mtx_unlock (&mtx);
  return 0;
}

int func4()
{
  mtx_lock (&mtx);
  printf ("444printing from foursasfadsqxzvp4: %d \n", counter);
  counter++;
  mtx_unlock (&mtx);
  return 0;
}


int main()
{
  mtx_init (&mtx, mtx_plain);

  thrd_t test1;
  thrd_t test2;
  thrd_t test3;
  thrd_t test4;

  thrd_create (&test1, func1, NULL);
  thrd_create (&test2, func2, NULL);
  thrd_create (&test3, func3, NULL);
  thrd_create (&test4, func4, NULL);


  thrd_join (test1, NULL);
  thrd_join (test2, NULL);
  thrd_join (test3, NULL);
  thrd_join (test4, NULL);


  printf ("printing from MAIN thread: %d \n", counter);

  mtx_destroy (&mtx);
  return 0;
}
