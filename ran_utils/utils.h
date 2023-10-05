#define INDEX_MAX_TBS_TABLE (93)
#define cmin(a,b)  ((a<b) ? (a) : (b))
#define cmax(a,b)  ((a>b) ? (a) : (b))

#define CEILIDIV(a,b) ((a+b-1)/b)
#define ROUNDIDIV(a,b) (((a<<1)+b)/(b<<1))
#define max(a,b) cmax(a,b)
#define min(a,b) cmin(a,b)

#include <stdint.h>
#include <stdio.h>
#include <math.h>

uint32_t nr_compute_tbs(uint16_t Qm,
                        uint16_t R,
                        uint16_t nb_rb,
                        uint16_t nb_symb_sch,
                        uint16_t nb_dmrs_prb,
                        uint16_t nb_rb_oh,
                        uint8_t tb_scaling,
                        uint8_t Nl);


uint32_t nr_get_code_rate_dl(uint8_t Imcs, uint8_t table_idx);

uint16_t nr_compute_nb_rb_from_tbs(uint32_t tbs,
                                    uint16_t Qm,
                                    uint16_t R,
                                    uint16_t nb_symb_sch,
                                    uint16_t nb_dmrs_prb,
                                    uint16_t nb_rb_oh,
                                    uint8_t tb_scaling,
                                    uint8_t Nl);

