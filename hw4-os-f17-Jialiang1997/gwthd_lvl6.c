#include "gwthd.h"
#include "types.h"
#include "user.h"

void* fn(void *data){
  exit();
  return 0;
}
//the variables from gwthd.h
int main(void){
  int temp = 3;
  void* data = &temp;
  gwthd_t child = 0;
  gwthd_t childid = 0;

  gwthd_create(&childid,fn,data);
  gwthd_exit();
  gwthd_join(child);
  //gwthd_id();

  exit();

  return 0;

}
