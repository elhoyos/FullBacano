#include "fullBacanoDsp.h"
#include <math.h>

#define THRESHOLD 0.333333333333333333333333333333

FullBacanoDSP::FullBacanoDSP(){
	 this->distortion = 0.0;
	 this->level = 0.0;
}

void FullBacanoDSP::setLevel(float level){
	 // distortion must be between 0 and 100
	 if(level > 100.0){
			// TODO: throw error
			this->level = 100.0;
	 }
	 else if(level < 0.0){
			// TODO: throw error
			this->level = 0.0;
	 }
	 else{
			this->level = level;	 
	 }
}

void FullBacanoDSP::setDist(float distortion){
	 // distortion must be between 0 and 100
	 if(distortion > 100.0){
			// TODO: throw error
			this->distortion = 100.0;
	 }
	 else if(distortion < 0.0){
			// TODO: throw error
			this->distortion = 0.0;
	 }
	 else{
			this->distortion = distortion;	 
	 }
}

void FullBacanoDSP::process(unsigned int nSamples, float *inBuf, float *outBuf){
	 for(unsigned int i=0; i<nSamples; i++){
			if(&inBuf < THRESHOLD)             
				 &outBuf = &inBuf * 2;

			if(&inBuf > THRESHOLD){
				 &outBuf = pow(3 * (2 - &inBuf), 2);
				 // &outBuf *= BacanizedSample;   
				 // &outBuf = (3-BacanizedSampleoutBuf)/3;   
			}

			// if(inputSample<(-1*Threshold)) BacanizedSample*=-1;

			// if(inputSample>2*Threshold)            
			// {
			//    if(inputSample>0) BacanizedSample=1;
			//    if(inputSample<0) BacanizedSample=-1;
			// }
			// BacanizedSample=BacanizedSample*BacaneriaDepth;
			// outputSample=inputSample+BacanizedSample;

			// outputSample=outputSample*gain;
			// *destP = outputSample;
			// destP += inNumChannels;
			// sourceP += inNumChannels;
	 }
