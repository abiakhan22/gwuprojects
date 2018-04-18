#include "gwthd.h"
#include "types.h"
#include "user.h"

void* fn(){
  gwthd_exit();
  return 0;
}
//the variables from gwthd.h

int main(void){
  void* data = 0;
  gwthd_t child = 0;
  gwthd_t childid = 0;

  gwthd_create(&childid,fn,data);
  gwthd_join(child);
  //gwthd_id();
  printf(1,"pID is: %d\n", gwthd_id());
  printf(1,"level 1 passed!\n");//self notation
  exit();

  return 0;

}
