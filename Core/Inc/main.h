/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

#include "hci_tl_interface.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SPBTLE_RF_IRQ_EXTI6_Pin GPIO_PIN_6
#define SPBTLE_RF_IRQ_EXTI6_GPIO_Port GPIOE
#define SPBTLE_RF_IRQ_EXTI6_EXTI_IRQn EXTI9_5_IRQn
#define LeftStick_X_Pin GPIO_PIN_0
#define LeftStick_X_GPIO_Port GPIOC
#define LeftStick_Y_Pin GPIO_PIN_1
#define LeftStick_Y_GPIO_Port GPIOC
#define RightStick_X_Pin GPIO_PIN_2
#define RightStick_X_GPIO_Port GPIOC
#define RightStick_Y_Pin GPIO_PIN_3
#define RightStick_Y_GPIO_Port GPIOC
#define XINPUT_GAMEPAD_B_Pin GPIO_PIN_0
#define XINPUT_GAMEPAD_B_GPIO_Port GPIOA
#define XINPUT_GAMEPAD_A_Pin GPIO_PIN_1
#define XINPUT_GAMEPAD_A_GPIO_Port GPIOA
#define XINPUT_GAMEPAD_DPAD_UP_Pin GPIO_PIN_2
#define XINPUT_GAMEPAD_DPAD_UP_GPIO_Port GPIOA
#define XINPUT_GAMEPAD_START_Pin GPIO_PIN_3
#define XINPUT_GAMEPAD_START_GPIO_Port GPIOA
#define XINPUT_GAMEPAD_RIGHT_THUMB_Pin GPIO_PIN_4
#define XINPUT_GAMEPAD_RIGHT_THUMB_GPIO_Port GPIOA
#define XINPUT_GAMEPAD_DPAD_RIGHT_Pin GPIO_PIN_5
#define XINPUT_GAMEPAD_DPAD_RIGHT_GPIO_Port GPIOA
#define XINPUT_GAMEPAD_DPAD_LEFT_Pin GPIO_PIN_6
#define XINPUT_GAMEPAD_DPAD_LEFT_GPIO_Port GPIOA
#define XINPUT_GAMEPAD_DPAD_DOWN_Pin GPIO_PIN_7
#define XINPUT_GAMEPAD_DPAD_DOWN_GPIO_Port GPIOA
#define LeftTrigger_Pin GPIO_PIN_4
#define LeftTrigger_GPIO_Port GPIOC
#define RightTrigger_Pin GPIO_PIN_5
#define RightTrigger_GPIO_Port GPIOC
#define XINPUT_GAMEPAD_Y_Pin GPIO_PIN_0
#define XINPUT_GAMEPAD_Y_GPIO_Port GPIOB
#define XINPUT_GAMEPAD_LEFT_THUMB_Pin GPIO_PIN_1
#define XINPUT_GAMEPAD_LEFT_THUMB_GPIO_Port GPIOB
#define XINPUT_GAMEPAD_LEFT_SHOULDER_Pin GPIO_PIN_2
#define XINPUT_GAMEPAD_LEFT_SHOULDER_GPIO_Port GPIOB
#define LED2_Pin GPIO_PIN_14
#define LED2_GPIO_Port GPIOB
#define SPBTLE_RF_SPI3_CSN_Pin GPIO_PIN_13
#define SPBTLE_RF_SPI3_CSN_GPIO_Port GPIOD
#define XINPUT_GAMEPAD_X_Pin GPIO_PIN_14
#define XINPUT_GAMEPAD_X_GPIO_Port GPIOD
#define LED3_WIFI__LED4_BLE_Pin GPIO_PIN_9
#define LED3_WIFI__LED4_BLE_GPIO_Port GPIOC
#define SPBTLE_RF_RST_Pin GPIO_PIN_8
#define SPBTLE_RF_RST_GPIO_Port GPIOA
#define USB_OTG_FS_VBUS_Pin GPIO_PIN_9
#define USB_OTG_FS_VBUS_GPIO_Port GPIOA
#define USB_OTG_FS_ID_Pin GPIO_PIN_10
#define USB_OTG_FS_ID_GPIO_Port GPIOA
#define USB_OTG_FS_DM_Pin GPIO_PIN_11
#define USB_OTG_FS_DM_GPIO_Port GPIOA
#define USB_OTG_FS_DP_Pin GPIO_PIN_12
#define USB_OTG_FS_DP_GPIO_Port GPIOA
#define SYS_JTMS_SWDIO_Pin GPIO_PIN_13
#define SYS_JTMS_SWDIO_GPIO_Port GPIOA
#define SYS_JTCK_SWCLK_Pin GPIO_PIN_14
#define SYS_JTCK_SWCLK_GPIO_Port GPIOA
#define XINPUT_GAMEPAD_RIGHT_SHOULDER_Pin GPIO_PIN_15
#define XINPUT_GAMEPAD_RIGHT_SHOULDER_GPIO_Port GPIOA
#define INTERNAL_SPI3_SCK_Pin GPIO_PIN_10
#define INTERNAL_SPI3_SCK_GPIO_Port GPIOC
#define INTERNAL_SPI3_MISO_Pin GPIO_PIN_11
#define INTERNAL_SPI3_MISO_GPIO_Port GPIOC
#define INTERNAL_SPI3_MOSI_Pin GPIO_PIN_12
#define INTERNAL_SPI3_MOSI_GPIO_Port GPIOC
#define SYS_JTD0_SWO_Pin GPIO_PIN_3
#define SYS_JTD0_SWO_GPIO_Port GPIOB
#define XINPUT_GAMEPAD_BACK_Pin GPIO_PIN_4
#define XINPUT_GAMEPAD_BACK_GPIO_Port GPIOB
#define ST_LINK_UART1_TX_Pin GPIO_PIN_6
#define ST_LINK_UART1_TX_GPIO_Port GPIOB
#define ST_LINK_UART1_RX_Pin GPIO_PIN_7
#define ST_LINK_UART1_RX_GPIO_Port GPIOB
#define ARD_D15_Pin GPIO_PIN_8
#define ARD_D15_GPIO_Port GPIOB
#define ARD_D14_Pin GPIO_PIN_9
#define ARD_D14_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
