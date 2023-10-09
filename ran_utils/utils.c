#include <utils.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

#define  NB_DMRS_PRB   12;
#define  NB_SYMB_SCH   13;
#define  NR_RB_OH  0;
#define TB_SCALING   0;
#define NL  1;







//Table 5.1.2.2-2
static const uint16_t Tbstable_nr[INDEX_MAX_TBS_TABLE] = {
    24,   32,   40,   48,   56,   64,   72,   80,   88,   96,   104,  112,  120,  128,  136,  144,  152,  160,  168,
    176,  184,  192,  208,  224,  240,  256,  272,  288,  304,  320,  336,  352,  368,  384,  408,  432,  456,  480,
    504,  528,  552,  576,  608,  640,  672,  704,  736,  768,  808,  848,  888,  928,  984,  1032, 1064, 1128, 1160,
    1192, 1224, 1256, 1288, 1320, 1352, 1416, 1480, 1544, 1608, 1672, 1736, 1800, 1864, 1928, 2024, 2088, 2152, 2216,
    2280, 2408, 2472, 2536, 2600, 2664, 2728, 2792, 2856, 2976, 3104, 3240, 3368, 3496, 3624, 3752, 3824};


// the following tables contain 10 times the value reported in 214 (in line with SCF specification and to avoid fractional values)
//Table 5.1.3.1-1 of 38.214
static const uint16_t Table_51311[32][2] = {{2, 1200}, {2, 1570}, {2, 1930}, {2, 2510}, {2, 3080}, {2, 3790}, {2, 4490}, {2, 5260},
                                            {2, 6020}, {2, 6790}, {4, 3400}, {4, 3780}, {4, 4340}, {4, 4900}, {4, 5530}, {4, 6160},
                                            {4, 6580}, {6, 4380}, {6, 4660}, {6, 5170}, {6, 5670}, {6, 6160}, {6, 6660}, {6, 7190},
                                            {6, 7720}, {6, 8220}, {6, 8730}, {6, 9100}, {6, 9480}, {2, 0}, {4, 0}, {6, 0}};

//Table 5.1.3.1-2 of 38.214
// Imcs values 20 and 26 have been multiplied by 2 to avoid the floating point
static const uint16_t Table_51312[32][2] = {{2, 1200}, {2, 1930}, {2, 3080}, {2, 4490}, {2, 6020}, {4, 3780}, {4, 4340},
                                            {4, 4900}, {4, 5530}, {4, 6160}, {4, 6580}, {6, 4660}, {6, 5170}, {6, 5670},
                                            {6, 6160}, {6, 6660}, {6, 7190}, {6, 7720}, {6, 8220}, {6, 8730}, {8, 6825},
                                            {8, 7110}, {8, 7540}, {8, 7970}, {8, 8410}, {8, 8850}, {8, 9165}, {8, 9480},
                                            {2, 0}, {4, 0}, {6, 0}, {8, 0}};

//Table 5.1.3.1-3 of 38.214
static const uint16_t Table_51313[32][2] = {{2, 300},  {2, 400},  {2, 500},  {2, 640},  {2, 780},  {2, 990},  {2, 1200}, {2, 1570},
                                            {2, 1930}, {2, 2510}, {2, 3080}, {2, 3790}, {2, 4490}, {2, 5260}, {2, 6020}, {4, 3400},
                                            {4, 3780}, {4, 4340}, {4, 4900}, {4, 5530}, {4, 6160}, {6, 4380}, {6, 4660}, {6, 5170},
                                            {6, 5670}, {6, 6160}, {6, 6660}, {6, 7190}, {6, 7720}, {2, 0}, {4, 0}, {6, 0}};



uint32_t nr_compute_tbs(uint16_t Qm,
                        uint16_t R,
                        uint16_t nb_rb,
                        uint16_t nb_symb_sch,
                        uint16_t nb_dmrs_prb,
                        uint16_t nb_rb_oh,
                        uint8_t tb_scaling,
                        uint8_t Nl)
{

//   printf( "In %s: nb_symb_sch %d, nb_dmrs_prb %d, nb_rb %d, nb_rb_oh %d, tb_scaling %d Nl %d\n", __FUNCTION__, nb_symb_sch, nb_dmrs_prb, nb_rb, nb_rb_oh, tb_scaling, Nl);

  const int nb_subcarrier_per_rb = 12;
  const uint32_t nbp_re =  nb_subcarrier_per_rb * nb_symb_sch - nb_dmrs_prb - nb_rb_oh;
  const uint32_t nb_re = min(156, nbp_re) * nb_rb;
  // Intermediate number of information bits
  // Rx1024 is tabulated as 10 times the actual code rate
  const uint32_t R_5 = R/5; // R can be fractional so we can't divide by 10
  // So we ned to right shift by 11 (10 for x1024 and 1 additional as above)
  const uint32_t Ninfo = ((nb_re * R_5 * Qm * Nl)>>11)>>tb_scaling;

  uint32_t nr_tbs=0;
  uint32_t Np_info, C, n;

  if (Ninfo <=3824) {
    n = max(3, floor(log2(Ninfo)) - 6);
      Np_info = max(24, (Ninfo>>n)<<n);
      for (int i=0; i<INDEX_MAX_TBS_TABLE; i++) {
        if (Tbstable_nr[i] >= Np_info){
          nr_tbs = Tbstable_nr[i];
          break;
        }
      }
  } else {
    n = log2(Ninfo-24)-5;
    Np_info = max(3840, (ROUNDIDIV((Ninfo-24),(1<<n)))<<n);

    if (R <= 2560) {
        C = CEILIDIV((Np_info+24),3816);
        nr_tbs = (C<<3)*CEILIDIV((Np_info+24),(C<<3)) - 24;
    } else {
      if (Np_info > 8424){
          C = CEILIDIV((Np_info+24),8424);
          nr_tbs = (C<<3)*CEILIDIV((Np_info+24),(C<<3)) - 24;
      } else {
        nr_tbs = ((CEILIDIV((Np_info+24),8))<<3) - 24;
      }
    }
  }

//   printf("In %s: Ninfo %u nbp_re %d nb_re %d Qm %d, R %d, tbs %d bits\n", __FUNCTION__, Ninfo, nbp_re, nb_re, Qm, R, nr_tbs);
  return nr_tbs;
}



uint32_t nr_get_code_rate_dl(uint8_t Imcs, uint8_t table_idx) {
  switch(table_idx) {
    case 0:
      if (Imcs > 31) {
        printf("Invalid MCS index %d for MCS table 0 (expected range [0,31])\n", Imcs);
        return 0;
      }
      return (Table_51311[Imcs][1]);
    break;

    case 1:
      if (Imcs > 31) {
        printf("Invalid MCS index %d for MCS table 1 (expected range [0,31])\n", Imcs);
        return 0;
      }
      return (Table_51312[Imcs][1]);
    break;

    case 2:
      if (Imcs > 31) {
        printf("Invalid MCS index %d for MCS table 2 (expected range [0,31])\n", Imcs);
        return 0;
      }
      return (Table_51313[Imcs][1]);
    break;

    default:
      printf( "Invalid MCS table index %d (expected in range [0,2])\n", table_idx);
      return 0;
  }
}




uint8_t nr_get_Qm_dl(uint8_t Imcs, uint8_t table_idx) {
  switch(table_idx) {
    case 0:
      if (Imcs > 31) {
        printf( "Invalid MCS index %d for MCS table 0 (expected range [0,31])\n", Imcs);
        return 0;
      }
      return (Table_51311[Imcs][0]);
    break;

    case 1:
      if (Imcs > 31) {
        printf("Invalid MCS index %d for MCS table 1 (expected range [0,31])\n", Imcs);
        return 0;
      }
      return (Table_51312[Imcs][0]);
    break;

    case 2:
      if (Imcs > 31) {
        printf("Invalid MCS index %d for MCS table 2 (expected range [0,31])\n", Imcs);
        return 0;
      }
      return (Table_51313[Imcs][0]);
    break;

    default:
      printf( "Invalid MCS table index %d (expected in range [0,2])\n", table_idx);
      return 0;
  }
}



uint16_t nr_compute_nb_rb_from_tbs(uint32_t tbs,
                                    uint16_t Qm,
                                    uint16_t R,
                                    uint16_t nb_symb_sch,
                                    uint16_t nb_dmrs_prb,
                                    uint16_t nb_rb_oh,
                                    uint8_t tb_scaling,
                                    uint8_t Nl)
{
    uint16_t nb_rb_max = 5000;
    uint16_t nb_rb_min = 5;

    uint16_t hi = nb_rb_max;
    uint16_t lo = nb_rb_min;
    uint16_t nb_rb = nb_rb_min;
    for (int p = (hi + lo) / 2; lo + 1 < hi; p = (hi + lo) / 2) {

        // If by increasing p for transform precoding we already hit the high, break to avoid infinite loop
        if (p == hi)
        break;

        const uint32_t TBS = nr_compute_tbs(Qm, R, p, nb_symb_sch, nb_dmrs_prb, 0, 0, Nl) ;
        // printf("\nTBS tmp is %u",TBS);
        if (TBS == tbs) {
            hi = p;
            break;
        } else if (TBS > tbs) {
            hi = p;
        } else {
            lo = p;
        }
    }
    nb_rb = hi;
    return nb_rb;
}


uint32_t nr_compute_nb_rb_needed_to_achive_throughput(uint32_t required_throughput, uint32_t mcs){


    // initialize  the required throughput in MBits/s 


  // uint32_t required_throughput = 50000000; // 50MBits/s

  // in one sec we have 100 frames 
  // in each slot we have 10 subframes 
  // in each subframe we have 2 slots because we are using numerology 1

  uint32_t tbs = (uint32_t)(required_throughput / 2000) ; 


  uint16_t nb_symb_sch  = NB_SYMB_SCH;
  uint16_t nb_dmrs_prb  = NB_DMRS_PRB;
  uint16_t nb_rb_oh  = NR_RB_OH;
  uint8_t tb_scaling  = TB_SCALING;
  uint8_t Nl = NL;

  // calculating parameters : 

  uint32_t Qm = nr_get_Qm_dl(mcs, 1);
  uint32_t R = nr_get_code_rate_dl(mcs, 1);

  uint16_t nb_prb ;

  nb_prb = nr_compute_nb_rb_from_tbs(tbs,Qm,R,nb_symb_sch,nb_dmrs_prb,nb_rb_oh,tb_scaling,Nl);

  return nb_prb; 

}