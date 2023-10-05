#include <stdio.h>
#include <stdint.h>
int lookup_ue(uint32_t UE_list[],uint8_t list_len, uint32_t rnti);

typedef struct {
      int uid; // unique ID of this UE
  uint32_t boost_factor;
  uint32_t nb_prb;
} NR_UE_info_t;

int main(int argc, char *argv[]){

        printf("\n--------   argc  IS : %d ",argc);

    int nb_resource_blocs = 5  ;
    if (argc > 1){
        nb_resource_blocs = atoi( argv[1]);
        printf("\n--------   nb resource blocs IS : %d ",nb_resource_blocs);
    }

    // NR_UE_info_t tmp = {.uid = 5};
    // if(1){
    //     printf("%d -- %d -- %d",tmp.boost_factor,tmp.nb_prb,tmp.uid);
    // }

    // uint32_t t = 0xad11;
    // uint32_t UEs[5];
    // int UE_list_len = 0;
    // UEs[0] = 0xab11;
    // UEs[1] = 0xac11;
    // UEs[2] = 0xad11;

    // printf("UE with RNTI : %x is added",UEs[0]); 

    // if (lookup_ue(UEs,0,t)){
    //     printf("\nUE FOUND");
    // }else{
    //     printf("\nUE NOT FOUND");
    // }
    return 0;
}

int lookup_ue(uint32_t UE_list[],uint8_t list_len, uint32_t rnti){
  int found = 0;
  for (int i = 0; i < list_len ; i++) {
          if (UE_list[i] == rnti) {
              found = 1;
              break;
          }
  }
  return found;

}