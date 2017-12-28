#include "thread_lora.h"
#include "message.h"
#include "stdio.h"
#include "usart.h"
#include "string.h"
#include "mye2prom.h"

TaskThread_t loraThread;

static void TaskLoop(void const * argument)
{

    osEvent ret;

    printf("loraThread taskloop started\r\n");


    while(1)
    {
        // wait for comming commands
        // waiting for the comming characters
        osDelay(1000);
        ret = osSignalWait(0x3, 1000);

        if(ret.status ==  osEventSignal && ret.value.v == 1)
        {
          printf("lorathread signal 1 rx\r\n");
          
        }
        else if(ret.status ==  osEventSignal && ret.value.v == 2)
        {
          printf("lorathread signal 2 rx\r\n");
        }
        else if(ret.status == osEventTimeout)
        {
          printf("lorathread timeout\r\n");
        }
        
    }

}

void LoraThreadInit()
{

    osThreadDef(lorathread, TaskLoop, osPriorityHigh, 0, 128);
    loraThread.idThread = osThreadCreate(osThread(lorathread), NULL);

    if(loraThread.idThread == NULL)
    {

        printf("lorathread create fail\r\n");
    }
    else
    {
        printf("lorathread create OK\r\n");
    }


}
