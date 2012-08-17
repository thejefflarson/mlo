#include <lm.h>
#include <status.h>
#include <iostream>


int main(void){
  mlo::LM lm(5);
  std::cout << "Getting file." << std::endl;
  mlo::Status status = lm.Load("test.tok");
  if(status.IsIOError())
    std::cout << "Couldn't open file!" << std::endl;

  lm.query("Is this an english sentence ?");

  return 0;
}

