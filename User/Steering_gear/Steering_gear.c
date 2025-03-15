#include "Steering_gear.h"

/*******************************************************************************/
/*                  (���ID)       (Ŀ��λ��)       (�ٶ�)         (���ٶ�)    */
/*                 (�������)       (0-4095)       (0-2250)        (      )    */
/*  int WritePosEx(uint8_t ID, int16_t Position, uint16_t Speed, uint8_t ACC)  */
/*                Delay����[(P1-P0)/V]*1000+[V/(A*100)]*1000                 */
/*********************************************************************************************************************/
/*  ���� WritePosEx(1, 0, 2250, 50);      //���(ID1),������ٶ�V=2250��/��,���ٶ�A=50(50*100��/��^2),������P1=4095  */
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





