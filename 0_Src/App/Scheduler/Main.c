/*----------------------------------------------------------------*/
/*						Include Header File						  */
/*----------------------------------------------------------------*/
#include "Main.h"
#include "DrvSys.h"
#include "Scheduler.h"
#include "DrvTlf.h"

/*----------------------------------------------------------------*/
/*						Define						  			  */
/*----------------------------------------------------------------*/

/*----------------------------------------------------------------*/
/*						Typedefs						  		  */
/*----------------------------------------------------------------*/

/*----------------------------------------------------------------*/
/*						Static Function Prototype				  */
/*----------------------------------------------------------------*/

/*----------------------------------------------------------------*/
/*						Variables				  				  */
/*----------------------------------------------------------------*/
App_Cpu g_AppCpu0;

/*----------------------------------------------------------------*/
/*						Functions				  				  */
/*----------------------------------------------------------------*/

/*---------------------Main Function--------------------------*/
int main(void)
{
	/*System Initialization*/
	DrvSys();

	/*Register Callback Function*/
	Scheduler_Init();

    /*Enable the global interrupts of this CPU*/
    IfxCpu_enableInterrupts();

	DrvTlfInit();

    while(1u)
    {
    	Scheduler();
    }

    return 0;
}
