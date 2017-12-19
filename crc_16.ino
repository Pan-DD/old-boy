#include <stdlib.h>

int8_t  data[1]={0x01};
int16_t result_crc16; 
char str[4];
String c="";

//=============================================================================================
const static int POLYNOMIAL   = 0x8408;
const static int PRESET_VALUE = 0xFFFF;
uint16_t crc16(uint8_t *data, uint16_t length)
{
    unsigned int current_crc_value = PRESET_VALUE;

    for (int i = 0; i < length; i++ ) {
        current_crc_value ^= data[i] & 0xFF;
        for (int j = 0; j < 8; j++) {
            if ((current_crc_value & 1) != 0) {
                current_crc_value = (current_crc_value >> 1) ^ POLYNOMIAL;
            } else {
                current_crc_value = current_crc_value >> 1;
            }
        }
    }
    current_crc_value = ~current_crc_value;

    //return (int16_t)(current_crc_value & 0xFFFF);
    return current_crc_value;
}


//=============================================================================================
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
result_crc16=crc16(data,1);
sprintf(str,"%04X",result_crc16);
}

void loop() {
  // put your main code here, to run repeatedly:
  
result_crc16=crc16(data,1);
sprintf(str,"%04X",result_crc16);  
Serial.println(str);

delay(2000);
/*for(int i=2;i<4;i++)                        //反向输出
Serial.print(str[i]);
for(int i=0;i<2;i++)
Serial.print(str[i]);
Serial.println();
delay(2000);*/

}







