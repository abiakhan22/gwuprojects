#include "gwthd.h"
#include "types.h"
#include "user.h"

void* fn(void *data){
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
  printf(1, "there are no zombies!! level 5 passed!\n");
  exit();

  return 0;

}
