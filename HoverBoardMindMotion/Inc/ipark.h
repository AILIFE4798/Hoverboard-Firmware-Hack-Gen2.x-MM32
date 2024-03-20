#ifdef TARGET_MM32SPIN25
#include "HAL_device.h"                 // Device header
#else
#include "mm32_device.h"                // Device header
#endif

typedef volatile struct {  
						int32_t  Alpha;		// Output: stationary d-axis stator variable
						int32_t  Beta;		// Output: stationary q-axis stator variable
						int16_t  Theta;		// Input: rotating angle (pu)
						int32_t  Ds;		// Input: rotating d-axis stator variable
						int32_t  Qs;		// Input: rotating q-axis stator variable
						int16_t  Sin;		// Input: Sine term
						int16_t  Cos;		// Input: Cosine term
		 	    } IPARK_T;	            

/*-----------------------------------------------------------------------------
Default initalizer for the IPARK object.
-----------------------------------------------------------------------------*/                     
#define IPARK_DEFAULTS {  0, \
                          0, \
                          0, \
                          0, \
                          0, \
                          0, \
													0  \
              		   }

					   
extern IPARK_T ipark1;
										 
//------------------------------------------------------------------------------
void IPARK_MACRO1(volatile IPARK_T *v);
//------------------------------------------------------------------------------

