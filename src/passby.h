#ifndef PASSBY_DATA_H_
#define PASSBY_DATA_H_

void Passby_Proccess();

//各旁路信息
struct Passby_Box  
{
   unsigned int Passby_Port;
   unsigned int Passby_Byte;
   unsigned int Passby_Bit;
}Passby_Box_Struct[9]={{0x01,21,0},{0x01,21,1},{0x01,21,2},{0x01,21,3},{0x01,21,4},{0x01,21,5},{0x01,21,7},{0x01,20,0},{0x01,20,1}};

#endif
