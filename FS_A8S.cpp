#include "FS_A8S.h"

FS_A8S::FS_A8S()
{
  Serial.begin(115200);
  Serial.println("Setup Done!");
}

void FS_A8S::readRx()
{
  if (Serial.available()) 
  {
    uint8_t val = Serial.read();

    if (index == 0 && val != 0x20) 
    {
      index = 0;
      return;
    }
    if (index == 1 && val != 0x40) 
    {
      index = 1;
      return;
    }

    if (index == BUFFSIZE) 
    {
      index = 0;
      int high = 3;
      int low = 2;

      for (int i = 0; i < MAX_CHANNELS; i++) 
      {
        rawCh[i] = (bus[high] << 8) + bus[low];
        high += 2;
        low += 2;
      }

      for (int i = 0;i < MAX_CHANNELS; i++)
      {
        ch[i] = map(rawCh[i], 1000, 2000, 0, 255);
      }

      return;
    }
    else
    {
      bus[index] = val;
      index++;
    }
  }
}