#ifndef __CHASSIS_H
#define __CHASSIS_H

#include "can.h"
#include "stm32f4xx_hal.h"


#define		ABS(x)		((x) > 0 ? (x) : -(x)) 

typedef enum {
	S_VER   = 0,			/* 读取固件版本和对应的硬件版本 */
	S_RL    = 1,			/* 读取读取相电阻和相电感 */
	S_PID   = 2,			/* 读取PID参数 */
	S_VBUS  = 3,			/* 读取总线电压 */
	S_CPHA  = 5,			/* 读取相电流 */
	S_ENCL  = 7,			/* 读取经过线性化校准后的编码器值 */
	S_TPOS  = 8,			/* 读取电机目标位置角度 */
	S_VEL   = 9,			/* 读取电机实时转速 */
	S_CPOS  = 10,			/* 读取电机实时位置角度 */
	S_PERR  = 11,			/* 读取电机位置误差角度 */
	S_FLAG  = 13,			/* 读取使能/到位/堵转状态标志位 */
	S_Conf  = 14,			/* 读取驱动参数 */
	S_State = 15,			/* 读取系统状态参数 */
	S_ORG   = 16,     /* 读取正在回零/回零失败状态标志位 */
}SysParams_t;


void Chassis_Reset_CurPos_To_Zero(uint8_t addr); // 将当前位置清零
void Chassis_Reset_Clog_Pro(uint8_t addr); // 解除堵转保护
void Chassis_Read_Sys_Params(uint8_t addr, SysParams_t s); // 读取参数
void Chassis_Modify_Ctrl_Mode(uint8_t addr, bool svF, uint8_t ctrl_mode); // 发送命令修改开环/闭环控制模式
void Chassis_En_Control(uint8_t addr, bool state, bool snF); // 电机使能控制
void Chassis_Vel_Control(uint8_t addr, uint8_t dir, uint16_t vel, uint8_t acc, bool snF); // 速度模式控制
void Chassis_Pos_Control(uint8_t addr, uint8_t dir, uint16_t vel, uint8_t acc, uint32_t clk, bool raF, bool snF); // 位置模式控制
void Chassis_Stop_Now(uint8_t addr, bool snF); // 让电机立即停止运动
void Chassis_Synchronous_motion(uint8_t addr); // 触发多机同步开始运动
void Chassis_Origin_Set_O(uint8_t addr, bool svF); // 设置挡圈回零的零点位置
void Chassis_Origin_Modify_Params(uint8_t addr, bool svF, uint8_t o_mode, uint8_t o_dir, uint16_t o_vel, uint32_t o_tm, uint16_t sl_vel, uint16_t sl_ma, uint16_t sl_ms, bool potF); // 修改回零参数
void Chassis_Origin_Trigger_Return(uint8_t addr, uint8_t o_mode, bool snF); // 发送命令触发回零
void Chassis_Origin_Interrupt(uint8_t addr); // 强制中断并退出回零


void Chasssis_Test(void);
void Chassis_response(void); //等待底盘初始化应答函数
uint32_t Chassis_Read_Loc(void);        //位置读取
void Chassis_Forward(uint16_t vel, uint8_t acc, uint32_t clk);
void Chassis_Backward(uint16_t vel, uint8_t acc, uint32_t clk);
void Chassis_Left(uint16_t vel, uint8_t acc, uint32_t clk);
void Chassis_Right(uint16_t vel, uint8_t acc, uint32_t clk);

#endif
