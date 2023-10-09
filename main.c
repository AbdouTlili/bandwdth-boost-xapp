#include <utils.h>



int main(){





    // initialize  the required throughput in MBits/s 


    uint32_t required_throughput = 50000000; // 50MBits/s

    // in one sec we have 100 frames 
    // in each slot we have 10 subframes 
    // in each subframe we have 2 slots because we are using numerology 1

    uint32_t tbs = (uint32_t)(required_throughput / 2000) ; 

    // calculating parameters : 

    uint16_t Qm = 6;
    uint16_t R  = 438;
    uint16_t nb_rb  = 200;
    uint16_t nb_symb_sch  = 13;
    uint16_t nb_dmrs_prb  = 12;
    uint16_t nb_rb_oh  = 0;
    uint8_t tb_scaling  = 0;
    uint8_t Nl = 1;

    uint8_t mcs = 9 ;


    Qm = nr_get_Qm_dl(mcs, 1);
    R = nr_get_code_rate_dl(mcs, 1);

    uint16_t tmp_tbs,nb_prb,nb_rb2 ;





    printf("\nTBS : %u",tbs);
    // / Testing TBS ---> TBS
    nb_prb = nr_compute_nb_rb_from_tbs(tbs,Qm,R,nb_symb_sch,nb_dmrs_prb,nb_rb_oh,tb_scaling,Nl);

    printf("\n to achieve a %u Bits Per Second in MCS : %u we need nb_prb : %u",required_throughput,mcs,nb_prb);


    // // # testing nb_rb   ->>>> TBS 
    // nb_prb = nb_prb;
    // tmp_tbs = nr_compute_tbs(Qm,R,nb_prb,nb_symb_sch,nb_dmrs_prb,nb_rb_oh,tb_scaling,Nl);
    // printf("\ncalculated tbs is : %u",tmp_tbs);
    

    nb_rb2 = nr_compute_nb_rb_needed_to_achive_throughput(100000000,9);
    printf("\n to achieve a %u Bits Per Second in MCS : %u we need nb_prb : %u",100000000,9,nb_rb2);

}