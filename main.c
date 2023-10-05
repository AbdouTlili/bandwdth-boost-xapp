#include <utils.h>



int main(){


    

    uint16_t Qm = 6;
    uint16_t R  = 438;
    uint16_t nb_rb  = 200;
    uint16_t nb_symb_sch  = 13;
    uint16_t nb_dmrs_prb  = 12;
    uint16_t nb_rb_oh  = 0;
    uint8_t tb_scaling  = 0;
    uint8_t Nl = 1;


    // Qm = nr_get_Qm_dl(sched_pdsch->mcs, dl_bwp->mcsTableIdx);
    // R = nr_get_code_rate_dl(sched_pdsch->mcs, dl_bwp->mcsTableIdx);

    uint16_t tmp_tbs,nb_prb ;


    tmp_tbs = nr_compute_tbs(Qm,R,nb_rb,nb_symb_sch,nb_dmrs_prb,nb_rb_oh,tb_scaling,Nl);

    printf("\nTBS : %u",tmp_tbs);

    nb_prb = nr_compute_nb_rb_from_tbs(tmp_tbs,Qm,R,nb_symb_sch,nb_dmrs_prb,nb_rb_oh,tb_scaling,Nl);

    printf("\nnb_prb : %u",nb_prb);
    

}