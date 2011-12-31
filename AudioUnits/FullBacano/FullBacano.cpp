/*
*	File:		FullBacano.cpp
*	
*	Version:	1.0
* 
*	Created:	10/31/11
*	
*	Copyright:  Copyright 2011 __MyCompanyName__. All rights reserved.
* 
*	Disclaimer:	IMPORTANT:  This Apple software is supplied to you by Apple Computer, Inc. ("Apple") in 
*				consideration of your agreement to the following terms, and your use, installation, modification 
*				or redistribution of this Apple software constitutes acceptance of these terms.  If you do 
*				not agree with these terms, please do not use, install, modify or redistribute this Apple 
*				software.
*
*				In consideration of your agreement to abide by the following terms, and subject to these terms, 
*				Apple grants you a personal, non-exclusive license, under Apple's Copyrights in this 
*				original Apple software (the "Apple Software"), to use, reproduce, modify and redistribute the 
*				Apple Software, with or without modifications, in source and/or binary forms; provided that if you 
*				redistribute the Apple Software in its entirety and without modifications, you must retain this 
*				notice and the following text and disclaimers in all such redistributions of the Apple Software. 
*				Neither the name, trademarks, service marks or logos of Apple Computer, Inc. may be used to 
*				endorse or promote products derived from the Apple Software without specific prior written 
*				permission from Apple.  Except as expressly stated in this notice, no other rights or 
*				licenses, express or implied, are granted by Apple herein, including but not limited to any 
*				patent rights that may be infringed by your derivative works or by other works in which the 
*				Apple Software may be incorporated.
*
*				The Apple Software is provided by Apple on an "AS IS" basis.  APPLE MAKES NO WARRANTIES, EXPRESS OR 
*				IMPLIED, INCLUDING WITHOUT LIMITATION THE IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY 
*				AND FITNESS FOR A PARTICULAR PURPOSE, REGARDING THE APPLE SOFTWARE OR ITS USE AND OPERATION ALONE 
*				OR IN COMBINATION WITH YOUR PRODUCTS.
*
*				IN NO EVENT SHALL APPLE BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL OR CONSEQUENTIAL 
*				DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS 
*				OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) ARISING IN ANY WAY OUT OF THE USE, 
*				REPRODUCTION, MODIFICATION AND/OR DISTRIBUTION OF THE APPLE SOFTWARE, HOWEVER CAUSED AND WHETHER 
*				UNDER THEORY OF CONTRACT, TORT (INCLUDING NEGLIGENCE), STRICT LIABILITY OR OTHERWISE, EVEN 
*				IF APPLE HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/
/*=============================================================================
	FullBacano.cpp
	
=============================================================================*/
//#import <Foundation/Foundation.h>
#include "FullBacano.h"
#include "math.h"
#include <iostream>
#include <fstream>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

COMPONENT_ENTRY(FullBacano)


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	FullBacano::FullBacano
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
FullBacano::FullBacano (AudioUnit component) : AUEffectBase (component) {
  /*  ofstream logFile;
    logFile.open ("debugLog.raw");
    logFile << "Writing this to a file.\n";
    logFile.close();
    */
    
    
    
    CreateElements ();
    Globals () -> UseIndexedParameters (kNumberOfParameters);
    
    SetParameter (                                       // 1
                  kParameter_Frequency,
                  kDefaultValue_FullBacano_Freq
                  );
    
    SetParameter (                                       // 2
                  kParameter_Bacaneria,
                  kDefaultValue_FullBacano_Bacaneria
                  );
    
    
   SetParameter (                                       // 2
                  kParameter_Ganancia,
                  kDefaultValue_FullBacano_Ganancia
                  );

    
    
    SetParameter (                                       // 3
                  kParameter_LaMondaEnElVolco,
                  kDefaultValue_FullBacano_LaMondaEnElVolco
                  );
    
    // code for setting default values for the audio unit parameters
    SetAFactoryPresetAsCurrent (                    // 1
                                kPresets [kPreset_Default]
                                );
    
#if AU_DEBUG_DISPATCHER
    mDebugDispatcher = new AUDebugDispatcher (this);
#endif
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	FullBacano::GetParameterValueStrings
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ComponentResult FullBacano::GetParameterValueStrings (
                                                      AudioUnitScope          inScope,
                                                      AudioUnitParameterID    inParameterID,
                                                      CFArrayRef              *outStrings
                                                      ) {
    if ((inScope == kAudioUnitScope_Global) &&             // 1
        (inParameterID == kParameter_LaMondaEnElVolco)) {
        
        if (outStrings == NULL) return noErr;              // 2
        
        CFStringRef strings [] = {                         // 3
            kMenuItem_FullBacano_Queso,
            kMenuItem_FullBacano_Zipo,
            kMenuItem_FullBacano_Troque,
            kMenuItem_FullBacano_Eerda,
            
        };
        
        *outStrings = CFArrayCreate (                      // 4
                                     NULL,
                                     (const void **) strings,
                                     (sizeof (strings) / sizeof (strings [0])),     // 5
                                     NULL
                                     );
        return noErr;
    }
    return kAudioUnitErr_InvalidParameter;
}





//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	FullBacano::GetParameterInfo
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#pragma mark ____Parameters
ComponentResult FullBacano::GetParameterInfo (
                                               AudioUnitScope          inScope,
                                               AudioUnitParameterID    inParameterID,
                                               AudioUnitParameterInfo  &outParameterInfo
                                               ) {
    ComponentResult result = noErr;
    
    outParameterInfo.flags =    kAudioUnitParameterFlag_IsWritable        // 1
    | kAudioUnitParameterFlag_IsReadable;
    
    if (inScope == kAudioUnitScope_Global) {                              // 2
        switch (inParameterID) {
            case kParameter_Frequency:                                    // 3
                AUBase::FillInParameterName (
                                             outParameterInfo,
                                             kParamName_FullBacano_Freq,
                                             false
                                             );
                outParameterInfo.unit =                                   // 4
                kAudioUnitParameterUnit_Hertz;
                outParameterInfo.minValue =                               // 5
                kMinimumValue_FullBacano_Freq;
                outParameterInfo.maxValue =                               // 6
                kMaximumValue_FullBacano_Freq;
                outParameterInfo.defaultValue =                           // 7
                kDefaultValue_FullBacano_Freq;
                outParameterInfo.flags                                    // 8
                |= kAudioUnitParameterFlag_DisplayLogarithmic;
                break;
                
            case kParameter_Bacaneria:                                        // 9
                AUBase::FillInParameterName (
                                             outParameterInfo,
                                             kParamName_FullBacano_Bacaneria,
                                             false
                                             );
                outParameterInfo.unit =                                   // 10
                kAudioUnitParameterUnit_Percent;
                outParameterInfo.minValue =
                kMinimumValue_FullBacano_Bacaneria;
                outParameterInfo.maxValue =
                kMaximumValue_FullBacano_Bacaneria;
                outParameterInfo.defaultValue =
                kDefaultValue_FullBacano_Bacaneria;
                break;
                
            case kParameter_Ganancia:                                        // 9
                AUBase::FillInParameterName (
                                             outParameterInfo,
                                             kParamName_FullBacano_Ganancia,
                                             false
                                             );
                outParameterInfo.unit =                                   // 10
                kAudioUnitParameterUnit_Percent;
                outParameterInfo.minValue =
                kMinimumValue_FullBacano_Ganancia;
                outParameterInfo.maxValue =
                kMaximumValue_FullBacano_Ganancia;
                outParameterInfo.defaultValue =
                kDefaultValue_FullBacano_Ganancia;
                break;

            case kParameter_LaMondaEnElVolco:                                     // 11
                AUBase::FillInParameterName (
                                             outParameterInfo,
                                             kParamName_FullBacano_LaMondaEnElVolco,
                                             false
                                             );
                outParameterInfo.unit =                                   // 12
                kAudioUnitParameterUnit_Indexed;
                outParameterInfo.minValue =
                kZipoSpeaker_FullBacano_LaMondaEnElVolco;
                outParameterInfo.maxValue =
                kTroqueSpeaker_FullBacano_LaMondaEnElVolco;
                outParameterInfo.defaultValue =
                kDefaultValue_FullBacano_LaMondaEnElVolco;
                break;
                
            default:
                result = kAudioUnitErr_InvalidParameter;
                break;
        }
    } else {
        result = kAudioUnitErr_InvalidParameter;
    }
    return result;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	FullBacano::GetPropertyInfo
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
OSStatus			FullBacano::GetPropertyInfo (AudioUnitPropertyID	inID,
                                                        AudioUnitScope		inScope,
                                                        AudioUnitElement	inElement,
                                                        UInt32 &		outDataSize,
                                                        Boolean &		outWritable)
{
	if (inScope == kAudioUnitScope_Global) 
	{
		switch (inID) 
		{
			case kAudioUnitProperty_CocoaUI:
				outWritable = false;
				outDataSize = sizeof (AudioUnitCocoaViewInfo);
				return noErr;
					
		}
	}

	return AUEffectBase::GetPropertyInfo (inID, inScope, inElement, outDataSize, outWritable);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	FullBacano::GetProperty
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
OSStatus			FullBacano::GetProperty(	AudioUnitPropertyID inID,
															AudioUnitScope 		inScope,
															AudioUnitElement 	inElement,
															void *				outData )
{
	if (inScope == kAudioUnitScope_Global) 
	{
		switch (inID) 
		{
			case kAudioUnitProperty_CocoaUI:
			{
				// Look for a resource in the main bundle by name and type.
				CFBundleRef bundle = CFBundleGetBundleWithIdentifier( CFSTR("com.audiounit.FullBacano") );
				
				if (bundle == NULL) return fnfErr;
                
				CFURLRef bundleURL = CFBundleCopyResourceURL( bundle, 
                    CFSTR("FullBacanoCocoaViewFactory"), 
                    CFSTR("bundle"), 
                    NULL);
                
                if (bundleURL == NULL) return fnfErr;

				AudioUnitCocoaViewInfo cocoaInfo;
				cocoaInfo.mCocoaAUViewBundleLocation = bundleURL;
				cocoaInfo.mCocoaAUViewClass[0] = CFStringCreateWithCString(NULL, "FullBacanoCocoaViewFactory", kCFStringEncodingUTF8);
				
				*((AudioUnitCocoaViewInfo *)outData) = cocoaInfo;
				
				return noErr;
			}
		}
	}


	return AUEffectBase::GetProperty (inID, inScope, inElement, outData);
}

#pragma mark ____Factory Presets
ComponentResult FullBacano::GetPresets (                     // 1
                                         CFArrayRef *outData
                                         ) const {
    
    if (outData == NULL) return noErr;                        // 2
    
    CFMutableArrayRef presetsArray = CFArrayCreateMutable (   // 3
                                                           NULL,
                                                           kNumberPresets,
                                                           NULL
                                                           );
    
    for (int i = 0; i < kNumberPresets; ++i) {                // 4
        CFArrayAppendValue (
                            presetsArray,
                            &kPresets [i]
                            );
    }
    
    *outData = (CFArrayRef) presetsArray;                     // 5
    return noErr;
}

OSStatus FullBacano::NewFactoryPresetSet (                         // 1
                                           const AUPreset &inNewFactoryPreset
                                           ) {
    SInt32 chosenPreset = inNewFactoryPreset.presetNumber;          // 2
    
    if (                                                            // 3
        chosenPreset == kPreset_Mera ||
        chosenPreset == kPreset_NoTanBacano
        ) {
        for (int i = 0; i < kNumberPresets; ++i) {                  // 4
            if (chosenPreset == kPresets[i].presetNumber) {
                switch (chosenPreset) {                             // 5
                        
                    case kPreset_Mera:                              // 6
                        SetParameter (                              // 7
                                      kParameter_Frequency,
                                      kParameter_Preset_Frequency_Mera
                                      );
                        SetParameter (                              // 8
                                      kParameter_Bacaneria,
                                      kParameter_Preset_Bacaneria_Mera
                                      );
                        SetParameter (                              // 9
                                      kParameter_LaMondaEnElVolco,
                                      kParameter_Preset_LaMondaEnElVolco_Mera
                                      );
                        break;
                        
                    case kPreset_NoTanBacano:                             // 10
                        SetParameter (
                                      kParameter_Frequency,
                                      kParameter_Preset_Frequency_NoTanBacano
                                      );
                        SetParameter (
                                      kParameter_Bacaneria,
                                      kParameter_Preset_Bacaneria_NoTanBacano
                                      );
                        SetParameter (
                                      kParameter_LaMondaEnElVolco,
                                      kParameter_Preset_LaMondaEnElVolco_NoTanBacano
                                      );
                        break;
                }
                SetAFactoryPresetAsCurrent (                        // 11
                                            kPresets [i]
                                            );
                return noErr;                                       // 12
            }
        }
    }
    return kAudioUnitErr_InvalidProperty;                           // 13
}
#pragma mark ____FullBacanoEffectKernel


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	FullBacano::FullBacanoKernel::Reset()
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void		FullBacano::FullBacanoKernel::Reset()
{
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	FullBacano::FullBacanoKernel::Process
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void		FullBacano::FullBacanoKernel::Process(	const Float32 	*inSourceP,
                                                    Float32		 	*inDestP,
                                                    UInt32 			inFramesToProcess,
                                                    UInt32			inNumChannels, // for version 2 AudioUnits inNumChannels is always 1
                                                    bool			&ioSilence )
{
    if(!ioSilence)
    {    
	//This code will pass-thru the audio data.
	//This is where you want to process data to produce an effect.

	
	UInt32 nSampleFrames = inFramesToProcess;
	const Float32 *sourceP = inSourceP;
	Float32 *destP = inDestP;
	Float32 outputSample, distortedSample;
        Float32 Threshold=0.333330000000000;//333333333333;
    Float32 gain = (GetParameter( kParameter_Ganancia )/100);
	Float32 BacaneriaDepth= (GetParameter( kParameter_Bacaneria)/100);
	while (nSampleFrames-- > 0) {
    Float32 inputSample = *sourceP;
        distortedSample=0;  
		//NSLog("Distorted sample %i",23);
		//The current (version 2) AudioUnit specification *requires* 
	    //non-interleaved format for all inputs and outputs. Therefore inNumChannels is always 1
		
		//sourceP += inNumChannels;	// advance to next frame (e.g. if stereo, we're advancing 2 samples);
									// we're only processing one of an arbitrary number of interleaved channels

			// here's where you do your DSP work
      
      /* if(inputSample<Threshold)             
            distortedSample = inputSample * 2;
		
        if(inputSample>Threshold)            
            {
            distortedSample=(2-inputSample)*3;
            distortedSample*=distortedSample;   
            distortedSample=(3-distortedSample)/3;   
            }
        
        if(inputSample<(-1*Threshold)) distortedSample*=-1;

        if(inputSample>2*Threshold)            
            {
            if(inputSample>0) distortedSample=1;
            if(inputSample<0) distortedSample=-1;
            }
        */            
   
         if(fabs(inputSample)<Threshold)             
         distortedSample = 2*inputSample ;
         
         if(fabs(inputSample)>=Threshold)            
         {
             if(inputSample>0)
             { 
                 if(fabs(inputSample)>2*Threshold) distortedSample=1;
                 else distortedSample=(3-(powf((2-inputSample*3),2)))/3;
                
             }
            if(inputSample<0)
             {
                 if(fabs(inputSample)>2*Threshold) distortedSample=-1;
                else distortedSample=-(3-(powf((2-inputSample*3),2)))/3;
             }
         }
         
         
                   
                                   
        
        
        
        
        
        
        
        
        distortedSample=distortedSample*BacaneriaDepth;
        outputSample=inputSample+distortedSample;
        
        outputSample=outputSample*gain;
          *destP = outputSample;
		destP += inNumChannels;
        sourceP += inNumChannels;
        }
    }
}
