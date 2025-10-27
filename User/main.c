/**
 ****************************************************************************************************
 * @file        main.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2023-04-23
 * @brief       �����ʵ��
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 * 
 * ʵ��ƽ̨:����ԭ�� M144Z-M4��Сϵͳ��STM32F407��
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 * 
 ****************************************************************************************************
 */

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/LED/led.h"
#include "SEGGER_RTT.h"

#define LOG_TAG "main"
#include "elog.h"
uint8_t RTT_BufferUp0[1024]={0}; /* �������л����� */
uint8_t RTT_BufferDown0[16]={0};  /* �������л����� */
int main(void)
{
    HAL_Init();                         /* ��ʼ��HAL�� */
    sys_stm32_clock_init(336, 8, 2, 7); /* ����ʱ�ӣ�168MHz */
    delay_init(168);                    /* ��ʼ����ʱ */
    usart_init(115200);                 /* ��ʼ������ */
    led_init();                         /* ��ʼ��LED */

    elog_init();
    elog_set_fmt(ELOG_LVL_ASSERT, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    elog_set_fmt(ELOG_LVL_ERROR, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    elog_set_fmt(ELOG_LVL_WARN, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    elog_set_fmt(ELOG_LVL_INFO, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    elog_set_fmt(ELOG_LVL_DEBUG, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    elog_set_fmt(ELOG_LVL_VERBOSE, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    elog_start();

    SEGGER_RTT_ConfigUpBuffer(0,          /* ͨ��0 */
                            "Terminal", /* ���� */
                            (void*)RTT_BufferUp0,      /* ���л����� */
                            sizeof(RTT_BufferUp0), /* ��С */
                            SEGGER_RTT_MODE_NO_BLOCK_SKIP); /* ������ģʽ */
    SEGGER_RTT_ConfigDownBuffer(0,            /* ͨ��0 */
                              "Terminal",   /* ���� */
                              (void*)RTT_BufferDown0,    /* ���л����� */
                              sizeof(RTT_BufferDown0), /* ��С */
                              SEGGER_RTT_MODE_NO_BLOCK_SKIP); /* ������ģʽ */
    while (1)
    {
        LED0(0);        /* ����LED0 */
        LED1(1);        /* �ر�LED1 */
        log_v("Hello EasyLogger!");
        log_d("Hello EasyLogger!");
        log_i("Hello EasyLogger!");
        log_w("Hello EasyLogger!");
        log_e("Hello EasyLogger!");
        log_a("Hello EasyLogger!");
        
        //elog_flush();  // ˢ����־�����������ȷ����־��ʱ���
        delay_ms(500);  /* ��ʱ500���� */
    }
}
