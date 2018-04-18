#include "gwthd.h"
#include "types.h"
#include "user.h"

void* fn(void *data){
  printf(1, "thread id is: %d\n", gwthd_id());
  printf(1, "level 2 passed!\n");
  //printf(1, "data is : %d\n", *(int*) data); //===============**
  //printf(1, "level 3 passed!\n");
  gwthd_exit();

  return 0;
}
//the variables from gwthd.h
int main(void){
  int i = 3;
  void* data = &i;
  gwthd_t child = 0;
  gwthd_t childid = 0;

  gwthd_create(&childid,fn,data);
  gwthd_join(child);
  //gwthd_id();

  exit();

  return 0;

}
