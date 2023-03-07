#include "xparameters.h"
#include "xil_printf.h"
#include "xgpio.h"
#include "xil_types.h"
#include "xil_io.h"

#define BTN_ID XPAR_AXI_GPIO_BUTTONS_DEVICE_ID
#define LED_ID XPAR_AXI_GPIO_LED_DEVICE_ID
#define BTN_CHANNEL 1
#define LED_CHANNEL 1
#define BTN_MASK 0xFF
#define LED_MASK 0xAA

#define PWM_MAX 8100
#define PMW_DUTY_10 (PWM_MAX * 0.10)
#define PWM_DUTY_50 (PWM_MAX * 0.50)
#define PWM_DUTY_75 (PWM_MAX * 0.75)

//value from address editor in vivado
#define MY_PWM XPAR_CUSTOMPWM_0_S00_AXI_BASEADDR

int main()
{
	XGpio_Config *cfg_ptr;
	XGpio led_device, btn_device;
	u32 data;

	xil_printf("Entered function main\r\n");

	// Initialize LED Device
	cfg_ptr = XGpio_LookupConfig(LED_ID);
	XGpio_CfgInitialize(&led_device, cfg_ptr, cfg_ptr->BaseAddress);

	// Initialize Button Device
	cfg_ptr = XGpio_LookupConfig(BTN_ID);
	XGpio_CfgInitialize(&btn_device, cfg_ptr, cfg_ptr->BaseAddress);

	// Set Button Tristate
	XGpio_SetDataDirection(&btn_device, BTN_CHANNEL, BTN_MASK);

	// Set Led Tristate
	XGpio_SetDataDirection(&led_device, LED_CHANNEL, 0);

	Xil_Out32(MY_PWM, PWM_DUTY_50);
	Xil_Out32(MY_PWM+4, 810);
	Xil_Out32(MY_PWM+8, PWM_DUTY_75);
	Xil_Out32(MY_PWM+12, PMW_DUTY_10);

	float percent = 0.0;
	u32 duty_cycle = (u32)(PWM_MAX * percent);
	u8 state_changed = 0;
	while (1) {
		data = XGpio_DiscreteRead(&btn_device, BTN_CHANNEL);
		data &= BTN_MASK;
		if (data != 0) {
			data = LED_MASK;
			state_changed = 1;
			percent += 0.1;
			if(percent >= 1)
				percent = 0.0;
			duty_cycle = (u32)(PWM_MAX * percent);
		} else {
			data = 0;
		}

		if(state_changed){
			state_changed = 0;
			Xil_Out32(MY_PWM, duty_cycle);
		}

		XGpio_DiscreteWrite(&led_device, LED_CHANNEL, data);
	}
}
