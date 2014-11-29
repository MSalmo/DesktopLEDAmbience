#include "LEDInfo.h"
/* ActiveLEDInfo Declarations */

ActiveLEDInfo::ActiveLEDInfo(){
	step = (float*)malloc(3*sizeof(float));
	deltas = (float*)malloc(3*sizeof(float));
	carryOver = (float*)malloc(3*sizeof(float));

	isActive = false;
}

ActiveLEDInfo::~ActiveLEDInfo(){
	free(curColor);
	free(step);
	free(deltas);
	free(carryOver);
}

void ActiveLEDInfo::setTargetColor(uint32_t colorInfo) {
		if(tgtColor != NULL)
			free(tgtColor);
		tgtColor=new uint8_t[3];

		tgtColor[0] = (colorInfo%256);			//Blue
		tgtColor[1] = (colorInfo >> 8) % 256;	//Green
		tgtColor[2] = (colorInfo >> 16) % 256;	//Red

		tgtColorAsUINT32 = colorInfo;

}

void ActiveLEDInfo::setStepValues() {
  
  		//curColor[2] = curColor % 256;        //Old Blue Value
  		deltas[2] = (int)tgtColor[2] - (int)curColor[2];
  
  		//curColor[1] = (curColor >> 8) % 256; //Old Green Value
  		deltas[1] = (int)tgtColor[1] - (int)curColor[1];
  
  		//curColor[0] = (curColor >> 16) % 256;//Old Red Value
  		deltas[0] = (int)tgtColor[0] - (int)curColor[0];

		int absDelta0 = abs(deltas[0]);
		int absDelta1 = abs(deltas[1]);
  		int absDelta2 = abs(deltas[2]);
  		int farthest = max(max(absDelta0,absDelta1),absDelta2);
  
  		//Flip the denom and the num, use modf to extract carryover.
  		float carryValR = (1.0f*deltas[0]/farthest);
  		float carryValG = (1.0f*deltas[1]/farthest); 
  		float carryValB = (1.0f*deltas[2]/farthest);
  
  
  		carryOver[0] = modf(carryValR, &(step[0]));
  		carryOver[1] = modf(carryValG, &(step[1]));
  		carryOver[2] = modf(carryValB, &(step[2]));

		if(carryValR < 0)
    		step[0] = 0 - step[0];
  		if(carryValG < 0)
    		step[1] = 0 - step[1];
  		if(carryValB < 0)
    		step[2] = 0 - step[2]; 
}
void ActiveLEDInfo::processStep(){
	if(tgtColor[0] != curColor[0]){
      curColor[0] = curColor[0] + step[0];
      
      carryOver[0] += step[0];
      if(carryOver[0] >= 1.0){
        curColor[0]++;
        carryOver[0]--;
      }
      if(carryOver[0] <= -1.0){
        curColor[0]--;
        carryOver[0]++;
      }
    }
    if(tgtColor[1] != curColor[1]){
      curColor[1] = curColor[1] + step[1];
      carryOver[1] += carryOver[1];
      
      if(carryOver[1] >= 1.0){
        curColor[1]++;
        carryOver[1]--;
      }
      if(carryOver[1] <= -1.0){
        curColor[1]--;
        carryOver[1]++;
      }    
    }
   if(tgtColor[2] != curColor[2]){
      curColor[2] = curColor[2] + step[2];
      
      carryOver[2] += carryOver[2];
    
      if(carryOver[2] >= 1.0){
        curColor[2]++;
        carryOver[2]--;
      }
      if(carryOver[2] <= -1.0){
        curColor[2]--;
        carryOver[2]++;
      }
  	} 
}