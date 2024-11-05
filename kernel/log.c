#include <log.h>
#include <tasks.h>

#define LOGQUEUE_SIZE 512
#define LOGQUEUE_END (logQueue + LOGQUEUE_SIZE)

Task *taskLog;

uint8_t logQueue[LOGQUEUE_SIZE];
uint8_t *logQueueHead;
uint8_t *logQueueTail;
volatile uint8_t logReady;

void task_logger()
{
    while (1)
    {
        while (logQueueTail != logQueueHead)
        {
            __Log_SendByte(*(logQueueTail)++);
            if (logQueueTail == LOGQUEUE_END)
                logQueueTail = logQueue;
        }
    }
}

void Log_Init()
{
    __Log_Init();

    taskLog = Task_New(task_logger, 1, 128);
    logQueueHead = logQueue;
    logQueueTail = logQueue;
    logReady = 0;
}

void Log_SendByte(uint8_t b)
{
    *(logQueueHead++) = b;

    if (logQueueHead == LOGQUEUE_END)
        logQueueHead = logQueue;
}

void Log_SendLine(uint8_t *str)
{
    while (*str)
    {
        Log_SendByte(*(str++));
    }
    Log_SendByte('\n');
}

void Log_Printf(uint8_t *format, uint8_t *s_arg, int32_t d_arg, uint32_t x_arg)
{
    const uint8_t *p = format;

    while (*p)
    {
        if (*p == '%')
        {
            p++;
            if (*p == 's')
            {
                while (*s_arg)
                {
                    Log_SendByte(*s_arg++);
                }
            }
            else if (*p == 'd')
            {
                int32_t num = d_arg;
                if (num < 0)
                {
                    Log_SendByte('-');
                    num = -num;
                }

                uint8_t buffer[10];
                int32_t i = 0;
                do
                {
                    buffer[i++] = (num % 10) + '0';
                    num /= 10;
                } while (num);

                while (i--)
                {
                    Log_SendByte(buffer[i]);
                }
            }
            else if (*p == 'x')
            {
                uint32_t num = x_arg;
                uint8_t buffer[8];
                int32_t i = 0;

                do
                {
                    int32_t digit = num % 16;
                    if (digit < 10)
                    {
                        buffer[i++] = digit + '0';
                    }
                    else
                    {
                        buffer[i++] = digit - 10 + 'a';
                    }
                    num /= 16;
                } while (num);

                while (i--)
                {
                    Log_SendByte(buffer[i]);
                }
            }
        }
        else
        {
            Log_SendByte(*p);
        }
        p++;
    }

    Log_SendByte('\n');
}
