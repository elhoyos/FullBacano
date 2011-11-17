#pragma once 

class FullBacanoDSP{
	 private: 
			float distortion;
			float level; -I../include

   public:
			FullBacanoDSP::FullBacanoDSP();
			void setDistortion(float distortion);
			void setLevel(float level);
			void process(unsigned int nSamples, float *inBuf, float *outBuf);
};
