#include "Steering_gear.h"

/*******************************************************************************/
/*                  (舵机ID)       (目标位置)       (速度)         (加速度)    */
/*                 (软件设置)       (0-4095)       (0-2250)        (      )    */
/*  int WritePosEx(uint8_t ID, int16_t Position, uint16_t Speed, uint8_t ACC)  */
/*                Delay规则：[(P1-P0)/V]*1000+[V/(A*100)]*1000                 */
/*********************************************************************************************************************/
/*  例： WritePosEx(1, 0, 2250, 50);      //舵机(ID1),以最高速度V=2250步/秒,加速度A=50(50*100步/秒^2),运行至P1=4095  */
/*       PosEx_Delay(0,1,2250,50);        //[(P1-P0)/V]*1000+[V/(A*100)]*1000                                        */
/*********************************************************************************************************************/
void Steering_gear_Test(void)
{
    RegWritePosEx(1, 3072, 2250, 100);
    RegWritePosEx(2, 2048, 1500, 80);
    RegWritePosEx(3, 1024, 1000, 50);
    RegWritePosEx(4, 1, 1000, 30);
    RegWriteAction();
    PosEx_Delay(1,3072,1000,30);

    RegWritePosEx(4, 3072, 2250, 100);
    RegWritePosEx(3, 2048, 1500, 80);
    RegWritePosEx(2, 1024, 1000, 50);
    RegWritePosEx(1, 1, 1000, 30);
    RegWriteAction();
    PosEx_Delay(1,3072,1000,30);


}

void PosEx_Delay(int16_t P1, int16_t P2, uint16_t Speed, uint8_t ACC)
{
	int ms;
    ms=((P2-P1)/Speed)*1000+(Speed/(ACC*100))*1000;
	if(ms>=0) ms=ms;
	else ms=-ms;
	HAL_Delay(ms);
}





