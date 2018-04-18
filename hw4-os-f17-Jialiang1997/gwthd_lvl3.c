#include "gwthd.h"
#include "types.h"
#include "user.h"

void* fn(void *data){
  printf(1, "data is : %d\n", *(int*) data); //===============**
  printf(1, "level 3 passed!\n");
  gwthd_exit();

  return 0;
}
//the variables from gwthd.h
int main(void){
  int temp = 3;
  void* data = &temp;
  gwthd_t child = 0;
  gwthd_t childid = 0;

  gwthd_create(&childid,fn,data);
  gwthd_join(child);
  //gwthd_id();

  exit();

  return 0;

}
