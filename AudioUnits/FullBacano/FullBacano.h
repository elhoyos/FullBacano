/*
*	File:		FullBacano.h
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


#include "AUEffectBase.h"
#include "FullBacanoVersion.h"

#if AU_DEBUG_DISPATCHER
	#include "AUDebugDispatcher.h"
#endif


#ifndef __FullBacano_h__
#define __FullBacano_h__


#pragma mark ____FullBacano Parameters


#pragma mark ____FullBacano Parameter Constants

static CFStringRef kParamName_FullBacano_Freq     = CFSTR ("Frecuencia");    // 1
static const float kDefaultValue_FullBacano_Freq   = 300.0;                    // 2
static const float kMinimumValue_FullBacano_Freq   = 20;                    // 3
static const float kMaximumValue_FullBacano_Freq   = 500.0;                   // 4

static CFStringRef kParamName_FullBacano_Bacaneria     = CFSTR ("Bacaneria");        // 5
static const float kDefaultValue_FullBacano_Bacaneria  = 100.0;
static const float kMinimumValue_FullBacano_Bacaneria  = 0.0;
static const float kMaximumValue_FullBacano_Bacaneria  = 100.0;

static CFStringRef kParamName_FullBacano_Ganancia     = CFSTR ("Ganancia");        // 5
static const float kDefaultValue_FullBacano_Ganancia  = 100.0;
static const float kMinimumValue_FullBacano_Ganancia  = 0.0;
static const float kMaximumValue_FullBacano_Ganancia  = 100.0;


static CFStringRef kParamName_FullBacano_LaMondaEnElVolco  = CFSTR ("La Monda en el Volco");     // 6

static const int kQuesoSpeaker_FullBacano_LaMondaEnElVolco     = 1;
static const int kZipoSpeaker_FullBacano_LaMondaEnElVolco     = 2;
static const int kTroqueSpeaker_FullBacano_LaMondaEnElVolco   = 3;
static const int kErdaSpeaker_FullBacano_LaMondaEnElVolco   = 5;
static const int kDefaultValue_FullBacano_LaMondaEnElVolco = kQuesoSpeaker_FullBacano_LaMondaEnElVolco;

// menu item names for the LaMondaEnElVolco parameter
static CFStringRef kMenuItem_FullBacano_Queso     = CFSTR ("Quesito de la cojta");
static CFStringRef kMenuItem_FullBacano_Zipo       = CFSTR ("Zipote Parlante");         // 7
static CFStringRef kMenuItem_FullBacano_Troque     = CFSTR ("Doble Troque");     
static CFStringRef kMenuItem_FullBacano_Eerda     = CFSTR ("Eeeeerda");   // 8

// parameter identifiers
enum {                                                                    // 9
    kParameter_Frequency  = 0,
    kParameter_Bacaneria  = 1,
    kParameter_Ganancia=2,
    kParameter_LaMondaEnElVolco = 3,
    kNumberOfParameters   = 4
};

#pragma mark ____FullBacano Factory Preset Constants
static const float kParameter_Preset_Frequency_Mera = 300;    // 1
static const float kParameter_Preset_Frequency_NoTanBacano = 60.0;   // 2
static const float kParameter_Preset_Bacaneria_Mera     = 100;   // 3
static const float kParameter_Preset_Bacaneria_NoTanBacano     = 20;   // 4
static const float kParameter_Preset_Ganancia_Mera     = 100;   // 3
static const float kParameter_Preset_Ganancia_NoTanBacano    = 100;   // 3

static const float kParameter_Preset_LaMondaEnElVolco_Mera            // 5
= kErdaSpeaker_FullBacano_LaMondaEnElVolco;
static const float kParameter_Preset_LaMondaEnElVolco_NoTanBacano            // 5
= kZipoSpeaker_FullBacano_LaMondaEnElVolco;



enum {
    kPreset_Mera    = 0,                                      // 7
    kPreset_NoTanBacano= 1,                                      // 8
    kNumberPresets  = 2                                       // 9
};

static AUPreset kPresets [kNumberPresets] = {                 // 10
    {kPreset_Mera, CFSTR ("Mera Mondá")},
    {kPreset_NoTanBacano, CFSTR ("No ejtá tan bacano")}
};

static const int kPreset_Default = kPreset_Mera;              // 11



#pragma mark ____FullBacano
class FullBacano : public AUEffectBase
{
public:
	FullBacano(AudioUnit component);
    
  
    
    
#if AU_DEBUG_DISPATCHER
	virtual ~FullBacano () { delete mDebugDispatcher; }
#endif

	virtual ComponentResult GetPresets (       // 1
                                        CFArrayRef        *outData
                                        ) const;
    
    virtual OSStatus NewFactoryPresetSet (     // 2
                                          const AUPreset    &inNewFactoryPreset
                                          );
    
    
	virtual AUKernelBase *		NewKernel() { return new FullBacanoKernel(this); }
	
	virtual	OSStatus			GetParameterValueStrings(AudioUnitScope			inScope,
														 AudioUnitParameterID		inParameterID,
														 CFArrayRef *			outStrings);
    
	virtual	OSStatus			GetParameterInfo(AudioUnitScope			inScope,
												 AudioUnitParameterID	inParameterID,
												 AudioUnitParameterInfo	&outParameterInfo);
    
	virtual OSStatus			GetPropertyInfo(AudioUnitPropertyID		inID,
												AudioUnitScope			inScope,
												AudioUnitElement		inElement,
												UInt32 &			outDataSize,
												Boolean	&			outWritable );
	
	virtual OSStatus			GetProperty(AudioUnitPropertyID inID,
											AudioUnitScope 		inScope,
											AudioUnitElement 		inElement,
											void *			outData);
	
 	virtual	bool				SupportsTail () { return false; }
	
	/*! @method Version */
	virtual OSStatus		Version() { return kFullBacanoVersion; }
	
    
	
protected:
		class FullBacanoKernel : public AUKernelBase		// most real work happens here
	{
public:
		FullBacanoKernel(AUEffectBase *inAudioUnit )
		: AUKernelBase(inAudioUnit)
	{
	}
		
		// *Required* overides for the process method for this effect
		// processes one channel of interleaved samples
        virtual void 		Process(	const Float32 	*inSourceP,
										Float32		 	*inDestP,
										UInt32 			inFramesToProcess,
										UInt32			inNumChannels,
										bool			&ioSilence);
		
        virtual void		Reset();
		
		private: //state variables...
	
        //ofstream *logFile;
        
    };
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


#endif