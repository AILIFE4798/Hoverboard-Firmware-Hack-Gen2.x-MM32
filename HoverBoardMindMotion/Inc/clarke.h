#ifdef TARGET_MM32SPIN25
#include "HAL_device.h"                 // Device header
#else
#include "mm32_device.h"                // Device header
#endif
#define INV_SQRT3		591				// (1/sqrt(3)) << 10

typedef struct {  
						int16_t  As;  		// Input: phase-a stator variable
						int16_t  Bs;			// Input: phase-b stator variable
						int16_t  Cs;			// Input: phase-c stator variable  
						int16_t  Alpha;		// Output: stationary d-axis stator variable 
						int16_t  Beta;		// Output: stationary q-axis stator variable
						}CLARKE_T;	            

/*-----------------------------------------------------------------------------
	Default initalizer for the CLARKE object.
-----------------------------------------------------------------------------*/                     
#define CLARKE_DEFAULTS { 0, \
                          0, \
                          0, \
                          0, \
                          0, \
              			} 

//------------------------------------------------------------------------------
extern CLARKE_T clarke1;	
extern CLARKE_T Emf_AB;	
										
extern void CLARKE_MACRO1(CLARKE_T *u1);
